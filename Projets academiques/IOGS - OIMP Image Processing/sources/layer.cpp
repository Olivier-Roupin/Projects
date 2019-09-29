#include "layer.h"

Layer::Layer()
{

}

Layer::Layer(const Layer &l)
    :_width(l._width), _height(l._height), _pixels(l._pixels)
{

}

void Layer::resize(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
    _pixels.resize(_width*_height);
}

float Layer::getPixel(unsigned int row, unsigned int col) const
{
    return _pixels[index(row,col)];
}

void Layer::setPixel(unsigned int row,unsigned int col, float value)
{
    _pixels[index(row,col)] = value;
}

void Layer::debug() const
{
    for(unsigned int i=0; i<_height; i++) {
        for(unsigned int j=0; j<_width; j++) {
            std::cout << _pixels[index(i,j)] << " ";
        }
        std::cout << std::endl;
    }
}

unsigned int Layer::index(unsigned int row, unsigned int col) const
{
    return col + row * _width;
}
