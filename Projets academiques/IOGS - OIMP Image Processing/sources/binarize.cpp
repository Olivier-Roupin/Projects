#include "binarize.h"

Binarize::Binarize(float threshold)
    : _threshold(threshold)
{

}

void Binarize::setThreshold(float threshold)
{
    _threshold = threshold;
}

float Binarize::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image &img) const
{
    return (img.getPixel(i, j, c) < _threshold) ? 0 : 1;
}

