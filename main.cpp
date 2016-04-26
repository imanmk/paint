

#include <QApplication>

#include "mainwindow.h"
//#include "toolbar.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    //toolbar.resize(300, 200);

    window.show();
    //toolbar.show();
    return app.exec();
}
