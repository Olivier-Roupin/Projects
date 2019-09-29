#ifndef BLOCANIME_H
#define BLOCANIME_H

#include <BlocGraphique.h>

#define NOMBRE_BLOCS_GRAPHIQUES 256

extern BlocGraphique* blocs_graphiques[NOMBRE_BLOCS_GRAPHIQUES];

class BlocAnime
{
    public:
        BlocAnime(int Nombre_Blocs, int* Blocs, int Vitesse, int Nombre, int* Sequence);
        virtual ~BlocAnime();
        BlocGraphique* GetBlocs(int id) const;
        void SetBlocs(BlocGraphique* val, int id);
        int GetVitesse() const;
        void SetVitesse(int val);
        int GetNombre() const;
        void SetNombre(int val);
        int* GetSequence() const;
        void SetSequence(int* val);
    protected:
    private:
        BlocGraphique** m_Blocs;
        int m_Vitesse;
        int m_Nombre;
        int* m_Sequence;
};

#endif // BLOCANIME_H
