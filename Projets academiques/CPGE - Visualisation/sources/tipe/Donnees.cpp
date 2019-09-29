#include "Donnees.h"

using namespace std;

void proj(int d, double* u, double* v, double* p)
{
    gsl_vector_view U,V,P;
    double produit,norme;
    U = gsl_vector_view_array(u,d);
    V = gsl_vector_view_array(v,d);
    P = gsl_vector_view_array(p,d);

    gsl_vector_memcpy(&P.vector, &U.vector);
    norme = 1.0/gsl_blas_dnrm2(&U.vector);
    gsl_blas_ddot(&U.vector, &V.vector, &produit);
    gsl_vector_scale(&P.vector, produit*norme*norme);
}

void genunit(int d, gsl_vector* u)
{
    int i;
    double s = 0.0;

    for(i = 0; i < d; i++)
    {
        gsl_vector_set(u, i, ((double) rand()) / ((double) RAND_MAX) - 0.5);
    }
    s = 1.0/gsl_blas_dnrm2(u);
    gsl_vector_scale(u, s);
}

void proj(int d, gsl_vector* u, gsl_vector* v, gsl_vector* p)
{
    double produit,norme;
    gsl_vector_memcpy(p, u);
    norme = 1.0/gsl_blas_dnrm2(u);
    gsl_blas_ddot(u, v, &produit);
    gsl_vector_scale (p, produit*norme*norme);
}

double* genbase(int d, int k)
{
    double *entree, *sortie;
    entree = new double[sizeof(double)*d*k];
    sortie = new double[sizeof(double)*d*k];

    gsl_matrix_view Tee;
    gsl_matrix* Te;
    gsl_matrix_view Ts;

    gsl_matrix* P;

    Tee = gsl_matrix_view_array(entree, k, d);
    Ts = gsl_matrix_view_array(sortie, k, d);

    P = gsl_matrix_calloc(d,d);
    Te = gsl_matrix_calloc(k,d);

    int i,j,m;
    gsl_vector_view colonne,u;
    gsl_vector *v,*p;
    double norme;
    v = gsl_vector_alloc(d);
    p = gsl_vector_alloc(d);

    for(j=0; j < k; j++)
    {
        for(i=0; i < d; i++)
        {
            entree[i*d + j] = 1*(i == j);
        }
    }

    for(i = 0; i < k; i++)
    {
        for(j = 0; j < d; j++)
        {
            gsl_matrix_set(Te,i,j,gsl_matrix_get(&Tee.matrix,i,j));
        }
    }

    for(j = 0; j < d; j++)
    {
        colonne = gsl_matrix_column(P, j);
        genunit(d, &colonne.vector);
        gsl_vector_memcpy(v, &colonne.vector);
        for(m = 0; m < j; m++)
        {
            u = gsl_matrix_column(P, m);
            proj(d, &u.vector, v, p);
            gsl_vector_sub(&colonne.vector, p);
            norme = 1.0/gsl_blas_dnrm2(&colonne.vector);
            gsl_vector_scale(&colonne.vector, norme);
        }

    }
/*    cout << endl;

    for(i = 0; i < k; i++)
    {
        for(j = 0; j < d; j++)
        {
            cout << gsl_matrix_get(Te,i,j) << "\t";
        }
        cout << endl;
    }
    cout << endl;

    for(i = 0; i < d; i++)
    {
        for(j = 0; j < d; j++)
        {
            cout << gsl_matrix_get(P,i,j) << "\t";
        }
        cout << endl;
    }
    cout << endl;*/

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, Te, P, 0.0, &Ts.matrix);// Ts = Te * P

/*    for(i = 0; i < k; i++)
    {
        for(j = 0; j < d; j++)
        {
            cout << gsl_matrix_get(&Ts.matrix,i,j) << "\t";
        }
        cout << endl;
    }
    cout << endl;*/

    delete entree;

    return sortie;

}

double fusion(Donnees* entree, Donnees* sortie)
{
    int x,y,d,k,n,N;
    gsl_vector_view vx,vy,ux,uy;//points x,y pour les 2 objets
    gsl_vector *v,*u;//vecteurs y-x
    double dv,du;//longeurs de y-x
    double *Tv,*Tu;
    d = entree->d;
    k = sortie->d;
    n = entree->n;
    Tv = entree->T;
    Tu = sortie->T;
    v = gsl_vector_calloc(d);
    u = gsl_vector_calloc(k);

    N = 0;

    for(x = 0; x < n; x++)
    {
        vx = gsl_vector_view_array(Tv + x*d, d);
        ux = gsl_vector_view_array(Tu + x*k, k);
        for(y = x+1; y < n; y++)
        {
            vy = gsl_vector_view_array(Tv + y*d, d);
            uy = gsl_vector_view_array(Tu + y*k, k);

            gsl_vector_memcpy(v, &vy.vector);
            gsl_vector_sub(v, &vx.vector);
            dv = gsl_blas_dnrm2(v);

            gsl_vector_memcpy(u, &uy.vector);
            gsl_vector_sub(u, &ux.vector);
            du = gsl_blas_dnrm2(u);

            if(dv && not(du))
            {
                N++;
            }
        }
    }
    return 1.0/(1.0+N);
}

double distances_aretes(Donnees* entree, Donnees* sortie)
{
    double e,em;
    int i,x,y,d,k,a,m;
    gsl_vector_view vx,vy,ux,uy;//points x,y pour les 2 objets
    gsl_vector *v,*u;//vecteurs y-x
    double dv,du;//longeurs de y-x
    double* Tv;
    double* Tu;
    double** H;
    d = entree->d;
    k = sortie->d;
    Tv = entree->T;
    Tu = sortie->T;
    a = entree->a;
    H = entree->H;
    v = gsl_vector_calloc(d);
    u = gsl_vector_calloc(k);

    em = 0;
    m = 0;

    for(i = 0; i < a; i++)
    {
        if(H[i][0] == 2)
        {
            x = H[i][1];
            y = H[i][2];

            vx = gsl_vector_view_array(Tv + x*d, d);
            ux = gsl_vector_view_array(Tu + x*k, k);

            vy = gsl_vector_view_array(Tv + y*d, d);
            uy = gsl_vector_view_array(Tu + y*k, k);

            gsl_vector_memcpy(v, &vy.vector);
            gsl_vector_sub(v, &vx.vector);
            dv = gsl_blas_dnrm2(v);

            gsl_vector_memcpy(u, &uy.vector);
            gsl_vector_sub(u, &ux.vector);
            du = gsl_blas_dnrm2(u);

            //cout << x << "\t" << y << "\t" << (double)(du-dv)/dv << endl;
            e = 0;
            if(du <= dv)
            {
                if(dv)
                {
                    e = du/dv;
                }
            }
            else
            {
                if(du)
                {
                    e = dv/du;
                }
            }
            em = (em*m+e)/(m+1.0);
            m++;
        }
    }
    return em;
}

double surfaces_aretes(Donnees* entree, Donnees* sortie)
{
    double e,em;
    int i,x,y,z,d,k,a,m;
    gsl_vector_view vx,vy,vz,ux,uy,uz;
    gsl_vector *vY,*uY;//vecteur y-x
    gsl_vector *vZ,*uZ;//vecteur z-x
    double pv,pu;//(y-x|z-x)
    double dvY,dvZ,duY,duZ;//||y-x||,||z-x||
    double sv,su;//surfaces xyz
    double* Tv;
    double* Tu;
    double** H;
    d = entree->d;
    k = sortie->d;
    Tv = entree->T;
    Tu = sortie->T;
    a = entree->a;
    H = entree->H;
    vY = gsl_vector_calloc(d);
    uY = gsl_vector_calloc(k);
    vZ = gsl_vector_calloc(d);
    uZ = gsl_vector_calloc(k);

    em = 0;
    m = 0;

    for(i = 0; i < a; i++)
    {
        if(H[i][0] == 3)
        {
            x = H[i][1];
            y = H[i][2];
            z = H[i][3];

            vx = gsl_vector_view_array(Tv + x*d, d);
            ux = gsl_vector_view_array(Tu + x*k, k);

            vy = gsl_vector_view_array(Tv + y*d, d);
            uy = gsl_vector_view_array(Tu + y*k, k);

            vz = gsl_vector_view_array(Tv + z*d, d);
            uz = gsl_vector_view_array(Tu + z*k, k);

            gsl_vector_memcpy(vY, &vy.vector);
            gsl_vector_sub(vY, &vx.vector);
            dvY = gsl_blas_dnrm2(vY);

            gsl_vector_memcpy(uY, &uy.vector);
            gsl_vector_sub(uY, &ux.vector);
            duY = gsl_blas_dnrm2(uY);

            gsl_vector_memcpy(vZ, &vz.vector);
            gsl_vector_sub(vZ, &vx.vector);
            dvZ = gsl_blas_dnrm2(vZ);

            gsl_vector_memcpy(uZ, &uz.vector);
            gsl_vector_sub(uZ, &ux.vector);
            duZ = gsl_blas_dnrm2(uZ);

            gsl_blas_ddot(vY, vZ, &pv);
            sv = dvY*dvZ*dvY*dvZ-pv*pv;//sqrt(...)*0.5

            gsl_blas_ddot(uY, uZ, &pu);
            su = duY*duZ*duY*duZ-pu*pu;

            //cout << x << "\t" << y << "\t" << z << "\t" << (su-sv)/sv << endl;
            if(su > 0 && sv > 0)
            {
                if(su <= sv)
                {
                    e = sqrt(su/sv);
                }
                else
                {
                    e = sqrt(sv/su);
                }
            }
            else
            {
                e = 0;
            }
            em = (em*m+e)/(m+1.0);
            m++;
        }
    }
    return em;
}

double volumes_aretes(Donnees* entree, Donnees* sortie)
{
    double e,em;
    int i,x,y,z,w,d,k,a,m;
    gsl_vector_view vx,vy,vz,vw,ux,uy,uz,uw;
    gsl_vector *vY,*uY;//vecteur y-x
    gsl_vector *vZ,*uZ;//vecteur z-x
    gsl_vector *vW,*uW;//vecteur w-x
    double dvY,dvZ,dvW;
    double pvY,pvZ,pvW;
    double duY,duZ,duW;
    double puY,puZ,puW;
    double vv,vu;
    double *Tv,*Tu;
    double** H;
    d = entree->d;
    k = sortie->d;
    Tv = entree->T;
    Tu = sortie->T;
    a = entree->a;
    H = entree->H;
    vY = gsl_vector_calloc(d);
    uY = gsl_vector_calloc(k);
    vZ = gsl_vector_calloc(d);
    uZ = gsl_vector_calloc(k);
    vW = gsl_vector_calloc(d);
    uW = gsl_vector_calloc(k);

    em = 0;
    m = 0;

    for(i = 0; i < a; i++)
    {
        if(H[i][0] == 4)
        {
            x = H[i][1];
            y = H[i][2];
            z = H[i][3];
            w = H[i][4];

            vx = gsl_vector_view_array(Tv + x*d, d);
            ux = gsl_vector_view_array(Tu + x*k, k);

            vy = gsl_vector_view_array(Tv + y*d, d);
            uy = gsl_vector_view_array(Tu + y*k, k);

            vz = gsl_vector_view_array(Tv + z*d, d);
            uz = gsl_vector_view_array(Tu + z*k, k);

            vw = gsl_vector_view_array(Tv + w*d, d);
            uw = gsl_vector_view_array(Tu + w*k, k);

            gsl_vector_memcpy(vY, &vy.vector);
            gsl_vector_sub(vY, &vx.vector);
            dvY = gsl_blas_dnrm2(vY);

            gsl_vector_memcpy(uY, &uy.vector);
            gsl_vector_sub(uY, &ux.vector);
            duY = gsl_blas_dnrm2(uY);

            gsl_vector_memcpy(vZ, &vz.vector);
            gsl_vector_sub(vZ, &vx.vector);
            dvZ = gsl_blas_dnrm2(vZ);

            gsl_vector_memcpy(uZ, &uz.vector);
            gsl_vector_sub(uZ, &ux.vector);
            duZ = gsl_blas_dnrm2(uZ);

            gsl_vector_memcpy(vW, &vw.vector);
            gsl_vector_sub(vW, &vx.vector);
            dvW = gsl_blas_dnrm2(vW);

            gsl_vector_memcpy(uW, &uw.vector);
            gsl_vector_sub(uW, &ux.vector);
            duW = gsl_blas_dnrm2(uW);

            gsl_blas_ddot(vY, vZ, &pvW);
            gsl_blas_ddot(vZ, vW, &pvY);
            gsl_blas_ddot(vY, vW, &pvZ);

            gsl_blas_ddot(uY, uZ, &puW);
            gsl_blas_ddot(uZ, uW, &puY);
            gsl_blas_ddot(uY, uW, &puZ);

            vv = dvY*dvZ*dvW*dvY*dvZ*dvW
                 - dvY*dvY*pvY*pvY
                 - dvZ*dvZ*pvZ*pvZ
                 - dvW*dvW*pvW*pvW
                 + 2*pvY*pvZ*pvW;//sqrt(...)/6.0

            vu = duY*duZ*duW*duY*duZ*duW
                 - duY*duY*puY*puY
                 - duZ*duZ*puZ*puZ
                 - duW*duW*puW*puW
                 + 2*puY*puZ*puW;

            //cout << x << "\t" << y << "\t" << z << "\t" << w << "\t" << (vu-vv)/vv << endl;
            if(vu > 0 && vv > 0)
            {
                if(vu <= vv)
                {
                    e = sqrt(vu/vv);
                }
                else
                {
                    e = sqrt(vv/vu);
                }
            }
            else
            {
                e = 0;
            }
            em = (em*m+e)/(m+1.0);
            m++;
        }
    }
    return em;
}

double* GetPoint(Donnees* entree, int i)
{
    int d(entree->d);
    double* T(entree->T);
    return GetPoint(T, d, i);
}

double* GetPoint(double* T, int d, int i)
{
    double* p;
    p = new double[sizeof(double)*d];
    for(int m(0); m < d; m++)
    {
        p[m]= T[i*d + m];
    }
    return p;
}

void SetPoint(Donnees* entree, int i, double* p)
{
    int d(entree->d);
    double* T(entree->T);
    SetPoint(T, d, i, p);
}

void SetPoint(double* T, int d, int i, double* p)
{
    for(int m(0); m < d; m++)
    {
        T[i*d+m] = p[m];
    }
}

double* Copie(double* T, int d, int n)
{
    double* copie;
    copie = new double[sizeof(double)*n*d];
    for (int i(0); i < n; i++)
    {
        for (int j(0); j < d; j++)
        {
            copie[i*d+j]=T[i*d+j];
        }
    }
    return copie;
}

double* Copie(double* p, int d)
{
    double* copie;
    copie = new double[sizeof(double)*d];
    for (int i(0); i < d; i++)
    {
        copie[i] = p[i];
    }
    return copie;
}

double* Tronquer(double* T, int d, int k, int n)
{
    double* copie;
    copie = new double[sizeof(double)*n*k];
    for (int i(0); i < n; i++)
    {
        for(int j(0); j < k; j++)
        {
            copie[i*k+j] = T[i*d+j];
        }
    }
    return copie;
}

double degres2rad(int val)
{
    return M_PI*val/180.;
}

double* normer(int d, double* p)
{
    double val(norme_vect(d,p));
    double* q(Copie(p,d));
    if(val)
    {
        for(int i(0); i < d; i++)
        {
            q[i] /= val;
        }
    }
    return q;
}

double angle(int d, double* p, double* q)
{
    return acos(produit_scalaire_vect(d,normer(d,p),normer(d,q)));
}

double* vecteur_nul(int d)
{
    double* r;
    r = new double[sizeof(double)*d];
    for(int i(0); i < d; i++)
    {
        r[i] = 0;
    }
    return r;
}

double* somme_vect(int d, double* p, double* q)
{
    double* r;
    r = new double[sizeof(double)*d];
    for(int i(0); i < d; i++)
    {
        r[i] = p[i]+q[i];
    }
    return r;
}

double* produit_externe_vect(int d, double* p, double a)
{
    double* r;
    r = new double[sizeof(double)*d];
    for(int i(0); i < d; i++)
    {
        r[i] = a*p[i];
    }
    return r;
}

/*double* produit_interne_vect(int d, double* p, double* q)
{

}*/

double produit_scalaire_vect(int d, double* p, double* q)
{
    double val(0);
    for(int i(0); i < d; i++)
    {
        val += p[i]*q[i];
    }
    return val;
}

double norme_vect(int d, double* p)
{
    return sqrt(produit_scalaire_vect(d,p,p));
}

double distance_vect(int d, double* p, double* q)
{
    return norme_vect(d,somme_vect(d,p,produit_externe_vect(d,q,-1)));
}
