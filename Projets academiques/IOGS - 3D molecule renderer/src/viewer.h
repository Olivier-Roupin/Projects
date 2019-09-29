#ifndef VIEWER_H
#define VIEWER_H

#include "opengl.h"
#include "shader.h"
#include "camera.h"
#include "sphere.h"
#include "atom.h"

#include <iostream>

#define M_PI5 M_PI/5
#define M_3PI10 3*M_PI/10

static const int N = 20;

//Ascorbic Acid
static int atoms[N] = {A_C, A_C, A_C, A_C, A_C, A_C, //6
                       A_O, A_O, A_O, A_O, A_O, A_O, //6
                       A_H, A_H, A_H, A_H, A_H, A_H, A_H, A_H }; //8

static int edges[N] = {1, 2, 3, 4, 5, 6, //6
                       2, 0, 1, 3, 4, 5, //6
                       0, 0, 7, 1, 8, 2, 9, 10 }; //8


static float positions[3*N] = {0,0,0,
                               1,0,0,
                               2,0,0,
                               2+cos(M_3PI10),-sin(M_3PI10),0,
                               2+1/(2*sin(M_PI5))+cos(M_PI5),-sin(M_PI5),0,
                               2+1/(2*sin(M_PI5))+cos(M_PI5),sin(M_PI5),0,

                               2+cos(M_3PI10),sin(M_3PI10),0,
                               0,-1,0,
                               1,1,0,
                               2+cos(M_3PI10)-sqrt(0.5),-sin(M_3PI10)-sqrt(0.5),0,
                               2+1/(2*sin(M_PI5))+cos(M_PI5)+sqrt(0.5),-sin(M_PI5)-sqrt(0.5),0,
                               2+1/(2*sin(M_PI5))+cos(M_PI5)+sqrt(0.5),sin(M_PI5)+sqrt(0.5),0,

                               0,sqrt(0.5),-sqrt(0.5),
                               0,sqrt(0.5),sqrt(0.5),
                               -1,-1,0,
                               1,-sqrt(0.5),sqrt(0.5),
                               1,1,-1,
                               2,0,1,
                               2+cos(M_3PI10),-sin(M_3PI10)-sqrt(2),0,
                               2+1/(2*sin(M_PI5))+cos(M_PI5)+sqrt(0.5),-sin(M_PI5)-sqrt(2),sqrt(0.5)};

class Viewer{
public:
    //! Constructor
    Viewer();
    virtual ~Viewer();

    // gl stuff
    void init(int w, int h);
    void display();
    void updateScene();
    void reshape(int w, int h);
    void loadProgram();

    // events
    void mousePressed(GLFWwindow* window, int button, int action);
    void mouseMoved(int x, int y);
    void mouseScroll(double x, double y);
    void keyPressed(int key, int action, int mods);
    void charPressed(int key);

private:
    int _winWidth, _winHeight;

    Camera _cam;
    Shader _prg;
    Shader _prg2;
    Shader _prg3;
    std::vector<std::string> _prgNames;
    int _currentPrg;
    Sphere2 _sphere;
    std::vector<Atom> _atoms;
    float _length;

    int _textureHandle;

    // Mouse parameters
    Eigen::Vector2f _lastMousePos;
    int _button = -1;
};

#endif
