#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string.h>

#include "fichiers.h"
#include "simple.h"
#include "perspective.h"
#include "Input.h"
#include "tracer.h"

#define PULSE_VITESSE 1.5
#define PULSE_LIMITE 1e-2
#define PAS 1e-2
#define TOLERANCE 1e-4
#define SEUIL_MOUVEMENT 10
#define SEUIL_DETECTION 50
#define SEUIL_ZOOM 20

using namespace std;

#include <cmath>
#include <SDL/SDL_main.h>
#include <SDL/SDL_mixer.h>

/* linker options: -lmingw32 -lSDLmain -lSDL -mwindows */

void Auto(double* delta_angles, double* r)
{
    delta_angles[0] = PAS*1e-1;
    delta_angles[1] = PAS*1e-1;
    delta_angles[3] = PAS*1e-1;
}

void Pulse(int* pulse, double* r)
{
    if(*pulse == 1)
    {
        if(*r > PULSE_LIMITE)
        {
            *r /= PULSE_VITESSE;
        }
        else
        {
            *pulse = 2;
        }
    }
    else if(*pulse == 2)
    {
        if(*r < 1)
        {
            *r *= PULSE_VITESSE;
        }
        else
        {
            *pulse = 0;
        }
    }
}

void Controle(Input input1, double* delta_angles, double* r, double* delta_r, int* retour, int* pulse)
{
    delta_angles[0] = PAS*(input1.GetA()-input1.GetQ());
    delta_angles[1] = PAS*(input1.GetZ()-input1.GetS());
    delta_angles[2] = PAS*(input1.GetE()-input1.GetD());
    delta_angles[3] = PAS*(input1.GetR()-input1.GetF());
    delta_angles[4] = PAS*(input1.GetT()-input1.GetG());
    delta_angles[5] = PAS*(input1.GetY()-input1.GetH());
    if(input1.Gethaut())
    {
        *r += PAS;
        *delta_r = PAS;
    }
    if(input1.Getbas())
    {
        *r -= PAS;
        *delta_r = -PAS;
    }
    if(input1.Getgauche() && *retour == 0)
    {
        *retour = 1;
        input1.Setgauche(0);
    }
    if(input1.Getdroite() && *pulse == 0)
    {
        *pulse = 1;
        input1.Setdroite(0);
    }
}

void Inertie(double* delta_angles)
{
    delta_angles[0] = delta_angles[0]/2;
    delta_angles[1] = delta_angles[1]/2;
    delta_angles[2] = delta_angles[2]/2;
    delta_angles[3] = delta_angles[3]/2;
    delta_angles[4] = delta_angles[4]/2;
    delta_angles[5] = delta_angles[5]/2;
}

void Reset(int* retour, double* angles, double* delta_angles, double* r, double* delta_r)
{
    int i;
    int check = 0;
    int cnk = 6;
    for(i = 0; i < cnk; i++)
    {
        if(angles[i] <= -TOLERANCE || angles[i] >= TOLERANCE)
            delta_angles[i] = -angles[i]/2;
        else
            check++;
    }
    if(*r < 1 || *r > 1)
    {
        *delta_r = (1-*r)/2;
        *r -= (*r-1)/2;
    }
    else
        check++;
    if(check == cnk+1)
        *retour = 0;
}

int main(int argc, char** argv)
{
    Donnees* entree;
    Donnees* inter;
    Donnees* sortie;
    double* base;
    double* oeil;
    entree = new Donnees();
    string nom(argv[1]);
    string methode(argv[2]);
    string dimension(argv[3]);
    int k(atoi(argv[3]));
    string nomEntree,nomSortie;
    int i,j;
    int d;
    Input input1;
    int n,p1,p2;
    ifstream flux;
    int x1(0),y1(0),z1(0),x2(0),y2(0),z2(0);

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME/16);
    Mix_Music *fond,*detection; //Création du pointeur de type Mix_Music
    fond = Mix_LoadMUS("/home/olivier/Background.wav"); //Chargement de la musique
    detection = Mix_LoadMUS("/home/olivier/Chrystal.wav"); //Chargement de la musique
    Mix_Chunk *son0; //Créer un pointeur pour stocker un .WAV
    Mix_Chunk *son1;
    Mix_Chunk *son2;
    Mix_Chunk *son3;
    son0 = Mix_LoadWAV("/home/olivier/detection.wav"); //Charger un wav dans un pointeur
    son1 = Mix_LoadWAV("/home/olivier/gauche.wav");
    son2 = Mix_LoadWAV("/home/olivier/haut.wav");
    son3 = Mix_LoadWAV("/home/olivier/loin.wav");
    Mix_VolumeChunk(son0, MIX_MAX_VOLUME); //Mettre un volume pour ce wav
    Mix_VolumeChunk(son1, 0);
    Mix_VolumeChunk(son2, 0);
    Mix_VolumeChunk(son3, 0);
    cout << Mix_GetError();

    nomSortie.append(nom);
    nomSortie.append("-");
    nomSortie.append(methode);
    nomSortie.append("-");
    nomSortie.append(dimension);
    nomSortie.append("D");

    nomEntree.append(nom);

    nomEntree.append(".in");
    nomSortie.append(".out");

    ouvrir(nomEntree, entree);
    d = entree->d;
    base = new double[sizeof(double)*k*d];
    oeil = new double[sizeof(double)*d];

    double* angles;
    double* delta_angles;
    double r = 1;
    double delta_r = 0;
    int pulse = 0;
    int retour = 0;
    int automatique = 0;
    int inertie = 0;
    int N = 0;
    int N2 = 0;
    int detecte = 0;
    int sens = 0;
    int cnk = (int)gsl_sf_choose(d,2);
    gsl_matrix* Mangles;
    gsl_matrix* Mdelta_angles;
    gsl_matrix* Mcopie;

    Mangles = gsl_matrix_calloc(d,d);
    gsl_matrix_set_identity(Mangles);
    angles = Matrix2Angles(Mangles,d);

    Mdelta_angles = gsl_matrix_calloc(d,d);
    gsl_matrix_set_identity(Mdelta_angles);
    delta_angles = Matrix2Angles(Mdelta_angles,d);

    Mcopie = gsl_matrix_calloc(d,d);

    inter = homothetie(rotation(entree,angles),r);

    if(SDL_Init(SDL_INIT_VIDEO) < 0) //initialize SDL video
    {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    atexit(SDL_Quit); //make sure SDL cleans up before exit

    SDL_Surface* screen = SDL_SetVideoMode(TAILLE_ECRAN, TAILLE_ECRAN, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);//|SDL_FULLSCREEN); //create a new window
    SDL_ShowCursor(SDL_DISABLE);
    if(!screen)
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        return 1;
    }

    for(j = 0; j < d; j++)
        for(i = 0; i < k; i++)
            base[i*d + j] = 1*(i == j);
    for(j = 0; j < d; j++)
        oeil[j] = 2.0*(j == 2);

    Mix_PlayMusic(fond, -1); //Jouer infiniment la musique

    bool done = false;
    while(!done) //program main loop
    {
        flux.open("/home/olivier/fichier.txt");
        if(flux)
        {
            x1 = x2;
            y1 = y2;
            z1 = z2;
            flux >> x2;
            flux >> y2;
            flux >> z2;
        }
        flux.close();

        //N2++;
        //x2=(N2/16)%96;
        //y2=(N2/16)%64;
        //z2 = SEUIL_DETECTION+1;

        if(z2 > SEUIL_DETECTION  && !detecte)
        {
            detecte = 1;
            sens = !sens;
            //Mix_PlayChannel(1, son0, 0);
            Mix_PlayChannel(2, son1, -1);
            Mix_PlayChannel(3, son2, -1);
            Mix_PlayChannel(4, son3, -1);
            /*Mix_FadeInChannel(2, son1, 1000,-1);
            Mix_FadeInChannel(3, son2, 1000,-1);
            Mix_FadeInChannel(4, son3, 1000,-1);*/
            //Mix_FadeOutMusic(1000);
            //Mix_FadeInMusic(detection,-1,60);
            Mix_VolumeMusic(0);
            //Mix_PlayMusic(detection, -1); //Jouer infiniment la musique
        }

        if(z2 < SEUIL_DETECTION  && detecte)
        {
            detecte = 0;
            //Mix_FadeOutChannel(1,60);
            Mix_FadeOutChannel(2,60);
            Mix_FadeOutChannel(3,60);
            Mix_FadeOutChannel(4,60);
            //Mix_FadeOutMusic(60);
            //Mix_FadeInMusic(fond,-1,4000);
            Mix_VolumeMusic(MIX_MAX_VOLUME/16);
            //Mix_PlayMusic(fond, -1); //Jouer infiniment la musique
        }

        if(detecte)
        {

            Matrix2Angles(Mangles, d, angles);

            delta_angles[2] = PAS*(2*M_PI*(x2-48)/96-angles[2]);
            delta_angles[3] = PAS*(2*M_PI*(x2-48)/96-angles[3]);
            delta_angles[4] = PAS*(2*M_PI*(16-y2)/32-angles[4]);
            delta_angles[5] = PAS*(2*M_PI*(16-y2)/32-angles[5]);
            //delta_angles[5] = PAS*(2*M_PI*(50-z2)/100-angles[5]);
            r = 1+PAS*(z2-500)/100;
            //input1.Setbas((z1-z2 > SEUIL_ZOOM));
            //input1.Sethaut((SEUIL_ZOOM < z2-z1));

            //if(delta_angles[1] || delta_angles[2])

            Mix_VolumeChunk(son1, abs(MIX_MAX_VOLUME*(x2-48)/48));
            Mix_VolumeChunk(son2, abs(MIX_MAX_VOLUME*(16-y2)/16));
            Mix_VolumeChunk(son3, MIX_MAX_VOLUME*z2/6000);

            //if(delta_angles[3] || delta_angles[4])


            //Angles2Matrix(angles, d, Mangles);

        }
        else
        {
            input1.Actualiser();
        }
        SDL_Delay(1);

        if(input1.GetBouton())
        {
            inertie = 0;
            Controle(input1,delta_angles,&r,&delta_r,&retour,&pulse);
        }
        else if(!inertie)
        {
            inertie = 1;
            Inertie(delta_angles);
        }

        if(N > 60)
            automatique = 1;

        if(automatique)
            Auto(delta_angles,&r);

        if(pulse)
            Pulse(&pulse,&r);

        if(retour && !pulse)
        {
            Matrix2Angles(Mangles,d,angles);
            Reset(&retour,angles,delta_angles,&r,&delta_r);
        }

        if(input1.GetBouton())
        {
            N = 0;
            automatique = 0;
        }

        if(input1.GetBouton() || pulse || retour || automatique || inertie || detecte)
        {
            Angles2Matrix(delta_angles, d, Mdelta_angles);

            gsl_matrix_memcpy(Mcopie,Mangles);
            gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, Mdelta_angles, Mcopie, 0.0, Mangles); //Mangles = Mangles*Mdelta_angles
            delta_r = 0;
            inter = homothetie(rotation(entree,Mangles),r);
        }
        else
            N++;

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                break;
            }
        }

        if(strcmp(methode.c_str(), "PS") == 0)
            sortie = simple(inter,k,base);
        else if(strcmp(methode.c_str(), "PP") == 0)
            sortie = perspective(inter,k,base,oeil,1);
        else
            return -1;

        //DRAWING STARTS HERE
        //clear screen
        SDL_SetAlpha(screen, SDL_SRCALPHA, 1);
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_SetAlpha(screen, SDL_SRCALPHA, 100);

        //tracerLigne(screen, screen->w*.5, screen->h*.5, screen->w*.5+x2-x1, screen->h*.5+y2-y1, 255, 0, 0, 1);
        //tracerLigne(screen, screen->w*.5, screen->h*.5, screen->w*.5+screen->w*(x2-48)/96, screen->h*.5+screen->h*(16-y2)/32, 255, 0, 0, 1);

        for(i = 0; i < sortie->a; i++)
        {
            n = sortie->H[i][0];
            if(n == 2)
            {
                p1 = sortie->H[i][1];
                p2 = sortie->H[i][2];
                tracerLigne(screen, screen->w*.5*sortie->T[p1*sortie->d]+screen->w/2,\
                            /*screen->h*.5*sortie->T[p1*sortie->d+1]+screen->h/2,\*/
                            screen->h/2-screen->h*.5*sortie->T[p1*sortie->d+1],\
                            screen->w*.5*sortie->T[p2*sortie->d]+screen->w/2,\
                            /*screen->h*.5*sortie->T[p2*sortie->d+1]+screen->h/2,\*/
                            screen->h/2-screen->h*.5*sortie->T[p2*sortie->d+1],\
                            0, 255, 255, 1);
            }
        }
        //DRAWING ENDS HERE
        SDL_Flip(screen); //finally, update the screen
    } //end main loop

    gsl_matrix_free(Mangles);
    gsl_matrix_free(Mdelta_angles);
    gsl_matrix_free(Mcopie);
    delete angles;
    delete delta_angles;
    delete entree;
    delete inter;
    delete sortie;

    Mix_FreeMusic(fond); //Libération de la musique
    Mix_FreeMusic(detection); //Libération de la musique
    Mix_FreeChunk(son0);//Libération du son 0
    Mix_FreeChunk(son1);
    Mix_FreeChunk(son2);
    Mix_FreeChunk(son3);
    Mix_CloseAudio(); //Fermeture de l'API

    printf("Exited cleanly\n");
    return 0;
}
