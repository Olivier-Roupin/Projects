#include "operation.h"

Operation::~Operation()
{

}

void Operation::process(const Image &in, Image &out) const
{
    resizeOutputImage(in, out);
    for(unsigned int l=0 ; l<out.getNofLayer() ; ++l)
        for(unsigned int j=0 ; j<out.getWidth() ; ++j)
            for(unsigned int i=0 ; i<out.getHeight() ; ++i) {
                out.setPixel(i,j,l,processPixel(i,j,l,in));
            }

}

void Operation::resizeOutputImage(const Image &in, Image& out) const
{
    out.resize(in.getWidth(), in.getHeight(), in.getNofLayer());
    out.setType(in.getType());
}
