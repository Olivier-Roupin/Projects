#ifndef TILESETS_H_INCLUDED
#define TILESETS_H_INCLUDED

for (i = 0; i < NOMBRE_TILESETS+1; ++i)
    tilesets[i] = 0;

#ifdef PRINTIN
    nombre = 4;
    printf("Tilesets : %d\n", nombre);
#endif //PRINTIN
    tilesets[1] = new Tileset(1,6);
    tilesets[1]->SetImage("_",0); tilesets[1]->SetTraversable(1,0);
    tilesets[1]->SetImage("O",1); tilesets[1]->SetTraversable(0,1);
    tilesets[1]->SetImage("A",2); tilesets[1]->SetTraversable(0,2);
    tilesets[1]->SetImage("H",3); tilesets[1]->SetTraversable(0,3);
    tilesets[1]->SetImage("P",4); tilesets[1]->SetTraversable(0,4);
    tilesets[1]->SetImage("*",5); tilesets[1]->SetTraversable(1,5);
    tilesets[2] = new Tileset(2,4);
    tilesets[2]->SetImage("_",0); tilesets[2]->SetTraversable(1,0);
    tilesets[2]->SetImage("~",1); tilesets[2]->SetTraversable(0,1);
    tilesets[2]->SetImage("*",2); tilesets[2]->SetTraversable(1,2);
    tilesets[2]->SetImage("M",3); tilesets[2]->SetTraversable(0,3);
    tilesets[3] = new Tileset(3,7);
    tilesets[3]->SetImage(",",0); tilesets[3]->SetTraversable(1,0);
    tilesets[3]->SetImage("O",1); tilesets[3]->SetTraversable(0,1);
    tilesets[3]->SetImage("A",2); tilesets[3]->SetTraversable(0,2);
    tilesets[3]->SetImage("H",3); tilesets[3]->SetTraversable(0,3);
    tilesets[3]->SetImage("P",4); tilesets[3]->SetTraversable(0,4);
    tilesets[3]->SetImage("%",5); tilesets[3]->SetTraversable(1,5);
    tilesets[3]->SetImage("a",6); tilesets[3]->SetTraversable(1,6);
    tilesets[4] = new Tileset(4,7);
    tilesets[4]->SetImage(".",0); tilesets[4]->SetTraversable(1,0);
    tilesets[4]->SetImage("p",1); tilesets[4]->SetTraversable(0,1);
    tilesets[4]->SetImage("B",2); tilesets[4]->SetTraversable(0,2);
    tilesets[4]->SetImage("H",3); tilesets[4]->SetTraversable(0,3);
    tilesets[4]->SetImage("P",4); tilesets[4]->SetTraversable(0,4);
    tilesets[4]->SetImage("%",5); tilesets[4]->SetTraversable(1,5);
    tilesets[4]->SetImage("b",6); tilesets[4]->SetTraversable(1,6);
#ifdef PRINTIN
    for (i = 1; i < nombre+1; ++i) {
        tilesets[i]->Ecrire(str);
        printf("%s\\0", str);
    }
#endif //PRINTIN
#ifdef PRINTIN
    printf("\n");
#endif //PRINTIN

#endif // TILESETS_H_INCLUDED
