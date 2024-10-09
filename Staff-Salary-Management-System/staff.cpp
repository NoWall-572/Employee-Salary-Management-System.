#include "staff.h"


Staff :: Staff()
{

}

Staff::~Staff()
{

}

Staff::Staff(const Staff & staff)
{
    num   =  staff.num;
    age   =  staff.age;
    tele  =  staff.tele;
    date  =  staff.date;
    name  =  staff.name;
    addr  =  staff.addr;
    sal   =  staff.sal;
    rank  =  staff.rank;
}

Staff& Staff::operator= (const Staff& staff)
{
    num   =  staff.num;
    age   =  staff.age;
    tele  =  staff.tele;
    date  =  staff.date;
    name  =  staff.name;
    addr  =  staff.addr;
    sal   =  staff.sal;
    rank  =  staff.rank;
    return *this;
}

void Staff::Savestaff(QTextStream &aStream)
{

    aStream<<num<<'\n';
    aStream<<name<<'\n';
    aStream<<age<<'\n';
    int year,month,day;
    year=date.year();
    month=date.month();
    day=date.day();
    aStream<<year<<" "<<month<<" "<<day<<'\n';
    aStream<<tele<<'\n';
    aStream<<addr<<'\n';

    sal.Savesalary(aStream);
}

void Staff::Readstaff(QTextStream &aStream)
{

    aStream>>num;
    aStream>>name;
    aStream>>age;
    int year, month, day;
    year=date.year();
    month=date.month();
    day=date.day();
    aStream >>year>>month>>day;
    date.setDate(year,month,day);
    aStream>>tele;
    aStream>>addr;

    sal.Readsalary(aStream);
}
