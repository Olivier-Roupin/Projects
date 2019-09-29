/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2011 individual OpenKinect contributors. See the CONTRIB file
 * for details.
 *
 * This code is licensed to you under the terms of the Apache License, version
 * 2.0, or, at your option, the terms of the GNU General Public License,
 * version 2.0. See the APACHE20 and GPL2 files for the text of the licenses,
 * or the following URLs:
 * http://www.apache.org/licenses/LICENSE-2.0
 * http://www.gnu.org/licenses/gpl-2.0.txt
 *
 * If you redistribute this file in source form, modified or unmodified, you
 * may:
 *   1) Leave this header intact and distribute it under the same terms,
 *      accompanying it with the APACHE20 and GPL20 files, or
 *   2) Delete the Apache 2.0 clause and accompany it with the GPL2 file, or
 *   3) Delete the GPL v2 clause and accompany it with the APACHE20 file
 * In all cases you must keep the copyright notice intact and include a copy
 * of the CONTRIB file.
 *
 * Binary distributions must follow the binary distribution requirements of
 * either License.
 */

/** @file Protonect.cpp Main application file. */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <signal.h>

/// [headers]
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>
/// [headers]
#ifdef EXAMPLES_WITH_OPENGL_SUPPORT
#include "viewer.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define TAILLE 6144 //32*32*6
#define LONGUEUR 96 //32*3
#define HAUTEUR 64 //32*2

#define DECALAGE_H_H depth->height/32
#define DECALAGE_H_B depth->height/3
#define DECALAGE_V_G depth->width/10
#define DECALAGE_V_D depth->width/12

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

bool protonect_shutdown = false; ///< Whether the running application should shut down.

void sigint_handler(int s)
{
    protonect_shutdown = true;
}

bool protonect_paused = false;
libfreenect2::Freenect2Device *devtopause;

//Doing non-trivial things in signal handler is bad. If you want to pause,
//do it in another thread.
//Though libusb operations are generally thread safe, I cannot guarantee
//everything above is thread safe when calling start()/stop() while
//waitForNewFrame().
void sigusr1_handler(int s)
{
    if(devtopause == 0)
        return;
/// [pause]
    if(protonect_paused)
        devtopause->start();
    else
        devtopause->stop();
    protonect_paused = !protonect_paused;
/// [pause]
}

//The following demonstrates how to create a custom logger
/// [logger]
#include <fstream>
#include <cstdlib>
class MyFileLogger: public libfreenect2::Logger
{
private:
    std::ofstream logfile_;
public:
    MyFileLogger(const char *filename)
    {
        if(filename)
            logfile_.open(filename);
        level_ = Debug;
    }
    bool good()
    {
        return logfile_.is_open() && logfile_.good();
    }
    virtual void log(Level level, const std::string &message)
    {
        logfile_ << "[" << libfreenect2::Logger::level2str(level) << "] " << message << std::endl;
    }
};
/// [logger]

/// [main]
/**
 * Main application entry point.
 *
 * Accepted argumements:
 * - cpu Perform depth processing with the CPU.
 * - gl  Perform depth processing with OpenGL.
 * - cl  Perform depth processing with OpenCL.
 * - <number> Serial number of the device to open.
 * - -noviewer Disable viewer window.
 */
int main(int argc, char *argv[])
/// [main]
{
    std::string program_path(argv[0]);
    std::cerr << "Version: " << LIBFREENECT2_VERSION << std::endl;
    std::cerr << "Environment variables: LOGFILE=<protonect.log>" << std::endl;
    std::cerr << "Usage: " << program_path << " [-gpu=<id>] [gl | cl | clkde | cuda | cudakde | cpu] [<device serial>]" << std::endl;
    std::cerr << "        [-noviewer] [-norgb | -nodepth] [-help] [-version]" << std::endl;
    std::cerr << "        [-frames <number of frames to process>]" << std::endl;
    std::cerr << "To pause and unpause: pkill -USR1 Protonect" << std::endl;
    size_t executable_name_idx = program_path.rfind("Protonect");

    std::string binpath = "/";

    if(executable_name_idx != std::string::npos)
    {
        binpath = program_path.substr(0, executable_name_idx);
    }

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    // avoid flooding the very slow Windows console with debug messages
    libfreenect2::setGlobalLogger(libfreenect2::createConsoleLogger(libfreenect2::Logger::Info));
#else
    // create a console logger with debug level (default is console logger with info level)
/// [logging]
    libfreenect2::setGlobalLogger(libfreenect2::createConsoleLogger(libfreenect2::Logger::Debug));
/// [logging]
#endif
/// [file logging]
    MyFileLogger *filelogger = new MyFileLogger(getenv("LOGFILE"));
    if(filelogger->good())
        libfreenect2::setGlobalLogger(filelogger);
    else
        delete filelogger;
/// [file logging]

/// [context]
    libfreenect2::Freenect2 freenect2;
    libfreenect2::Freenect2Device *dev = 0;
    libfreenect2::PacketPipeline *pipeline = 0;
/// [context]

    std::string serial = "";

    bool viewer_enabled = true;
    bool enable_rgb = true;
    bool enable_depth = true;
    bool ethernet_enabled = true;
    int deviceId = -1;
    size_t framemax = -1;

    for(int argI = 1; argI < argc; ++argI)
    {
        const std::string arg(argv[argI]);

        if(arg == "-help" || arg == "--help" || arg == "-h" || arg == "-v" || arg == "--version" || arg == "-version")
        {
            // Just let the initial lines display at the beginning of main
            return 0;
        }
        else if(arg.find("-gpu=") == 0)
        {
            if(pipeline)
            {
                std::cerr << "-gpu must be specified before pipeline argument" << std::endl;
                return -1;
            }
            deviceId = atoi(argv[argI] + 5);
        }
        else if(arg == "cpu")
        {
            if(!pipeline)
/// [pipeline]
                pipeline = new libfreenect2::CpuPacketPipeline();
/// [pipeline]
        }
        else if(arg == "gl")
        {
#ifdef LIBFREENECT2_WITH_OPENGL_SUPPORT
            if(!pipeline)
                pipeline = new libfreenect2::OpenGLPacketPipeline();
#else
            std::cout << "OpenGL pipeline is not supported!" << std::endl;
#endif
        }
        else if(arg == "cl")
        {
#ifdef LIBFREENECT2_WITH_OPENCL_SUPPORT
            if(!pipeline)
                pipeline = new libfreenect2::OpenCLPacketPipeline(deviceId);
#else
            std::cout << "OpenCL pipeline is not supported!" << std::endl;
#endif
        }
        else if(arg == "clkde")
        {
#ifdef LIBFREENECT2_WITH_OPENCL_SUPPORT
            if(!pipeline)
                pipeline = new libfreenect2::OpenCLKdePacketPipeline(deviceId);
#else
            std::cout << "OpenCL pipeline is not supported!" << std::endl;
#endif
        }
        else if(arg == "cuda")
        {
#ifdef LIBFREENECT2_WITH_CUDA_SUPPORT
            if(!pipeline)
                pipeline = new libfreenect2::CudaPacketPipeline(deviceId);
#else
            std::cout << "CUDA pipeline is not supported!" << std::endl;
#endif
        }
        else if(arg == "cudakde")
        {
#ifdef LIBFREENECT2_WITH_CUDA_SUPPORT
            if(!pipeline)
                pipeline = new libfreenect2::CudaKdePacketPipeline(deviceId);
#else
            std::cout << "CUDA pipeline is not supported!" << std::endl;
#endif
        }
        else if(arg == "-noethernet" || arg == "--noethernet")
        {
            ethernet_enabled = false;
        }
        else if(arg == "-noviewer" || arg == "--noviewer")
        {
            viewer_enabled = false;
        }
        else if(arg == "-norgb" || arg == "--norgb")
        {
            enable_rgb = false;
        }
        else if(arg == "-nodepth" || arg == "--nodepth")
        {
            enable_depth = false;
        }
        else if(arg == "-frames")
        {
            ++argI;
            framemax = strtol(argv[argI], NULL, 0);
            if (framemax == 0)
            {
                std::cerr << "invalid frame count '" << argv[argI] << "'" << std::endl;
                return -1;
            }
        }
        else if(arg.find_first_not_of("0123456789") == std::string::npos) //check if parameter could be a serial number
        {
            //serial = arg;
        }
        else
        {
            //std::cout << "Unknown argument: " << arg << std::endl;
        }
    }

    if(!enable_rgb && !enable_depth)
    {
        std::cerr << "Disabling both streams is not allowed!" << std::endl;
        return -1;
    }

/// [discovery]
    if(freenect2.enumerateDevices() == 0)
    {
        std::cout << "no device connected!" << std::endl;
        return -1;
    }

    if(serial == "")
    {
        serial = freenect2.getDefaultDeviceSerialNumber();
    }
/// [discovery]

    if(pipeline)
    {
/// [open]
        dev = freenect2.openDevice(serial, pipeline);
/// [open]
    }
    else
    {
        dev = freenect2.openDevice(serial);
    }

    if(dev == 0)
    {
        std::cout << "failure opening device! " << serial << " " << pipeline << std::endl;
        return -1;
    }

    devtopause = dev;

    signal(SIGINT,sigint_handler);
#ifdef SIGUSR1
    signal(SIGUSR1, sigusr1_handler);
#endif
    protonect_shutdown = false;

/// [listeners]
    int types = 0;
    if(enable_rgb)
        types |= libfreenect2::Frame::Color;
    if(enable_depth)
        types |= libfreenect2::Frame::Ir | libfreenect2::Frame::Depth;
    libfreenect2::SyncMultiFrameListener listener(types);
    libfreenect2::FrameMap frames;

    dev->setColorFrameListener(&listener);
    dev->setIrAndDepthFrameListener(&listener);
/// [listeners]

/// [start]
    if(enable_rgb && enable_depth)
    {
        if(!dev->start())
            return -1;
    }
    else
    {
        if(!dev->startStreams(enable_rgb, enable_depth))
            return -1;
    }

    std::cout << "device serial: " << dev->getSerialNumber() << std::endl;
    std::cout << "device firmware: " << dev->getFirmwareVersion() << std::endl;
/// [start]

/// [registration setup]
    libfreenect2::Registration* registration = new libfreenect2::Registration(dev->getIrCameraParams(), dev->getColorCameraParams());
    libfreenect2::Frame undistorted(512, 424, 4), registered(512, 424, 4);
/// [registration setup]

    size_t framecount = 0;

    int sockfd, portno, n;
    int i,j,p,q;
    int ratio_H,ratio_L;
    int pixel;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[TAILLE];
    char ack[1];

    if(ethernet_enabled)
    {
        portno = atoi(argv[2]);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0)
            error("ERROR opening socket");

        server = gethostbyname(argv[1]);
        if(server == NULL)
        {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }

        bzero((char*) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char*) server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(portno);
        if(connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0)
            error("ERROR connecting");
    }

#ifdef EXAMPLES_WITH_OPENGL_SUPPORT
    Viewer viewer;
    if(viewer_enabled)
        viewer.initialize();
#else
    viewer_enabled = false;
#endif

    ofstream flux;
/// [loop start]
    while(!protonect_shutdown && (framemax == (size_t)-1 || framecount < framemax))
    {
        bzero(buffer,TAILLE);
        if(!listener.waitForNewFrame(frames, 10*1000)) // 10 seconds
        {
            std::cout << "timeout!" << std::endl;
            return -1;
        }
        libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];
        //libfreenect2::Frame *ir = frames[libfreenect2::Frame::Ir];
/// [loop start]

        framecount++;
        if(!viewer_enabled)
        {
            if(framecount % 100 == 0)
                std::cout << "The viewer is turned off. Received " << depth << "frames. Ctrl-C to stop." << std::endl;
            listener.release(frames);
            //continue;
        }

        for(i = 0; i < LONGUEUR; i++)
        {
            for(j = 0; j < HAUTEUR; j++)
            {
                pixel = 0;
                ratio_L = (depth->width-DECALAGE_V_D-DECALAGE_V_G)/LONGUEUR;
                ratio_H = (depth->height-DECALAGE_H_B-DECALAGE_H_H)/HAUTEUR;
                for(p = 0; p < ratio_L; p++)
                {
                    for(q = 0; q < ratio_H; q++)
                    {
                        pixel += (depth->data[4*(DECALAGE_V_G+p+i*ratio_L + (DECALAGE_H_H+q+j*ratio_H)*depth->width)])/(ratio_H*ratio_L);
                    }
                }
                buffer[LONGUEUR-i+j*LONGUEUR] = 127*(pixel != 0)+not(pixel);
            }
        }
#ifdef EXAMPLES_WITH_OPENGL_SUPPORT
        if(viewer_enabled)
        {
            if(enable_depth)
            {
                viewer.addFrame("depth", depth);
            }
            protonect_shutdown = protonect_shutdown || viewer.render();
        }
#endif
        if(ethernet_enabled)
        {

            n = write(sockfd,"A",1);
            if(n < 0)
                error("ERROR writing to socket");
            //do
            //{
            //bzero(ack,1);
            //n = read(sockfd,ack,1);
            //if(n < 0)
            //    error("ERROR reading from socket");
            //}while(ack[0] != 'A');
            n = write(sockfd,buffer,TAILLE);
            if(n < 0)
                error("ERROR writing to socket");
        }
        p = 0;
        q = 0;
        n = 0;
        for(i = 0; i < LONGUEUR; i++)
        {
            for(j = 0; j < HAUTEUR; j++)
            {
                if(buffer[LONGUEUR-i+j*LONGUEUR] == 1)
                {
                    n++;
                    p += i;
                    q += j;
                }
            }
        }
        flux.open("/home/projet/fichier.txt");
        if(flux)
        {
            if(n)
            {
                system("clear");
                std::cout << "n: " << n << "\tx: " << p/n << "\ty: " << q/n << endl;
                flux << p/n << " ";
                flux << q/n << " ";
                flux << n;

            }
            else
            {
                flux << 0 << " ";
                flux << 0 << " ";
                flux << 0;
            }
        }
        else
            printf("problème controles\n");
        flux.close();

        if(ethernet_enabled)
        {
            bzero(ack,1);
            n = read(sockfd,ack,1);
            if(n<0)
                error("ERROR reading from socket");
        }

/// [loop end]
        listener.release(frames);
        /** libfreenect2::this_thread::sleep_for(libfreenect2::chrono::milliseconds(100)); */
    }
/// [loop end]
/// [stop]
    if(ethernet_enabled)
        close(sockfd);
    dev->stop();
    dev->close();
/// [stop]

    delete registration;
    return 0;
}
