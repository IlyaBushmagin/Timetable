#ifndef CLASS_H
#define CLASS_H

#include <QString>

class Class
{
public:
    void setDay(QString day);

    void setWeekType(QString weekType);

    void setClassStartTime(QString classStartTime);

    void setClassEndTime(QString classEndTime);

    void setClassName(QString className);

    void setClassType(QString classType);

    void setTeacherName(QString teacherName);

    void setCabinetNumber(QString cabinetNumber);

    void setGroupNumber(QString groupNumber);

    void setClassNumber(int classNumber);

    QString getDay(void);

    QString getWeekType(void);

    QString getClassStartTime(void);

    QString getClassEndTime(void);

    QString getClassName(void);

    QString getClassType(void);

    QString getTeacherName(void);

    QString getCabinetNumber(void);

    QString getGroupNumber(void);

    int getClassNumber(void);

private:
    QString day;
    QString weekType;
    QString classStartTime;
    QString classEndTime;
    QString className;
    QString classType;
    QString teacherName;
    QString cabinetNumber;
    QString groupNumber;
    int classNumber;
};

#endif // CLASS_H
