#ifndef COLORSHIFT_H
#define COLORSHIFT_H

#include "rgb2hsl.h"
#include "hsl2rgb.h"

class ColorShift : public Operation
{
public:
    ColorShift(float alpha=0);
    void setAlpha(float alpha);
    void process(const Image &in, Image &out) const;

protected:
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;

private:
    float _alpha; // angle of rotation in degree
};

#endif // COLORSHIFT_H
