#include "particle.h"
#include "utilities.h"

Particle::Particle() {
    _mass = 1;
    _fixed = false;
    _pos = QVector3D(0,0,0);
    _oldPos = QVector3D(0,0,0);
    _force = QVector3D(0,0,0);
}

Particle::~Particle() {
}

void Particle::SetFixed(bool f) {
    _fixed = f;
}

void Particle::SetPos(QVector3D pos, bool init) {
    if (!_fixed) {
        _pos = pos;
    }

    if (init)
        _oldPos = _pos;
}

void Particle::SetPosX(float x) {
    _pos.setX(x);
}

void Particle::SetPosY(float y) {
    _pos.setY(y);
}

void Particle::SetPosZ(float z) {
    _pos.setZ(z);
}

QVector3D Particle::GetPos() {
    return _pos;
}

QVector3D Particle::GetOldPos() {
    return _oldPos;
}

void Particle::AddForce(QVector3D f) {
    _force += f;
}

void Particle::SetForce(QVector3D f) {
    _force = f;
}

QVector3D Particle::GetForce() {
    return _force;
}

void Particle::SetMass(GLdouble m) {
    _mass = m;
}

GLdouble Particle::GetMass() {
    return _mass;
}

void Particle::SetNormal(QVector3D n) {
    _normal = n;
}

QVector3D Particle::GetNormal() {
    return _normal;
}

void Particle::SimStep(float damping) {
    if (_fixed)
        return;

    QVector3D temp = _pos;
    _pos = _pos + (_pos-_oldPos) * (1.0-damping) + (_force / _mass) * SIMULATION_STEP;
    _oldPos = temp;
    _force *= 0;
}

void Particle::Draw(){
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3d(0.9, 1.0, 0.3);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex3f(_pos.x(), _pos.y(), _pos.z());
    glEnd();
    glEnable((GL_LIGHTING));
    glPopMatrix();
}

