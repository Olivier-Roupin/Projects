#ifndef HEROSS_H_INCLUDED
#define HEROSS_H_INCLUDED

using namespace std;

for(int i = 0; i < NOMBRE_HEROS+1; i++)
{
    heross[i] = 0;
}

flux.open("bdd/heros.txt");
if(flux)
{
    int nombre(0);
    string nom("");
    int in[NOMBRE_IN_HEROS];

    flux >> nombre;

    for(int i(1); i < nombre+1; i++)
    {
        flux >> nom;
        for(int n(0); n < NOMBRE_IN_HEROS; n++)
        {
            flux >> in[n];
        }
        heross[i] = new Heros(i,nom,in[IN_HEROS_VIE],in[IN_HEROS_MAGIE],\
                              in[IN_HEROS_VIEMAX],in[IN_HEROS_ATTAQUEP],in[IN_HEROS_DEFENSEP],\
                              in[IN_HEROS_MAGIEMAX],in[IN_HEROS_ATTAQUEM],in[IN_HEROS_DEFENSEM],\
                              in[IN_HEROS_VITESSE],in[IN_HEROS_PRECISION],in[IN_HEROS_ESQUIVE],\
                              in[IN_HEROS_STATUT],in[IN_HEROS_EXPERIENCE],in[IN_HEROS_NIVEAU],\
                              in[IN_HEROS_FORCE],in[IN_HEROS_INTELLIGENCE],in[IN_HEROS_AGILITE],in[IN_HEROS_RANG],\
                              objets[in[IN_HEROS_ID_MAINGAUCHE]],objets[in[IN_HEROS_ID_MAINDROITE]],objets[in[IN_HEROS_ID_TETE]],\
                              objets[in[IN_HEROS_ID_CORPS]],objets[in[IN_HEROS_ID_ACCESSOIRE1]],objets[in[IN_HEROS_ID_ACCESSOIRE2]]);
    }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

flux.close();

#endif // HEROSS_H_INCLUDED
