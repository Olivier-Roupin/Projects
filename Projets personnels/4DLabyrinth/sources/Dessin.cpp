#include "Dessin.h"

using namespace std;

void DessinerQuads(Donnees* sortie, int taille, int a)
{
    int i,j;
    int p1,p2,p3,p4;
    int d(sortie->Points->size2);

    glBegin(GL_QUADS);
    for(i = 0; i < taille; i++)
    {
        for(j = 0; j < a; j++)
        {
            glColor3ub(10*j,(16*i)%255,255-10*j);
            //glColor3ub((i/125)*51,i*51,j*255/16);
            if(sortie->H[i*a+j][0] == 4)
            {
                p1 = sortie->H[i*a+j][1];
                p2 = sortie->H[i*a+j][2];
                p3 = sortie->H[i*a+j][3];
                p4 = sortie->H[i*a+j][4];
                glVertex3d(sortie->Points->data[p1*d],sortie->Points->data[p1*d+1],sortie->Points->data[p1*d+2]);
                glVertex3d(sortie->Points->data[p2*d],sortie->Points->data[p2*d+1],sortie->Points->data[p2*d+2]);
                glVertex3d(sortie->Points->data[p3*d],sortie->Points->data[p3*d+1],sortie->Points->data[p3*d+2]);
                glVertex3d(sortie->Points->data[p4*d],sortie->Points->data[p4*d+1],sortie->Points->data[p4*d+2]);
            }
        }
    }
    glEnd();
}

void DessinerQuads0(Donnees* sortie, int taille, int a, int RVBA)
{
    int i,j;
    int p1,p2,p3,p4;
    int d(sortie->Points->size2);

    for(i = 0; i < taille; i++)
    {
        for(j = 0; j < a; j++)
        {
            switch(RVBA)
            {
            case 0:
                glColor4ub(255-10*j,0,0, 85);
                break;
            case 1:
                glColor4ub(0,255-10*j,0, 127);
                break;
            default:
                glColor4ub(0,0,255-10*j, 255);
                break;
            }
            if(sortie->H[i*a+j][0] == 4)
            {
                p1 = sortie->H[i*a+j][1];
                p2 = sortie->H[i*a+j][2];
                p3 = sortie->H[i*a+j][3];
                p4 = sortie->H[i*a+j][4];
                glVertex3d(sortie->Points->data[p1*d]*(80+RVBA)/82,sortie->Points->data[p1*d+1]*(80+RVBA)/82,sortie->Points->data[p1*d+2]*(80+RVBA)/82);
                glVertex3d(sortie->Points->data[p2*d]*(80+RVBA)/82,sortie->Points->data[p2*d+1]*(80+RVBA)/82,sortie->Points->data[p2*d+2]*(80+RVBA)/82);
                glVertex3d(sortie->Points->data[p3*d]*(80+RVBA)/82,sortie->Points->data[p3*d+1]*(80+RVBA)/82,sortie->Points->data[p3*d+2]*(80+RVBA)/82);
                glVertex3d(sortie->Points->data[p4*d]*(80+RVBA)/82,sortie->Points->data[p4*d+1]*(80+RVBA)/82,sortie->Points->data[p4*d+2]*(80+RVBA)/82);
            }
        }
    }
}

void DessinerQuads(Donnees* sortie, int taille, int a, int RVBA)
{
    int i,j;
    int p1,p2,p3,p4;
    int d(sortie->Points->size2);

    for(i = 0; i < taille; i++)
    {
        for(j = 0; j < a; j++)
        {
            switch(RVBA)
            {
            case 0:
                glColor4ub(255-10*j,0,0, 85);
                break;
            case 1:
                glColor4ub(0,255-10*j,0, 127);
                break;
            default:
                glColor4ub(0,0,255-10*j, 255);
                break;
            }
            if(sortie->H[i*a+j][0] == 4)
            {
                p1 = sortie->H[i*a+j][1];
                p2 = sortie->H[i*a+j][2];
                p3 = sortie->H[i*a+j][3];
                p4 = sortie->H[i*a+j][4];
                glVertex3d(sortie->Points->data[p1*d],sortie->Points->data[p1*d+1],sortie->Points->data[p1*d+2]);
                glVertex3d(sortie->Points->data[p2*d],sortie->Points->data[p2*d+1],sortie->Points->data[p2*d+2]);
                glVertex3d(sortie->Points->data[p3*d],sortie->Points->data[p3*d+1],sortie->Points->data[p3*d+2]);
                glVertex3d(sortie->Points->data[p4*d],sortie->Points->data[p4*d+1],sortie->Points->data[p4*d+2]);
            }
        }
    }
}
