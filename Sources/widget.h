#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <vector>
#include <QtCore/QTimer>
#include <time.h>
#include <QElapsedTimer>
#include <cmath>
#include <QtCore/QThread>

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

    string winPath = "D:/QtProjects/TextureMapping/Resources";
    string macPath = "/Users/martinsandfuchs/Desktop/TextureMapping/Resources";
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
