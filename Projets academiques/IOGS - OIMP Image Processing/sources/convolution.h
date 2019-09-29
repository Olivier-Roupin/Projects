#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "operation.h"

class Convolution : public Operation
{
public:
    Convolution(Image* _masque);

protected:
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;

private:
    Image* _masque;
};

#endif // CONVOLUTION_H
