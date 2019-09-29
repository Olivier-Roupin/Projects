#include "maxcut.h"

using namespace std;

/*Donnees* maxcut2(Donnees* entree, int k)
{
    int d(entree->d);
    int n(entree->n);
    double* T;
    //double* T0;
    T = Copie(entree->T,d,n);

    Donnees* sortie;
    sortie = new Donnees();
    sortie->d = k;
    sortie->n = n;
    sortie->a = entree->a;
    sortie->H = entree->H;

    double* Tt;
    double* Ttmax;
    double ftmax,ft,norm;
    double* normes;
    gsl_vector_view vect;

    normes = new double[sizeof(double)*n];
    Tt = new double[sizeof(double)*n*d];
    Ttmax = new double[sizeof(double)*n*d];

    int i,m;
    double theta;

    double* W;

    W = poids(n,entree->a,entree->H);

    //on norme tous les vecteurs
    for(i = 0; i < n; i++)
    {
        vect = gsl_vector_view_array(T + i*d, d);
        normes[i] = gsl_blas_dnrm2(&vect.vector);
        if(normes[i])
        {
            gsl_blas_dscal(1.0/normes[i], &vect.vector);
        }
    }

    //T0 = Copie(T,d,n);

    cout << "dim : " << d << " ; f = " << f(d,n,T,W) << endl;
    for(m = d; m > k; m--)//m va de la dimension de départ à la dimension d'arrivée
    {
        ftmax = -1e9;
        ft = 0;
        for(theta = -M_PI*0.5; theta < M_PI*0.5; theta += 0.01)//on veut theta tel que f(theta)(v1,..,vn) maximal
        {
            Tt = Copie(T,m,n);
            for(i = 0; i < n; i++)//pour chaque point/vecteur vi unitaire
            {
                //on note (vi,m-1,vi,m)=(ti*cos(gammai),ti*sin(gammai))
                //        ai(theta) = vi|(ti*cos(gammai-theta))
                //        ui(theta) = ai(theta)/||ai(theta)||
                if(normes[i])
                {
                    Tt[i*m + m-2] = Tt[i*m + m-2]*cos(theta)+Tt[i*m + m-1]*sin(theta); //ui[m-2] = ui[m-2]*cos(theta)+ui[m-1]*sin(theta); //ti*cos(gammai-theta)
                    Tt[i*m + m-1] = 0; //ui[m-1] = 0;

                    vect = gsl_vector_view_array(Tt + i*m, m);//ui
                    norm = gsl_blas_dnrm2(&vect.vector);
                    gsl_blas_dscal(1.0/norm, &vect.vector);//on norme ui
                }
            }
            ft = f(m,n,Tt,W);
            if(ft > ftmax)
            {
                delete Ttmax;
                Ttmax = Tt;//Copie(Tt,m,n);
                ftmax = ft;
            }
            //on choisit le theta tel que ftheta est maximale
            //u1(theta)...un(theta) sont les nouveaux vecteurs
        }
        cout << "dim : " << m-1 << " ; f = " << ftmax << endl;
        T = Tronquer(Ttmax,m,m-1,n);
    }

    //angles(d,k,n,T0,T);
    for(i = 0; i < n; i++)
    {
        vect = gsl_vector_view_array(T + i*k, k);
        gsl_blas_dscal(normes[i], &vect.vector);
    }
    sortie->T = T;
    return sortie;
}*/

Donnees* maxcut(Donnees* entree, int k)
{
    int d(entree->d);
    int n(entree->n);

    Donnees* sortie;
    sortie = new Donnees();
    sortie->d = k;
    sortie->n = n;
    sortie->a = entree->a;
    sortie->H = entree->H;

    int i,m;
    double *T,*Tt,*Ttmax,*W,*normes;
    double f0,ft,ftmax,norm,theta;
    gsl_vector_view vect;

    T = Copie(entree->T,d,n);
    Tt = new double[sizeof(double)*n*d]; //on initialise Tt pour pouvoir écrire "delete Tt"
    Ttmax = new double[sizeof(double)*n*d]; //on initialise Ttmax pour pouvoir écrire "delete Ttmax"
    W = poids(n,entree->a,entree->H);
    normes = new double[sizeof(double)*n];

    //on norme tous les vecteurs
    for(i = 0; i < n; i++)
    {
        vect = gsl_vector_view_array(T + i*d, d);
        normes[i] = gsl_blas_dnrm2(&vect.vector);
        if(normes[i])
        {
            gsl_blas_dscal(1.0/normes[i], &vect.vector);
        }
    }

    f0 = f(d,n,T,W);

    cout << "dim : " << d << " ; f = " << f0 << endl;
    for(m = d; m > k; m--)//m va de la dimension de départ à la dimension d'arrivée
    {
        ftmax = -f0-1e9;
        ft = 0;
        for(theta = -M_PI*0.5; theta < M_PI*0.5; theta += DTHETA)
        {
            delete Tt;
            Tt = Copie(T,m,n);
            for(i = 0; i < n; i++)//pour chaque point/vecteur vi unitaire, (vi[m-2],vi[m-1])=(t*cos(gamma),t*sin(gamma))
            {
                if(normes[i])
                {
                    Tt[i*m + m-2] = Tt[i*m + m-2]*cos(theta)+Tt[i*m + m-1]*sin(theta);//ui[m-2] = vi[m-2]*cos(theta)+vi[m-1]*sin(theta) = t*cos(gamma-theta)
                    Tt[i*m + m-1] = 0;//ui[m-1] = 0;

                    vect = gsl_vector_view_array(Tt + i*m, m);//ui
                    norm = gsl_blas_dnrm2(&vect.vector);
                    gsl_blas_dscal(1.0/norm, &vect.vector);//on norme ui
                }
            }
            ft = f(m,n,Tt,W);
            if(fabs(ft-f0) < fabs(ftmax-f0))//on veut theta tel que f(theta)(v1,..,vn) proche de f0
            {
                delete Ttmax;
                Ttmax = Copie(Tt,m,n);
                ftmax = ft;
            }
        }
        cout << "dim : " << m-1 << " ; f = " << ftmax <<endl;
        delete T;
        T = Tronquer(Ttmax,m,m-1,n);//u1(theta)...un(theta) sont les nouveaux vecteurs
    }
    for(i = 0; i < n; i++)
    {
        vect = gsl_vector_view_array(T + i*k, k);
        gsl_blas_dscal(normes[i], &vect.vector);
    }
    sortie->T = T;
    return sortie;
}

/*double f(int d, int n, double* T, double* W)//np,nq == 0 ou 1
{
    double val(0);
    gsl_vector_view vp,vq;
    gsl_vector* vdif;
    double dist,angl,np,nq;
    int p,q;

    vdif = gsl_vector_calloc(d);

    for(p = 0; p < n; p++)
    {
        vp = gsl_vector_view_array(T + p*d, d);
        np = gsl_blas_dnrm2(&vp.vector);
        if(np)
        {
            for(q = p+1; q < n; q++)
            {
                vq = gsl_vector_view_array(T + q*d, d);
                nq = gsl_blas_dnrm2(&vq.vector);
                if(nq)
                {
                    gsl_vector_memcpy(vdif, &vp.vector);
                    gsl_vector_sub(vdif, &vq.vector);
                    dist = gsl_blas_dnrm2(vdif);
                    if(dist)
                    {
                        gsl_blas_ddot(&vp.vector, &vq.vector, &angl);
                        if(angl < 1 && angl > -1)
                        {
                            angl = acos(angl);
                        }
                        else if(angl <= -1)
                        {
                            angl = 0;
                        }
                        else
                        {
                            angl = M_PI;
                        }
                        val += W[n*p+q]*dist*angl;
                        //cout << val << endl;
                    }
                }
            }
        }
    }
    return val;
}*/

double f(int d, int n, double* T, double* W)//np,nq == 0 ou 1
{
    double val(0);
    gsl_vector_view vp,vq;
    double prod;
    int p,q;
    for(p = 0; p < n; p++)
    {
        vp = gsl_vector_view_array(T + p*d, d);
        if(gsl_blas_dnrm2(&vp.vector))
        {
            for(q = p+1; q < n; q++)
            {
                vq = gsl_vector_view_array(T + q*d, d);
                if(gsl_blas_dnrm2(&vq.vector))
                {
                    gsl_blas_ddot(&vp.vector,&vq.vector,&prod);
                    val += W[n*p+q]*(1.0-prod);
                    //cout << val << endl;
                }
            }
        }
    }
    return val;
}

double* poids(int n, int a, double** H)
{
    double* W;
    int i,x,y,z,w;

    W = new double[sizeof(double)*n*n];

    for(x = 0; x < n; x++)
    {
        for(y = 0; y < n; y++)
        {
            W[x*n + y] = POIDSBASE;
        }
    }
    for(i = 0; i < a; i++)
    {
        switch((int)H[i][0])
        {
        case 2 :
            x = H[i][1];
            y = H[i][2];

            W[x*n + y] += POIDSDISTANCE;
            W[y*n + x] += POIDSDISTANCE;
            break;
        case 3 :
            x = H[i][1];
            y = H[i][2];
            z = H[i][3];

            W[x*n + y] += POIDSSURFACE;
            W[y*n + x] += POIDSSURFACE;

            W[x*n + z] += POIDSSURFACE;
            W[z*n + x] += POIDSSURFACE;

            W[y*n + z] += POIDSSURFACE;
            W[z*n + y] += POIDSSURFACE;
            break;
        case 4 :
            x = H[i][1];
            y = H[i][2];
            z = H[i][3];
            w = H[i][4];

            W[x*n + y] += POIDSVOLUME;
            W[y*n + x] += POIDSVOLUME;

            W[x*n + z] += POIDSVOLUME;
            W[z*n + x] += POIDSVOLUME;

            W[y*n + z] += POIDSVOLUME;
            W[z*n + y] += POIDSVOLUME;

            W[x*n + w] += POIDSVOLUME;
            W[w*n + x] += POIDSVOLUME;

            W[y*n + w] += POIDSVOLUME;
            W[w*n + y] += POIDSVOLUME;

            W[z*n + w] += POIDSVOLUME;
            W[w*n + z] += POIDSVOLUME;
            break;
        }
    }
    return W;
}

void angles(int d,int k, int n, double* Tv, double* Tu)
{
    gsl_vector_view vp,vq,up,uq;
    double anglv,anglu;
    int p,q;

    for(p = 0; p < n; p++)
    {
        vp = gsl_vector_view_array(Tv + p*d, d);
        up = gsl_vector_view_array(Tu + p*k, k);
        if(gsl_blas_dnrm2(&vp.vector) && gsl_blas_dnrm2(&up.vector))
        {
            for(q = p+1; q < n; q++)
            {
                vq = gsl_vector_view_array(Tv + q*d, d);
                uq = gsl_vector_view_array(Tu + q*k, k);

                if(gsl_blas_dnrm2(&vq.vector) && gsl_blas_dnrm2(&uq.vector))
                {
                    gsl_blas_ddot(&vp.vector, &vq.vector, &anglv);
                    gsl_blas_ddot(&up.vector, &uq.vector, &anglu);

                    if(anglv < 1 && anglv > -1)
                    {
                        anglv = acos(anglv);
                    }
                    else if(anglv <= -1)
                    {
                        anglv = 0;
                    }
                    else
                    {
                        anglv = M_PI;
                    }
                    if(anglu < 1 && anglu > -1)
                    {
                        anglu = acos(anglu);
                    }
                    else if(anglu <= -1)
                    {
                        anglu = 0;
                    }
                    else
                    {
                        anglu = M_PI;
                    }
                    //if (fabs(angle(d,p1,q1)- angle(d,p2,q2)) > 1e-1)
                    //{
                    cout << abs(anglv - anglu) <<"  ";
                    if (not(q%5))
                    {
                        cout << endl;
                    }
                    //}
                }
            }
        }
    }
}
