#include "opengl.h"

#include "sphere2.h"

using namespace Eigen;

// cube ///////////////////////////////////////////////////////////////////////
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3

// vertex coords array for glDrawArrays() =====================================
// A cube has 6 sides and each side has 2 triangles, therefore, a cube consists
// of 36 vertices (6 sides * 2 tris * 3 vertices = 36 vertices). And, each
// vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
// array is 108 floats (36 * 3 = 108).
GLfloat vertices[]  = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
                       -1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

                        1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
                        1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

                        1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
                       -1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

                       -1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
                       -1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

                       -1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
                        1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

                        1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
                       -1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

Sphere2::Sphere2()
{
    unsigned int const nVertices  = 36;

    _vertices.resize(nVertices);

    for(unsigned int i = 0; i < nVertices; i++)
    {
        unsigned int j = 3*i;
        _vertices[i] = Vector3f(vertices[j],vertices[j+1],vertices[j+2]);
    }

    _bbox.extend(Vector3f(-1,-1,-1));
    _bbox.extend(Vector3f(1,1,1));

    _ready = false;
}

Sphere2::~Sphere2()
{
    glDeleteBuffers(1, _vbo);
}

void Sphere2::init()
{
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, _vbo);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

    checkError();

    _ready = true;
}

void Sphere2::display(Shader *shader)
{
    if(!_ready)
        init();

    glBindVertexArray(_vao);

    // Recuperation des emplacements des deux attributs dans le shader
    int vertexPositionIndex = shader->getAttribLocation("vtx_position");

    if(vertexPositionIndex >=0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
        glVertexAttribPointer(vertexPositionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(vertexPositionIndex);
    }

    glDrawArrays(GL_TRIANGLES, 0, 36);

    if(vertexPositionIndex>=0)
        glDisableVertexAttribArray(vertexPositionIndex);

    glBindVertexArray(0);
}
