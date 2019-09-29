#include "image.h"

Image::Image()
{

}

Image::Image(const Image &img)
    :_width(img._width), _height(img._height), _layers(img._layers), _type(img._type)
{

}

void Image::resize(unsigned int width, unsigned int height, unsigned int channel)
{
    _width = width;
    _height = height;

    _layers.resize(channel);
    for(unsigned int i = 0; i < channel; i++)
        _layers[i].resize(width,height);
}

Image::ImageType Image::getType() const
{
    return _type;
}

void Image::setType(ImageType type)
{
    _type = type;
}

float Image::getPixel(unsigned int row, unsigned int col, unsigned int channel) const
{
    assert(channel<_layers.size());
    return _layers[channel].getPixel(row,col);
}

void Image::setPixel(unsigned int row, unsigned int col, unsigned int channel, float value)
{
    assert(channel<_layers.size());
    _layers[channel].setPixel(row,col,value);
}

void Image::save(std::string const & filename) const
{
    std::size_t found = filename.find_last_of(".");
    if((int)found == -1) {
        std::cerr << "Error : " << filename << " is not a file" << std::endl;
        return;
    }

    std::string extension = filename.substr(found);
    if(extension == ".pgm" && getType() == Image::GRAY_SCALE)
        savePGM(filename);
    else if(extension == ".ppm"  && getType() == Image::RGB)
        savePPM(filename);
    else
    {
        std::cerr << "Error : " << filename << " is not compatible" << std::endl;
        return;
    }
}

void Image::savePGM(std::string const & filename) const
{
    std::ofstream fs;
    fs.open(filename.c_str());
    if(!fs.is_open()) {
        std::cerr << "Error : fail to open the file " << filename << std::endl;
        return;
    }
    fs << "P2" << std::endl;
    fs << _width << " " << _height << std::endl;
    fs << "255" << std::endl;
    for(unsigned int i=0; i<_height; i++) {
        for(unsigned int j=0; j<_width; j++) {
            fs << (unsigned int) (getPixel(i,j,0) * 255) << " ";
        }
        fs << std::endl;
    }

    fs.close();
}

void Image::savePPM(std::string const & filename) const
{
    std::ofstream fs;
    fs.open(filename.c_str());
    if(!fs.is_open()) {
        std::cerr << "Error : fail to open the file " << filename << std::endl;
        return;
    }
    fs << "P3" << std::endl;
    fs << _width << " " << _height << std::endl;
    fs << "255" << std::endl;
    for(unsigned int i=0; i<_height; i++) {
        for(unsigned int j=0; j<_width; j++) {
            for(unsigned int k=0; k<3; k++) {
                fs << (unsigned int) (getPixel(i,j,k) * 255) << " ";
            }
        }
        fs << std::endl;
    }

    fs.close();
}

bool Image::load(std::string const & filename)
{
    std::size_t found = filename.find_last_of(".");
    if((int)found == -1) {
        std::cerr << "Error : " << filename << " is not a file" << std::endl;
        return false;
    }

    std::string extension = filename.substr(found);
    if(extension == ".pgm")
        return loadPGM(filename);
    else if(extension == ".ppm")
        return loadPPM(filename);
    else
    {
        std::cerr << "Error : " << filename << " is not compatible" << std::endl;
        return false;
    }
}

bool Image::loadPGM(std::string const & filename)
{
    std::ifstream fs;
    fs.open(filename.c_str());
    if(!fs.is_open()) {
        std::cerr << "Error : fail to open the file " << filename << std::endl;
        return false;
    }

    std::string magicNumber;
    fs >> magicNumber;
    if(magicNumber.compare("P2") != 0) {
        std::cerr << "Error : Format unknown " << magicNumber << std::endl;
        return false;
    }

    unsigned int width, height, maxVal;
    fs >> width;
    fs >> height;
    fs >> maxVal;

    resize(width,height,1);

    for(unsigned int i=0; i<height; i++) {
        for(unsigned int j=0; j<width; j++) {
            unsigned int val;
            fs >> val;
            setPixel(i,j,0,val/(float)maxVal);
        }
    }
    setType(Image::GRAY_SCALE);

    fs.close();

    return true;
}

bool Image::loadPPM(const std::string &filename)
{
    std::ifstream fs;
    fs.open(filename.c_str());
    if(!fs.is_open()) {
        std::cerr << "Error : fail to open the file " << filename << std::endl;
        return false;
    }

    std::string magicNumber;
    fs >> magicNumber;
    if(magicNumber.compare("P3") != 0) {
        std::cerr << "Error : Format unknown " << magicNumber << std::endl;
        return false;
    }

    unsigned int width, height, maxVal;
    fs >> width;
    fs >> height;
    fs >> maxVal;

    resize(width,height,3);

    for(unsigned int i=0; i<height; i++) {
        for(unsigned int j=0; j<width; j++) {
            for(unsigned int k=0 ; k<3 ; k++)
            {
                unsigned int val;
                fs >> val;
                setPixel(i,j,k,val/(float)maxVal);
            }
        }
    }
    setType(Image::RGB);

    fs.close();

    return true;
}

void Image::debug() const
{
      for(unsigned int i=0; i<_layers.size(); i++)
      {
          std::cout << "Layer " << i << std::endl;
          _layers[i].debug();
          std::cout << std::endl;
      }
}
