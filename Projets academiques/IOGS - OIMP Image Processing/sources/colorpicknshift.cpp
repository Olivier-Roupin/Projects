#include "colorpicknshift.h"

ColorPicknShift::ColorPicknShift(float beta, float delta, float alpha)
    : ColorShift(alpha), _beta(beta), _delta(delta)
{

}

void ColorPicknShift::setDelta(float delta)
{
    _delta = delta;
}

void ColorPicknShift::setBeta(float beta)
{
    _beta = beta;
}

float ColorPicknShift::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const
{
    if(img.getType() == Image::RGB)
    {
        if(std::min(std::abs(360*img.getPixel(i,j,0)-_beta),std::abs(360-360*img.getPixel(i,j,0)+_beta))*2 <= _delta)
            return ColorShift::processPixel(i,j,c,img);
    }
    return img.getPixel(i,j,c);
}
