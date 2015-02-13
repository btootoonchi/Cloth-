//-------------------------------------------------------------------------------------------
//  This is a demo. program for open gl vertex arrays
//-------------------------------------------------------------------------------------------
#include "glwidget.h"

#include <QtGui>
#include <QtOpenGL>

#include "window.h"

//------------------------------------------------------------------------------------
// Creates and initializes the main window for application
//------------------------------------------------------------------------------------
Window::Window(QWidget *parent):QDialog(parent)
{
    //We create an instance of GLWidget component we built in glwidget.h
	m_glWidget = new GLWidget;

	//Setup application interface. Creates all the required components and sliders.
	setupUi(this);

    //The widget accepts keyboard focus by pushing buttons
    m_glWidget->setFocusPolicy(Qt::ClickFocus);

    //We need to attach our m_glWidget to glWidgetArea
    //All our drawings will be on glWidgetArea
    glWidgetArea->setWidget(m_glWidget);

    //Setting up all the SIGNALS and SLOTS
    connect(TabArea, SIGNAL(currentChanged(int)), this, SLOT(InitTabs()));

    connect(FlagRadio, SIGNAL(clicked()), m_glWidget, SLOT(SetFlagModel()));
    connect(CurtainRadio, SIGNAL(clicked()), m_glWidget, SLOT(SetCurtainModel()));
    connect(SinglePinRadio, SIGNAL(clicked()), m_glWidget, SLOT(SetSinglePinModel()));
    connect(CoverRadio, SIGNAL(clicked()), m_glWidget, SLOT(SetCoverModel()));
    connect(CoverRadio, SIGNAL(clicked()), this, SLOT(SetCoverMode()));
    connect(JimboRadio, SIGNAL(clicked()), m_glWidget, SLOT(SetJimboModel()));
    connect(JimboRadio, SIGNAL(clicked()), this, SLOT(SetJimboMode()));

    connect(BallRadio, SIGNAL(clicked()), m_glWidget, SLOT(SetBallObject()));
    connect(BallRadio, SIGNAL(clicked()), this, SLOT(SetBallMode()));
    connect(CubeRadio, SIGNAL(clicked()), m_glWidget, SLOT(SetCubeObject()));
    connect(CubeRadio, SIGNAL(clicked()), this, SLOT(SetCubeMode()));

    connect(Texture1Radio, SIGNAL(clicked()), m_glWidget, SLOT(SetTexture1()));
    connect(Texture2Radio, SIGNAL(clicked()), m_glWidget, SLOT(SetTexture2()));
    connect(Texture3Radio, SIGNAL(clicked()), m_glWidget, SLOT(SetTexture3()));

    connect(ThicknessSlider, SIGNAL(valueChanged(int)), m_glWidget, SLOT(SetThickness(int)));

    connect(startButton, SIGNAL(clicked()), m_glWidget, SLOT(StartAnimation()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(PlayPause()));
    connect(resetButton, SIGNAL(clicked()), m_glWidget, SLOT(ResetAnimation()));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(Reset()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));
    connect(xDoubleSpinBox, SIGNAL(valueChanged(double)), m_glWidget, SLOT(SetXWind(double)));
    connect(yDoubleSpinBox, SIGNAL(valueChanged(double)), m_glWidget, SLOT(SetYWind(double)));
    connect(zDoubleSpinBox, SIGNAL(valueChanged(double)), m_glWidget, SLOT(SetZWind(double)));

    connect(resetButton, SIGNAL(clicked()), m_glWidget, SLOT(ResetAnimation()));

    _simulationTimer = new QTimer(this);
    connect(_simulationTimer, SIGNAL(timeout()), m_glWidget, SLOT(Animate()));
    _simulationTimer->start(10);  //in miliseconds
}

void Window::Reset() {
    _play = false;
    retranslateUi(this);
}

void Window::PlayPause() {
    _play = !_play;
    retranslateUi(this);
}

void Window::InitTabs() {
    if (TabArea->currentIndex()) {
        m_glWidget->SetCoverModel();
        CoverRadio->setChecked(true);
        resetButton->setHidden(false);
        BallRadio->setChecked(true);
        CubeRadio->setChecked(false);
    } else {
        m_glWidget->SetFlagModel();
        FlagRadio->setChecked(true);
        xDoubleSpinBox->setValue(5);
        yDoubleSpinBox->setValue(5);
        zDoubleSpinBox->setValue(1);
        m_glWidget->SetXWind(xDoubleSpinBox->value());
        m_glWidget->SetYWind(yDoubleSpinBox->value());
        m_glWidget->SetZWind(zDoubleSpinBox->value());
        resetButton->setHidden(true);
    }
}

void Window::SetBallMode() {
    JimboRadio->setEnabled(true);
    retranslateUi(this);
}

void Window::SetCubeMode() {
    JimboRadio->setEnabled(false);
    CoverRadio->setChecked(true);
    m_glWidget->SetCoverModel();
    retranslateUi(this);
}

void Window::SetJimboMode() {
    CubeRadio->setEnabled(false);
    BallRadio->setChecked(true);
    m_glWidget->SetBallObject();
    retranslateUi(this);
}

void Window::SetCoverMode() {
    CubeRadio->setEnabled(true);
    retranslateUi(this);
}
