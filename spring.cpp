#include "spring.h"

Spring::Spring(Particle *head, Particle *tail) {
    _head = head;
    _tail = tail;
    _restLength = (_tail && _head) ? (_tail->GetPos() - _head->GetPos()).length() : 0;
}

Spring::Spring() {
    Spring(NULL, NULL);
}

void Spring::SetRestLength(GLdouble len) {
    _restLength = len;
}

GLdouble Spring::GetRestLength() {
    return _restLength;
}

void Spring::SetPostion(Particle *head, Particle *tail) {
    _head = head;
    _tail = tail;
}

void Spring::ApplyConstraints() {
    QVector3D springEffect;
    QVector3D distance = _tail->GetPos()-_head->GetPos();
    if (distance.length() == 0) {
        distance = _tail->GetOldPos()-_head->GetOldPos();
        springEffect = _restLength * (distance/distance.length());
    } else {
        springEffect = distance * (1 - _restLength/distance.length());
    }

    //apply spring effect equally to both ends
    _head->SetPos(_head->GetPos() + springEffect * 0.5);
    _tail->SetPos(_tail->GetPos() - springEffect * 0.5);
}

Particle *Spring::GetHead() {
    return _head;
}

Particle *Spring::GetTail() {
    return _tail;
}

void Spring::Draw() {
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3d(1.0, 1.0, 1.0);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex3d(_head->GetPos().x(), _head->GetPos().y(), _head->GetPos().z());
    glVertex3d(_tail->GetPos().x(), _tail->GetPos().y(), _tail->GetPos().z());
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();
}
