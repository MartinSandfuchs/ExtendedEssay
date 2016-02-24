#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <vector>
#include <QTimer>
#include <time.h>
#include <QElapsedTimer>
#include <cmath>
#include <QThread>

#include "camera.h"
#include "vector3d.h"
#include "mesh.h"
#include "vertex.h"

using namespace std;

namespace Ui {
	class Widget;
}

class Widget: public QWidget {
	Q_OBJECT

 public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

 private:
	Ui::Widget *ui;
	Camera cam;
	Mesh mesh;
	Mesh mesh1;

	QPoint lastMousePos;
	QPoint currentMousePos;
	QPoint pressPos;
	Vector3f rotPoint;

	bool leftMouse = false;
	bool rightMouse = false;
	bool middleMouse = false;

	bool forward = false;
	bool backward = false;
	bool left = false;
	bool up = false;

	bool ctrl = false;
	bool alt = false;

	QTimer timer;

	//Change these paths depending on the OS and where the repository was cloned to
	string winPath = "D:/QtProjects/TextureMapping/Resources";
	string macPath = "/Users/martinsandfuchs/Downloads/ExtendedEssay/Sources/Resources";
	string linPath = "/run/media/martinsandfuchs/Data/QtProjects/TextureMapping/Resources";
	string path = "../Resources";

 private slots:
	void paintEvent(QPaintEvent *) override;

	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void wheelEvent(QWheelEvent *e) override;

	void keyPressEvent(QKeyEvent *e) override;
	void keyReleaseEvent(QKeyEvent *e) override;
	void resizeEvent(QResizeEvent *) override;

	void updateScene();

	void on_horizontalSlider_sliderMoved(int position);
	void on_pushButton_clicked();
};

#endif // WIDGET_H
