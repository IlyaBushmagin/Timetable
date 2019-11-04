#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *app, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->app = app;
    filesBase = new QList<QString>;
    classesBase = new QList<Class>;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete filesBase;
    delete classesBase;
}

void MainWindow::readDir(void)
{
    filesBase->clear();
    QDirIterator iterator(app->applicationDirPath() + "/timetable/");
    while(iterator.hasNext())
    {
        QFile file(iterator.next());
        if(file.open(QIODevice::ReadOnly))
        {
            filesBase->append(file.fileName());
            file.close();
        }
    }
}

void MainWindow::searchClasses(void)
{
    classesBase->clear();
    QString name = ui->searchBar->text();
    if(!name.isEmpty())
    {
        int filesBaseSize = filesBase->size();
        for(int i = 0; i < filesBaseSize; i++)
        {
            Document timetable(filesBase->operator[](i));
            if(timetable.load())
            {
                int maxCol = timetable.dimension().lastColumn();
                int maxRow = timetable.dimension().lastRow();
                int colCnt = 1;
                int col = 8;
                while(col < maxCol)
                {
                    int row = 4;
                    while(row < maxRow)
                    {
                        Cell *teacherName = timetable.cellAt(row, col);
                        if(teacherName)
                        {
                            if(teacherName->readValue().toString().contains(name, Qt::CaseInsensitive))
                            {
                                Cell *classType = timetable.cellAt(row, col - 1);
                                Cell *cabinetNumber = timetable.cellAt(row, col + 1);
                                Cell *className = timetable.cellAt(row, col - 2);
                                Cell *groupNumber = timetable.cellAt(2, col - 2);
                                Cell *day = timetable.cellAt(row, 1);
                                Cell *classNumber = timetable.cellAt(row, 2);
                                Cell *classStartTime = timetable.cellAt(row, 3);
                                Cell *classEndTime = timetable.cellAt(row, 4);
                                Cell *weekType = timetable.cellAt(row, 5);
                                int rowShift = 1;
                                while(day && classNumber && classStartTime && classEndTime && weekType)
                                {
                                    bool emptyCells = false;
                                    if(day->readValue().toString().isEmpty())
                                    {
                                        day = timetable.cellAt(row - rowShift, 1);
                                        emptyCells = true;
                                    }
                                    if(classNumber->readValue().toString().isEmpty())
                                    {
                                        classNumber = timetable.cellAt(row - rowShift, 2);
                                        emptyCells = true;
                                    }
                                    if(classStartTime->readValue().toString().isEmpty())
                                    {
                                        classStartTime = timetable.cellAt(row - rowShift, 3);
                                        emptyCells = true;
                                    }
                                    if(classEndTime->readValue().toString().isEmpty())
                                    {
                                        classEndTime = timetable.cellAt(row - rowShift, 4);
                                        emptyCells = true;
                                    }
                                    if(weekType->readValue().toString().isEmpty())
                                    {
                                        weekType = timetable.cellAt(row - rowShift, 5);
                                        emptyCells = true;
                                    }
                                    if(!emptyCells)
                                        break;
                                    else
                                        rowShift++;
                                }
                                bool isCells = classType && cabinetNumber && className &&
                                        groupNumber && weekType && classNumber &&
                                        classStartTime && classEndTime && day;
                                if(isCells)
                                {
                                    bool isEmptyCells = className->readValue().toString().isEmpty() ||
                                            teacherName->readValue().toString().isEmpty() ||
                                            cabinetNumber->readValue().toString().isEmpty() ||
                                            groupNumber->readValue().toString().isEmpty();
                                    if(!isEmptyCells)
                                    {
                                        Class *newClass = new Class;
                                        newClass->setTeacherName(teacherName->readValue().toString());
                                        newClass->setClassType(classType->readValue().toString());
                                        newClass->setCabinetNumber(cabinetNumber->readValue().toString());
                                        newClass->setClassName(className->readValue().toString());
                                        newClass->setGroupNumber(groupNumber->readValue().toString());
                                        newClass->setWeekType(weekType->readValue().toString());
                                        newClass->setClassNumber(classNumber->readValue().toInt());
                                        newClass->setClassStartTime(classStartTime->readValue().toString());
                                        newClass->setClassEndTime(classEndTime->readValue().toString());
                                        newClass->setDay(day->readValue().toString());
                                        classesBase->append(*newClass);
                                        delete newClass;
                                    }
                                }
                            }
                        }
                        row++;
                    }
                    if(colCnt != 3)
                    {
                        colCnt++;
                        col = col + 4;
                    }
                    else
                    {
                        colCnt = 1;
                        col = col + 9;
                    }
                }
            }
        }
    }
}

void MainWindow::genReport(void)
{
    int classesBaseSize = classesBase->size();
    if(classesBaseSize != 0)
    {
        Document report;
        int col = 1;
        QString days[] = {"ПОНЕДЕЛЬНИК", "ВТОРНИК", "СРЕДА", "ЧЕТВЕРГ", "ПЯТНИЦА", "СУББОТА"};
        QString weekTypes[] = {"I", "II"};
        for(int i = 0; i < 6; i++)
        {
            report.write(col, 1, days[i]);
            col++;
            for(int j = 0; j < 2; j++)
            {
                report.write(col, 1, weekTypes[j] + "-ая неделя");
                col++;
                for(int k = 1; k <= 8; k++)
                {
                    int l = 0;
                    while(l < classesBaseSize)
                    {
                        bool foundMatch = classesBase->operator[](l).getDay() == days[i] &&
                                classesBase->operator[](l).getWeekType() == weekTypes[j] &&
                                classesBase->operator[](l).getClassNumber() == k;
                        if(foundMatch)
                        {
                            report.write(col, 1, classesBase->operator[](l).getClassNumber());
                            report.write(col, 2, classesBase->operator[](l).getClassStartTime());
                            report.write(col, 3, classesBase->operator[](l).getClassEndTime());
                            report.write(col, 4, classesBase->operator[](l).getClassName());
                            report.write(col, 5, classesBase->operator[](l).getClassType());
                            report.write(col, 6, classesBase->operator[](l).getTeacherName());
                            report.write(col, 7, classesBase->operator[](l).getCabinetNumber());
                            report.write(col, 8, classesBase->operator[](l).getGroupNumber());
                            classesBase->removeAt(l);
                            classesBaseSize = classesBase->size();
                            col++;
                        }
                        else l++;
                    }
                }
            }
            col++;
        }
        report.saveAs(app->applicationDirPath() + "/reports/" + ui->searchBar->text()+ ".xlsx");
    }
}

void MainWindow::on_genReport_clicked(void)
{
    readDir();
    searchClasses();
    genReport();
}
