#include "class.h"

void Class::setDay(QString day)
{
    this->day = day;
}

void Class::setWeekType(QString weekType)
{
    this->weekType = weekType;
}

void Class::setClassStartTime(QString classStartTime)
{
    this->classStartTime = classStartTime;
}

void Class::setClassEndTime(QString classEndTime)
{
    this->classEndTime = classEndTime;
}

void Class::setClassName(QString className)
{
    this->className = className;
}

void Class::setClassType(QString classType)
{
    this->classType = classType;
}

void Class::setTeacherName(QString teacherName)
{
    this->teacherName = teacherName;
}

void Class::setCabinetNumber(QString cabinetNumber)
{
    this->cabinetNumber = cabinetNumber;
}

void Class::setGroupNumber(QString groupNumber)
{
    this->groupNumber = groupNumber;
}

void Class::setClassNumber(int classNumber)
{
    this->classNumber = classNumber;
}

QString Class::getDay(void)
{
    return day;
}

QString Class::getWeekType(void)
{
    return weekType;
}

QString Class::getClassStartTime(void)
{
    return classStartTime;
}

QString Class::getClassEndTime(void)
{
    return classEndTime;
}

QString Class::getClassName(void)
{
    return className;
}

QString Class::getClassType(void)
{
    return classType;
}

QString Class::getTeacherName(void)
{
    return teacherName;
}

QString Class::getCabinetNumber(void)
{
    return cabinetNumber;
}

QString Class::getGroupNumber(void)
{
    return groupNumber;
}

int Class::getClassNumber(void)
{
    return classNumber;
}
