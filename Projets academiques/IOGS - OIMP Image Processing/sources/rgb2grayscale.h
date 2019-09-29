#ifndef RGB2GRAYSCALE_H
#define RGB2GRAYSCALE_H

#include "operation.h"

class RGB2GrayScale : public Operation
{
public:
    RGB2GrayScale();
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;
    virtual void resizeOutputImage(const Image& in, Image &out) const;
};

#endif // RGB2GRAYSCALE_H
