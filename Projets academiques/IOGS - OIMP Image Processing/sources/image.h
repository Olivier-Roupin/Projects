#ifndef IMAGE_H
#define IMAGE_H

#include "layer.h"
#include <string>
#include <cassert>
#include <fstream>

class Image
{
public:
    enum ImageType
    {
        RGB,
        GRAY_SCALE
    };

    Image();
    Image(const Image& img);
    ~Image() {}

    void resize(unsigned int width,unsigned int height,unsigned int channel);

    ImageType getType() const;
    void setType(ImageType type);

    float getPixel(unsigned int row, unsigned int col, unsigned int c) const;
    void setPixel(unsigned int row, unsigned int col, unsigned int c, float value);

    unsigned int getWidth() const { return _width; }
    unsigned int getHeight() const { return _height; }
    unsigned int getNofLayer() const { return _layers.size(); }

    void save(std::string const & filename) const;
    bool load(std::string const & filename);

    void debug() const;

private:
    void savePGM(std::string const & filename) const;
    void savePPM(std::string const & filename) const;
    bool loadPGM(std::string const & filename);
    bool loadPPM(std::string const & filename);


private:
    unsigned int _width, _height;
    std::vector<Layer> _layers;
    ImageType _type;
};

#endif // IMAGE_H
