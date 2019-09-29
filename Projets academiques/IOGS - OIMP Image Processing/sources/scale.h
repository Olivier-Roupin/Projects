#ifndef SCALE_H
#define SCALE_H

#include "operation.h"

class Scale : public Operation
{
public:
    Scale(float scale=1);
    void setScale(float scale);

protected:
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;
    virtual void resizeOutputImage(const Image& in, Image &out) const;

private:
    float _scale;
};

#endif // SCALE_H
