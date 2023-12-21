#ifndef TILESET_H
#define TILESET_H

class Tileset {
public:
    Tileset(int id);
    Tileset(int id, unsigned int nombre, char* traversable = 0, const char* image = 0);
    virtual ~Tileset();
    int GetId();
    void SetId(int val);
    unsigned int GetNombre() const;
    void SetNombre(unsigned int val);
    char GetTraversable(unsigned int id) const;
    void SetTraversable(char val, unsigned int id);
    const char* GetImage(unsigned int id) const;
    void SetImage(const char* val, unsigned int id);
    // char GetImage(unsigned int id) const;
    // void SetImage(char val, unsigned int id);

    void Ecrire(char* data) const;
    void Lire(int& i, const char* data);
    unsigned int TailleD() const;
    // char* EcrireD(char* data, unsigned int taille = 2048) const;
    char* EcrireD(char* data) const;
    const char* LireD(const char* data);
protected:
private:
    int m_Id;
    unsigned int m_Nombre;
    char* m_Traversable;
    char* m_Image; //images stockées consécutivement en 1D
};

#endif // TILESET_H
