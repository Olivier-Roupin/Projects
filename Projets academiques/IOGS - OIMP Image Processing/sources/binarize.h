#ifndef BINARIZE_H
#define BINARIZE_H

#include "operation.h"

class Binarize : public Operation
{
public:
    Binarize(float threshold=0.5);
    void setThreshold(float threshold);

protected:
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;

private:
    float _threshold;

};

#endif // BINARIZE_H
