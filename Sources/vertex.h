#ifndef VERTEX_H
#define VERTEX_H

#include "vector3d.h"
#include "vector2d.h"

struct Vertex {
    Vector3f* p  = 0;
    //QPointF texCoord;
    Vector2f texCoord;
};

struct Triangle {
    Vertex v1;
    Vertex v2;
    Vertex v3;
};

#endif // VERTEX_H
