#ifndef STAFFTABLE_H
#define STAFFTABLE_H

#include"staff.h"
#include<QVector>

class StaffTable
{
public:
    StaffTable();
    QVector<Staff> Staffs;

    void addStaff(const Staff& st);
};

#endif // STAFFTABLE_H
