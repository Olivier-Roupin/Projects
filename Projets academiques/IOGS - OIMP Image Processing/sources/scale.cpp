#include "scale.h"

Scale::Scale(float scale)
    : _scale(scale)
{

}

void Scale::setScale(float scale)
{
    _scale = scale;
}

float Scale::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image &img) const
{
    return img.getPixel((float)i/_scale, (float)j/_scale, c);
}

void Scale::resizeOutputImage(const Image &in, Image &out) const
{
    out.resize(_scale*in.getWidth(), _scale*in.getHeight(), in.getNofLayer());
    out.setType(in.getType());
}
