#ifndef EGALISATION_H
#define EGALISATION_H

#include "histogram.h"
#include "hsl2rgb.h"

class Egalisation : public Operation
{
public:
    Egalisation(const Histogram &histo);
    void process(const Image &in, Image &out) const;

protected:
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;

private:
    float _cdfinv[256];
};

#endif // EGALISATION_H
