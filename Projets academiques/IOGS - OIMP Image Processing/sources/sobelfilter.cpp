#include "sobelfilter.h"

SobelFilter::SobelFilter()
{

}

float SobelFilter::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const
{
    std::vector<float> vecx;
    vecx.push_back(1);
    vecx.push_back(0);
    vecx.push_back(-1);
    vecx.push_back(2);
    vecx.push_back(0);
    vecx.push_back(-2);
    vecx.push_back(1);
    vecx.push_back(0);
    vecx.push_back(-1);

    std::vector<float> vecy;
    vecy.push_back(1);
    vecy.push_back(2);
    vecy.push_back(1);
    vecy.push_back(0);
    vecy.push_back(0);
    vecy.push_back(0);
    vecy.push_back(-1);
    vecy.push_back(-2);
    vecy.push_back(-1);

    ConvolutionMask Mx;
    Mx.setMask(3,3,vecx);
    Mx.normalizeMask();

    ConvolutionMask My;
    My.setMask(3,3,vecy);
    My.normalizeMask();

    float px(Mx.processPixel(i,j,c,img));
    float py(My.processPixel(i,j,c,img));
    return std::sqrt(px*px+py*py);
}
