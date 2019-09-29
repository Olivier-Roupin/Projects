#ifndef OBJETS_H_INCLUDED
#define OBJETS_H_INCLUDED

using namespace std;

for(int i = 0; i < NOMBRE_OBJETS+1; i++)
{
    objets[i] = 0;
}

flux.open("bdd/objets.txt");
if(flux)
{
    int nombre(0);

    string nom("");
    int type(0);
    int prix(0);
    string description("");

    int id_effet(0);
    bool illimite(0);

    int ine[NOMBRE_DONNEES_EQUIPABLE];

    flux >> nombre;

    for(int i(1); i < nombre+1; i++)
    {
        flux >> nom;
        flux >> type;
        flux >> prix;
        flux >> description;
        switch(type)
        {
        case OBJET:
        {
            objets[i] = new Objet(i,nom,type,prix,description);
            break;
        }
        case UTILISABLE:
        {
            flux >> illimite;
            flux >> id_effet;
            objets[i] = new Utilisable(i,nom,type,prix,description,illimite,effets[id_effet]);
            break;
        }
        case EQUIPABLE:
        case EQUIPABLE_ACCESSOIRE:
        case EQUIPABLE_ARME:
        case EQUIPABLE_ARMURE:
        case EQUIPABLE_BOUCLIER:
        case EQUIPABLE_CASQUE:
        {
            for(int n(0); n < NOMBRE_DONNEES_EQUIPABLE; n++)
            {
                flux >> ine[n];
            }
            objets[i] = new Equipable(i,nom,type,prix,description,\
                                      ine[0],ine[1],ine[2],\
                                      ine[3],ine[4],ine[5],\
                                      ine[6],ine[7],ine[8],\
                                      ine[9],ine[10],ine[11]);
            break;
        }
        }
    }
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

flux.close();

#endif // OBJETS_H_INCLUDED
