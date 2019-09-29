#ifndef TILESET_H
#define TILESET_H

#include <string>

class Tileset
{
    public:
        Tileset(int id, int nombre = 0, int* traversable = 0, std::string* image = 0);
        virtual ~Tileset();
        int GetId();
        void SetId(int val);
        int GetNombre();
        void SetNombre(int val);
        int GetTraversable(int id) const;
        void SetTraversable(int val, int id);
        std::string GetImage(int id) const;
        void SetImage(std::string val, int id);
    protected:
    private:
        int m_Id;
        int m_Nombre;
        int* m_Traversable;
        std::string* m_Image;
};

#endif // TILESET_H
