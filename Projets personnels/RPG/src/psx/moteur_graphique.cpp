#include "moteur_graphique.h"
#include <sys/types.h>	// This provides typedefs needed by psxgte and psxgpu
#include <stdio.h>	// Not necessary but include it anyway
// #include <psxetc.h>	// Includes some functions that controls the display: font
#include <psxgte.h>	// GTE header, not really used but psxgpu.h depends on it
#include <psxgpu.h>	// GPU library header
#include <psxapi.h> // API header, has InitPAD() and StartPAD() defs
#include <psxcd.h>  // CdInit
#include <stdlib.h> // malloc/free
#include <macros.h> //MIN, MAX

#define TAILLE_BASIQUE 8
#define LARGEUR_ECRAN (LARGEUR_FENETRE*TAILLE_BASIQUE) // 256 // 320//
#define HAUTEUR_ECRAN (HAUTEUR_FENETRE*TAILLE_BASIQUE) // 224 // 256//
#define TEMPS_IMAGE 20 // 16

#include <fonctions_graphiques.h>
#define HAUTEUR_PAGE 32
#define TAILLE_PAGE (HAUTEUR_PAGE*LARGEUR_PAGE)

int ecran_fondu = 0;
unsigned int frameLimit = 0;

// TIM_IMAGE* textures[NOMBRE_PAGES];
u_short textures[NOMBRE_PAGES];
const char* fichiers_pages[NOMBRE_PAGES] = {
      "\\POLICE.TIM;1",
      "\\TUILES.TIM;1",
     "\\SPRITES.TIM;1",
       "\\HEROS.TIM;1",
    "\\MONSTRES.TIM;1"
};

#define MAX_LARGEUR 320
#define MAX_HAUTEUR 240 //256

// Define environment pairs and buffer counter
DISPENV disp[2];
DRAWENV draw[2];
int db = 0; // Make sure db starts with zero

#define OTLEN 2
u_long ot[2][OTLEN];    // Ordering table length
char pribuff[2][32768]; // Primitive buffer
char *nextpri;          // Next primitive pointer
unsigned char page_actuelle = 255;
char* prevpri = 0;

unsigned char padbuff[2][34];
unsigned char paddelai = 0;

unsigned int  horloge_s = 0;
unsigned char horloge_f = 0;

void allumerEcran(const char *titre) {
    // Reset GPU and enable interrupts
    ResetGraph(0);
    CdInit();
    SetDefDispEnv(&disp[0], 0,           0, MAX_LARGEUR, MAX_HAUTEUR);
    SetDefDispEnv(&disp[1], 0, MAX_HAUTEUR, MAX_LARGEUR, MAX_HAUTEUR);
    // SetDefDispEnv(&disp[0], (MAX_LARGEUR-LARGEUR_ECRAN)/2, (MAX_HAUTEUR-HAUTEUR_ECRAN)/2,             LARGEUR_ECRAN, HAUTEUR_ECRAN);
    // SetDefDispEnv(&disp[1], (MAX_LARGEUR-LARGEUR_ECRAN)/2, (MAX_HAUTEUR-HAUTEUR_ECRAN)/2+MAX_HAUTEUR, LARGEUR_ECRAN, HAUTEUR_ECRAN);
    // Screen offset to center the picture vertically
    disp[0].screen.y = 24;
    disp[1].screen.y = disp[0].screen.y;
    disp[0].screen.x = 6;
    disp[1].screen.x = disp[0].screen.x;
    // Forces PAL video standard
    SetVideoMode(MODE_PAL);
    // Configures the pair of DRAWENVs for the DISPENVs
    // SetDefDrawEnv(&draw[0], 0, MAX_HAUTEUR, MAX_LARGEUR, MAX_HAUTEUR);
    // SetDefDrawEnv(&draw[1], 0,           0, MAX_LARGEUR, MAX_HAUTEUR);
    SetDefDrawEnv(&draw[0], (MAX_LARGEUR-LARGEUR_ECRAN)/2, (MAX_HAUTEUR-HAUTEUR_ECRAN)/4+MAX_HAUTEUR, LARGEUR_ECRAN, HAUTEUR_ECRAN);
    SetDefDrawEnv(&draw[1], (MAX_LARGEUR-LARGEUR_ECRAN)/2, (MAX_HAUTEUR-HAUTEUR_ECRAN)/4,             LARGEUR_ECRAN, HAUTEUR_ECRAN);
    // Specifies the clear color of the DRAWENV
    setRGB0(&draw[0], 0, 0, 0);
    setRGB0(&draw[1], 0, 0, 0);
    // Enable background clear
    draw[0].isbg = 1;
    draw[1].isbg = 1;
    // Apply environments
    PutDispEnv(&disp[0]);
    PutDrawEnv(&draw[0]);

    nextpri = pribuff[0];           // Set initial primitive pointer address

    // set tpage of lone texture as initial tpage
    // draw[0].tpage = getTPage(0, 0, 640, 0);
    // draw[1].tpage = getTPage(0, 0, 640, 0);

    // apply initial drawing environment
    PutDrawEnv(&draw[!db]);

    // Initialize the pads
    InitPAD((char*)padbuff[0], 34, (char*)padbuff[1], 34);
    // Begin polling
    StartPAD();
    // To avoid VSync Timeout error, may not be defined in PsyQ
    ChangeClearPAD(1);

    // Load the internal font texture
    FntLoad(960, 0);
    // Create the text stream
    FntOpen(0, 8, 320, 224, 0, 100);
}

void syncEcran(unsigned int &frameLimit) {
    // horloge rudimentaire
    ++horloge_f;
    if (horloge_f == 2*TEMPS_IMAGE) {
        horloge_f = 0;
        ++horloge_s;
    }
    return;
}

void LoadTexture(u_long *tim, TIM_IMAGE *tparam) {
    // Read TIM information (PSn00bSDK)
    GetTimInfo(tim, tparam);
    // Upload pixel data to framebuffer
    LoadImage(tparam->prect, (u_long*)tparam->paddr);
    DrawSync(0);
    // Upload CLUT to framebuffer if present
    if (tparam->mode & 0x8) {
        LoadImage(tparam->crect, (u_long*)tparam->caddr);
        DrawSync(0);
    }
}

char *LoadFile(const char *filename) {
    CdlFILE filePos;
    int     numsecs;
    char    *buff;
    buff = NULL;
    /* locate the file on the CD */
    if (CdSearchFile(&filePos, filename)) {
    //if (CdSearchFile(filename, &filePos)) {
        /* calculate number of sectors to read for the file */
        numsecs = (filePos.size+2047)/2048;
        /* allocate buffer for the file (replace with malloc3() for PsyQ) */
        buff = (char*)malloc(2048*numsecs);
        /* set read target to the file */
        CdControl(CdlSetloc, (u_char*)&filePos.pos, 0);
        /* start read operation */
        CdRead(numsecs, (u_long*)buff, CdlModeSpeed);
        /* wait until the read operation is complete */
        CdReadSync(0, 0);
    }
    return buff ;
}

// TIM_IMAGE* ChargerImage(const char* fichier) {
u_short ChargerImage(const char* fichier) {
    // This can be defined locally, if you don't need the TIM coordinates
    TIM_IMAGE* my_image = 0;  // TIM image parameters
    u_int*     filebuff;      // Pointer for the file loaded from the disc
    if ((filebuff = (u_int*)LoadFile(fichier))) {
        my_image = new TIM_IMAGE();
        // On successful file read, load the texture to VRAM
        // Load the TIM
        LoadTexture((u_long*)filebuff, my_image);

        // Copy the TIM coordinates
        // RECT tim_prect = *my_image->prect;
        // RECT tim_crect = *my_image->crect;
        // tim_mode  =  my_image->mode;
        // u_long tim_caddr = *my_image->caddr;
        // u_long tim_paddr = *my_image->paddr;

        // Calculate U,V offset for TIMs that are not page aligned
        // tim_uoffs = (tim_prect.x%64) << (2-(tim_mode&0x3));
        // tim_voffs = (tim_prect.y&0xff);

        // Free the file buffer
        free(filebuff);
    }
    // return my_image;
    if (my_image)
        return getTPage(0, 0, my_image->prect->x, my_image->prect->y);
    return 0;
}

bool ChargerPage(unsigned char page) {
    return (textures[page] = ChargerImage(fichiers_pages[page])) != 0;
}

bool actif_fondu = false; //beta

void setCouleurEcran(unsigned char r, unsigned char v, unsigned char b, unsigned char a) {
    // Specifies the clear color of the DRAWENV
    setRGB0(&draw[0], r, v, b);
    setRGB0(&draw[1], r, v, b);
    actif_fondu = r == 0x00 && v == 0x00 && b == 0x00; //a != 0xFF && 
}

void effacerEcran() {
    ClearOTagR(ot[db], OTLEN);  // Clear ordering table
}

void ChangerPage(unsigned char page) {
    DR_TPAGE* tpage = (DR_TPAGE*)nextpri;
    // setDrawTPage(tpage, 0, 1, getTPage(0, 0, 640+page*64, 0));
    setDrawTPage(tpage, 0, 1, textures[page]);
    if (prevpri)
        addPrim(prevpri, tpage);
    else
        addPrim(ot[db], tpage);
    prevpri  = nextpri;
    nextpri += sizeof(DR_TPAGE);
}

void afficherEcran() {
    // FntPrint(-1,"hello");
    // FntFlush(-1);
    // ChangerPage(page_actuelle); // Changer à la dernière page utilisée

    // Wait for GPU to finish drawing and V-Blank
    DrawSync(0);
    VSync(0);
    // Apply environments
    PutDispEnv(&disp[db]);
    PutDrawEnv(&draw[db]);
    // Enable display
    SetDispMask(1);
    // Draw the ordering table
    DrawOTag(ot[db]+OTLEN-1);
    // Flip buffer counter
    db = !db;
    // Reset next primitive pointer
    nextpri = pribuff[db];
    page_actuelle = 255;
    prevpri = 0;
}

typedef struct _FADERECT {
	u_long	tag;
	u_long	tpage;
	u_char	r0,g0,b0,code;
	short	x0,y0;
	short	w,h;
} FADERECT;

void remplirEcran() {
    if (actif_fondu) {
        FADERECT *fade = (FADERECT*)nextpri;
        fade->tag   = 0x04000000;
        fade->tpage = 0xe1000040;
        fade->code  = 0x62;
        
        setRGB0(fade, ecran_fondu, ecran_fondu, ecran_fondu);
        setXY0(fade, 0, 0);
        setWH(fade, LARGEUR_ECRAN, HAUTEUR_ECRAN);
        if (prevpri)
            addPrim(prevpri, fade);
        else
            addPrim(ot[db], fade);
        prevpri  = nextpri;
        nextpri += sizeof(FADERECT);
    }
    return;
}

bool changePleinEcran(bool vrai_ratio) {
    return true;
}

int premierElementListe(int id, int hauteur, int nombre) {
    if (id < hauteur/2 || nombre < hauteur)
        return 0;
    if (id > nombre - (hauteur+1)/2 - 1)
        return nombre - hauteur-1;
    return id - hauteur/2;
}

unsigned int horloge() {
    return horloge_s;
}

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned char u, unsigned char v,
                                        unsigned char w, unsigned char h,
                                        bool fw, bool fh) {
    // return AfficherTexture(page,x,y,u,v,w,h);
    // if (page_actuelle == 255)
    //     page_actuelle = page;
    // else if (page != page_actuelle) {
    //     ChangerPage(page_actuelle);
    //     page_actuelle = page;
    // }
    if (page != page_actuelle) {
        ChangerPage(page);
        page_actuelle = page;
    }
    SPRT* sprt = (SPRT*)nextpri;
    setSprt(sprt);
    setXY0(sprt, x, y);
    setWH( sprt, w, h);
    // if (fw)
    //     setUV0(sprt, u, v+96);
    // else
        setUV0(sprt, u, v);
    setClut(sprt, 640+page*64, 256);
    setRGB0(sprt, 128, 128, 128);
    if (prevpri)
        addPrim(prevpri, sprt);
    else
        addPrim(ot[db], sprt);
    prevpri  = nextpri;
    nextpri += sizeof(SPRT);
    return 1;
} //p,x,y,u,v,w,h,fw,fh

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned char u, unsigned char v,
                                        unsigned char w, unsigned char h) {
    if (page != page_actuelle) {
        ChangerPage(page);
        page_actuelle = page;
    }
    SPRT* sprt = (SPRT*)nextpri;
    setSprt(sprt);
    setXY0(sprt, x, y);
    setWH( sprt, w, h);
    setUV0(sprt, u, v);
    setClut(sprt, 640+page*64, 256);
    setRGB0(sprt, 128, 128, 128);
    if (prevpri)
        addPrim(prevpri, sprt);
    else
        addPrim(ot[db], sprt);
    prevpri  = nextpri;
    nextpri += sizeof(SPRT);
    return 1;
} //p,x,y,u,v,w,h

//TAILLE_BASIQUE == 8

int AfficherElement(unsigned char page,          int  x,          int  y,
                                        unsigned char u, unsigned char v) {
    if (x <= -TAILLE_BASIQUE || y <= -TAILLE_BASIQUE || x > LARGEUR_ECRAN || y > HAUTEUR_ECRAN)
        return 0;
    if (page != page_actuelle) {
        ChangerPage(page);
        page_actuelle = page;
    }
    SPRT_8* sprt = (SPRT_8*)nextpri;
    setSprt8(sprt);
    setXY0(sprt, x, y);
    setUV0(sprt, u, v);
    setClut(sprt, 640+page*64, 256);
    setRGB0(sprt, 128, 128, 128);
    if (prevpri)
        addPrim(prevpri, sprt);
    else
        addPrim(ot[db], sprt);
    prevpri  = nextpri;
    nextpri += sizeof(SPRT_8);
    return 1;
} //p,x,y,u,v

int AfficherElementL(unsigned char page,          int  x,          int  y,
                                         unsigned char u, unsigned char v) {
    if (x <= -2*TAILLE_BASIQUE || y <= -2*TAILLE_BASIQUE || x > LARGEUR_ECRAN || y > HAUTEUR_ECRAN)
        return 0;
    if (page != page_actuelle) {
        ChangerPage(page);
        page_actuelle = page;
    }
    SPRT_16* sprt = (SPRT_16*)nextpri;
    setSprt16(sprt);
    setXY0(sprt, x, y);
    setUV0(sprt, u, v);
    setClut(sprt, 640+page*64, 256);
    setRGB0(sprt, 128, 128, 128);
    if (prevpri)
        addPrim(prevpri, sprt);
    else
        addPrim(ot[db], sprt);
    prevpri  = nextpri;
    nextpri += sizeof(SPRT_16);
    return 1;
} //p,x,y,u,v

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j,
                                        unsigned int  e,
                                        unsigned char m, unsigned char n) {
    // return AfficherTexture(page,
    //         TAILLE_BASIQUE*i+x,              TAILLE_BASIQUE*j+y, 
    //         // (e%TAILLE_PAGE) % LARGEUR_PAGE, (e%TAILLE_PAGE) / LARGEUR_PAGE,
    //         TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE),
    //         TAILLE_BASIQUE*m,                TAILLE_BASIQUE*n);
    if (page != page_actuelle) {
        ChangerPage(page);
        page_actuelle = page;
    }
    SPRT* sprt = (SPRT*)nextpri;
    setSprt(sprt);
    setXY0(sprt, TAILLE_BASIQUE*i+x, TAILLE_BASIQUE*j+y);
    setWH( sprt, TAILLE_BASIQUE*m,   TAILLE_BASIQUE*n);
    setUV0(sprt, TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE));
    setClut(sprt, 640+page*64, 256);
    setRGB0(sprt, 128, 128, 128);
    if (prevpri)
        addPrim(prevpri, sprt);
    else
        addPrim(ot[db], sprt);
    prevpri  = nextpri;
    nextpri += sizeof(SPRT);
    return 1;
} //p,x,y,i,j,e,m,n

int AfficherTexture(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j,
                                        unsigned int  e,
                                        unsigned char m, unsigned char n,
                                        bool fw, bool fh) {
    // return AfficherTexture(page,
    //         TAILLE_BASIQUE*i+x,              TAILLE_BASIQUE*j+y, 
    //         // (e%TAILLE_PAGE) % LARGEUR_PAGE, (e%TAILLE_PAGE) / LARGEUR_PAGE,
    //         TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE),
    //         TAILLE_BASIQUE*m,                TAILLE_BASIQUE*n, fw, fh);
    if (page != page_actuelle) {
        ChangerPage(page);
        page_actuelle = page;
    }
    SPRT* sprt = (SPRT*)nextpri;
    setSprt(sprt);
    setXY0(sprt, TAILLE_BASIQUE*i+x, TAILLE_BASIQUE*j+y);
    setWH( sprt, TAILLE_BASIQUE*m,   TAILLE_BASIQUE*n);
    setUV0(sprt, TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE));
    setClut(sprt, 640+page*64, 256);
    setRGB0(sprt, 128, 128, 128);
    if (prevpri)
        addPrim(prevpri, sprt);
    else
        addPrim(ot[db], sprt);
    prevpri  = nextpri;
    nextpri += sizeof(SPRT);
    return 1;
} //p,x,y,i,j,e,m,n,fw,fh

int AfficherTexture(unsigned char page, unsigned int  i, unsigned int  j,
                                        unsigned int  e,
                                        unsigned char m, unsigned char n) {
    // return AfficherTexture(page, 0, 0, i, j, e, m, n);
    if (page != page_actuelle) {
        ChangerPage(page);
        page_actuelle = page;
    }
    SPRT* sprt = (SPRT*)nextpri;
    setSprt(sprt);
    setXY0(sprt, TAILLE_BASIQUE*i, TAILLE_BASIQUE*j);
    setWH( sprt, TAILLE_BASIQUE*m,   TAILLE_BASIQUE*n);
    setUV0(sprt, TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE));
    setClut(sprt, 640+page*64, 256);
    setRGB0(sprt, 128, 128, 128);
    if (prevpri)
        addPrim(prevpri, sprt);
    else
        addPrim(ot[db], sprt);
    prevpri  = nextpri;
    nextpri += sizeof(SPRT);
    return 1;
} //p,i,j,e,m,n

// Sur?
int AfficherElement(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j,
                                        unsigned int  e) {
    // if (i < LARGEUR_FENETRE && j < HAUTEUR_FENETRE)
    //     return AfficherElement(page,
    //             TAILLE_BASIQUE*i+x,              TAILLE_BASIQUE*j+y, 
    //             TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE));
    // return 0;
    x = x+TAILLE_BASIQUE*i;
    y = y+TAILLE_BASIQUE*j;
    if (x <= -TAILLE_BASIQUE || y <= -TAILLE_BASIQUE || x > LARGEUR_ECRAN || y > HAUTEUR_ECRAN)
        return 0;
    if (page != page_actuelle) {
        ChangerPage(page);
        page_actuelle = page;
    }
    SPRT_8* sprt = (SPRT_8*)nextpri;
    setSprt8(sprt);
    setXY0(sprt, x, y);
    setUV0(sprt, TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE));
    setClut(sprt, 640+page*64, 256);
    setRGB0(sprt, 128, 128, 128);
    if (prevpri)
        addPrim(prevpri, sprt);
    else
        addPrim(ot[db], sprt);
    prevpri  = nextpri;
    nextpri += sizeof(SPRT_8);
    return 1;
} //p,x,y,i,j,e

int AfficherElement(unsigned char page, unsigned int  i, unsigned int  j,
                                        unsigned int  e) {
    // if (i < LARGEUR_FENETRE && j < HAUTEUR_FENETRE)
    //     return AfficherElement(page,
    //             TAILLE_BASIQUE*i,                TAILLE_BASIQUE*j, 
    //             TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE));
    // return 0;
    const int x = TAILLE_BASIQUE*i;
    const int y = TAILLE_BASIQUE*j;
    if (x <= -TAILLE_BASIQUE || y <= -TAILLE_BASIQUE || x > LARGEUR_ECRAN || y > HAUTEUR_ECRAN)
        return 0;
    if (page != page_actuelle) {
        ChangerPage(page);
        page_actuelle = page;
    }
    SPRT_8* sprt = (SPRT_8*)nextpri;
    setSprt8(sprt);
    setXY0(sprt, x, y);
    setUV0(sprt, TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE));
    setClut(sprt, 640+page*64, 256);
    setRGB0(sprt, 128, 128, 128);
    if (prevpri)
        addPrim(prevpri, sprt);
    else
        addPrim(ot[db], sprt);
    prevpri  = nextpri;
    nextpri += sizeof(SPRT_8);
    return 1;
    // return AfficherElement(page, 0, 0, i, j, e);
} //p,i,j,e

/*int AfficherElement(unsigned char page,          int  x,          int  y,
                                        unsigned int  i, unsigned int  j,
                                        unsigned int  e) {
    return AfficherTexture(page, x, y, i, j, e, 1, 1);
} //p,x,y,i,j,e

int AfficherElement(unsigned char page, unsigned int  i, unsigned int  j,
                                        unsigned int  e) {
    return AfficherElement(page, 0, 0, i, j, e);
    // return AfficherTexture(page, 0, 0, i, j, e, 1, 1);
} //p,i,j,e*/

int AfficherElementL(unsigned char page,          int  x,          int  y,
                                         unsigned int  i, unsigned int  j,
                                         unsigned int  e) {
    // if (i <= LARGEUR_FENETRE && j <= HAUTEUR_FENETRE)
    //     return AfficherElementL(page,
    //             TAILLE_BASIQUE*i+x,              TAILLE_BASIQUE*j+y, 
    //             TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE));
    // return 0;
    x = x+TAILLE_BASIQUE*i;
    y = y+TAILLE_BASIQUE*j;
    if (x <= -2*TAILLE_BASIQUE || y <= -2*TAILLE_BASIQUE || x > LARGEUR_ECRAN || y > HAUTEUR_ECRAN)
        return 0;
    if (page != page_actuelle) {
        ChangerPage(page);
        page_actuelle = page;
    }
    SPRT_16* sprt = (SPRT_16*)nextpri;
    setSprt16(sprt);
    setXY0(sprt, x, y);
    setUV0(sprt, TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE));
    setClut(sprt, 640+page*64, 256);
    setRGB0(sprt, 128, 128, 128);
    if (prevpri)
        addPrim(prevpri, sprt);
    else
        addPrim(ot[db], sprt);
    prevpri  = nextpri;
    nextpri += sizeof(SPRT_16);
    return 1;
} //p,x,y,i,j,e

int AfficherElementL(unsigned char page, unsigned int  i, unsigned int  j,
                                         unsigned int  e) {
    // if (i <= LARGEUR_FENETRE && j <= HAUTEUR_FENETRE)
    //     return AfficherElementL(page,
    //             TAILLE_BASIQUE*i,                TAILLE_BASIQUE*j, 
    //             TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE));
    // return 0;
    const int x = TAILLE_BASIQUE*i;
    const int y = TAILLE_BASIQUE*j;
    if (x <= -2*TAILLE_BASIQUE || y <= -2*TAILLE_BASIQUE || x > LARGEUR_ECRAN || y > HAUTEUR_ECRAN)
        return 0;
    if (page != page_actuelle) {
        ChangerPage(page);
        page_actuelle = page;
    }
    SPRT_16* sprt = (SPRT_16*)nextpri;
    setSprt16(sprt);
    setXY0(sprt, x, y);
    setUV0(sprt, TAILLE_BASIQUE*(e%LARGEUR_PAGE), TAILLE_BASIQUE*(e/LARGEUR_PAGE));
    setClut(sprt, 640+page*64, 256);
    setRGB0(sprt, 128, 128, 128);
    if (prevpri)
        addPrim(prevpri, sprt);
    else
        addPrim(ot[db], sprt);
    prevpri  = nextpri;
    nextpri += sizeof(SPRT_16);
    return 1;
    // return AfficherElementL(page, 0, 0, i, j, e);
} //p,i,j,e

int AfficherCaractere(         char c,
                               int  x,          int  y,
                      unsigned int  i, unsigned int  j) {
    return AfficherElement(PAGE_POLICE, x, y, i, j, Caractere2Element(c));
}
                                                   
int AfficherCaractere(         char c,
                      unsigned int  i, unsigned int  j) {
    // return AfficherCaractere(c, 0, 0, i, j);
    return AfficherElement(PAGE_POLICE, i, j, Caractere2Element(c));
}

int AfficherCaractere(         char c, char couleur,
                               int  x,          int  y,
                      unsigned int  i, unsigned int  j) {
    return AfficherElement(PAGE_POLICE, x, y, i, j, Caractere2Element(c, couleur));
}
                                                   
int AfficherCaractere(         char c, char couleur,
                      unsigned int  i, unsigned int  j) {
    return AfficherElement(PAGE_POLICE, i, j, Caractere2Element(c, couleur));
}

#define MAX_LONGUEUR_TEXTE 64

int AfficherTexte(  const char* t,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j) {
    unsigned int l = 0;
    while (t[l] != '\0' && l < MAX_LONGUEUR_TEXTE) {
        AfficherCaractere(t[l], x, y, i+l, j);
        ++l;
    }
    return l;
}

int AfficherTexte(  const char* t,
                  unsigned int  i, unsigned int  j) {
    return AfficherTexte(t, 0, 0, i, j);
    // unsigned int l = 0;
    // while (t[l] != '\0' && l < MAX_LONGUEUR_TEXTE) {
    //     AfficherCaractere(t[l], i+l, j);
    //     ++l;
    // }
    // return l;
}

int AfficherTexte(  const char* t, char couleur,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j) {
    unsigned int l = 0;
    while (t[l] != '\0' && l < MAX_LONGUEUR_TEXTE) {
        AfficherCaractere(t[l], couleur, x, y, i+l, j);
        ++l;
    }
    return l;
}

int AfficherTexte(  const char* t, char couleur,
                  unsigned int  i, unsigned int  j) {
    return AfficherTexte(t, couleur, 0, 0, i, j);
}

void AfficherCadre(int x, int y, int* w, int* h) {
    int i, j;
    if (*w < 0)
        *w = LARGEUR_ECRAN/TAILLE_BASIQUE-x+*w;
    if (*h < 0)
        *h = HAUTEUR_ECRAN/TAILLE_BASIQUE-y+*h;
    for (i = 0; i < *h; ++i)
        for (j = 0; j < *w; ++j)
            AfficherElement(PAGE_POLICE, x+j, y+i, P_blank);
    for (i = 0; i < *h; ++i) {
        AfficherElement(PAGE_POLICE, x- 1, y+i, P_left);
        AfficherElement(PAGE_POLICE, x+*w, y+i, P_right);
    }
    for (j = 0; j < *w; ++j) {
        AfficherElement(PAGE_POLICE, x+j, y- 1, P_top);
        AfficherElement(PAGE_POLICE, x+j, y+*h, P_bottom);
    }
    AfficherElement(PAGE_POLICE, x- 1, y- 1, P_top_left);
    AfficherElement(PAGE_POLICE, x+*w, y- 1, P_top_right);
    AfficherElement(PAGE_POLICE, x- 1, y+*h, P_bottom_left);
    AfficherElement(PAGE_POLICE, x+*w, y+*h, P_bottom_right);
}

void AfficherCadre(int x, int y, int w, int h) {
    AfficherCadre(x, y, &w, &h);
}

void AfficherCadre(int x, int y, int* w, int h) {
    AfficherCadre(x, y, w, &h);
}

void AfficherCadre(int x, int y, int w, int* h) {
    AfficherCadre(x, y, &w, h);
}

int AfficherHeros(  const char* t,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j,
                  bool fw, bool fh) {
    if (t[1] < 6) {
        if (fw)
            AfficherElementL(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1])+12*LARGEUR_PAGE);
        else
            AfficherElementL(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]));
        return 2;
    }
    if (t[1] < 12) {
        AfficherTexture(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]), 2, 3, fw, fh);
        return 3;
    }
    AfficherTexture(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]), 3, 2, fw, fh);
    return 3;
}

int AfficherHeros(  const char* t,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j) {
    if (t[1] < 6) {
        AfficherElementL(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]));
        return 2;
    }
    if (t[1] < 12) {
        AfficherTexture(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]), 2, 3);
        return 3;
    }
    AfficherTexture(PAGE_HEROS, x, y, i, j, Caractere2Heros(t[0],t[1]), 3, 2);
    return 3;
}

int AfficherHeros(  const char* t,
                  unsigned int  i, unsigned int  j) {
    return AfficherHeros(t, 0, 0, i, j);
}

int AfficherCurseur(         int  x,          int  y,
                    unsigned int  i, unsigned int  j) {
    return AfficherElement(PAGE_POLICE, x, y, i, j, P_arrow);
}

int AfficherCurseur(unsigned int  i, unsigned int  j) {
    // return AfficherCurseur(0, 0, i, j);
    return AfficherElement(PAGE_POLICE, i, j, P_arrow);
}

int AfficherDither(         char d,
                            int  x,          int  y,
                   unsigned int  i, unsigned int  j) {
    return AfficherElement(PAGE_POLICE, x, y, i, j,
        MIN(MAX(P_dither_0,P_dither_0+d),P_dither_4));
}

int AfficherDither(         char d,
                   unsigned int  i, unsigned int  j) {
    // return AfficherDither(0, 0, i, j);
    return AfficherElement(PAGE_POLICE, i, j,
        MIN(MAX(P_dither_0,P_dither_0+d),P_dither_4));
}

int AfficherDithers(         char d,
                             int  x,          int  y,
                    unsigned int  i, unsigned int  j,  //*TAILLE_BASIQUE
                    unsigned char m, unsigned char n) {
    for (unsigned char k = 0; k < m; ++k)
        for (unsigned char l = 0; l < n; ++l)
            if (k+(n-1-l)+d >= 0)
                AfficherDither(k+(n-1-l)+d, x, y, i+k, j+l);
    
    return m;
}

int AfficherDithers(         char d,
                    unsigned int  i, unsigned int  j,  //*TAILLE_BASIQUE
                    unsigned char m, unsigned char n) {
    for (unsigned char k = 0; k < m; ++k)
        for (unsigned char l = 0; l < n; ++l)
            if (k+(n-1-l)+d >= 0)
                AfficherDither(k+(n-1-l)+d, i+k, j+l);
    return m;
}

int AfficherSprite(  const char* t,
                            int  x,          int  y,
                   unsigned int  i, unsigned int  j,
                   bool fw, bool fh) {
    // AfficherTexture(PAGE_SPRITES, x, y, i, j, Caractere2Sprite(t[0],t[1]), 2, 2, fw, fh);
    if (fw)
        AfficherElementL(PAGE_SPRITES, x, y, i, j, Caractere2Sprite(t[0],t[1])+12*LARGEUR_PAGE);
    else
        AfficherElementL(PAGE_SPRITES, x, y, i, j, Caractere2Sprite(t[0],t[1]));
    return 2;
}

int AfficherSprite(  const char* t,
                            int  x,          int  y,
                   unsigned int  i, unsigned int  j) {
    // AfficherTexture(PAGE_SPRITES, x, y, i, j, Caractere2Sprite(t[0],t[1]), 2, 2);
    AfficherElementL(PAGE_SPRITES, x, y, i, j, Caractere2Sprite(t[0],t[1]));
    return 2;
}

int AfficherSprite(  const char* t,
                   unsigned int  i, unsigned int  j) {
    AfficherElementL(PAGE_SPRITES, i, j, Caractere2Sprite(t[0],t[1]));
    return 2;
    // return AfficherSprite(t, 0, 0, i, j);
}

int AfficherTuile(  const char* t,
                           int  x,          int  y,
                  unsigned int  i, unsigned int  j) {
    // AfficherTexture(PAGE_TUILES, x, y, i, j, Caractere2Tuile(t[0]), 2, 2);
    AfficherElementL(PAGE_TUILES, x, y, i, j, Caractere2Tuile(t[0]));
    return 2;
}

int AfficherTuile(  const char* t,
                  unsigned int  i, unsigned int  j) {
    AfficherElementL(PAGE_TUILES, i, j, Caractere2Tuile(t[0]));
    return 2;
    // return AfficherTuile(t, 0, 0, i, j);
}

int AfficherMonstre(  const char* t,
                             int  x,          int  y,
                    unsigned int  i, unsigned int  j,
                    bool fw, bool fh) {
    if (t[0] < 3) {
        AfficherTexture(PAGE_MONSTRES, x, y, i, j, Caractere2Monstre(t[0]), 4, 4, fw, fh);
        return 4;
    }
    AfficherTexture(PAGE_MONSTRES, x, y, i, j, Caractere2Monstre(t[0]), 4, 6, fw, fh);
    return 6;
}

int AfficherMonstre(  const char* t,
                             int  x,          int  y,
                    unsigned int  i, unsigned int  j) {
    if (t[0] < 3) {
        AfficherTexture(PAGE_MONSTRES, x, y, i, j, Caractere2Monstre(t[0]), 4, 4);
        return 4;
    }
    AfficherTexture(PAGE_MONSTRES, x, y, i, j, Caractere2Monstre(t[0]), 4, 6);
    return 6;
}

int AfficherMonstre(  const char* t,
                    unsigned int  i, unsigned int  j) {
    return AfficherMonstre(t, 0, 0, i, j);
}

/*  Mix_HaltMusic();
    if (intro)
        Mix_FreeMusic(intro);
    if (music)
        Mix_FreeMusic(music);
    intro = Mix_LoadMUS("audio/island_0.ogg");
    music = Mix_LoadMUS("audio/island_1.ogg");
    if (music == 0) {
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
        exit(1);
    }
    Mix_PlayMusic(intro, 1);*/
