#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "xlsxdocument.h"
#include "class.h"

#include <QMainWindow>
#include <QDirIterator>
#include <QtDebug>

using namespace QXlsx;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *app, QWidget *parent = nullptr);

    void readDir(void);

    void searchClasses(void);

    void genReport(void);

    ~MainWindow();

private slots:
    void on_genReport_clicked(void);

private:
    Ui::MainWindow *ui;
    QApplication *app;
    QList<QString> *filesBase;
    QList<Class> *classesBase;
};
#endif // MAINWINDOW_H
