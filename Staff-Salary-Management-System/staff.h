#ifndef STAFF_H
#define STAFF_H

#include <QString>
#include<QDate>
#include"salary.h"

class Staff
{    
public:
    Staff();
    Staff(const Staff & staff);
    Staff& operator = (const Staff & staff);
    virtual ~Staff();

    void Savestaff(QTextStream &aStream);
    void Readstaff(QTextStream &aStream);

    QString       num;           //工号
    int           age;           //年龄
    QString       tele;          //电话号码
    QDate         date;          //入职日期
    QString       name;          //姓名
    QString       addr;          //住址

    Salary        sal;
    int           rank;
};

#endif // STAFF_H
