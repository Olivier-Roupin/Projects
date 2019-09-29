#include "hsl2rgb.h"

HSL2RGB::HSL2RGB()
{

}

float HSL2RGB::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image &img) const
{
    if(img.getType() == Image::RGB)
    {
        float C(img.getPixel(i, j, 1)*img.getPixel(i, j, 2));
        float m(img.getPixel(i, j, 2)-C);
        float T(6.0 * img.getPixel(i, j, 0));
        float X(C*(1-std::fabs(std::fmod(T,2)-1)));
        switch(c)
        {
        case 0: //R
            if(T >= 2 && T < 4)
                return m;
            if(T < 1 || T >= 5)
                return C+m;
            return X+m;
        case 1: //G
            if(T >= 4)
                return m;
            if(T >= 1 && T < 3)
                return C+m;
            return X+m;
        case 2: //B
            if(T < 2)
                return m;
            if(T >= 3 && T < 5)
                return C+m;
            return X+m;
        }
    }
    //GRAYSCALE
    return img.getPixel(i, j, 0);
}
