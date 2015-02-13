#ifndef UTILS_H
#define UTILS_H

#include<QWindow>
#include <QtOpenGL/QGLWidget>
#include <GL/glu.h>
#include <QVector3D>
#include <QVector>
#include <stdio.h>
#include <math.h>

#define GRAVITY             (-10)       /// gravity
#define ADJACENT_NUM        (12)        /// number of adjacent springs for each mass

#define DEFAULT_REST_LEN    (0.1)       /// Default rest length of springs
#define SIMULATION_STEP     (0.25)      /// Simulation step
#define DAMPING             (0.05)      /// Damping
#define SPRING_ITERATIONS   (15)        /// Spring constraints iteration number

/*! SpringType Type Of Spring */
typedef enum {
    STRUCTURAL_SPRING = 0,  ///< structural spring
    SHEAR_SPRING = 1,       ///< shear spring
    FLEX_SPRING = 2         ///< flex spring
} spring_t;

/*! Type Of Cloth */
typedef enum {
    FLAG,            ///< for simulating aerodynamic forces
    CURTAIN,
    SINGLE_PIN,
    COVER            ///< for simulating collisions and elasticity
} cloth_t;

/*! Type Of Colliding Object */
typedef enum {
    BALL,
    CUBE,
    IMPORTED
} object_t;

/*! Type Of Movement */
typedef enum {
    FALLING,
    BOUNCING,
    STATIONARY
} movement_t;

#endif // UTILS_H
