#include "colorpick.h"

ColorPick::ColorPick(float beta, float delta)
    : _beta(beta), _delta(delta)
{

}

void ColorPick::setBeta(float beta)
{
    _beta = beta;
}

void ColorPick::setDelta(float delta)
{
    _delta = delta;
}

float ColorPick::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const
{
    if(img.getType() == Image::RGB)
        return (std::min(std::abs(360*img.getPixel(i,j,0)-_beta),std::abs(360-360*img.getPixel(i,j,0)+_beta))*2 <= _delta)*img.getPixel(i,j,c);
    return 0;
}

void ColorPick::process(const Image &in, Image &out) const
{
    Image hsl,hsl2;
    RGB2HSL rgb2hsl;
    HSL2RGB hsl2rgb;

    rgb2hsl.process(in, hsl);
    Operation::process(hsl, hsl2);
    hsl2rgb.process(hsl2,out);
}

