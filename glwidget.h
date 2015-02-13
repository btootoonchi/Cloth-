/*!
 *  \author    Babak Tootoonchi
 *  \date      December 2014
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "Utilities.h"
#include "cloth.h"
#include "object.h"

class QGLShaderProgram;

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    //! Default constructor
    GLWidget(QWidget *parent = 0);

    //! Default destructor
    ~GLWidget();

    //! Get the simulation time.
    GLdouble GetSimulationTime();

    /*!
     * \brief Set simulation time. It means that time frame.
     * \param time the time frame.
     */
    void SetSimulationTime(GLdouble time);

private:
    Cloth *_cloth;

    Object *_object;

    //! Simulation time interval.
    GLdouble _time;

    //! Camera view rotation on y axi.
    float _viewRotatey;

    //! Camera view rotation on x axi.
    float _viewRotateVert;

    //! Camera zoom value.
    float _zoom;

    //! Camera position in the 3D scene.
    QVector3D _cameraPosition;

    //! Object position in the 3D scene.
    QVector3D _objectPosition;

    //! Rotation array.
    GLdouble _rotation[16];

    //! Draw the surface grid.
    void Draw3DGrid();

    //! draws the flag hanger and the curtain rod.
    void DrawRacks();

    //! Detect collision.
    void DetectCollision();

protected:
    /// OPENGL
    void initializeGL();
    void paintGL();

signals:
public slots:
private slots:
public slots:
    //TODO
    //! Set flag model.
    void SetFlagModel();

    //! Set curtain model.
    void SetCurtainModel();

    //! Set single pin model.
    void SetSinglePinModel();

    //! Set cover model.
    void SetCoverModel();

    //! Set jimbo model.
    void SetJimboModel();

    //! Set ball object in the scene.
    void SetBallObject();

    //! Set cube object in the scene.
    void SetCubeObject();

    //! Set texture 1 for cloth.
    void SetTexture1();

    //! Set texture 2 for cloth.
    void SetTexture2();

    //! Set texture 3 for cloth.
    void SetTexture3();

    //! Set thickness of cloth.
    void SetThickness(int d);

    //! Set the x parameter of the wind force.
    void SetXWind(double x);

    //! Set the y parameter of the wind force.
    void SetYWind(double y);

    //! Set the z parameter of the wind force.
    void SetZWind(double z);

    //! Apply wind force on cloth.
    void ApplyWind();

    //! Start the animation by resetting the simulation time.
    void StartAnimation();

    //! Animate the mass-spring (cloth).
    void Animate();

    //! Reset the animation state.
    void ResetAnimation();

protected slots:

    /*!
     * \brief When user resizes main window, the scrollArea will be resized and it will call this function from its attached GLWidget.
     * \param width width of the screen.
     * \param height height of the screen.
     */
    void resizeGL(int width, int height);

    /*!
     * \brief Handle keybord press event in scrollArea.
     * \param e is keybord event.
     */
    void keyPressEvent(QKeyEvent *e);
};

#endif // GLWIDGET_H
