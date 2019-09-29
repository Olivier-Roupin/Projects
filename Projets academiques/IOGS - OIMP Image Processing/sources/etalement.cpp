#include "etalement.h"

Etalement::Etalement(const Histogram &histo)
    : _noir(histo.getNoir()/255.0), _blanc(histo.getBlanc()/255.0)
{

}


float Etalement::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image &img) const
{
    if(img.getType() == Image::RGB && c == 2 || img.getType() == Image::GRAY_SCALE && c == 0)
    {
        if(img.getPixel(i,j,c) >= _blanc)
            return 1;
        return (img.getPixel(i,j,c)-_noir)/(_blanc-_noir);
    }
    return img.getPixel(i,j,c);
}

void Etalement::process(const Image &in, Image &out) const
{
    Image hsl, sht;
    RGB2HSL rgb2hsl;
    HSL2RGB hsl2rgb;

    rgb2hsl.process(in, hsl);
    Operation::process(hsl, sht);
    hsl2rgb.process(sht, out);
}
