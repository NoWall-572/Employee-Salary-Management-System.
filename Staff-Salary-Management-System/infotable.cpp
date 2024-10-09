#include "infotable.h"

#include <qfile.h>
#include <QTextStream>
#include <QTextCodec>

InfoTable::InfoTable()
{
    m_number = 0;
}


bool InfoTable::ReadStaffFromFile(const QString &aReadFileName)
{
    QFile aFile(aReadFileName);
    if(!aFile.exists()) //文件不存在
        return false;
    if(!aFile.open(QIODevice::ReadOnly | QIODevice::Text)) //以文本方式打开
        return false;
    QTextStream aStream(&aFile); //用文本流读取文件
    aStream.setEncoding(QStringConverter::Utf8); //显示汉字

    //初始化
    m_staff.clear();
    m_number = 0;

    //逐个读取职工信息
    aStream>>m_number; //职工总数
    Staff tempstaff;
    if(m_number>0)
    {
        for(int i=0; i<m_number; i++)
        {
            tempstaff.Readstaff(aStream);
            m_staff.push_back(tempstaff);
        }
    }
    aFile.close();//关闭文件
    return true;
}

bool InfoTable::SaveStaffToFile(const QString &aSaveFileName)
{
    QFile aFile(aSaveFileName);
    if(!aFile.open(QIODevice::WriteOnly| QIODevice::Text)) //保存为文本
        return false;
    QTextStream aStream(&aFile);//用文本流保存文件
    aStream.setEncoding(QStringConverter::Utf8);  //显示汉字

    //逐个写入员工信息
    aStream<<m_number<<'\n';//职工总数
    if(m_number>0)
    {
        for(int i=0; i<m_number; i++)
            m_staff[i].Savestaff(aStream);

    }
    aFile.close(); //关闭文件
    return true;
}

void InfoTable::AddStaff(Staff &staff)
{
    m_staff.push_back(staff);
    m_number++;
}

int InfoTable::GetStaffNum()
{
    m_number = m_staff.size();
    return m_number;
}

Staff & InfoTable::GetStaff(int index)
{
    return m_staff[index];
}

int InfoTable::findByNum(const QString& num)
{
    for(int i = 0; i < this->m_staff.size(); i++)
    {
        if(num == m_staff[i].num)
            return i;
    }
    return -1;
}
int InfoTable::findByName(const QString& name)
{
    for(int i = 0; i < this->m_staff.size(); i++)
    {
        if(name == m_staff[i].name)
            return i;
    }
    return -1;
}

void InfoTable::RemoveStaff(int index)
{
    m_staff.erase(m_staff.begin() + index);
    m_number--;
}

void InfoTable::sortStaff()    //排序
{
    bool StaffCompare(const Staff& s1, const Staff& s2);
    std::sort(m_staff.begin(), m_staff.end(), StaffCompare);
}

bool StaffCompare(const Staff& s1, const Staff& s2)
{
    return s1.sal.TOTAL > s2.sal.TOTAL;
}
