#ifndef INPUT_H
#define INPUT_H

#define NOMBRE_BOUTONS 12
#define BOUTON_HAUT    0
#define BOUTON_DROITE  1
#define BOUTON_BAS     2
#define BOUTON_GAUCHE  3
#define BOUTON_A       4
#define BOUTON_B       5
#define BOUTON_X       6
#define BOUTON_Y       7
#define BOUTON_L       8
#define BOUTON_R       9
#define BOUTON_START  10
#define BOUTON_SELECT 11

#define getHaut()   GetBouton(BOUTON_HAUT)
#define getDroite() GetBouton(BOUTON_DROITE)
#define getBas()    GetBouton(BOUTON_BAS)
#define getGauche() GetBouton(BOUTON_GAUCHE)
#define getA()      GetBouton(BOUTON_A)
#define getB()      GetBouton(BOUTON_B)
#define getX()      GetBouton(BOUTON_X)
#define getY()      GetBouton(BOUTON_Y)
#define getL()      GetBouton(BOUTON_L)
#define getR()      GetBouton(BOUTON_R)
#define getStart()  GetBouton(BOUTON_START)
#define getSelect() GetBouton(BOUTON_SELECT)

#define setHaut(val)   SetBouton(val, BOUTON_HAUT)
#define setDroite(val) SetBouton(val, BOUTON_DROITE)
#define setBas(val)    SetBouton(val, BOUTON_BAS)
#define setGauche(val) SetBouton(val, BOUTON_GAUCHE)
#define setA(val)      SetBouton(val, BOUTON_A)
#define setB(val)      SetBouton(val, BOUTON_B)
#define setX(val)      SetBouton(val, BOUTON_X)
#define setY(val)      SetBouton(val, BOUTON_Y)
#define setL(val)      SetBouton(val, BOUTON_L)
#define setR(val)      SetBouton(val, BOUTON_R)
#define setStart(val)  SetBouton(val, BOUTON_START)
#define setSelect(val) SetBouton(val, BOUTON_SELECT)

#define takeHaut()   TakeBouton(BOUTON_HAUT)
#define takeDroite() TakeBouton(BOUTON_DROITE)
#define takeBas()    TakeBouton(BOUTON_BAS)
#define takeGauche() TakeBouton(BOUTON_GAUCHE)
#define takeA()      TakeBouton(BOUTON_A)
#define takeB()      TakeBouton(BOUTON_B)
#define takeX()      TakeBouton(BOUTON_X)
#define takeY()      TakeBouton(BOUTON_Y)
#define takeL()      TakeBouton(BOUTON_L)
#define takeR()      TakeBouton(BOUTON_R)
#define takeStart()  TakeBouton(BOUTON_START)
#define takeSelect() TakeBouton(BOUTON_SELECT)

class Input {
    public:
        Input();
        virtual ~Input();
        bool GetBouton(unsigned char id) const;
        void SetBouton(bool val, unsigned char id);
        bool TakeBouton(unsigned char id);
        void Actualiser();
        void Vider();
    protected:
    private:
        bool m_Boutons[NOMBRE_BOUTONS];
};

#endif // INPUT_H
