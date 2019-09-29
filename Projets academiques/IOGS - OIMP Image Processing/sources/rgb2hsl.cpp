#include "rgb2hsl.h"

RGB2HSL::RGB2HSL()
{

}

float RGB2HSL::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image &img) const
{
    if(img.getType() == Image::RGB)
    {
        float M(std::max(std::max(img.getPixel(i, j, 0),img.getPixel(i, j, 1)),img.getPixel(i, j, 2)));
        float C(M-std::min(std::min(img.getPixel(i, j, 0),img.getPixel(i, j, 1)),img.getPixel(i, j, 2)));
        switch(c)
        {
        case 0: //H:360
            if(C)
            {
                if(M == img.getPixel(i, j, 0))
                    return std::fmod((img.getPixel(i, j, 1)-img.getPixel(i, j, 2))/C+6.0,6)/6.0;
                if(M == img.getPixel(i, j, 1))
                    return std::fmod((img.getPixel(i, j, 2)-img.getPixel(i, j, 0))/C+8.0,6)/6.0;
                if(M == img.getPixel(i, j, 2))
                    return std::fmod((img.getPixel(i, j, 0)-img.getPixel(i, j, 1))/C+10.0,6)/6.0;
            }
            return 0;
        case 1: //S
            if(M)
                return C/M;
            return 0;
        case 2: //L
            return M;
        }
    }
    return img.getPixel(i, j, 0);
}
