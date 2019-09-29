#ifndef HSL2RGB_H
#define HSL2RGB_H

#include "operation.h"
#include <cmath>

class HSL2RGB : public Operation
{
public:
    HSL2RGB();
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;
};

#endif // HSL2RGB_H
