#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "operation.h"


class ConvolutionMask : public Operation
{
public:
    ConvolutionMask();
    void setMask(unsigned int w, unsigned int h, const std::vector<float>& mask);
    void normalizeMask();
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;

private:
    float maskValue(unsigned int i, unsigned int j) const;
    unsigned int _w, _h;
    std::vector<float> _mask;
};

#endif // CONVOLUTION_H
