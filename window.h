//-------------------------------------------------------------------------------------------
//  University of Victoria Computer Science Department 
//	FrameWork for OpenGL application under QT
//  Course title: Computer Animation CSC 578A
//-------------------------------------------------------------------------------------------
#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include "ui_MainWindow.h"

class GLWidget;
class PositionController;
class VelocityController;
class AccelerationController;

//Create a window and load the components from generated code ui_MainWindow.h
class Window : public QDialog, public Ui::frmMain {
	Q_OBJECT;

public:
    //! Default constructor
	Window(QWidget *parent = 0);
	
private:
    //! GLWidget attribute. It hold the GLWidget instance
    GLWidget *m_glWidget;

    //! Simulation timer
    QTimer *_simulationTimer;

private slots:
    void Reset();
    void PlayPause();
    void InitTabs();
    void SetBallMode();
    void SetCubeMode();
    void SetJimboMode();
    void SetCoverMode();
};
#endif
