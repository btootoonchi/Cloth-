/*!
 *  \author    Babak Tootoonchi
 *  \date      December 2014
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "Utilities.h"

class Object
{
public:
    //! Constructor
    Object(object_t type, QVector3D pos, movement_t m);

    //! Default destructor
    ~Object(){}

    /*!
     * \brief Set position.
     * \param pos position.
     */
    void SetPosition(QVector3D pos);

    /*!
     * \brief Get position.
     * \return rturn position.
     */
    QVector3D GetPos();

    /*!
     * \brief Get old position.
     * \return return old position.
     */
    QVector3D GetOldPos();

    /*!
     * \brief Get radius.
     * \return return radius.
     */
    GLfloat GetRadius();

    /*!
     * \brief Set type of object.
     * \param type type of object that could be a ball or cube.
     */
    void SetType(object_t type);

    /*!
     * \brief Get type of object.
     * \return return type of object.
     */
    object_t GetType();

    //! Draw an object.
    void Draw();

    //! Simulation step.
    void SimStep();

private:
    //! Object type.
    object_t _type;

    //! Position.
    QVector3D _pos;

    //! Old position.
    QVector3D _oldPos;

    //! Radius.
    GLfloat _radius;

    //! Movement type.
    movement_t _move;

    //! Direction.
    int _direction;
};

#endif // OBJECT_H
