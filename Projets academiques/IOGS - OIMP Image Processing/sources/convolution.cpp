#include "convolution.h"

Convolution::Convolution(Image* masque) : _masque(masque)
{

}

float Convolution::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const
{
    unsigned int p,q;
    float pixel(0);

    if(_masque->getType() == Image::RGB)
    {
        for(p = 0; p < _masque->getHeight(); p++)
            for(q = 0; q < _masque->getWidth(); q++)
            {
                if(i >= _masque->getHeight()/2 && i+_masque->getHeight()/2 < img.getHeight() && j >= _masque->getWidth()/2 && j+_masque->getWidth()/2 < img.getWidth())
                    pixel += (_masque->getPixel(p,q,c)-0.5)*img.getPixel(i+p-_masque->getHeight()/2,j+q-_masque->getWidth()/2,c);

            }
    }
    else
    {
        for(p = 0; p < _masque->getHeight(); p++)
            for(q = 0; q < _masque->getWidth(); q++)
            {
                if(i >= _masque->getHeight()/2 && i+_masque->getHeight()/2 < img.getHeight() && j >= _masque->getWidth()/2 && j+_masque->getWidth()/2 < img.getWidth())
                    pixel += (_masque->getPixel(p,q,0)-0.5)*img.getPixel(i+p-_masque->getHeight()/2,j+q-_masque->getWidth()/2,c);
            }
    }
    return pixel/(_masque->getHeight()*_masque->getWidth());
}
