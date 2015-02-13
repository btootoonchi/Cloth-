/*!
 *  \author    Babak Tootoonchi
 *  \date      December 2014
 */

#ifndef CLOTH_H
#define CLOTH_H

#include "Utilities.h"
#include "spring.h"
#include "particle.h"

class Cloth
{
public:
    //! Constructor
    Cloth(cloth_t type, GLdouble width, GLdouble height, GLuint x, GLuint y);

    //! Destructor
    ~Cloth();

    /*! Set the wind that is applied to the cloth.
     * \param w wind vector
     */
    void SetWind(QVector3D w);

    //! Get the wind vector that is applied to the cloth.
    QVector3D GetWind();

    /*! Set the cloth texture.
     * \param t texture index
     */
    void SetTexture(GLuint t);

    //! Get the cloth texture.
    GLuint GetTexture();

    /*! Set the thickness of the cloth.
     * \param t cloth thickness
     */
    void SetThickness(float t);

    //! Get the thickness of the cloth.
    float GetThickness();

    /*! Set the damping of the cloth.
     * \param d damping of the cloth
     */
    void SetDamping(float d);

    //! Get the damping of the cloth.
    float GetDamping();

    /*! Set the type of the cloth.
     * \param t type of the cloth
     */
    void SetType(cloth_t t);

    //! Get the type of the cloth.
    cloth_t GetType();

    //! Initialize the texture of the cloth.
    void LoadTexture();

    //! Draw the texture
    void DrawTexture();

    //! Draw the cloth.
    void Draw();

    /*! Draw the given triangle.
     * \param p1 vertice of a tirangle.
     * \param p2 vertice of a tirangle.
     * \param p3 vertice of a tirangle.
     * \param color the color of cloth.
     */
    void DrawTriangle(Particle *p1, Particle *p2, Particle *p3, const QVector3D color);

    //! Draw default texture.
    void DrawDefaultTexture();

    //! Calculate and apply the gravity force to all of particles in the cloth.
    void ApplyGravityForce();

    //! Calculate and apply the wind force to all of particles in the cloth.
      void ApplyWindForce();

    //! Check the spring constraints and update the positions.
    void CheckConstraints();

    //! Perform the simulation for the next time interval.
    void SimStep();

    /*!
     * \brief Apply the given force to the vertices in the given plane.
     * \param force the force that is applied.
     * \param p1 vertice of a tirangle.
     * \param p2 vertice of a tirangle.
     * \param p3 vertice of a tirangle.
     */
    void ApplyPlaneForce(Particle *p1, Particle *p2, Particle *p3, QVector3D force);

    //! Detect collision of every particle with other particles in the cloth and remove collision by adjusting the positions.
    void SelfCollision();

    /*!
     * \brief Detect collision of cloth and a ball, and reponse.
     * \param center the center of the ball.
     * \param radius the radiuse of the ball.
     */
    void BallCollision(const QVector3D center,const float radius);

    /*!
     * \brief Return the intersection of the given line and plane.
     * \param oldPos head of the line which is the position of the particle in the last time step.
     * \param newPos tail of the line which is the position of the particle in the last time step.
     * \param p1 a vertice on the plane.
     * \param p2 a vertice on the plane.
     * \param p3 a vertice on the plane.
     */
    QVector3D linePlaneIntersection(QVector3D oldPos, QVector3D newPos, QVector3D p1, QVector3D p2, QVector3D p3);

    /*!
     * \brief Detect collision of cloth and a cube, and reponse.
     * \param oldCenter position of the center of the cube in previous time step.
     * \param center position of the center of the cube.
     * \param radius distance from the center to any of the cube faces.
     */
    void CubeCollision(QVector3D oldCenter, QVector3D center, float radius);

    //! Detect collision of cloth with ground.
    void GroundCollision();

    /*!
     * \brief Reset position of cloth in different simulation.
     * \param width width of cloth.
     * \param height height of cloth.
     */
    void ResetPosition(GLdouble width, GLdouble height);

    /*!
     * \brief calculate dotproduct of three vertice of a triangle.
     * \param p1 vertice of a tirangle.
     * \param p2 vertice of a tirangle.
     * \param p3 vertice of a tirangle.
     */
    QVector3D calculateNormal(Particle *p1,Particle *p2,Particle *p3);

private:
    //! Width of the cloth
    GLuint _width;

    //! Height of the cloth
    GLuint _height;

    //! Damping of the cloth that is given as a parameter to simulate cloth thickness
    GLfloat _damping;

    //! Texture of the cloth
    GLuint _texture;

    //! Wind vector
    QVector3D _wind;

    //! Type of cloth for this particular simulation
    cloth_t _type;

    //! The thickness of the cloth for drawing
    GLfloat _thickness;

    //! Particle matrix
    Particle **_particleMatrix;

    std::vector<Spring> _springs;

    //! the texture handler
    GLuint _textureHandle;
};

#endif // CLOTH_H
