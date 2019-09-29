#ifndef RGB2HSL_H
#define RGB2HSL_H

#include "operation.h"
#include <cmath>

class RGB2HSL : public Operation
{
public:
    RGB2HSL();
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;
};

#endif // RGB2HSL_H
