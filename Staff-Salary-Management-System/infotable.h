#ifndef INFOTABLE_H
#define INFOTABLE_H

#include "staff.h"
#include <vector>
#include <QVector>
#include<algorithm>

class InfoTable
{
public:
    InfoTable();

    bool ReadStaffFromFile(const QString &aReadFileName);
    bool SaveStaffToFile(const QString &aSaveFileName);

    void AddStaff(Staff & staff);
    Staff & GetStaff(int index);
    int GetStaffNum();

    int findByNum(const QString& num);   //按员工号查找
    int findByName(const QString& name);

    QVector <Staff> m_staff; //员工列表
    //对员工工资进行排序
    void sortStaff();
    int m_number;            //员工总数

    void RemoveStaff(int index);//删除编号为index的数据
};

#endif // INFOTABLE_H
