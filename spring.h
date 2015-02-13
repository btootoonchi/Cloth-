/*!
 *  \author    Babak Tootoonchi
 *  \date      December 2014
 */

#ifndef SPRING_H
#define SPRING_H

#include "Utilities.h"
#include "particle.h"

class Particle;

/*! The Spring class is for simulating spring objects and their behaviour. */
class Spring
{
public:
    //! CONSTRUCTOR
    /*!
     * \brief Initializes spring parameters to default values.
     * \param head pointer to the head Particle.
     * \param restLen the initial rest length
     */
    Spring(Particle *head, Particle *tail);

    //! DEFAULT CONSTRUCTOR
    Spring();

    //! DESTRUCTOR
    ~Spring(){}

    /*!
     * \brief Sets the rest length of the spring to the given value.
     * \param len new rest length for the spring.
     */
    void SetRestLength(GLdouble len);

    /*!
     * \brief Returns the current rest length of the spring.
     * \return the rest length of the spring.
     */
    GLdouble GetRestLength();

    /*!
     * \brief Sets the head and tail pointers
     * \param head pointer to the head Particle.
     * \param tail pointer to the tail Particle.
     */
    void SetPostion(Particle *head, Particle *tail);

    //! Apply moving constraints to head and tail to simulate spring constant and damping effects.
    void ApplyConstraints();

    //! Returns the head pointer.
    Particle *GetHead();

    //! Returns the tail pointer.
    Particle *GetTail();

    /*! Draws the spring */
    void Draw();

 private:
    //! Rest length of the spring.
    GLdouble _restLength;

    //! Spring constant a.k.a. stiffness.
    GLdouble _springConstant;

    //! Damping coefficient
    GLdouble _dampingCoeff;

    //! Spring type
    spring_t _springType;

    //! Pointer to the head of the spring.
    Particle *_head;

    //! Pointer to the tail of the spring.
    Particle *_tail;
};

#endif // SPRING_H
