#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <iostream>

class Layer
{
public:
    Layer();
    Layer(const Layer& l);

    void resize(unsigned int width, unsigned int height);

    float getPixel(unsigned int row, unsigned int col) const;
    void setPixel(unsigned int row, unsigned int col, float value);

    void debug() const;

private:
    unsigned int index(unsigned int row, unsigned int col) const;

    unsigned int _width, _height;
    std::vector<float> _pixels;
};

#endif // LAYER_H
