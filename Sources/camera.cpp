#include "camera.h"

//Constructor/Destructor
Camera::Camera(const int &width, const int &height) {
	eyePos = Vector3f(0, 0, 5);
	cz = -1 * eyePos;
	cz.normalize();

	cy = Vector3f(0, 1, 0);
	cy.normalize();

	cx = crossP(cz, cy);
	cx.normalize();

	frame = new QImage;

	setResolution(width, height);
}

Camera::~Camera() {
	delete frame;
}

void Camera::addMeshToRenderQueue(Mesh *mesh) {
	meshes.push_back(mesh);
}

Vector3f Camera::getPointAtPixel(const QPoint &pixel) const {
	const float midx = pixelX * .5f;
	const float midy = pixelY * .5f;
	const QPointF screenP((pixel.x() - midx) / midx, (midy - pixel.y()) / midx);
	const float n = ZBuffer.at(pixel.y()).at(pixel.x()) / distance;
	if (n >= 255.0f / distance - 1) return vec3f::origin;
	const Vector3f cameraP(n * screenP.x(), n * screenP.y(), n * distance);
	const Vector3f worldP = cameraP.x * cx + cameraP.y * cy + cameraP.z * cz + eyePos;
	return worldP;
}

void Camera::clearBuffers() {
	frame->fill(Qt::lightGray);
	for (int y = 0; y < pixelY; ++y) {
		std::fill(ZBuffer[y].begin(), ZBuffer[y].end(), 255.0f);
	}
}

Vector2f Camera::projectPoint(const Vector3f &point) const {
	const Vector3f ep = point - eyePos;
	const float z = abs(scalarP(cz, ep));
	const float x = scalarP(cx, ep) * distance / z;
	const float y = scalarP(cy, ep) * distance / z;
	const float midx = pixelX * .5f;
	const float midy = pixelY * .5f;
	return Vector2f(midx + midx * x, midy - midx * y);
}

//Move the camera
void Camera::moveOnNormal(const float &amount) {
	eyePos += amount * cz;
}

void Camera::moveRight(const float &amount) {
	eyePos += amount * cx;
}

void Camera::move(const Vector3f &direction) {
	eyePos += direction;
}


//Rendering
void Camera::render() {
	//Clear the last frame
	clearBuffers();
	//Draw all the meshes
	for (auto &&i: meshes) {
		for (auto &&j: i->Triangles) {
			renderTriangle(j.v1, j.v2, j.v3, i->tex);
		}
	}
}


#define pz distance
void Camera::renderTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const QImage &tex) {
	//Get the coordinates in camera space
	const Vector3f P1 = toCameraSpace(*v1.p);
	const Vector3f P2 = toCameraSpace(*v2.p);
	const Vector3f P3 = toCameraSpace(*v3.p);

	const Vector3f normal = crossP(P2 - P1, P3 - P1);
	if (scalarP(normal, P1) < 0.0f && backFaceCulling) return; //Backface culling and return when behind camera
	if (P1.z < 0.0f && P2.z < 0.0f && P3.z < 0.0f) return;

	//The projected points
	const Vector2f Proj1 = projectPoint(*v1.p);
	const Vector2f Proj2 = projectPoint(*v2.p);
	const Vector2f Proj3 = projectPoint(*v3.p);

	//Return when the triangle is out of the screen
	if (Proj1.x < 0.0f && Proj2.x < 0.0f && Proj3.x < 0.0f) return;
	if (Proj1.x > pixelX && Proj2.x > pixelX && Proj3.x > pixelX) return;
	if (Proj1.y < 0.0f && Proj2.y < 0.0f && Proj3.y < 0.0f) return;
	if (Proj3.y > pixelY && Proj2.y > pixelY && Proj1.y > pixelY) return;

	//The factors for the cartesian form of a plane
	const float A = normal.x;
	const float B = normal.y;
	const float C = normal.z;
	const float D = scalarP(normal, P1) * pz;

	//Find min, max and mid points
	Vector2f PA(0.0f, pixelY), PB(0.0f, 0.0f), PC(100, 100);
	//min
	if (Proj1.y < PA.y) PA = Proj1;
	if (Proj2.y < PA.y) PA = Proj2;
	if (Proj3.y < PA.y) PA = Proj3;
	const float yMin = PA.y;

	//max
	if (Proj1.y > PB.y) PB = Proj1;
	if (Proj2.y > PB.y) PB = Proj2;
	if (Proj3.y > PB.y) PB = Proj3;
	const float yMax = PB.y < pixelY - 1.0f ? PB.y : pixelY - 1.0f;

	//mid
	if (Proj1 != PA && Proj1 != PB) { PC = Proj1; }
	else if (Proj2 != PA && Proj2 != PB) { PC = Proj2; }
	else { PC = Proj3; }

	const int yStart = yMin > 0.0f ? yMin + 1.0f : 0;
	const int yEnd = yMax + 1.0f;

	const float midX = pixelX * .5f;
	const float midY = pixelY * .5f;
	int xMax, xMin;

	//Slopes for traversing the triangle
	const float slopeAC = (PC.x - PA.x) / (PC.y - PA.y);
	const float slopeAB = (PB.x - PA.x) / (PB.y - PA.y);
	const float slopeCB = (PB.x - PC.x) / (PB.y - PC.y);

	//Helper variables for finding texture coordinates
	const Vector2f ABTex = v2.texCoord - v1.texCoord;
	const Vector2f ACTex = v3.texCoord - v1.texCoord;
	const Vector2f ABScr = Proj2 - Proj1;
	const Vector2f ACScr = Proj3 - Proj1;

	const float denomScr1 = 1.0f / ((ACScr.x * ABScr.y - ACScr.y * ABScr.x) * P2.z);
	const float denomScr2 = 1.0f / ((ACScr.x * ABScr.y - ACScr.y * ABScr.x) * P3.z);
	const float helpABScr = ACScr.y * Proj1.x - ACScr.x * Proj1.y;
	const float helpACScr = ABScr.x * Proj1.y - ABScr.y * Proj1.x;

	const int textureWidth = tex.width();
	const int textureHeight = tex.height();

	//Helper variables for iterating through the triangle
	const float dx = 1.0f / midX;
	const float dy = -dx;
	float py = (yStart - midY) * dy;

	//Variables for direct access to pixel data
	const uchar *const texStart = tex.bits();
	uchar *const frameStart = frame->bits();
	uchar *curPixel;
	const int pixelSizeTex = tex.bytesPerLine() / tex.width();
	const int pixelSizeFrame = frame->bytesPerLine() / frame->width();


	//Iterate through the triangle and calculate z-values and texture coordinates
	for (int y = yStart; y < yEnd; ++y) {
		const int x2 = PA.x + (y - PA.y) * slopeAB;
		const int x1 = y < PC.y ? PA.x + (y - PA.y) * slopeAC : PC.x + (y - PC.y) * slopeCB;
		if (x1 > x2) {
			xMax = x1;
			xMin = x2;
		} else {
			xMax = x2;
			xMin = x1;
		}
		if (xMax > pixelX) xMax = pixelX;
		if (xMin < 0) xMin = 0;

		float px = (xMin - midX) * dx;
		curPixel = frameStart + pixelSizeFrame * (pixelX * y + xMin); //Set the pointer to the current pixel

		//Extracted helper variables
		const float BtYpCtZ = B * py + C * pz;
		const float ACXtY = ACScr.x * y;
		const float ABXtY = ABScr.x * y;

		for (int x = xMin; x < xMax; ++x) {
			px += dx;
			const float z = D / (A * px + BtYpCtZ);
			if (z < ZBuffer[y][x]) { //Pixel is closer than value in Z-Buffer
				ZBuffer[y][x] = z;

				//Calculate the texture coordinate scalars
				const float scalarS = (ACXtY - ACScr.y * x + helpABScr) * denomScr1 * z;
				const float scalarT = (ABScr.y * x - ABXtY + helpACScr) * denomScr2 * z;

				const Vector2f texCoord = v1.texCoord + ABTex * scalarS + ACTex * scalarT;
				const Vector2i pixelCoord(clamp(textureWidth * texCoord.x, textureWidth - 1),
										  clamp(textureHeight - textureHeight * texCoord.y, textureHeight - 1));

				//Copy the pixel from the texture to the frame buffer
				memcpy(curPixel, texStart + pixelSizeTex * (pixelCoord.y * textureWidth + pixelCoord.x), pixelSizeTex);
			}
			curPixel += pixelSizeFrame; //Iterate to the next pixel
		}
		py += dy;
	}
}
#undef pz

//Rotate
void Camera::rotate(const Vector3f &axis, const float &radians) {
	Matrix3x3 rotMat;
	rotMat.makeRotation(axis, radians);
	cz = rotMat * cz;
	cy = rotMat * cy;
	cx = crossP(cz, cy);
}

void Camera::rotate(const Vector3f &axis, const float &radians, const Vector3f &point) {
	this->move(-1 * point);
	this->rotate(axis, radians);
	this->eyePos.rotate(axis, radians);
	this->move(point);
}

void Camera::rotate(const Matrix3x3 &m, const bool &rotateEye) {
	cz = m * cz;
	cy = m * cy;
	cx = crossP(cz, cy);
	if (rotateEye)
		eyePos = m * eyePos;
}

Vector3f Camera::toCameraSpace(const Vector3f &point) const {
	const Vector3f ep = point - eyePos;
	const float x = scalarP(cx, ep);
	const float y = scalarP(cy, ep);
	const float z = scalarP(cz, ep);
	return Vector3f(x, y, z);
}

//Setter functions
void Camera::setFov(const float &angle) {
	fov = 2 * pi * angle / 360;
	const float ang = 90 - angle / 2;
	const float rad = 2 * pi * ang / 360.0f;
	distance = tanf(rad);
}

void Camera::setNormal(const Vector3f &norm) {
	cz = norm;
	cz.normalize();
	cx = crossP(cz, Vector3f(0, 1, 0));
	cx.normalize();
	cy = crossP(cx, cz);
}

void Camera::setResolution(const int &width, const int &height) {
	pixelX = width;
	pixelY = height;

	delete frame;
	frame = new QImage(pixelX, pixelY, QImage::Format_RGB32);
	frame->fill(Qt::lightGray);

	ZBuffer.clear();
	ZBuffer.resize(height);
	for (int y = 0; y < height; ++y) {
		ZBuffer[y].resize(width, 255);
	}
}

void Camera::setFocus(const Vector3f &pos) {
	setNormal(pos - eyePos);
}

void Camera::setPosition(const Vector3f &pos) {
	eyePos = pos;
}

int Camera::clamp(const int &n, const int &max) {
	const int x = n < 0 ? 0 : n;
	return x > max ? max : x;
}
