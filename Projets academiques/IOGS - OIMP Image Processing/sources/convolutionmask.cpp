#include "convolutionmask.h"
#include <vector>
#include <cmath>

ConvolutionMask::ConvolutionMask()
{
    std::vector<float> mask;
    mask.push_back(-1);
    mask.push_back(0);
    mask.push_back(1);
    mask.push_back(-1);
    mask.push_back(0);
    mask.push_back(1);
    mask.push_back(-1);
    mask.push_back(0);
    mask.push_back(1);
    setMask(3, 3, mask);
    normalizeMask();
}

void ConvolutionMask::setMask(unsigned int w, unsigned int h, const std::vector<float> &mask)
{
    _w = w;
    _h = h;
    _mask = mask;
}

void ConvolutionMask::normalizeMask()
{
    unsigned int i;
    float weight;
    weight = _h*_w;

    for(i = 0; i < _mask.size(); i++)
        _mask[i] /= weight;
}

float ConvolutionMask::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image &img) const
{
    unsigned int h, w, new_i, new_j;
    float v=0;
    for(h = 0; h < _h; h++)
        for(w = 0; w < _w; w++)
        {
            if( i >= _h/2 && i+_h/2 < img.getHeight() &&
                j >= _w/2 && j+_w/2 < img.getWidth() )
            {
                new_i = h + (i - _h/2);
                new_j = w + (j - _w/2);
                v += img.getPixel(new_i, new_j, c) * maskValue(h,w);
            }
        }

    return std::abs(v);
}

float ConvolutionMask::maskValue(unsigned int i, unsigned int j) const
{
    return  _mask[ i*_w + j ];
}
