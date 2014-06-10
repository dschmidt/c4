
#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_X11InitThreads, true);
    
    QApplication app(argc, argv);

    MainWindow mainWindow;

    mainWindow.show();
    
    return app.exec();
}
