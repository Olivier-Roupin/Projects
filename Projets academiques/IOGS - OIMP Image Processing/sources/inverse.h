#ifndef INVERSE_H
#define INVERSE_H

#include "operation.h"


class Inverse : public Operation
{
public:
    Inverse();

protected:
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;
};

#endif // INVERSE_H
