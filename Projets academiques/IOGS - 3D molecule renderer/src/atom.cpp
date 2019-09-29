#include "atom.h"

using namespace Eigen;

Atom::Atom(int type, Vector3f center, float length)
{
    _type = type;
    _radius = 1.0f;
    _length = length;
    _center = center;
    updateTransformation(); // _transformation is initialized

    switch(type)
    {
        case A_H : //radius 0.5f, white
        setRadius(0.5f);
        _color = Vector3f(1.0f,1.0f,1.0f);
        break;
        case A_O : //red
        _color = Vector3f(1.0f,0.0f,0.0f);
        break;
        case A_C : //gray
        default :
        _color = Vector3f(0.5f,0.5f,0.5f);
        break;
    }
}

Atom::~Atom()
{

}

void Atom::updateTransformation()
{
    _transformation = Scaling(_length)*(Affine3f)Translation3f(_center)*Scaling(1/_length)*Scaling(_radius);
}

void Atom::setRadius(float val)
{
    _radius = val;
    updateTransformation();
}

void Atom::setCenter(Vector3f val)
{
    _center = val;
    updateTransformation();
}

void Atom::setLength(float length)
{
    _length = length;
    updateTransformation();
}
