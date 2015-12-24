#include "mesh.h"

//Constructor and destructor
Mesh::Mesh() {
}

Mesh::Mesh(const string &path) {
    loadObj(path);
}

Mesh::~Mesh() {
}

void Mesh::applyTransformation(const Matrix3x3 &m) {
    for (unsigned int i = 0; i < vertices.size(); ++i) {
        vertices.at(i) = m*vertices.at(i);
    }
    xaxis = m*xaxis;
    yaxis = m*yaxis;
    zaxis = m*zaxis;
    origin = m*origin;
}

void Mesh::center() {
    Vector3f sum(0, 0, 0);
    for (unsigned int i = 0; i < vertices.size(); ++i) {
        sum += vertices.at(i);
    }
    sum /= vertices.size();
    this->moveMesh(-1*sum);
}

//Converting between coordinate spaces
Vector3f Mesh::convertPointToWorldSpace(const Vector3f &vec) const {
    return origin + convertVecToWorldSpace(vec);
}
Vector3f Mesh::convertVecToWorldSpace(const Vector3f &vec) const {
    Matrix3x3 m;
    m.makeObjectToWorld(xaxis, yaxis, zaxis);
    return m*vec;
}
Vector3f Mesh::convertPointToObjectSpace(const Vector3f &vec) const {
    return convertVecToObjectSpace(vec - origin);
}
Vector3f Mesh::convertVecToObjectSpace(const Vector3f &vec) const {
    Matrix3x3 m;
    m.makeWorldToObject(xaxis, yaxis, zaxis);
    return m*vec;
}


void Mesh::flipUVs() {
    for (unsigned int i = 0; i < Triangles.size(); ++i) {
        Vertex temp = Triangles.at(i).v1;
        Triangles.at(i).v1 = Triangles.at(i).v2;
        Triangles.at(i).v2 = temp;
    }
}

void Mesh::loadObj(const string &path) {
    string meshpath = path + "/Mesh.obj";
    ifstream file(meshpath);
    tex = QImage(QString::fromStdString(path + "/tex.png"));
    tex = tex.convertToFormat(QImage::Format_RGB32);
    string s;
    file >> s;
    if (!file.is_open()) {
        cout << "Could not open File!" << endl;
        return;
    }

    vector<Vector2f> texCoords;

    while (file >> s) {
        //Save the vertices
        while (s=="v") {
            Vector3f vertex;
            for (unsigned int i = 0; i < 3; ++i) {
                file >> s;
                if (i==0) vertex.x = stof(s);
                if (i==1) vertex.y = stof(s);
                if (i==2) vertex.z = stof(s);
            }
            vertices.push_back(vertex);
            file >> s;
        }
        //Save the vertex texture Coordinates
        while (s=="vt") {
            file >> s;
            Vector2f coord;
            coord.x = stof(s);
            file >> s;
            coord.y = stof(s);
            texCoords.push_back(coord);
            file >> s;
            file >> s;
        }
        //Putting the faces together
        while (s=="f") {
            vector<unsigned int> positionIndices;
            vector<unsigned int> coordIndices;
            for (unsigned int i = 0; i < 3; ++i) {
                file >> s;
                string positionIndex;
                string coordIndex;
                for (unsigned int j = 0; j < s.size(); ++j) {
                    if (s.at(j)=='/') {
                        for (unsigned int k = j + 1; k < s.size(); ++k) {
                            coordIndex = coordIndex + s.at(k);
                        }
                        break;
                    }
                    positionIndex = positionIndex + s.at(j);
                }
                positionIndices.push_back(stoi(positionIndex));
                coordIndices.push_back(stoi(coordIndex));
            }

            Triangle tri;
            Vertex v1, v2, v3;
            v1.p = &vertices.at(positionIndices.at(0) - 1);
            v2.p = &vertices.at(positionIndices.at(1) - 1);
            v3.p = &vertices.at(positionIndices.at(2) - 1);

            v1.texCoord = texCoords.at(coordIndices.at(0) - 1);
            v2.texCoord = texCoords.at(coordIndices.at(1) - 1);
            v3.texCoord = texCoords.at(coordIndices.at(2) - 1);

            tri.v1 = v1;
            tri.v2 = v2;
            tri.v3 = v3;
            Triangles.push_back(tri);
            file >> s;
        }//End of face creation
    }
}

void Mesh::moveMesh(const Vector3f &direction) {
    for (unsigned int i = 0; i < vertices.size(); ++i) {
        vertices.at(i) += direction;
    }
    origin += direction;
}

void Mesh::moveRelative(const Vector3f &direction) {
    const Vector3f globalDir = this->xaxis*direction.x + this->yaxis*direction.y + this->zaxis*direction.z;
    moveMesh(globalDir);
}
void Mesh::rotateMesh(const Vector3f &axis, const float &radians) {
    const Matrix3x3 rotMat = Matrix3x3().makeRotation(axis, radians);
    applyTransformation(rotMat);
}
void Mesh::rotateRelative(const Vector3f &axis, const float &radians) {
    const Vector3f position = this->origin;
    moveMesh(-1*position);
    const Matrix3x3 m = Matrix3x3().makeObjectToWorld(xaxis, yaxis, zaxis);
    const Vector3f globalAxis = m*axis;
    const Matrix3x3 rotMat = Matrix3x3().makeRotation(globalAxis, radians);
    applyTransformation(rotMat);
    moveMesh(position);
}

void Mesh::scaleMesh(const float &factorX, const float &factorY, const float &factorZ) {
    for (unsigned int i = 0; i < vertices.size(); ++i) {
        vertices.at(i) = Vector3f(vertices.at(i).x*factorX, vertices.at(i).y*factorY, vertices.at(i).z*factorZ);
    }
}

void Mesh::scaleRelative(const float &factorX, const float &factorY, const float &factorZ) {
    const Matrix3x3 m1 = Matrix3x3().makeWorldToObject(xaxis, yaxis, zaxis);
    const Matrix3x3 m2 = Matrix3x3().makeScale(factorX, factorY, factorZ);
    const Matrix3x3 m3 = Matrix3x3().makeObjectToWorld(xaxis, yaxis, zaxis);
    const Matrix3x3 totalTransform = m3*m2*m1;
    for (unsigned int i = 0; i < vertices.size(); ++i) {
        const Vector3f op = vertices.at(i) - this->origin;
        vertices.at(i) = origin + totalTransform*op;
    }
}
void Mesh::scaleUniform(const float &factor) {
    for (unsigned int i = 0; i < vertices.size(); ++i) {
        vertices.at(i) *= factor;
    }
}

void Mesh::setAxes(const Vector3f &xaxis, const Vector3f &yaxis, const Vector3f &zaxis) {
    for (unsigned int i = 0; i < vertices.size(); ++i) {
        const Vector3f op = vertices.at(i) - this->origin;
        const float relx = scalarP(this->xaxis, op);
        const float rely = scalarP(this->yaxis, op);
        const float relz = scalarP(this->zaxis, op);

        vertices.at(i) = relx*xaxis + rely*yaxis + relz*zaxis + origin;
    }
    this->xaxis = xaxis;
    this->yaxis = yaxis;
    this->zaxis = zaxis;
}

void Mesh::setOrigin(const Vector3f &origin) {
    moveMesh(origin - this->origin);
}

void Mesh::setPosition(const Vector3f &pos) {
    moveMesh(pos - origin);
}
