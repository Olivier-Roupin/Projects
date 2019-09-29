#include "rotation.h"

float degree2radians(float angle)
{
    return angle * M_PI / 180.;
}

float rotate_x(int i, int j, int w, int h, float theta)
{
    float a = degree2radians( theta );
    return  (j-w/2.)*cos(a) - (i-h/2.)*sin(a) + w/2.;
}

float rotate_y(int i, int j, int w, int h, float theta)
{
    float a = degree2radians( theta );
    return  (j-w/2.)*sin(a) + (i-h/2.)*cos(a) + h/2.;
}

Rotation::Rotation(float theta)
    : _theta(theta)
{

}

void Rotation::setTheta(float theta)
{
    _theta = theta;
}

float Rotation::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const
{
    int w = img.getWidth();
    int h = img.getHeight();
    float a = degree2radians( _theta );
    float new_i =  rotate_y(i+_offset_y, j+_offset_x, w, h, _theta);
    float new_j =  rotate_x(i+_offset_y, j+_offset_x, w, h, _theta);
    if( new_i >= 0 && new_i < h && new_j >=0 && new_j < w )
        return img.getPixel(new_i, new_j, c);
    return 1;
}

void Rotation::resizeOutputImage(const Image &in, Image &out) const
{
    int w = in.getWidth();
    int h = in.getHeight();

    // top left corner
    int p1_i = rotate_y(0, 0, w, h, _theta);
    int p1_j = rotate_x(0, 0, w, h, _theta);

    // top right corner
    int p2_i = rotate_y(0, w, w, h, _theta);
    int p2_j = rotate_x(0, w, w, h, _theta);

    // bottom left corner
    int p3_i = rotate_y(h, 0, w, h, _theta);
    int p3_j = rotate_x(h, 0, w, h, _theta);

    // bottom right corner
    int p4_i = rotate_y(h, w, w, h, _theta);
    int p4_j = rotate_x(h, w, w, h, _theta);

    // min and max (i, j)
    int min_i = std::min(std::min(p1_i, p2_i), std::min(p3_i, p4_i));
    int max_i = std::max(std::max(p1_i, p2_i), std::max(p3_i, p4_i));
    int min_j = std::min(std::min(p1_j, p2_j), std::min(p3_j, p4_j));
    int max_j = std::max(std::max(p1_j, p2_j), std::max(p3_j, p4_j));

    // compute new resolution and offset
    int new_width  = max_j - min_j;
    int new_height = max_i - min_i;
    _offset_x = min_j;
    _offset_y = min_i;
    out.resize(new_width, new_height, in.getNofLayer());
    out.setType(in.getType());
}

