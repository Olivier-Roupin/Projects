#ifndef COLORPICK_H
#define COLORPICK_H

#include "rgb2hsl.h"
#include "hsl2rgb.h"

class ColorPick : public Operation
{
public:
    ColorPick(float beta=0, float delta=0);
    void setBeta(float beta);
    void setDelta(float delta);
    void process(const Image &in, Image &out) const;

protected:
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;

private:
    float _beta; // angle picked in degree
    float _delta; // angle tolerance in degree
};

#endif // COLORPICK_H
