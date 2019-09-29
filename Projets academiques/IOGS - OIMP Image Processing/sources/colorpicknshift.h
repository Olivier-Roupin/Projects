#ifndef COLORPICKNSHIFT_H
#define COLORPICKNSHIFT_H

#include "colorshift.h"

class ColorPicknShift : public ColorShift
{
public:
    ColorPicknShift(float delta=0,float beta=0,float alpha=0);
    void setDelta(float delta);
    void setBeta(float beta);

protected:
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;

private:
    float _beta; // angle picked in degree
    float _delta; // angle tolerance in degree
};

#endif // COLORPICKNSHIFT_H
