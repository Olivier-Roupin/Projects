#ifndef MONSTRES_H_INCLUDED
#define MONSTRES_H_INCLUDED

using namespace std;

for(int i = 0; i < NOMBRE_MONSTRES+1; i++)
{
    monstres[i] = 0;
}

flux.open("bdd/monstres.txt");
if(flux)
{
    int nombre(0);
    string nom("");
    int in[NOMBRE_IN_MONSTRE];
    GroupeObjets* butin(0);
    GroupeObjets* objetporte(0);

    flux >> nombre;

    for(int i(1); i < nombre+1; i++)
    {
        flux >> nom;
        for(int n(0); n < NOMBRE_IN_MONSTRE; n++)
        {
            flux >> in[n];
        }
            butin = new GroupeObjets(objets[in[IN_MONSTRE_ID_BUTIN]]);
            objetporte = new GroupeObjets(objets[in[IN_MONSTRE_ID_OBJETPORTE]]);
            monstres[i] = new Monstre(i,nom,in[IN_MONSTRE_VIE],in[IN_MONSTRE_MAGIE],\
                              in[IN_MONSTRE_VIE],in[IN_MONSTRE_ATTAQUEP],in[IN_MONSTRE_DEFENSEP],\
                              in[IN_MONSTRE_MAGIE],in[IN_MONSTRE_ATTAQUEM],in[IN_MONSTRE_DEFENSEM],\
                              in[IN_MONSTRE_VITESSE], in[IN_MONSTRE_PRECISION],in[IN_MONSTRE_ESQUIVE],\
                              in[IN_MONSTRE_EXPERIENCE],in[IN_MONSTRE_NIVEAU],\
                              butin,objetporte,in[IN_MONSTRE_OR]);
            monstres[i]->SetScript(scripts[in[IN_MONSTRE_ID_SCRIPT]]);
    }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

flux.close();

#endif // MONSTRES_H_INCLUDED
