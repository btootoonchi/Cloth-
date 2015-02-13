/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Sun Sep 28 20:17:55 2014
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <QCoreApplication>
#include <QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_frmMain {
public:
    QScrollArea *glWidgetArea;
    QWidget *scrollAreaWidgetContents;
    QTabWidget *TabArea;
    QWidget *WindTab;
    QWidget *CollisionTab;

    QGroupBox *groupBoxWindModel;
    QGroupBox *groupBoxCollisionModel;
    QGroupBox *groupBoxTexture;
    QGroupBox *groupBoxWind;
    QGroupBox *groupBoxObject;
    QGroupBox *groupBoxThickness;
    QRadioButton *FlagRadio;
    QRadioButton *CurtainRadio;
    QRadioButton *SinglePinRadio;
    QRadioButton *CoverRadio;
    QRadioButton *JimboRadio;
    QRadioButton *Texture1Radio;
    QRadioButton *Texture2Radio;
    QRadioButton *Texture3Radio;
    QRadioButton *BallRadio;
    QRadioButton *CubeRadio;
    QDoubleSpinBox *xDoubleSpinBox;
    QDoubleSpinBox *yDoubleSpinBox;
    QDoubleSpinBox *zDoubleSpinBox;
    QLabel *xLabel;
    QLabel *yLabel;
    QLabel *zLabel;
    QLabel *nLabel;
    QLabel *pLabel;
    QSlider *ThicknessSlider;
    QPushButton *btnClose;
    QPushButton *startButton;
    QPushButton *resetButton;
    bool _play;

    void setupUi(QWidget *frmMain)
    {
        if (frmMain->objectName().isEmpty())
            frmMain->setObjectName(QString::fromUtf8("frmMain"));
        frmMain->resize(1300, 750);
        glWidgetArea = new QScrollArea(frmMain);
        glWidgetArea->setObjectName(QString::fromUtf8("glWidgetArea"));
        glWidgetArea->setGeometry(QRect(0, 0, 1030, 750));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(glWidgetArea->sizePolicy().hasHeightForWidth());
        glWidgetArea->setSizePolicy(sizePolicy);
        glWidgetArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        glWidgetArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        glWidgetArea->setWidgetResizable(true);

        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1030, 750));
        glWidgetArea->setWidget(scrollAreaWidgetContents);

        TabArea = new QTabWidget(frmMain);
        TabArea->setObjectName(QStringLiteral("CollisionTab"));
        TabArea->setGeometry(QRect(1040, 15, 250, 730));
        WindTab = new QWidget();
        WindTab->setObjectName(QStringLiteral("WindTab"));
        TabArea->addTab(WindTab, QString());
        CollisionTab = new QWidget();
        CollisionTab->setObjectName(QStringLiteral("CollisionTab"));
        TabArea->addTab(CollisionTab, QString());
        QFont LargeFont, XLargeFont;
        LargeFont.setPointSize(10);
        XLargeFont.setPixelSize(20);
        TabArea->setFont(LargeFont);
        frmMain->setFont(LargeFont);

        groupBoxWindModel = new QGroupBox(WindTab);
        groupBoxWindModel->setObjectName(QString::fromUtf8("groupBoxWindModel"));
        groupBoxWindModel->setGeometry(QRect(20, 20, 205, 130));
        groupBoxWindModel->setStyleSheet(QString::fromUtf8(""));
        FlagRadio = new QRadioButton(groupBoxWindModel);
        FlagRadio->setObjectName(QStringLiteral("FlagRadio"));
        FlagRadio->setChecked(true);
        FlagRadio->setGeometry(QRect(30, 30, 150, 25));
        CurtainRadio = new QRadioButton(groupBoxWindModel);
        CurtainRadio->setObjectName(QStringLiteral("CurtainRadio"));
        CurtainRadio->setGeometry(QRect(30, 60, 150, 25));
        SinglePinRadio = new QRadioButton(groupBoxWindModel);
        SinglePinRadio->setObjectName(QStringLiteral("SinglePinRadio"));
        SinglePinRadio->setGeometry(QRect(30, 90, 150, 25));

        groupBoxCollisionModel = new QGroupBox(CollisionTab);
        groupBoxCollisionModel->setObjectName(QString::fromUtf8("groupBoxCollisionModel"));
        groupBoxCollisionModel->setGeometry(QRect(20, 20, 205, 130));
        groupBoxCollisionModel->setStyleSheet(QString::fromUtf8(""));
        CoverRadio = new QRadioButton(groupBoxCollisionModel);
        CoverRadio->setObjectName(QStringLiteral("CoverRadio"));
        CoverRadio->setChecked(true);
        CoverRadio->setGeometry(QRect(30, 30, 150, 25));
        JimboRadio = new QRadioButton(groupBoxCollisionModel);
        JimboRadio->setObjectName(QStringLiteral("JimboRadio"));
        JimboRadio->setGeometry(QRect(30, 60, 150, 25));

        groupBoxTexture = new QGroupBox(frmMain);
        groupBoxTexture->setObjectName(QString::fromUtf8("groupBoxTexture"));
        groupBoxTexture->setGeometry(QRect(1060, 210, 205, 130));
        groupBoxTexture->setStyleSheet(QString::fromUtf8(""));
        Texture1Radio = new QRadioButton(groupBoxTexture);
        Texture1Radio->setObjectName(QStringLiteral("Texture1Radio"));
        Texture1Radio->setChecked(true);
        Texture1Radio->setGeometry(QRect(30, 30, 150, 25));
        Texture2Radio = new QRadioButton(groupBoxTexture);
        Texture2Radio->setObjectName(QStringLiteral("Texture2Radio"));
        Texture2Radio->setGeometry(QRect(30, 60, 150, 25));
        Texture3Radio = new QRadioButton(groupBoxTexture);
        Texture3Radio->setObjectName(QStringLiteral("Texture3Radio"));
        Texture3Radio->setGeometry(QRect(30, 90, 150, 25));

        groupBoxObject = new QGroupBox(CollisionTab);
        groupBoxObject->setObjectName(QString::fromUtf8("groupBoxObject"));
        groupBoxObject->setGeometry(QRect(20, 310, 205, 130));
        groupBoxObject->setStyleSheet(QString::fromUtf8(""));
        BallRadio = new QRadioButton(groupBoxObject);
        BallRadio->setObjectName(QStringLiteral("BallRadio"));
        BallRadio->setChecked(true);
        BallRadio->setGeometry(QRect(30, 30, 150, 25));
        CubeRadio = new QRadioButton(groupBoxObject);
        CubeRadio->setObjectName(QStringLiteral("CubeRadio"));
        CubeRadio->setGeometry(QRect(30, 60, 150, 25));

        groupBoxWind = new QGroupBox(WindTab);
        groupBoxWind->setObjectName(QString::fromUtf8("groupBoxWind"));
        groupBoxWind->setGeometry(QRect(20, 310, 205, 150));
        xLabel = new QLabel("X :", groupBoxWind);
        xLabel->setGeometry(QRect(15, 40, 20, 25));
        yLabel = new QLabel("Y :", groupBoxWind);
        yLabel->setGeometry(QRect(15, 75, 20, 25));
        zLabel = new QLabel("Z :", groupBoxWind);
        zLabel->setGeometry(QRect(15, 110, 20, 25));
        xDoubleSpinBox = new QDoubleSpinBox(groupBoxWind);
        xDoubleSpinBox->setObjectName(QString::fromUtf8("xSpinBox"));
        xDoubleSpinBox->setGeometry(QRect(45, 35, 110, 25));
        xDoubleSpinBox->setValue(5);
        xDoubleSpinBox->setSingleStep(0.1);
        xDoubleSpinBox->setRange(-10.0,10.0);
        yDoubleSpinBox = new QDoubleSpinBox(groupBoxWind);
        yDoubleSpinBox->setObjectName(QString::fromUtf8("ySpinBox"));
        yDoubleSpinBox->setGeometry(QRect(45, 70, 110, 25));
        yDoubleSpinBox->setValue(5);
        yDoubleSpinBox->setSingleStep(0.1);
        yDoubleSpinBox->setRange(-10.0,10.0);
        zDoubleSpinBox = new QDoubleSpinBox(groupBoxWind);
        zDoubleSpinBox->setObjectName(QString::fromUtf8("zSpinBox"));
        zDoubleSpinBox->setGeometry(QRect(45, 105, 110, 25));
        zDoubleSpinBox->setValue(1);
        zDoubleSpinBox->setSingleStep(0.1);
        zDoubleSpinBox->setRange(-10.0,10.0);

        groupBoxThickness = new QGroupBox(frmMain);
        groupBoxThickness->setObjectName(QString::fromUtf8("groupBoxThickness"));
        groupBoxThickness->setGeometry(QRect(1060, 520, 205, 70));
        ThicknessSlider = new QSlider(frmMain);
        ThicknessSlider->setObjectName(QStringLiteral("ThicknessSlider"));
        ThicknessSlider->setGeometry(QRect(1085, 550, 150, 22));
        ThicknessSlider->setOrientation(Qt::Horizontal);
        ThicknessSlider->setTickPosition(QSlider::TicksBelow);
        ThicknessSlider->setMaximum(10);
        ThicknessSlider->setValue(1);
        ThicknessSlider->setOrientation(Qt::Horizontal);
        ThicknessSlider->setTickPosition(QSlider::TicksBelow);
        nLabel = new QLabel("-", frmMain);
        nLabel->setGeometry(QRect(1070, 540, 25, 25));
        nLabel->setFont(XLargeFont);
        pLabel = new QLabel("+", frmMain);
        pLabel->setGeometry(QRect(1240, 540, 20, 25));
        pLabel->setFont(XLargeFont);
        startButton= new QPushButton(frmMain);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(1110, 610, 100, 30));
        btnClose = new QPushButton(frmMain);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(1110, 655, 100, 30));
        resetButton = new QPushButton(frmMain);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(1110, 700, 100, 30));
        resetButton->setHidden(true);
        _play = true;

        retranslateUi(frmMain);
        TabArea->setCurrentIndex(0);

        QMetaObject::connectSlotsByName(frmMain);
    } // setupUi

    void retranslateUi(QWidget *frmMain)
    {
        frmMain->setWindowTitle(QCoreApplication::translate("frmMain", "Qt OpenGl Framework", 0, 1));
        TabArea->setTabText(TabArea->indexOf(WindTab), QApplication::translate("MainWindow", "Wind", 0));
        TabArea->setTabText(TabArea->indexOf(CollisionTab), QApplication::translate("MainWindow", "Collision", 0));

        groupBoxWindModel->setTitle(QApplication::translate("frmMain", " Model: ", 0, 1));
        FlagRadio->setText(QApplication::translate("frmMain", "Flag", 0));
        CurtainRadio->setText(QApplication::translate("frmMain", "Curtain", 0));
        SinglePinRadio->setText(QApplication::translate("frmMain", "Single Pin", 0));

        groupBoxCollisionModel->setTitle(QApplication::translate("frmMain", " Model: ", 0, 1));
        CoverRadio->setText(QApplication::translate("frmMain", "Cover", 0));
        JimboRadio->setText(QApplication::translate("frmMain", "Curtain", 0));

        groupBoxTexture->setTitle(QApplication::translate("frmMain", " Texture: ", 0, 1));
        Texture1Radio->setText(QApplication::translate("frmMain", "Texture 1", 0));
        Texture2Radio->setText(QApplication::translate("frmMain", "Texture 2", 0));
        Texture3Radio->setText(QApplication::translate("frmMain", "Texture 3", 0));

        groupBoxObject->setTitle(QApplication::translate("frmMain", " Object "));
        BallRadio->setText(QApplication::translate("frmMain", "Ball", 0));
        CubeRadio->setText(QApplication::translate("frmMain", "Cube", 0));

        groupBoxWind->setTitle(QApplication::translate("frmMain", " Wind: ", 0, 1));
        groupBoxThickness->setTitle(QApplication::translate("frmMain", " Thickness: ", 0, 1));
        startButton->setText(QApplication::translate("frmMain", _play?"Play":"Pause", 0, 1));
        btnClose->setText(QApplication::translate("frmMain", "Close", 0, 1));
        resetButton->setText(QApplication::translate("frmMain","Reset", 0, 1));
    } // retranslateUi

};

namespace Ui {
    class frmMain: public Ui_frmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
