#ifndef _ATOM_H
#define _ATOM_H

#include "sphere2.h"

#define A_H 1
#define A_C 6
#define A_O 8

class Atom
{
public:
    Atom(int type, Eigen::Vector3f center = Eigen::Vector3f(0,0,0), float length = 1.0f);
    ~Atom();
    int type() const { return _type; }
    Eigen::Affine3f transformation() const { return _transformation; }
    void updateTransformation();
    float radius() const { return _radius; }
    void setRadius(float val);
    void setCenter(Eigen::Vector3f val);
    Eigen::Vector3f color() const { return _color; }
    void setLength(float val);

private:
    int _type;
    Eigen::Affine3f _transformation;
    float _radius;
    Eigen::Vector3f _center;
    Eigen::Vector3f _color;
    float _length; //length of edges between atoms
};

#endif
