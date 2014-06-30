
#include "MainWindow.h"

#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    qsrand( QTime( 0, 0, 0 ).secsTo( QTime::currentTime() ) );

    QCoreApplication::setAttribute(Qt::AA_X11InitThreads, true);
    
    QApplication app(argc, argv);

    MainWindow mainWindow;

    mainWindow.show();
    
    return app.exec();
}
