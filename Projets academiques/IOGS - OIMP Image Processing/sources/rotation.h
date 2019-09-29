#ifndef ROTATION_H
#define ROTATION_H

#include "operation.h"
#include <cmath>

class Rotation : public Operation
{
public:
    Rotation(float theta=0);
    void setTheta(float theta);

protected:
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;
    virtual void resizeOutputImage(const Image& in, Image &out) const;

private:
    float _theta; // angle of rotation in degree
    mutable int _offset_x;
    mutable int _offset_y;
};

#endif // ROTATION_H
