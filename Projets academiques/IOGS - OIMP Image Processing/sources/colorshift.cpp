#include "colorshift.h"

ColorShift::ColorShift(float alpha)
    : _alpha(alpha)
{

}

void ColorShift::setAlpha(float alpha)
{
    _alpha = alpha;
}

float ColorShift::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const
{
    if(img.getType() == Image::RGB)
    {
        if(c)
            return img.getPixel(i,j,c);
        return std::fmod(img.getPixel(i,j,c)+_alpha/360.0+1.0,1);
    }
    return img.getPixel(i,j,0);
}

void ColorShift::process(const Image &in, Image &out) const
{
    Image hsl, sht;
    RGB2HSL rgb2hsl;
    HSL2RGB hsl2rgb;

    rgb2hsl.process(in, hsl);
    Operation::process(hsl, sht);
    hsl2rgb.process(sht, out);
}

