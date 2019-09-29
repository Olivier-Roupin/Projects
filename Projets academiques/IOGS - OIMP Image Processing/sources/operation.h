#ifndef OPERATION_H
#define OPERATION_H

#include "image.h"

class Operation
{
public:
    virtual void process(const Image& in, Image& out) const;
    virtual ~Operation();
protected:
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const = 0;
    virtual void resizeOutputImage(const Image& in, Image &out) const;
};

#endif // OPERATION_H
