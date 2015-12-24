#ifndef MESH_H
#define MESH_H

#include <fstream>
#include <QString>
#include <QImage>
#include <string>
#include <vector>
#include <iostream>

#include "vector3d.h"
#include "vertex.h"
#include "matrix3x3.h"
#include "vector2d.h"

using namespace std;
class Mesh {
 public:
    //Constructor/Destructor
    Mesh();
    Mesh(const string &path);
    ~Mesh();

    //Functions
    void applyTransformation(const Matrix3x3 &m);
    void center();

    Vector3f convertPointToWorldSpace(const Vector3f &vec) const;
    Vector3f convertVecToWorldSpace(const Vector3f &vec) const;
    Vector3f convertPointToObjectSpace(const Vector3f &vec) const;
    Vector3f convertVecToObjectSpace(const Vector3f &vec) const;

    void flipUVs();
    void loadObj(const string &path);
    void moveMesh(const Vector3f &direction);
    void moveRelative(const Vector3f &direction);
    void rotateMesh(const Vector3f &axis, const float &radians);
    void rotateRelative(const Vector3f &axis, const float &radians);
    void scaleMesh(const float &factorX, const float &factorY, const float &factorZ);
    void scaleRelative(const float &factorX, const float &factorY, const float &factorZ);
    void scaleUniform(const float &factor);

    void setAxes(const Vector3f &xaxis, const Vector3f &yaxis, const Vector3f &zaxis);
    void setOrigin(const Vector3f &origin);
    void setPosition(const Vector3f &pos);

    //Variables
    vector<Vector3f> vertices;
    vector<Triangle> Triangles;

    Vector3f origin = Vector3f(0, 0, 0);
    Vector3f xaxis = Vector3f(1, 0, 0);
    Vector3f yaxis = Vector3f(0, 1, 0);
    Vector3f zaxis = Vector3f(0, 0, 1);

    QImage tex;
};

#endif // MESH_H
