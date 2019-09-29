#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string>

#include "fichiers.h"
#include "perspective.h"
#include "Input.h"
#include "Dessin.h"

#define PULSE_VITESSE 1.5
#define PULSE_LIMITE 1e-2
#define PAS 2e-2
#define TOLERANCE 1e-4
#define SEUIL_MOUVEMENT 10
#define SEUIL_DETECTION 50
#define SEUIL_ZOOM 20

using namespace std;

#include <cmath>

//#include <SDL/SDL_mixer.h>

/* linker options: -lmingw32 -lSDLmain -lSDL -mwindows */

void Controle(Input& input1, double* delta_angles, gsl_vector* deplacement)
{
    delta_angles[0] = PAS*(input1.GetA()-input1.GetQ());
    delta_angles[1] = PAS*(input1.GetZ()-input1.GetS());
    delta_angles[2] = PAS*(input1.GetE()-input1.GetD());
    delta_angles[3] = PAS*(input1.GetR()-input1.GetF());
    delta_angles[4] = PAS*(input1.GetT()-input1.GetG());
    delta_angles[5] = PAS*(input1.GetY()-input1.GetH());

    gsl_vector_set_zero(deplacement);
    if(input1.GetEnter())
    {
        gsl_vector_set_basis(deplacement,2);
        gsl_vector_scale(deplacement,-0.1);
    }
    if(input1.GetBack())
    {
        gsl_vector_set_basis(deplacement,2);
        gsl_vector_scale(deplacement,0.1);
    }
    if(input1.Gethaut())
    {
        gsl_vector_set_basis(deplacement,1);
        gsl_vector_scale(deplacement,0.1);
    }
    if(input1.Getbas())
    {
        gsl_vector_set_basis(deplacement,1);
        gsl_vector_scale(deplacement,-0.1);
    }
    if(input1.Getgauche())
    {
        gsl_vector_set_basis(deplacement,0);
        gsl_vector_scale(deplacement,-0.1);
    }
    if(input1.Getdroite())
    {
        gsl_vector_set_basis(deplacement,0);
        gsl_vector_scale(deplacement,0.1);
    }
    if(input1.Getpgup())
    {
        gsl_vector_set_basis(deplacement,3);
        gsl_vector_scale(deplacement,-0.1);
    }
    if(input1.Getpgdown())
    {
        gsl_vector_set_basis(deplacement,3);
        gsl_vector_scale(deplacement,0.1);
    }
}

void ControleDiscret0(Input& input1, double* delta_angles, gsl_vector* deplacement)
{
    delta_angles[0] = M_PI_2*(input1.GetA()-input1.GetQ())*0.01;
    delta_angles[1] = M_PI_2*(input1.GetZ()-input1.GetS())*0.01;
    delta_angles[2] = M_PI_2*(input1.GetE()-input1.GetD())*0.01;
    delta_angles[3] = M_PI_2*(input1.GetR()-input1.GetF())*0.01;
    delta_angles[4] = M_PI_2*(input1.GetT()-input1.GetG())*0.01;
    delta_angles[5] = M_PI_2*(input1.GetY()-input1.GetH())*0.01;

    gsl_vector_set_zero(deplacement);
    if(input1.GetEnter())
    {
        gsl_vector_set_basis(deplacement,2);
        gsl_vector_scale(deplacement,-0.01);
    }
    if(input1.GetBack())
    {
        gsl_vector_set_basis(deplacement,2);
        gsl_vector_scale(deplacement,0.01);
    }
    if(input1.Gethaut())
    {
        gsl_vector_set_basis(deplacement,1);
        gsl_vector_scale(deplacement,0.01);
    }
    if(input1.Getbas())
    {
        gsl_vector_set_basis(deplacement,1);
        gsl_vector_scale(deplacement,-0.01);
    }
    if(input1.Getgauche())
    {
        gsl_vector_set_basis(deplacement,0);
        gsl_vector_scale(deplacement,-0.01);
    }
    if(input1.Getdroite())
    {
        gsl_vector_set_basis(deplacement,0);
        gsl_vector_scale(deplacement,0.01);
    }
    if(input1.Getpgup())
    {
        gsl_vector_set_basis(deplacement,3);
        gsl_vector_scale(deplacement,-0.01);
    }
    if(input1.Getpgdown())
    {
        gsl_vector_set_basis(deplacement,3);
        gsl_vector_scale(deplacement,0.01);
    }
}

void ControleDiscret(Input& input1, double* delta_angles, gsl_vector* deplacement)
{
    //delta_angles[0] = M_PI_2*(input1.GetA()-input1.GetQ())*0.01; //inutile
    delta_angles[1] = M_PI_2*(input1.Getgauche()-input1.Getdroite())*0.01;
    //delta_angles[2] = M_PI_2*(input1.GetE()-input1.GetD())*0.01;
    delta_angles[3] = M_PI_2*(input1.Gethaut()-input1.Getbas())*0.01;
    //delta_angles[4] = M_PI_2*(input1.GetT()-input1.GetG())*0.01;
    delta_angles[5] = M_PI_2*(input1.Getpgdown()-input1.Getpgup())*0.01;

    gsl_vector_set_zero(deplacement);
    if(input1.GetZ())
    {
        gsl_vector_set_basis(deplacement,2);
        gsl_vector_scale(deplacement,-0.01);
    }
    if(input1.GetS())
    {
        gsl_vector_set_basis(deplacement,2);
        gsl_vector_scale(deplacement,0.01);
    }
    /*if(input1.Gethaut())
    {
        gsl_vector_set_basis(deplacement,1);
        gsl_vector_scale(deplacement,0.01);
    }
    if(input1.Getbas())
    {
        gsl_vector_set_basis(deplacement,1);
        gsl_vector_scale(deplacement,-0.01);
    }*/
    if(input1.GetQ())
    {
        gsl_vector_set_basis(deplacement,0);
        gsl_vector_scale(deplacement,-0.01);
    }
    if(input1.GetD())
    {
        gsl_vector_set_basis(deplacement,0);
        gsl_vector_scale(deplacement,0.01);
    }
    /*if(input1.Getpgup())
    {
        gsl_vector_set_basis(deplacement,3);
        gsl_vector_scale(deplacement,-0.01);
    }
    if(input1.Getpgdown())
    {
        gsl_vector_set_basis(deplacement,3);
        gsl_vector_scale(deplacement,0.01);
    }*/
}

int main(int argc, char** argv)
{
    Donnees* bloc;
    Donnees* complet;
    Donnees* translate;
    Donnees* rotationne;
    Donnees* homothete;
    Donnees* sortie;
    gsl_matrix* base;
    gsl_vector* camera;
    gsl_vector* deplacement;
    gsl_vector* deplacementcopie;
    string nom(argv[1]);
    string methode(argv[2]);
    string dimension(argv[3]);
    int k(atoi(argv[3]));
    string mode(argv[4]);
    string nomBloc,nomSortie;
    int X,Y,Z,W;
    int i;
    int d,a,n,taille;
    int axe;
    Input input1;
    Labyrinthe* lab;
    int progression(99);
    double* angles;
    double* delta_angles;
    gsl_matrix* Mangles;
    gsl_matrix* Mdelta_angles;
    gsl_matrix* Mcopie;

    ifstream flux("/home/olivier/Documents/Labyrinthe/bin/Release/lab");
    if(flux)
    {
        flux >> X;
        flux >> Y;
        flux >> Z;
        flux >> W;
        lab = new Labyrinthe(X,Y,Z,W);
        flux >> X;
        flux >> Y;
        flux >> Z;
        flux >> W;
        for(i = 0; i < lab->GetTaille(); i++)
        {
            flux >> n;
            lab->SetTableau(i,n);
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        return -1;
    }
    flux.close();

    //AUDIO
    /*if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME/16);
    Mix_Music *fond,*detection; //Création du pointeur de type Mix_Music
    fond = Mix_LoadMUS("/home/olivier/Background.wav"); //Chargement de la musique
    detection = Mix_LoadMUS("/home/olivier/Chrystal.wav"); //Chargement de la musique
    Mix_Chunk *son0; //Créer un pointeur pour stocker un .WAV
    son0 = Mix_LoadWAV("/home/olivier/detection.wav"); //Charger un wav dans un pointeur
    Mix_VolumeChunk(son0, MIX_MAX_VOLUME); //Mettre un volume pour ce wav
    cout << Mix_GetError();*/

    nomSortie.append(nom);
    nomSortie.append("-");
    nomSortie.append(methode);
    nomSortie.append("-");
    nomSortie.append(dimension);
    nomSortie.append("D");
    nomSortie.append(".out");

    nomBloc.append(nom);
    nomBloc.append(".in");

    bloc = new Donnees();
    complet = new Donnees();
    //translate = new Donnees();
    //rotationne = new Donnees();
    sortie = new Donnees();

    ouvrir(nomBloc,bloc);
    taille = bloc->Points->size1;
    d = bloc->Points->size2;
    a = bloc->a;
    Labyrinthe2Donnees(lab,bloc,complet);
    n = complet->Points->size1;

    translate = init_translation_rotation_homothetie(complet);
    rotationne = init_translation_rotation_homothetie(complet);

    sortie->a = complet->a;
    sortie->H = complet->H;
    sortie->Points = gsl_matrix_calloc(n,k);

    homothete = init_translation_rotation_homothetie(sortie);

    base = gsl_matrix_calloc(k,d);
    gsl_matrix_set_identity(base);
    camera = gsl_vector_calloc(d);
    deplacement = gsl_vector_calloc(d);
    deplacementcopie = gsl_vector_calloc(d);

    Mangles = gsl_matrix_calloc(d,d);
    gsl_matrix_set_identity(Mangles);
    angles = Matrix2Angles(Mangles);
    axe = 3;

    Mdelta_angles = gsl_matrix_calloc(d,d);
    gsl_matrix_set_identity(Mdelta_angles);
    delta_angles = Matrix2Angles(Mdelta_angles);

    Mcopie = gsl_matrix_calloc(d,d);

    gsl_vector_set(camera,0,-X-.5);
    gsl_vector_set(camera,1,-Y-.5);
    gsl_vector_set(camera,2,-Z-.5);
    gsl_vector_set(camera,3,-W-.5);

    translation(complet,camera,translate);
    rotation(translate,Mangles,rotationne);
    selected(rotationne,k,base,lab,axe,(int)(-gsl_vector_get(camera,axe)-0.5+0.1),taille,sortie);

    if(SDL_Init(SDL_INIT_VIDEO) < 0) //initialize SDL video
    {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit); //make sure SDL cleans up before exit
    SDL_WM_SetCaption("HyperLabyrinth by Olivier Roupin", NULL);

    SDL_SetVideoMode(853, 480, 32, SDL_OPENGL);//|SDL_FULLSCREEN);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70,(double)853/480,0.05,10);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,0,0,0,-1,0,1,0);

    Uint32 last_time = SDL_GetTicks();
    Uint32 current_time,ellapsed_time;
    Uint32 start_time(0);

    //Mix_PlayMusic(fond, -1); //Jouer infiniment la musique

    bool done = false;
    while(!done) //program main loop
    {
        /*Mix_PlayChannel(1, son0, 0);
        Mix_FadeOutMusic(1000);
        Mix_FadeInMusic(detection,-1,60);
        Mix_VolumeMusic(0);
        Mix_PlayMusic(detection, -1); //Jouer infiniment la musique
        Mix_FadeOutChannel(1,60);
        Mix_VolumeChunk(son1, abs(MIX_MAX_VOLUME*(x2-48)/48));*/

        input1.Actualiser(done);

        if(input1.GetBouton() && progression == 100)
        {
            ControleDiscret(input1, delta_angles, deplacement);
            gsl_vector_memcpy(deplacementcopie,deplacement);
            gsl_blas_dgemv(CblasTrans, 1.0, Mangles, deplacementcopie, 0.0, deplacement); //deplacement = tMangles*deplacement
            if(not(lab->GetTableau(camera,deplacement)))
                progression = 0;

            if(strcmp(mode.c_str(), "DEBUG") == 0)
            {
                cout << "camera\t\t" <<\
                     gsl_vector_get(camera,0) << "    " <<\
                     gsl_vector_get(camera,1) << "    " <<\
                     gsl_vector_get(camera,2) << "    " <<\
                     gsl_vector_get(camera,3) << endl;
                cout << "deplacement\t" <<\
                     gsl_vector_get(deplacement,0) << "    " <<\
                     gsl_vector_get(deplacement,1) << "    " <<\
                     gsl_vector_get(deplacement,2) << "    " <<\
                     gsl_vector_get(deplacement,3) << endl;
                cout << "Sub\t\t" <<\
                     (int)(100*gsl_vector_get(deplacement,0)-gsl_vector_get(camera,0)-0.5+0.1) << "    " <<\
                     (int)(100*gsl_vector_get(deplacement,1)-gsl_vector_get(camera,1)-0.5+0.1) << "    " <<\
                     (int)(100*gsl_vector_get(deplacement,2)-gsl_vector_get(camera,2)-0.5+0.1) << "    " <<\
                     (int)(100*gsl_vector_get(deplacement,3)-gsl_vector_get(camera,3)-0.5+0.1) << endl;
                cout << "Mur? " << lab->GetTableau(camera,deplacement) << endl;
                cout << "axe " << axe << " indice " << (int)(-gsl_vector_get(camera,axe)-0.5+0.1) << endl << endl;
                sauver(nomSortie,rotationne);
            }
        }

        current_time = SDL_GetTicks();
        ellapsed_time = current_time - last_time;
        last_time = current_time;

        if(progression < 100)
        {
            progression++;
            Angles2Matrix(delta_angles, Mdelta_angles);
            gsl_matrix_memcpy(Mcopie,Mangles);
            gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, Mdelta_angles, Mcopie, 0.0, Mangles); //Mangles = Mangles*Mdelta_angles

            if(progression == 100)
                Reparer(Mangles);

            gsl_vector_sub(camera,deplacement);
            translation(complet,camera,translate);
            rotation(translate,Mangles,rotationne);
            axe = TrouverAxe(Mangles, axe);
            selected(rotationne,k,base,lab,axe,(int)(-gsl_vector_get(camera,axe)-0.5+0.1),taille,sortie);
            //sortie->T = perspectived(rotationne,k,base,0.05);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if(strcmp(methode.c_str(), "GL") == 0)
            DessinerQuads(sortie, lab->GetTaille(), a);
        else if(strcmp(methode.c_str(), "GL2") == 0)
        {
            glBegin(GL_QUADS);
            selected(rotationne,k,base,lab,axe,(int)(-gsl_vector_get(camera,axe)-0.5+0.1),taille,sortie);
            DessinerQuads(sortie, lab->GetTaille(), a, 2);
            selected(rotationne,k,base,lab,axe,(int)(-gsl_vector_get(camera,axe)-0.5+0.1)-1,taille,sortie);
            homothetie(sortie, 0.99, homothete);
            DessinerQuads(homothete, lab->GetTaille(), a, 1);
            selected(rotationne,k,base,lab,axe,(int)(-gsl_vector_get(camera,axe)-0.5+0.1)+1,taille,sortie);
            homothetie(sortie, 0.98, homothete);
            DessinerQuads(homothete, lab->GetTaille(), a, 0);
            glEnd();
        }
        glFlush();
        SDL_GL_SwapBuffers();

        ellapsed_time = SDL_GetTicks() - start_time;
        if(ellapsed_time < 10)
            SDL_Delay(10 - ellapsed_time);
    } //end main loop

    gsl_matrix_free(Mangles);
    gsl_matrix_free(Mdelta_angles);
    gsl_matrix_free(Mcopie);
    gsl_matrix_free(base);
    gsl_vector_free(camera);
    gsl_vector_free(deplacement);
    gsl_vector_free(deplacementcopie);
    gsl_matrix_free(translate->Points);
    gsl_matrix_free(rotationne->Points);
    gsl_matrix_free(homothete->Points);
    gsl_matrix_free(sortie->Points);
    delete translate;
    delete rotationne;
    delete homothete;
    delete sortie;
    delete angles;
    delete delta_angles;
    Donnees_free(bloc);
    Donnees_free(complet);
    /*Mix_FreeMusic(fond); //Libération de la musique
    Mix_FreeChunk(son0);//Libération du son 0
    Mix_CloseAudio(); //Fermeture de l'API*/

    printf("Exited cleanly\n");
    return 0;
}
