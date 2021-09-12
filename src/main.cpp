#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("fusion");
    MainWindow mainwindow(&app);
    mainwindow.show();
    return app.exec();
}
