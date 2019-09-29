#ifndef _SPHERE2_H
#define _SPHERE2_H

#include "shape.h"

class Sphere2 : public Shape
{
public:
    Sphere2(); //radius == 1.0f
    virtual ~Sphere2();

    void init();
    void display(Shader *shader);

private:
    GLuint _vbo[1];
    GLuint _vao;

    std::vector<int>              _indices;   /** vertex indices */
    std::vector<Eigen::Vector3f>	_vertices;  /** 3D positions */
};

#endif
