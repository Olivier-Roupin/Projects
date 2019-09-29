#include "tracer.h"

long tracerLigne(SDL_Surface *ecran, SDL_Rect point1, SDL_Rect point2, SDL_Color couleur, long epaisseur)
{
    SDL_Rect position, positionBlit;

    bool H_V = false;
    long arrondi = 0, iMax = 0;
    double progression = 0, X = 0, Y = 0, resultat = 0;
    long fin = 0, debut = 0, i, j;

    X = abs(point2.x - point1.x);
    Y = abs(point2.y - point1.y);

    if(X >= Y)
        H_V = true;

    if(H_V)
    {
        iMax = X;
        progression = Y/X;
    }
    else
    {
        iMax = Y;
        progression = X/Y;
    }

    for(i = 0; i < iMax; i++)
    {
        position = point2;
        X = i;
        if(point2.x <= point1.x && point2.y >= point1.y)
        {
            if(H_V)
            {
                position.x += i;
                resultat = progression*X;
                arrondi = resultat;
                position.y -= arrondi;
            }
            else
            {
                position.y -= i;
                resultat = progression*X;
                arrondi = resultat;
                position.x += arrondi;
            }
        }
        else if(point2.x <= point1.x && point2.y <= point1.y)
        {
            if(H_V)
            {
                position.x += i;
                resultat = progression*X;
                arrondi = resultat;
                position.y += arrondi;
            }
            else
            {
                position.y += i;
                resultat = progression*X;
                arrondi = resultat;
                position.x += arrondi;
            }
        }
        else if(point2.x >= point1.x && point2.y >= point1.y)
        {
            if(H_V)
            {
                position.x -= i;
                resultat = progression*X;
                arrondi = resultat;
                position.y -= arrondi;
            }
            else
            {
                position.y -= i;
                resultat = progression*X;
                arrondi = resultat;
                position.x -= arrondi;
            }
        }
        else if(point2.x >= point1.x && point2.y <= point1.y)
        {
            if(H_V)
            {
                position.x -= i;
                resultat = progression*X;
                arrondi = resultat;
                position.y += arrondi;
            }
            else
            {
                position.y += i;
                resultat = progression * X;
                arrondi = resultat;
                position.x -= arrondi;
            }
        }
        if(epaisseur == 1)
        {
            /*position.x %= TAILLE_ECRAN;
            position.y %= TAILLE_ECRAN;
            if(position.x < 0)
                position.x += TAILLE_ECRAN;
            if(position.y < 0)
                position.y += TAILLE_ECRAN;*/
            if(position.x >= 0 && position.x < TAILLE_ECRAN && position.y >= 0 && position.y < TAILLE_ECRAN)
                PutPixelColor(ecran, position.x, position.y, couleur);
        }
        else
        {
            fin = (epaisseur/2) + (epaisseur%2);
            debut = 0 - (epaisseur/2);
            for(i = debut; i < fin; i++)
            {
                for(j = debut; j < fin; j++)
                {
                    positionBlit.x = position.x + i;
                    positionBlit.y = position.y + j;
                    if(positionBlit.x < 0)
                        positionBlit.x = 0;
                    if(positionBlit.y < 0)
                        positionBlit.y = 0;
                    PutPixelColor(ecran, positionBlit.x, positionBlit.y, couleur);
                }
            }
        }
    }
    return 1;
}

long tracerLigne1(SDL_Surface *ecran, SDL_Rect point1, SDL_Rect point2, SDL_Color couleur, long epaisseur)
{
    SDL_Rect position, positionBlit;

    bool H_V = false;
    long horizontale = 0, verticale = 0, arrondi = 0, iMax = 0;
    double progression = 0, X = 0, Y = 0, resultat = 0;
    long fin = 0, debut = 0, i, j;

    horizontale = point2.x - point1.x;
    verticale = point2.y - point1.y;

    if(abs(horizontale) >= abs(verticale))
        H_V = true;

    X = abs(horizontale);
    Y = abs(verticale);

    if(H_V)
    {
        iMax = abs(horizontale);
        progression = Y/X;
    }
    else
    {
        iMax = abs(verticale);
        progression = X/Y;
    }

    for(i = 0; i < iMax; i++)
    {
        if(point2.x <= point1.x && point2.y >= point1.y)
        {
            if(H_V)
            {
                position = point2;
                position.x = position.x + i;
                X = i;
                resultat = progression*X;
                arrondi = resultat;
                position.y = position.y - arrondi;
                if(epaisseur == 1)
                {
                    PutPixelColor(ecran, position.x, position.y, couleur);
                }
                else
                {
                    fin = (epaisseur/2) + (epaisseur%2);
                    debut = 0 - (epaisseur/2);
                    for(i = debut; i < fin; i++)
                    {
                        for(j = debut; j < fin; j++)
                        {
                            positionBlit.x = position.x + i;
                            positionBlit.y = position.y + j;
                            if(positionBlit.x < 0)
                                positionBlit.x = 0;
                            if(positionBlit.y < 0)
                                positionBlit.y = 0;

                            PutPixelColor(ecran, positionBlit.x, positionBlit.y, couleur);
                        }
                    }
                }
            }
            else
            {
                position = point2;
                position.y -= i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.x += arrondi;
                if(epaisseur == 1)
                {
                    PutPixelColor(ecran, position.x, position.y, couleur);
                }
                else
                {
                    fin = (epaisseur/2) + (epaisseur%2);
                    debut = 0 - (epaisseur/2);
                    for(i = debut; i < fin; i++)
                    {
                        for(j = debut; j < fin; j++)
                        {
                            positionBlit.x = position.x+i;
                            positionBlit.y = position.y+j;
                            if(positionBlit.x < 0)
                                positionBlit.x = 0;
                            if(positionBlit.y < 0)
                                positionBlit.y = 0;

                            PutPixelColor(ecran, positionBlit.x, positionBlit.y, couleur);
                        }
                    }
                }
            }
        }
        if(point2.x <= point1.x && point2.y <= point1.y)
        {
            if(H_V)
            {
                position = point2;
                position.x = position.x + i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.y = position.y + arrondi;
                if(epaisseur == 1)
                {
                    PutPixelColor(ecran, position.x, position.y, couleur);
                }
                else
                {
                    fin = (epaisseur / 2) + (epaisseur % 2);
                    debut = 0 - (epaisseur / 2);
                    for(i = debut; i < fin; i++)
                    {
                        for(j = debut; j < fin; j++)
                        {
                            positionBlit.x = (position.x+i);
                            positionBlit.y = (position.y+j);
                            if(positionBlit.x < 0)
                                positionBlit.x = 0;
                            if(positionBlit.y < 0)
                                positionBlit.y = 0;

                            PutPixelColor(ecran, positionBlit.x, positionBlit.y, couleur);
                        }
                    }
                }
            }
            else
            {
                position = point2;
                position.y = position.y + i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.x = position.x + arrondi;
                if(epaisseur == 1)
                {
                    PutPixelColor(ecran, position.x, position.y, couleur);
                }
                else
                {
                    fin = (epaisseur / 2) + (epaisseur % 2);
                    debut = 0 - (epaisseur / 2);
                    for(i = debut; i < fin; i++)
                    {
                        for(j = debut; j < fin; j++)
                        {
                            positionBlit.x = (position.x+i);
                            positionBlit.y = (position.y+j);
                            if(positionBlit.x < 0)
                                positionBlit.x = 0;
                            if(positionBlit.y < 0)
                                positionBlit.y = 0;

                            PutPixelColor(ecran, positionBlit.x, positionBlit.y, couleur);
                        }
                    }
                }
            }
        }
        else if(point2.x >= point1.x && point2.y >= point1.y)
        {
            if(H_V)
            {
                position = point2;
                position.x = position.x - i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.y = position.y - arrondi;
                if(epaisseur == 1)
                {
                    PutPixelColor(ecran, position.x, position.y, couleur);
                }
                else
                {
                    fin = (epaisseur / 2) + (epaisseur % 2);
                    debut = 0 - (epaisseur / 2);
                    for(i = debut; i < fin; i++)
                    {
                        for(j = debut; j < fin; j++)
                        {
                            positionBlit.x = (position.x+i);
                            positionBlit.y = (position.y+j);
                            if(positionBlit.x < 0)
                                positionBlit.x = 0;
                            if(positionBlit.y < 0)
                                positionBlit.y = 0;

                            PutPixelColor(ecran, positionBlit.x, positionBlit.y, couleur);
                        }
                    }
                }
            }
            else
            {
                position = point2;
                position.y = position.y - i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.x = position.x - arrondi;
                if(epaisseur == 1)
                {
                    PutPixelColor(ecran, position.x, position.y, couleur);
                }
                else
                {
                    fin = (epaisseur/2) + (epaisseur%2);
                    debut = 0 - (epaisseur/2);
                    for(i = debut; i < fin; i++)
                    {
                        for(j = debut; j < fin; j++)
                        {
                            positionBlit.x = (position.x+i);
                            positionBlit.y = (position.y+j);
                            if(positionBlit.x < 0)
                                positionBlit.x = 0;
                            if(positionBlit.y < 0)
                                positionBlit.y = 0;

                            PutPixelColor(ecran, positionBlit.x, positionBlit.y, couleur);
                        }
                    }
                }
            }
        }
        else if(point2.x >= point1.x && point2.y <= point1.y)
        {
            if(H_V)
            {
                position = point2;
                position.x = position.x - i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.y = position.y + arrondi;
                if(epaisseur == 1)
                {
                    PutPixelColor(ecran, position.x, position.y, couleur);
                }
                else
                {
                    fin = (epaisseur / 2) + (epaisseur % 2);
                    debut = 0 - (epaisseur / 2);
                    for(i = debut; i < fin; i++)
                    {
                        for(j = debut; j < fin; j++)
                        {
                            positionBlit.x = (position.x+i);
                            positionBlit.y = (position.y+j);
                            if (positionBlit.x < 0)
                                positionBlit.x = 0;
                            if (positionBlit.y < 0)
                                positionBlit.y = 0;

                            PutPixelColor(ecran, positionBlit.x, positionBlit.y, couleur);
                        }
                    }
                }
            }
            else
            {
                position = point2;
                position.y = position.y + i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.x = position.x - arrondi;
                if(epaisseur == 1)
                {
                    PutPixelColor(ecran, position.x, position.y, couleur);
                }
                else
                {
                    fin = (epaisseur / 2) + (epaisseur % 2);
                    debut = 0 - (epaisseur / 2);
                    for(i = debut; i < fin; i++)
                    {
                        for(j = debut; j < fin; j++)
                        {
                            positionBlit.x = (position.x+i);
                            positionBlit.y = (position.y+j);
                            if(positionBlit.x < 0)
                                positionBlit.x = 0;
                            if(positionBlit.y < 0)
                                positionBlit.y = 0;

                            PutPixelColor(ecran, positionBlit.x, positionBlit.y, couleur);
                        }
                    }
                }
            }
        }
    }
    return 1;
}

long tracerLigne (SDL_Surface *ecran, long point1_X, long point1_Y, long point2_X, long point2_Y, SDL_Color couleur, long epaisseur)
{
    SDL_Rect point1, point2;
    point1.x = point1_X;
    point1.y = point1_Y;
    point2.x = point2_X;
    point2.y = point2_Y;

    return tracerLigne (ecran, point1, point2, couleur, epaisseur);
}


long tracerLigne (SDL_Surface *ecran, SDL_Rect point1, SDL_Rect point2, long couleur_R, long couleur_G, long couleur_B, long epaisseur)
{
    SDL_Color couleur;
    couleur.r = couleur_R;
    couleur.g = couleur_G;
    couleur.b = couleur_B;

    return tracerLigne (ecran, point1, point2, couleur, epaisseur);
}

long tracerLigne(SDL_Surface *ecran, long point1_X, long point1_Y, long point2_X, long point2_Y, long couleur_R, long couleur_G, long couleur_B, long epaisseur)
{
    SDL_Rect point1, point2;
    point1.x = point1_X;
    point1.y = point1_Y;
    point2.x = point2_X;
    point2.y = point2_Y;
    SDL_Color couleur;
    couleur.r = couleur_R;
    couleur.g = couleur_G;
    couleur.b = couleur_B;

    return tracerLigne (ecran, point1, point2, couleur, epaisseur);
}

long tracerRayon(SDL_Surface *ecran, long point1_X, long point1_Y, long point2_X, long point2_Y, long couleur_R, long couleur_G, long couleur_B, long epaisseur)
{
    long point_X;
    long point_Y;
    double t;

    for(t = 0; t < 1; t+=0.1)
    {
        point_X = (1-t)*point1_X + t*point2_X;
        point_Y = (1-t)*point1_Y + t*point2_Y;
        tracerLigne(ecran, point1_X, point1_Y, point_X, point_Y, couleur_R, couleur_G, couleur_B, epaisseur);
        SDL_Flip(ecran);
    }
    return tracerLigne(ecran, point1_X, point1_Y, point2_X, point2_Y, couleur_R, couleur_G, couleur_B, epaisseur);
}

long tracerCarre (SDL_Surface *ecran, SDL_Rect point1, SDL_Rect point2, SDL_Color couleur, long epaisseur)
{
    long horizontale = 0, verticale = 0;
    horizontale = point1.x - point2.x;
    verticale = point1.y - point2.y;

    SDL_Rect point3, point4;

    point4 = point3 = point2;
    point3.x = point3.x + horizontale;
    point4.y = point4.y + verticale;

    tracerLigne(ecran, point1, point3, couleur, epaisseur);
    tracerLigne(ecran, point1, point4, couleur, epaisseur);
    tracerLigne(ecran, point2, point3, couleur, epaisseur);
    tracerLigne(ecran, point2, point4, couleur, epaisseur);
}

long tracerCercle (SDL_Surface *ecran, SDL_Rect centre, long rayon, SDL_Color couleur)
{
    long diametre = rayon * 2;
    long hauteur = 0, arrondi = 0;
    double resultat = 0, r = rayon, x = 0;
    SDL_Rect position, positionPrecedente;
    positionPrecedente.x = 0;
    positionPrecedente.y = 0;

    for (long i = 0; i <= rayon; i++)
    {
        x = i;
        resultat = sqrt((r*r) - (x*x));
        arrondi = resultat;
        position = centre;
        position.x = position.x + i;
        position.y = position.y + arrondi;
        if (i == 0)
        {
            PutPixelColor(ecran, position.x, position.y, couleur);
        }
        else
        {
            tracerLigne (ecran, positionPrecedente, position, couleur, 1);
        }
        positionPrecedente = position;
    }
    for (long i = 0; i <= rayon; i++)
    {
        x = i;
        resultat = sqrt((r*r) - (x*x));
        arrondi = resultat;
        position = centre;
        position.x = position.x + i;
        position.y = position.y - arrondi;
        if (i == 0)
        {
            PutPixelColor(ecran, position.x, position.y, couleur);
        }
        else
        {
            tracerLigne (ecran, positionPrecedente, position, couleur, 1);
        }
        positionPrecedente = position;
    }
    for (long i = 0; i <= rayon; i++)
    {
        x = i;
        resultat = sqrt((r*r) - (x*x));
        arrondi = resultat;
        position = centre;
        position.x = position.x - i;
        position.y = position.y + arrondi;
        if (i == 0)
        {
            PutPixelColor(ecran, position.x, position.y, couleur);
        }
        else
        {
            tracerLigne (ecran, positionPrecedente, position, couleur, 1);
        }
        positionPrecedente = position;
    }
    for (long i = 0; i <= rayon; i++)
    {
        x = i;
        resultat = sqrt((r*r) - (x*x));
        arrondi = resultat;
        position = centre;
        position.x = position.x - i;
        position.y = position.y - arrondi;
        if (i == 0)
        {
            PutPixelColor(ecran, position.x, position.y, couleur);
        }
        else
        {
            tracerLigne (ecran, positionPrecedente, position, couleur, 1);
        }
        positionPrecedente = position;
    }
    return 1;
}


long tracerCercle (SDL_Surface *ecran, SDL_Rect point1, SDL_Rect point2, SDL_Color couleur)
{
    SDL_Rect centre;
    bool H = false, V = false;
    long rayon = 0, arrondi = 0, horizontale = 0, verticale = 0;
    double diametre = 0;

    if (point1.x > point2.x)
    {
        H = true;
        horizontale = point1.x - point2.x;
    }
    else
    {
        horizontale = point2.x - point1.x;
    }

    if (point1.y > point2.y)
    {
        V = true;
        verticale = point1.y - point2.y;
    }
    else
    {
        verticale = point2.y - point1.y;
    }

    diametre = sqrt((horizontale*horizontale) + (verticale*verticale));
    rayon = diametre/2;

    if (H == true)
    {
        centre.x = point1.x - (horizontale / 2);
    }
    else
    {
        centre.x = point1.x + (horizontale / 2);
    }

    if (V == true)
    {
        centre.y = point1.y - (verticale / 2);
    }
    else
    {
        centre.y = point1.y + (verticale / 2);
    }

    return tracerCercle (ecran, centre, rayon, couleur);
}

void PutPixelColor(SDL_Surface *surface, int x, int y, SDL_Color couleur)
{
    unsigned long pixel = SDL_MapRGBA(surface->format, couleur.r, couleur.g, couleur.b, 0);

    int bpp = surface->format->BytesPerPixel;
    unsigned char *p = (unsigned char *)surface->pixels + y * surface->pitch + x * bpp;
    switch (bpp)
    {
    case 1:
        *p = (unsigned char)pixel;
        break;
    case 2:
        *(unsigned short*)p = (unsigned short)pixel;
        break;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (unsigned char)((pixel >> 16) & 0xff);
            p[1] = (unsigned char)((pixel >> 8) & 0xff);
            p[2] = (unsigned char)(pixel & 0xff);
        }
        else
        {
            p[0] = (unsigned char)(pixel & 0xff);
            p[1] = (unsigned char)((pixel >> 8) & 0xff);
            p[2] = (unsigned char)((pixel >> 16) & 0xff);
        }
        break;
    case 4:
        *(unsigned long*)p = pixel;
        break;
    }
}
