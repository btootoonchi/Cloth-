#include "cloth.h"

Cloth::Cloth(cloth_t type, GLdouble width, GLdouble height, GLuint x, GLuint y) {

    _type = type;
    _width = x;
    _height = y;
    _texture = 0;
    _damping = 0.01;
    _thickness = 0.2;

    _particleMatrix = new Particle *[_height];
    for (size_t i=0; i<_height; i++) {
        _particleMatrix[i] = new Particle[_width];
    }

    ResetPosition(width, height);

    // Connect neighbor particles
    for(size_t j=0; j<_width; j++) {
        for(size_t i=0; i<_height; i++) {

            //structural horizental springs
            if (j < _width-1)
                _springs.push_back(Spring(&_particleMatrix[i][j],&_particleMatrix[i][j+1]));

            //structural vertical springs
            if (i < _height-1)
                _springs.push_back(Spring(&_particleMatrix[i][j],&_particleMatrix[i+1][j]));

            //shear springs
            if (j < _width-1 && i < _height-1) {
                _springs.push_back(Spring(&_particleMatrix[i][j],&_particleMatrix[i+1][j+1]));
                _springs.push_back(Spring(&_particleMatrix[i][j+1],&_particleMatrix[i+1][j]));
            }
        }
    }

    // Connect neighbor particles with distance two
    for(size_t j=0; j<_width; j++) {
        for(size_t i=0; i<_height; i++) {
            //structural horizental springs
            if (j < _width-2)
                _springs.push_back(Spring(&_particleMatrix[i][j],&_particleMatrix[i][j+2]));

            //structural vertical springs
            if (i < _height-2)
                _springs.push_back(Spring(&_particleMatrix[i][j],&_particleMatrix[i+2][j]));

            //shear springs
            if (j < _width-2 && i < _height-2) {
                _springs.push_back(Spring(&_particleMatrix[i][j],&_particleMatrix[i+2][j+2]));
                _springs.push_back(Spring(&_particleMatrix[i][j+2],&_particleMatrix[i+2][j]));
            }
        }
    }

    _wind = QVector3D(0.5, 0.5, 0.1);
    _textureHandle = 0;

}

Cloth::~Cloth() {
    for (size_t i=0; i<_height; i++) {
        delete []_particleMatrix[i];
    }
    delete []_particleMatrix;
}

void Cloth::Draw() {
    //default texture
    if (_texture == 0)
        DrawDefaultTexture();
    else
        DrawTexture();
}

void Cloth::DrawTriangle(Particle *p1, Particle *p2, Particle *p3, const QVector3D color) {
    glColor3f(color.x(),color.y(),color.z());

    QVector3D instance = p1->GetNormal().normalized();
    glNormal3f(instance.x(),instance.y(),instance.z());
    glVertex3f(p1->GetPos().x(),p1->GetPos().y(),p1->GetPos().z());

    instance = p2->GetNormal().normalized();
    glNormal3f(instance.x(),instance.y(),instance.z());
    glVertex3f(p2->GetPos().x(),p2->GetPos().y(),p2->GetPos().z());

    instance = p3->GetNormal().normalized();
    glNormal3f(instance.x(),instance.y(),instance.z());
    glVertex3f(p3->GetPos().x(),p3->GetPos().y(),p3->GetPos().z());
}

void Cloth::DrawDefaultTexture() {
    QVector3D normal;

    // reset normals (which where written to last frame)
    for (size_t i = 0; i < _height; i++) {
        for (size_t j = 0; j < _width; j++) {
            _particleMatrix[i][j].SetNormal(QVector3D(0,0,0));
        }
    }

    //create smooth per particle normals by adding up all the (hard) triangle normals that each particle is part of
    for (size_t y = 0; y < _width-1; y++) {
        for (size_t x = 0; x < _height-1; x++) {
            normal = calculateNormal(&_particleMatrix[x][y+1],&_particleMatrix[x][y],&_particleMatrix[x+1][y]);
            _particleMatrix[x][y+1].SetNormal(_particleMatrix[x][y+1].GetNormal()+normal.normalized());
            _particleMatrix[x][y].SetNormal(_particleMatrix[x][y].GetNormal()+normal.normalized());
            _particleMatrix[x+1][y].SetNormal(_particleMatrix[x+1][y].GetNormal()+normal.normalized());

            normal = calculateNormal(&_particleMatrix[x+1][y+1],&_particleMatrix[x][y+1],&_particleMatrix[x+1][y]);
            _particleMatrix[x+1][y+1].SetNormal(_particleMatrix[x+1][y+1].GetNormal()+normal.normalized());
            _particleMatrix[x][y+1].SetNormal(_particleMatrix[x][y+1].GetNormal()+normal.normalized());
            _particleMatrix[x+1][y].SetNormal(_particleMatrix[x+1][y].GetNormal()+normal.normalized());
        }
    }

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    for (size_t y = 0; y < _width-1; y++) {
        for (size_t x = 0; x < _height-1; x++) {
            QVector3D color(0,0,0);
            if (y%2 && x%2)
                color = QVector3D(0.9f,0.5f,0.6f);
            else if (y%2 && !(x%2))
                color = QVector3D(0.99f,0.88f,0.95f);
            else if (!(y%2) && x%2)
                color = QVector3D(1.0f,1.0f,1.0f);
            else if (!(y%2) && !(x%2))
                color = QVector3D(0.9f,0.6f,0.7f);

            DrawTriangle(&_particleMatrix[x][y+1],&_particleMatrix[x][y],&_particleMatrix[x+1][y],color);
            DrawTriangle(&_particleMatrix[x+1][y+1],&_particleMatrix[x][y+1],&_particleMatrix[x+1][y],color);
        }
    }
    glEnd();
    glPopMatrix();
}

void Cloth::ResetPosition(GLdouble width, GLdouble height) {
    switch (_type) {
    case FLAG:
        for(size_t i=0; i<_height; i++) {
            for(size_t j=0; j<_width; j++) {
                _particleMatrix[i][j].SetPos(QVector3D(width * (j/(GLdouble)_width) - 3, 8-height * (i/(GLdouble)_height), 0),true);
                if ((j == 0) && ( i < 3  || i >= _height - 3))
                    _particleMatrix[i][j].SetFixed(true);
            }
        }
        break;
    case CURTAIN:
        for(size_t i=0; i<_height; i++) {
            for(size_t j=0; j<_width; j++) {
                _particleMatrix[i][j].SetPos(QVector3D(width * (j/(GLdouble)_width) - 5, 8-height * (i/(GLdouble)_height), 0),true);
                if ((i == 0) && ( j < 3  || j >= _width - 3))
                    _particleMatrix[i][j].SetFixed(true);
            }
        }
        break;
    case SINGLE_PIN:
        for(size_t i=0; i<_height; i++) {
            for(size_t j=0; j<_width; j++) {
                _particleMatrix[i][j].SetPos(QVector3D(width * (j/(GLdouble)_width) - 5, 5, height * (i/(GLdouble)_height) - 5),true);
                if ((i == _height/2) && ( j == _width/2))
                    _particleMatrix[i][j].SetFixed(true);
            }
        }
        break;
    case COVER:
        for(size_t i=0; i<_height; i++) {
            for(size_t j=0; j<_width; j++) {
                _particleMatrix[i][j].SetPos(QVector3D(width * (j/(GLdouble)_width) - 5, 8, height * (i/(GLdouble)_height) - 5),true);
            }
        }
        break;
    };
}

QVector3D Cloth::calculateNormal(Particle *p1,Particle *p2,Particle *p3) {
    return QVector3D::crossProduct((p2->GetPos() - p1->GetPos()),(p3->GetPos() - p1->GetPos()));
}

void Cloth::SetWind(QVector3D w) {
    _wind = w;
}

QVector3D Cloth::GetWind() {
    return _wind;
}

void Cloth::SetTexture(GLuint t) {
    _texture = t;
}

GLuint Cloth::GetTexture() {
    return _texture;
}

void Cloth::SetThickness(float t) {
    _thickness = t;
}

float Cloth::GetThickness() {
    return _thickness;
}

void Cloth::SetDamping(float d) {
    _damping = d;
}

float Cloth::GetDamping() {
    return _damping;
}

void Cloth::SetType(cloth_t t) {
   _type = t;
}

cloth_t Cloth::GetType() {
    return _type;
}

void Cloth::LoadTexture() {
    //creating texture objects and returning handlers
    glGenTextures(0, &_textureHandle);

    //load image and return its color as an array
    QImage *image = new QImage();
    unsigned char *data;
    bool loaded = (_texture == 1) ? image->load(QString("../ClothSimulation/Textures/texture1.jpg")):
                                    image->load(QString("../ClothSimulation/Textures/texture3.jpg"));

    unsigned int index = 0;
    if(loaded) {
        data = new unsigned char[image->width() * image->height() * 4];

        QRgb color;
        for (int y = 0;y < image->height(); ++y) {
            for(int x = 0;x < image->width(); ++x) {
                color = image->pixel(x,y);

                data[index++] = qRed(color);
                data[index++] = qGreen(color);
                data[index++] = qBlue(color);
                data[index++] = qAlpha(color);
            }
        }
    }

    //load texture into the texture object
    glBindTexture(GL_TEXTURE_2D, _textureHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, 4, image->width() , image->height(), 0, GL_RGBA,GL_UNSIGNED_BYTE, data);
}

void Cloth::DrawTexture() {
    glPushMatrix();
    double wstep = 1.0 / _width;
    double hstep = 1.0 / _height;
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, _textureHandle);
    glBegin(GL_QUADS);
    for (size_t i = 0; i < _height-1; i++) {
        for (size_t j = 0; j < _width-1; j++) {
            glTexCoord2f(i * hstep, j * wstep);
            glVertex3f(_particleMatrix[i][j].GetPos().x(), _particleMatrix[i][j].GetPos().y(), _particleMatrix[i][j].GetPos().z());

            glTexCoord2f(i * hstep, (j + 1) * wstep);
            glVertex3f(_particleMatrix[i][j+1].GetPos().x(), _particleMatrix[i][j+1].GetPos().y(), _particleMatrix[i][j+1].GetPos().z());

            glTexCoord2f((i + 1) * hstep, (j + 1) * wstep);
            glVertex3f(_particleMatrix[i+1][j+1].GetPos().x(), _particleMatrix[i+1][j+1].GetPos().y(), _particleMatrix[i+1][j+1].GetPos().z());

            glTexCoord2f((i + 1) * hstep, j * wstep);
            glVertex3f(_particleMatrix[i+1][j].GetPos().x(), _particleMatrix[i+1][j].GetPos().y(), _particleMatrix[i+1][j].GetPos().z());
        }
    }
    glEnd();
    glPopMatrix();
}

void Cloth::ApplyGravityForce() {
    for(size_t i = 0; i < _height; i++) {
        for(size_t j = 0; j < _width; j++) {
            _particleMatrix[i][j].SetForce(0.005 * GRAVITY * QVector3D(0,1,0));
        }
    }
}

void Cloth::ApplyPlaneForce(Particle *p1, Particle *p2, Particle *p3, QVector3D force) {
    QVector3D n = calculateNormal(p1, p2, p3);
    QVector3D normal = n.normalized();
    QVector3D windForce = QVector3D::dotProduct(normal,force)*n;
    p1->AddForce(windForce);
    p2->AddForce(windForce);
    p3->AddForce(windForce);
}

void Cloth::ApplyWindForce() {
    for(size_t j = 0; j < _width-1; j++) {
        for(size_t i = 0; i < _height-1; i++) {

            //the upper left triangle
            ApplyPlaneForce(&_particleMatrix[i][j+1], &_particleMatrix[i][j], &_particleMatrix[i+1][j], _wind);

            //the lower right triangle
            ApplyPlaneForce(&_particleMatrix[i+1][j+1], &_particleMatrix[i][j+1], &_particleMatrix[i+1][j], _wind);
        }
    }
}

void Cloth::SelfCollision() {
    QVector3D response;
    QVector3D distance;
    for(size_t pi = 0; pi < _height; pi++) {
        for(size_t pj = 0; pj < _width; pj++) {
            for(size_t i = 0; i < pi; i++) {
                for(size_t j = 0; j < pj; j++) {

                    //do not check adjacent particles
                    if (abs(i-pi) < 2 && abs(j-pj) < 2)
                        continue;

                    distance = _particleMatrix[i][j].GetPos() - _particleMatrix[pi][pj].GetPos();
                    if (distance.length() == 0) {
                        distance =_particleMatrix[i][j].GetOldPos()-_particleMatrix[pi][pj].GetOldPos();
                        response = 0.1 * (distance/distance.length());
                    } else {
                        response = distance * (1 - 0.1/distance.length());
                    }

                    if (distance.length() < 0.1) {
                        _particleMatrix[pi][pj].SetPos(_particleMatrix[pi][pj].GetPos() + 0.5 * response);
                        _particleMatrix[i][j].SetPos(_particleMatrix[i][j].GetPos() - 0.5 * response);
                    }
                }
            }
        }
    }
}


void Cloth::BallCollision(const QVector3D center, const float radius) {
    for(size_t i = 0; i < _height; i++) {
        for(size_t j = 0; j < _width; j++) {
            QVector3D distance = _particleMatrix[i][j].GetPos() - center;
            if (distance.length() <= radius + 0.1)
                _particleMatrix[i][j].SetPos(distance.normalized() * (radius + _thickness - distance.length()) + _particleMatrix[i][j].GetPos());
        }
    }
}

QVector3D Cloth::linePlaneIntersection(QVector3D oldPos, QVector3D newPos, QVector3D p1, QVector3D p2, QVector3D p3) {
    QVector3D Direction = oldPos - newPos;
    QVector3D n = QVector3D::crossProduct(p2 - p1, p3 - p1);
    n = n.normalized();

    float normalDirection = QVector3D::dotProduct(Direction, n);

    //check to see if line and plane are parallel
    if(normalDirection == 0) {
        return newPos;
    }

    GLdouble distanceToPlane = QVector3D::dotProduct(p1 - newPos, n)/normalDirection;
    return (newPos + distanceToPlane*Direction);
}

void Cloth::CubeCollision(QVector3D oldCenter, QVector3D center, float radius) {
    QVector3D adjustedPos;
    float r = radius + _thickness;
    for(size_t i = 0; i < _height; i++) {
        for(size_t j = 0; j < _width; j++) {
            QVector3D newPos = _particleMatrix[i][j].GetPos();
            QVector3D newDistance = newPos - center;

            if (fabs(newDistance.x()) < r && fabs(newDistance.y()) < r && fabs(newDistance.z()) < r) {
                QVector3D oldPos = _particleMatrix[i][j].GetOldPos();
                QVector3D oldDistance = oldPos - oldCenter;
                if (oldDistance.x() >= r)
                    adjustedPos = linePlaneIntersection(oldPos, newPos+QVector3D(center.x()-oldCenter.x(),0,0),
                                  center + QVector3D(r,0,0), center + QVector3D(r,0,-1), center + QVector3D(r,1,0));
                else if (oldDistance.x() <= -r) {
                    adjustedPos = linePlaneIntersection(oldPos, newPos+QVector3D(center.x()-oldCenter.x(),0,0),
                                  center + QVector3D(-r,0,0), center + QVector3D(-r,0,-1), center + QVector3D(-r,-1,0));
                } else if (oldDistance.y() >= r) {
                        adjustedPos = linePlaneIntersection(oldPos, newPos+QVector3D(0,center.y()-oldCenter.y(),0),
                                  center + QVector3D(0,r,0), center + QVector3D(1,r,0), center + QVector3D(0,r,-1));
                } else if (oldDistance.y() <= -r) {
                    adjustedPos = linePlaneIntersection(oldPos, newPos+QVector3D(0,center.y()-oldCenter.y(),0),
                                  center + QVector3D(0,-r,0), center + QVector3D(-1,-r,0), center + QVector3D(0,-r,-1));
                } else if (oldDistance.z() >= r) {
                    adjustedPos = linePlaneIntersection(oldPos, newPos+QVector3D(0,0,center.z()-oldCenter.z()),
                                  center + QVector3D(0,0,r), center + QVector3D(1,0,r), center + QVector3D(0,1,r));
                } else if (oldDistance.z() <= -r) {
                    adjustedPos = linePlaneIntersection(oldPos, newPos+QVector3D(0,0,center.z()-oldCenter.z()),
                                  center + QVector3D(0,0,-r), center + QVector3D(1,0,-r), center + QVector3D(0,-1,-r));
                }
                _particleMatrix[i][j].SetPos(adjustedPos);
            }
        }
    }
}

void Cloth::GroundCollision() {
    for(size_t i = 0; i < _height; i++) {
        for(size_t j = 0; j < _width; j++) {
            if (_particleMatrix[i][j].GetPos().y() < 0)
                _particleMatrix[i][j].SetPosY(0);
        }
    }
}

void Cloth::CheckConstraints() {
    // apply spring effects in several iterations
    for(size_t i=0; i<SPRING_ITERATIONS; i++) {
        for(size_t j = 0; j < _springs.size(); j++) {
            _springs[j].ApplyConstraints();
        }
    }
}

void Cloth::SimStep() {

    //Apply gravity and wind forces
    ApplyGravityForce();
    ApplyWindForce();

    //apply the forces and update the positions
    for(size_t i = 0; i < _height; i++) {
        for(size_t j = 0; j < _width; j++) {
            _particleMatrix[i][j].SimStep(_damping);
        }
    }
    CheckConstraints();
}
