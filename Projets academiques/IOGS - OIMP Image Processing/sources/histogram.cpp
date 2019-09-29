#include "histogram.h"

Histogram::Histogram()
{
    unsigned int k;
    for(k = 0; k < 256; k++)
        _valeurs[k] = 0;
}

Histogram::Histogram(const Image &img)
{
    unsigned int k;
    for(k = 0; k < 256; k++)
        _valeurs[k] = 0;
    unsigned int i,j;
    RGB2HSL rgb2hsl;
    for(i = 0; i < img.getHeight(); i++)
        for(j = 0; j < img.getWidth(); j++)
            _valeurs[(int)(255*rgb2hsl.processPixel(i,j,2,img))]++;
}

int Histogram::getNoir() const
{
    unsigned int k;
    for(k = 0; k < 256; k++)
    {
        if(_valeurs[k])
            return k;
    }
    return 0;
}

int Histogram::getBlanc() const
{
    unsigned int k;
    for(k = 0; k < 256; k++)
    {
        if(_valeurs[255-k])
            return 255-k;
    }
    return 255;
}

int Histogram::getCDF(unsigned int i) const
{
    unsigned int k;
    int cdf(0);
    for(k = 0; k < i; k++)
        cdf += _valeurs[k];
    return cdf;
}

int Histogram::getMax() const
{
    unsigned int k;
    unsigned int max(0);
    for(k = 0; k < 256; k++)
    {
        if(_valeurs[k] > max)
            max = _valeurs[k];
    }
    return max;
}

void Histogram::save() const
{
    std::ofstream fs;
    unsigned int i, j;
    int max(getMax());
    fs.open("histo.pbm");
    if(!fs.is_open())
    {
        std::cerr << "Error : fail to open the file " << "histo.pbm" << std::endl;
        return;
    }

    fs << "P1" << std::endl;
    fs << 256 << " " << 256 << std::endl;
    for(i = 0; i < 256; i++)
    {
        for(j = 0; j < 256; j++)
            fs << (_valeurs[j]*256/max > 255-i) << " ";
        fs << std::endl;
    }

    fs.close();
}
