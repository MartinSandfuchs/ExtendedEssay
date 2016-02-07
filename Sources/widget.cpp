#include "widget.h"
#include "ui_widget.h"

//Constructor duh!
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    cam(width(), height()),
    ui(new Ui::Widget) {
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer.start(20);
    ui->label->setStyleSheet("color: white");

    //this->setWindowFlags(Qt::WindowStaysOnTopHint);

    cam.setFov(60);

    //Get the path to the meshes
#ifdef __APPLE__
    path = macPath;
#elif defined _WIN32
    path = winPath;
#elif defined __linux__
    path = linPath;
#endif

    //Setup all the meshes
    mesh1.loadObj (path + "/Mesh1");
    //mesh.loadObj(path + "/Mesh2");

    mesh1.scaleUniform(0.004f);
    mesh1.moveMesh(Vector3f(0.3f, -0.9f, 0));

    //mesh.rotateMesh(Vector3D(1.0f, 2.0f, 1.0f), 1.9f);

    cam.addMeshToRenderQueue(&mesh);
    cam.addMeshToRenderQueue(&mesh1);
}
//Clean up your trash!
Widget::~Widget() {
    delete ui;
}

void Widget::paintEvent(QPaintEvent *){
    QPainter p(this);
    cam.render();

    p.drawImage(0, 0, *cam.frame);
    p.end();
}

//Catch the mouse!
void Widget::mousePressEvent(QMouseEvent *e) {
    switch (e->button()) {
    case Qt::LeftButton:
        leftMouse = true;
        break;
    case Qt::RightButton:
        rightMouse = true;
        break;
    case Qt::MiddleButton:
        middleMouse = true;
        break;
    default:
        break;
    }

    this->setCursor(Qt::BlankCursor);
    lastMousePos = QCursor::pos();
    if (alt) rotPoint = cam.getPointAtPixel(e->pos());
    pressPos = e->pos();
}
void Widget::mouseReleaseEvent(QMouseEvent *e) {
    switch (e->button()) {
    case Qt::LeftButton:
        leftMouse = false;
        break;
    case Qt::RightButton:
        rightMouse = false;
        break;
    case Qt::MiddleButton:
        middleMouse = false;
        break;
    default:
        break;
    }

    //Make the mouse visible again
    this->setCursor(Qt::ArrowCursor);
}
void Widget::mouseMoveEvent(QMouseEvent *e) {
    //get the current mouse position and calculate the amount of movement
    currentMousePos = e->globalPos();
    const int dx = currentMousePos.x() - lastMousePos.x();
    const int dy = currentMousePos.y() - lastMousePos.y();

    //Build up the rotation matrix
    const Matrix3x3 rotX = Matrix3x3().makeRotation(vec3f::yaxis, -dx / 250.0f);
    const Matrix3x3 rotY = Matrix3x3().makeRotation(cam.cx, -dy / 250.0f);
    const Matrix3x3 totalRot = rotX * rotY;
    if (!ctrl && !alt) {
        if (leftMouse || rightMouse) {
            cam.rotate(totalRot, leftMouse);
        } else if (middleMouse) {
            cam.move(cam.cx * (dx / 100.0f));
            cam.move(cam.cy * (-dy / 100.0f));
        }
    } else if (ctrl) {
        mesh1.rotateMesh(vec3f::yaxis, dx / 250.0f);
    } else if (alt) {
        const Vector3f moveVec = rotPoint - cam.eyePos;
        const float length = moveVec.length();
        if (leftMouse) {
            cam.rotate(vec3f::yaxis, -dx / 250.0f, rotPoint);
            cam.rotate(cam.cx, -dy / 250.0f, rotPoint);
        } else if (rightMouse) {
            cam.move(moveVec * (dx / (length * 250.0f)));
        } else if (middleMouse) {
            cam.move(cam.cx * (-length * dx / 300.0f));
            cam.move(cam.cy * (length * dy / 300.0f));
        }
    }
    //Reset the cursor to the middle of the screen if any mouse button was pressed (avoid hitting the screen bounds)
    QPoint globPos = mapToGlobal(pressPos);
    QCursor::setPos(globPos);
    lastMousePos = globPos;
}
void Widget::wheelEvent(QWheelEvent *e) {
    if (e->delta() > 0) cam.moveOnNormal(+.5f);
    else cam.moveOnNormal(-.5f);
}

//And the keyboard
void Widget::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_W:
        forward = true;
        break;
    case Qt::Key_S:
        backward = true;
        break;
    case Qt::Key_A:
        left = true;
        break;
    case Qt::Key_D:
        up = true;
        break;
    case Qt::Key_Q:
        cam.rotate(cam.cx, +0.1f);
        break;
    case Qt::Key_E:
        cam.rotate(cam.cx, -0.1f);
        break;
    case Qt::Key_Control:
        ctrl = true;
        break;
    case Qt::Key_Alt:
        alt = true;
        break;
    default:
        break;
    }
}
void Widget::keyReleaseEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_W:
        forward = false;
        break;
    case Qt::Key_S:
        backward = false;
        break;
    case Qt::Key_A:
        left = false;
        break;
    case Qt::Key_D:
        up = false;
        break;
    case Qt::Key_Control:
        ctrl = false;
        break;
    case Qt::Key_Alt:
        alt = false;
        break;
    default:
        break;
    }
}

//Give me all the pixels!
void Widget::resizeEvent(QResizeEvent *) {
    cam.setResolution(this->width(), this->height());
}

//Just draw the next frame dammit!
void Widget::updateScene() {
    //React to keyboard input
	if (forward) cam.moveOnNormal(+0.1f);
	if (backward) cam.moveOnNormal(-0.1f);
	if (up) cam.moveRight(+0.1f);
	if (left) cam.moveRight(-0.1f);
    //Apply transformation to meshes for animation
    //mesh1.rotateMesh(YAXIS, +0.05f);
    //mesh.rotateRelative(XAXIS, +0.01f);
    update();
}

//There is some UI as well!
void Widget::on_horizontalSlider_sliderMoved(int position) {
    cam.setFov(position);
    ui->label->setNum(position);
}
void Widget::on_pushButton_clicked() {
    cam.frame->save(QString::fromStdString(path) + "/Image.png");
}
