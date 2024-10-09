#ifndef SALARY_H
#define SALARY_H

#include<QTextStream>
#include<QString>


class Salary
{
public:
    Salary();
    virtual ~Salary();
    Salary(const Salary & sal);
    Salary & operator = (const Salary & sal);

    void CalculateTotalsal();
    void Tax();
    void AfterTax();

    int month[12];                  //月份
    double base_salary[12];         //基本工资
    double post_salary[12];         //岗位工资
    double age_salary[12];          //工龄工资
    double allowance[12];           //津贴
    double post_sub[12];            //岗位补贴
    double subsidy[12];             //补贴
    double shelter_sub[12];         //住房补贴
    double trans_sub[12];           //交通补贴
    double tax[12];                 //个人所得税
    double Aftertax[12];            //税后收入

    double  m_totalsal[12];         //总工资
    double TOTAL;                   //年薪
    void total();

    void Savesalary(QTextStream &aStream); //往流文件中写入工资
    void Readsalary(QTextStream &aStream); //从流文件中读取工资



};

#endif // SALARY_H
