#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <QPainter>
#include <cmath>
#include <QImage>

#include "vector3d.h"
#include "vertex.h"
#include "mesh.h"
#include "vector2d.h"

using namespace std;
class Camera {
 public:
	//Constructor/Destructor
	Camera(const int &width, const int &height);
	~Camera();

	//Functions
	void addMeshToRenderQueue(Mesh* mesh);
	Vector3f getPointAtPixel(const QPoint &pixel) const;

	Vector2f projectPoint(const Vector3f& point) const;

	void moveOnNormal(const float &amount);
	void moveRight(const float &amount);
	void move(const Vector3f& direction);

	void render();
	void renderTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const QImage &tex);

	void rotate(const Vector3f &axis, const float &radians);
	void rotate(const Vector3f &axis, const float &radians, const Vector3f &point);
	void rotate(const Matrix3x3 &m, const bool &rotateEye = false);

	Vector3f toCameraSpace(const Vector3f &point) const;

	//Setters
	void setFov(const float &angle);
	void setNormal(const Vector3f& norm);
	void setFocus(const Vector3f& pos);
	void setPosition(const Vector3f &pos);
	void setResolution(const int &width, const int &height);

	//Getters
	inline bool hasCulling() const { return backFaceCulling; }
	inline int getWidth() const { return pixelX; }
	inline int getHeight() const { return pixelY; }
	inline float getFOV() const { return fov; }

	//Variables
	const float pi = 3.141592f;
	QImage* frame;
	vector< vector<float >> ZBuffer;

	//Defining the camera
	Vector3f eyePos;
	Vector3f cx;
	Vector3f cy;
	Vector3f cz;

 private:
	void clearBuffers();
	int clamp(const int &n, const int &max);

	float distance = 1.732f;
	float fov;
	bool backFaceCulling = true;

	int pixelX;
	int pixelY;

	std::vector<Mesh * > meshes;
};

#endif // CAMERA_H
