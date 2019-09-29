#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#define TROU false
#define MUR true

#include <gsl/gsl_blas.h>

class Labyrinthe
{
    public:
        Labyrinthe(int X, int Y, int Z, int W);
        ~Labyrinthe();
        int GetX() const;
        void SetX(int val);
        int GetY() const;
        void SetY(int val);
        int GetZ() const;
        void SetZ(int val);
        int GetW() const;
        void SetW(int val);
        int GetTaille() const;
        bool GetTableau(int i) const;
        bool GetTableau(int x, int y, int z, int w) const;
        bool GetTableau(float x, float y, float z, float w) const;
        bool GetTableau(gsl_vector* camera, gsl_vector* deplacement) const;
        void SetTableau(int i, bool val);
        void SetTableau(int x, int y, int z, int w, bool val);
        int GetNombreMurs() const;
        int Conversion(int x, int y, int z, int w) const;
        int Conversion2(int i, int &x, int &y, int &z, int &w) const;
    protected:
    private:
        int m_X;
        int m_Y;
        int m_Z;
        int m_W;
        bool* m_Tableau;
};

#endif // LABYRINTHE_H
