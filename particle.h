/*!
 *  \author    Babak Tootoonchi
 *  \date      December 2014
 */

#ifndef WEIGHT_H
#define WEIGHT_H

#include "Utilities.h"

class Spring;

/*! The particle class is for simulating particles and their movement. */
class Particle
{
public:
    //! CONSTRUCTOR
    /*! Initializes particle parameters to default values. */
    Particle();

    //! DESTRUCTOR
    /*! Clears the spring vector for each particle. */
    ~Particle();

    /*!
     * \brief Sets the particle to a fixed position or to a moving particle.
     * \param[in] f enable or disable stationary attirbute.
     */
    void SetFixed(bool f);

    /*!
     * \brief Sets the current position of the particle to the given value.
     * \param pos new position of the particle.
     */
    void SetPos(QVector3D pos, bool init=false);

    /*!
     * \brief Sets the X position of the particle to the given value.
     * \param x new x position of the particle.
     */
    void SetPosX(float x);

    /*!
     * \brief Sets the Y position of the particle to the given value.
     * \param y new y position of the particle.
     */
    void SetPosY(float y);

    /*!
     * \brief Sets the Z position of the particle to the given value.
     * \param z new z position of the particle.
     */
    void SetPosZ(float z);

    /*!
     * \brief Gets the old position of the particle.
     * \return returns the old position of the particle.
     */
    QVector3D GetOldPos();

    /*!
     * \brief Returns the current position of the particle.
     * \return the position of the particle.
     */
    QVector3D GetPos();

    /*!
     * \brief Add the given force to the total forces on the particle.
     * \param[in] f force on the particle.
     */
    void AddForce(QVector3D f);

    /*!
     * \brief Sets the total forces on the particle at a given time.
     * \param[in] f total forces on the particle.
     */
    void SetForce(QVector3D f);

    /*!
     * \brief Returns the total forces on the particle.
     * \return the total forces on the particle.
     */
    QVector3D GetForce();

    /*!
     * \brief Sets the mass of the particle to the given value.
     * \param m the mass of the particle.
     */
    void SetMass(GLdouble m);

    /*!
     * \brief Returns the mass of the particle.
     * \return the mass of the particle in kg.
     */
    GLdouble GetMass();

    //!
    /*!
     * \brief Calculate position for the next delta time.
     * \param the damping of spring.
     */
    void SimStep(float damping);

    //! Draws the particle.
    void Draw();

    /*!
     * \brief Sets the accumulated normal vector of the surrounding planes.
     * \param n normal vector of the particle.
     */
    void SetNormal(QVector3D n);

    /*!
     * \brief Returns the accumulated normal vector of the surrounding planes.
     * \return the normal vector of the particle.
     */
    QVector3D GetNormal();

private:
    //! flag showing that this particle is stationary or movable
    bool _fixed;

    //! Position of the particle at time t
    QVector3D _pos;

    //! Position of the particle at time t-dt
    QVector3D _oldPos;

    //! Total forces on the mass at time t
    QVector3D _force;

    //! Mass of the particle
    GLdouble _mass;

    //! Accumulated normal of the adjacent triangles
    QVector3D _normal;
};

#endif // WEIGHT_H
