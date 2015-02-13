#include "object.h"

Object::Object(object_t type, QVector3D pos, movement_t m) {
    _type = type;
    _pos = pos;
    _oldPos = pos;
    _radius = 1.5;
    _move = m;
    _direction = 1;
}

void Object::SetPosition(QVector3D pos) {
    _oldPos = _pos;
    _pos = pos;
}

QVector3D Object::GetPos() {
    return _pos;
}

QVector3D Object::GetOldPos() {
    return _oldPos;
}

GLfloat Object::GetRadius() {
    return _radius;
}

void Object::SetType(object_t type) {
    _type = type;
}

object_t Object::GetType() {
    return _type;
}

void Object::Draw() {
    glPushMatrix();
    glDisable(GL_TEXTURE_2D);
    switch (_type) {
    case BALL:
        glTranslatef(_pos.x(),_pos.y(),_pos.z());
        glColor3f(1.0f, 0.9f, 0.5f);
        GLUquadricObj *quadric;
        quadric = gluNewQuadric();
        gluSphere( quadric, _radius, 50, 50);
        break;
    case CUBE:
        glColor3f(0.6f, 0.4f, 0.2f);

        //back
        glBegin(GL_POLYGON);
        glNormal3f(0,0,-1);
        glVertex3f(_pos.x()-_radius, _pos.y()-_radius, _pos.z()-_radius);
        glVertex3f(_pos.x()+_radius, _pos.y()-_radius, _pos.z()-_radius);
        glVertex3f(_pos.x()+_radius, _pos.y()+_radius, _pos.z()-_radius);
        glVertex3f(_pos.x()-_radius, _pos.y()+_radius, _pos.z()-_radius);
        glEnd();

        //front
        glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        glVertex3f(_pos.x()-_radius, _pos.y()-_radius, _pos.z()+_radius);
        glVertex3f(_pos.x()+_radius, _pos.y()-_radius, _pos.z()+_radius);
        glVertex3f(_pos.x()+_radius, _pos.y()+_radius, _pos.z()+_radius);
        glVertex3f(_pos.x()-_radius, _pos.y()+_radius, _pos.z()+_radius);
        glEnd();

        //down
        glBegin(GL_POLYGON);
        glNormal3f(0,-1,0);
        glVertex3f(_pos.x()-_radius, _pos.y()-_radius, _pos.z()-_radius);
        glVertex3f(_pos.x()-_radius, _pos.y()-_radius, _pos.z()+_radius);
        glVertex3f(_pos.x()+_radius, _pos.y()-_radius, _pos.z()+_radius);
        glVertex3f(_pos.x()+_radius, _pos.y()-_radius, _pos.z()-_radius);
        glEnd();

        //top
        glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(_pos.x()-_radius, _pos.y()+_radius, _pos.z()-_radius);
        glVertex3f(_pos.x()-_radius, _pos.y()+_radius, _pos.z()+_radius);
        glVertex3f(_pos.x()+_radius, _pos.y()+_radius, _pos.z()+_radius);
        glVertex3f(_pos.x()+_radius, _pos.y()+_radius, _pos.z()-_radius);
        glEnd();

        //right
        glBegin(GL_POLYGON);
        glNormal3f(1,0,0);
        glVertex3f(_pos.x()+_radius, _pos.y()+_radius, _pos.z()-_radius);
        glVertex3f(_pos.x()+_radius, _pos.y()+_radius, _pos.z()+_radius);
        glVertex3f(_pos.x()+_radius, _pos.y()-_radius, _pos.z()+_radius);
        glVertex3f(_pos.x()+_radius, _pos.y()-_radius, _pos.z()-_radius);
        glEnd();

        //left
        glBegin(GL_POLYGON);
        glNormal3f(-1,0,0);
        glVertex3f(_pos.x()-_radius, _pos.y()+_radius, _pos.z()-_radius);
        glVertex3f(_pos.x()-_radius, _pos.y()+_radius, _pos.z()+_radius);
        glVertex3f(_pos.x()-_radius, _pos.y()-_radius, _pos.z()+_radius);
        glVertex3f(_pos.x()-_radius, _pos.y()-_radius, _pos.z()-_radius);
        glEnd();

        break;
    case IMPORTED:
        break;
    };
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();

}

void Object::SimStep() {
    switch (_move) {
    case FALLING:
        _pos.setY(_pos.y() + 0.5 * GRAVITY * SIMULATION_STEP);
        break;
    case BOUNCING:
        if (_pos.z() < -10 || _pos.z() > 10)
            _direction *= -1;
        _oldPos = _pos;
        _pos.setZ(_pos.z() + _direction * SIMULATION_STEP * 0.5);
        break;
    case STATIONARY:
        break;
    };
}
