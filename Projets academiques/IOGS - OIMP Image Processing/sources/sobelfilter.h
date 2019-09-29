#ifndef SOBELFILTER_H
#define SOBELFILTER_H

#include "convolutionmask.h"
#include <cmath>

class SobelFilter : public Operation
{
public:
    SobelFilter();
    float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;
};

#endif // SOBELFILTER_H
