#ifndef ETALEMENT_H
#define ETALEMENT_H

#include "histogram.h"
#include "rgb2hsl.h"
#include "hsl2rgb.h"

class Etalement : public Operation
{
public:
    Etalement(const Histogram &histo);
    void process(const Image &in, Image &out) const;

protected:
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;

private:
    float _noir;
    float _blanc;
};

#endif // ETALEMENT_H
