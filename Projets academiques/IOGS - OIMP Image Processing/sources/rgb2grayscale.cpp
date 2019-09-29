#include "rgb2grayscale.h"

RGB2GrayScale::RGB2GrayScale()
{

}

float RGB2GrayScale::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const
{
    if(img.getType() == Image::RGB)
        return img.getPixel(i,j,0)*0.21 + img.getPixel(i,j,1)*0.72 + img.getPixel(i,j,2)*0.07;
    return img.getPixel(i,j,0);
}

void RGB2GrayScale::resizeOutputImage(const Image &in, Image &out) const
{
    out.resize(in.getWidth(), in.getHeight(), 1);
    out.setType(Image::GRAY_SCALE);
}
