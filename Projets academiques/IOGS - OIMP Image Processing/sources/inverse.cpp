#include "inverse.h"

Inverse::Inverse()
{

}

float Inverse::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image &img) const
{
    return 1 - img.getPixel(i, j, c);
}

