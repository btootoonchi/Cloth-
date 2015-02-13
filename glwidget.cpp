#include "glwidget.h"
#include <QtOpenGL>

const float cameraStep = 2;
const float projectScale = 1;

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent) {
    _time = -1;

    _viewRotatey = 0;
    _viewRotateVert = 6;
    _zoom = -5;

    _objectPosition.setX(1.0);
    _objectPosition.setY(3.0);
    _objectPosition.setZ(0);

    _cameraPosition.setX(0);
    _cameraPosition.setY(5.0);
    _cameraPosition.setZ(8.0);

    //set the default to flag
    _cloth = new Cloth(FLAG, 6, 4, 45, 35);
    _object = NULL;
}

GLWidget::~GLWidget() {
    delete _cloth;
}

void GLWidget::initializeGL() {
    // initialize
    makeCurrent();

    glEnable(GL_DEPTH_TEST);
    static const GLfloat lightPos[4] = { 6.0f, 6.0f, 6.0f, 1.0f };
    static const GLfloat lightPos2[4] = { -6.0f, 6.0f, -6.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glClearColor(0.5f, 0.7f, 0.9f, 1.0f);

    glEnable(GL_TEXTURE_2D);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, 1.0, 0.5, 500.0 );
    gluLookAt( _cameraPosition.x(), _cameraPosition.y(), _cameraPosition.z(),
               _objectPosition.x(), _objectPosition.y(), _objectPosition.z(),
               0.0, 1.0, 0.0 );

    //camera
    glTranslatef(0, -0.5 * projectScale, _zoom);
    glRotatef(_viewRotateVert, 1, 0, 0);
    glRotatef(_viewRotatey, 0, 1 ,0);

    //draw a 3d grid on the ground
    Draw3DGrid();

    //check for collisions
    DetectCollision();

    //draw flag pole or curtain rod
    DrawRacks();

    //draw cloth and object
    _cloth->Draw();
    if (_object)
        _object->Draw();
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, w/(float)h, 0.5, 500.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
    case Qt::Key_D:
        _viewRotatey += cameraStep;
        updateGL();
        break;

    case Qt::Key_A:
        _viewRotatey -= cameraStep;
        updateGL();
        break;

    case Qt::Key_R:
        if(_viewRotateVert < 90) {
            _viewRotateVert += cameraStep;
            updateGL();
        }
        break;

    case Qt::Key_F:
        if(_viewRotateVert > -90) {
            _viewRotateVert -= cameraStep;
            updateGL();
        }
        break;

    case Qt::Key_S:
        if(_zoom > -58*projectScale) {
            _zoom -= cameraStep*projectScale;
            updateGL();
        }
        break;

    case Qt::Key_W:
        if(_zoom <= 2*projectScale) {
            _zoom += cameraStep*projectScale;
            updateGL();
        }
        break;
    }
}

void GLWidget::Draw3DGrid() {
    glPushMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glLineWidth(1.0f);
    glColor3f(0.3f, 0.6f, 0.3f);

    for(float i = -10; i <= 10; i += 0.5) {
        glBegin(GL_LINES);

        //along x axis
        glVertex3f(-10, -2, i);
        glVertex3f(10, -2, i);

        //along z axis
        glVertex3f(i, -2, -10);
        glVertex3f(i, -2, 10);

        glEnd();
    }
    glEnable(GL_LIGHTING);
    if (_cloth->GetTexture() != 0)
        glEnable(GL_TEXTURE_2D);
    glPopMatrix();
}

void GLWidget::DrawRacks() {
    glPushMatrix();
    glDisable(GL_TEXTURE_2D);

    if (_cloth->GetType() == FLAG) {
        glTranslatef(-3,8,0);
        glRotatef(90,1,0,0);
        glColor3f(0.6f, 0.4f, 0.2f);
        GLUquadricObj *quadric;
        quadric = gluNewQuadric();
        gluCylinder( quadric, 0.1, 0.1, 8, 50, 50);
    } else if (_cloth->GetType() == CURTAIN) {
        glTranslatef(-5,8,0);
        glRotatef(90,0,1,0);
        glColor3f(0.6f, 0.4f, 0.2f);
        GLUquadricObj *quadric;
        quadric = gluNewQuadric();
        gluCylinder( quadric, 0.1, 0.1, 9.8, 50, 50);
    }
    if (_cloth->GetTexture() != 0)
        glEnable(GL_TEXTURE_2D);
    glPopMatrix();
}

void GLWidget::DetectCollision() {
    if (!_object)
        return;
    if (_object->GetType() == BALL)
        _cloth->BallCollision(_object->GetPos(), _object->GetRadius());
    else if (_object->GetType() == CUBE) {
        _cloth->CubeCollision(_object->GetOldPos(), _object->GetPos(), _object->GetRadius());
    }
}

GLdouble GLWidget::GetSimulationTime() {
    return _time;
}

void GLWidget::SetSimulationTime(GLdouble time) {
    _time = time;
}

void GLWidget::SetFlagModel() {
    QVector3D wind = _cloth->GetWind();
    GLuint texture = _cloth->GetTexture();
    float damping = _cloth->GetDamping();
    delete _cloth;
    _cloth = new Cloth(FLAG, 6, 4, 45, 35);
    _cloth->SetWind(wind);
    _cloth->SetTexture(texture);
    _cloth->SetDamping(damping);
    delete _object;
    _object = NULL;
    updateGL();
}

void GLWidget::SetCurtainModel() {
    QVector3D wind = _cloth->GetWind();
    GLuint texture = _cloth->GetTexture();
    float damping = _cloth->GetDamping();
    delete _cloth;
    _cloth = new Cloth(CURTAIN, 10, 10, 50, 50);
    _cloth->SetWind(wind);
    _cloth->SetTexture(texture);
    _cloth->SetDamping(damping);
    delete _object;
    _object = NULL;
    updateGL();
}

void GLWidget::SetSinglePinModel() {
    QVector3D wind = _cloth->GetWind();
    GLuint texture = _cloth->GetTexture();
    float damping = _cloth->GetDamping();
    delete _cloth;
    _cloth = new Cloth(SINGLE_PIN, 10, 10, 50, 50);
    _cloth->SetWind(wind);
    _cloth->SetTexture(texture);
    _cloth->SetDamping(damping);
    delete _object;
    _object = NULL;
    updateGL();
}

void GLWidget::SetJimboModel() {
    QVector3D wind = _cloth->GetWind();
    GLuint texture = _cloth->GetTexture();
    float damping = _cloth->GetDamping();
    delete _cloth;
    _cloth = new Cloth(CURTAIN, 10, 10, 50, 50);
    _cloth->SetWind(wind);
    _cloth->SetTexture(texture);
    _cloth->SetDamping(damping);
    object_t type = BALL;
    if (_object) {
        type = _object->GetType();
        delete _object;
    }
    _object = new Object(type,QVector3D(0,3,-5),BOUNCING);
    updateGL();
}

void GLWidget::SetCoverModel() {
    GLuint texture = _cloth->GetTexture();
    float damping = _cloth->GetDamping();
    delete _cloth;
    _cloth = new Cloth(COVER, 10, 10, 50, 50);
    _cloth->SetTexture(texture);
    _cloth->SetWind(QVector3D(0,0.2,0));            //simulate air resistance
    _cloth->SetDamping(damping);
    object_t type = BALL;
    if (_object) {
        type = _object->GetType();
        delete _object;
    }
    _object = new Object(type,QVector3D(0,2,0),STATIONARY);
    updateGL();
}

void GLWidget::SetBallObject() {
    _object->SetType(BALL);
     updateGL();
}

void GLWidget::SetCubeObject() {
    _object->SetType(CUBE);
     updateGL();
}

void GLWidget::SetTexture1() {
    glDisable(GL_TEXTURE_2D);
    glLoadIdentity();
    _cloth->SetTexture(0);
    updateGL();
}

void GLWidget::SetTexture2() {
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
    _cloth->SetTexture(1);
    _cloth->LoadTexture();
    updateGL();
}

void GLWidget::SetTexture3() {
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
    _cloth->SetTexture(2);
    _cloth->LoadTexture();
    updateGL();
}

void GLWidget::SetThickness(int d) {
    _cloth->SetDamping(d*0.01);
    updateGL();
}

void GLWidget::SetXWind(double x) {
    _cloth->SetWind(QVector3D((float)0.1*x,_cloth->GetWind().y(),_cloth->GetWind().z()));
}

void GLWidget::SetYWind(double y) {
    _cloth->SetWind(QVector3D(_cloth->GetWind().x(),(float)0.1*y,_cloth->GetWind().z()));
}

void GLWidget::SetZWind(double z) {
    _cloth->SetWind(QVector3D(_cloth->GetWind().x(),_cloth->GetWind().y(),(float)0.1*z));
}

void GLWidget::ApplyWind() {
    _cloth->SetWind(QVector3D(0.1,0,0.5));
}

void GLWidget::StartAnimation() {
    if (_time >= 0)
        _time = -1;
    else
        _time = 0;
}

void GLWidget::Animate() {
    if (_time >= 0) {
        if (_object)
            _object->SimStep();
        _cloth->SimStep();
        _time += SIMULATION_STEP;
        updateGL();
    }
}

void GLWidget::ResetAnimation() {
    if (_cloth->GetType() == COVER)
        emit(SetCoverModel());
    else
        emit(SetJimboModel());
    _time = 0;
    updateGL();
}
