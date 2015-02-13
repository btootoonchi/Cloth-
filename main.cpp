#include <QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Instead of creating our GUI components ourselves. We will visually design
    //Everything then we subclass
    Window appWindow;

    //Show application MainWindow
    appWindow.show();
    return a.exec();
}
