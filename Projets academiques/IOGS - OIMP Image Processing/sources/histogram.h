#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <iostream>
#include <fstream>
#include "rgb2hsl.h"

class Histogram
{
public:
    Histogram();
    Histogram(const Image& img);
    int getNoir() const;
    int getBlanc() const;
    int getCDF(unsigned int i) const;
    int getMax() const;
    void save() const;

private:
    unsigned int _valeurs[256];
};

#endif // HISTOGRAM_H

