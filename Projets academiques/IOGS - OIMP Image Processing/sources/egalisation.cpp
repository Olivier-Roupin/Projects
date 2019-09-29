#include "egalisation.h"

Egalisation::Egalisation(const Histogram &histo)
{
    int somme(histo.getCDF(256));
    unsigned int k;
    for(k = 0; k < 256; k++)
        _cdfinv[k] = histo.getCDF(k)/(float)somme;
}


float Egalisation::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image &img) const
{
    if(img.getType() == Image::RGB && c == 2 || img.getType() == Image::GRAY_SCALE && c == 0)
        return _cdfinv[(int)(255*img.getPixel(i,j,c))];
    return img.getPixel(i,j,c);
}

void Egalisation::process(const Image &in, Image &out) const
{
    Image hsl, sht;
    RGB2HSL rgb2hsl;
    HSL2RGB hsl2rgb;

    rgb2hsl.process(in, hsl);
    Operation::process(hsl, sht);
    hsl2rgb.process(sht, out);
}
