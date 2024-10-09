#include "salary.h"
#include <math.h>


Salary::Salary()
{    //月份
    for(int i=0;i<12;i++)
    {
        month[i]=i+1;
        base_salary[i] =0;         //基本工资
        post_salary[i] =0;         //岗位工资
        age_salary[i] =0;          //工龄工资
        allowance[i] =0;           //津贴
        post_sub[i] =0;            //岗位补贴
        subsidy[i] =0;             //补贴
        shelter_sub[i] =0;         //住房补贴
        trans_sub[i] =0;           //交通补贴
        tax[i] =0;                 //个人所得税
        Aftertax[i] =0;            //税后收入
        m_totalsal[i] =0;          //总工资
        TOTAL =0;                  //年薪

    }
    total();
}

Salary::~Salary()
{
}

Salary::Salary(const Salary & sal)
{  for(int i=0;i<12;i++)
    {
    month[i]=sal.month[i];                   //月份
    base_salary[i]=sal.base_salary[i];       //基本工资
    post_salary[i]=sal.post_salary[i];       //岗位工资
    age_salary[i]=sal.age_salary[i];         //工龄工资
    allowance[i]=sal.allowance[i];           //津贴
    post_sub[i]=sal.post_sub[i];             //岗位补贴
    subsidy[i]=sal.subsidy[i];               //补贴
    shelter_sub[i]=sal.shelter_sub[i];       //住房补贴
    trans_sub[i]=sal.trans_sub[i];           //交通补贴
    tax[i]=sal.tax[i];                       //个人所得税
    Aftertax[i]=sal.Aftertax[i];             //税后收入
    m_totalsal[i]=sal.m_totalsal[i];         //总工资
    }
    this->total();
    TOTAL=sal.TOTAL;
}

Salary& Salary::operator= (const Salary & sal)
{
    for(int i=0;i<12;i++)
    {
    month[i]=sal.month[i];                   //月份
    base_salary[i]=sal.base_salary[i];       //基本工资
    post_salary[i]=sal.post_salary[i];       //岗位工资
    age_salary[i]=sal.age_salary[i];         //工龄工资
    allowance[i]=sal.allowance[i];           //津贴
    post_sub[i]=sal.post_sub[i];             //岗位补贴
    subsidy[i]=sal.subsidy[i];               //补贴
    shelter_sub[i]=sal.shelter_sub[i];       //住房补贴
    trans_sub[i]=sal.trans_sub[i];           //交通补贴
    tax[i]=sal.tax[i];                       //个人所得税
    Aftertax[i]=sal.Aftertax[i];             //税后收入
    m_totalsal[i]=sal.m_totalsal[i];         //总工资
    }
    this->total();
    TOTAL=sal.TOTAL;
    return *this;
}
void Salary::Savesalary(QTextStream &aStream)
{
    for(int i=0;i<12;i++)
    {
    aStream << month[i]<<'\n';
    aStream << base_salary[i]<<'\n';
    aStream << post_salary[i]<<'\n';
    aStream << age_salary[i]<<'\n';
    aStream << allowance[i]<<'\n';
    aStream << post_sub[i]<<'\n';
    aStream << subsidy[i]<<'\n';
    aStream << shelter_sub[i]<<'\n';
    aStream << trans_sub[i]<<'\n';
    aStream << m_totalsal[i]<<'\n';
    aStream << tax[i]<<'\n';
    aStream << Aftertax[i]<<'\n';
    }
    aStream << TOTAL<<'\n';
}

void Salary::Readsalary(QTextStream &aStream)
{
    for(int i=0;i<12;i++)
    {
    aStream >> month[i];
    aStream >> base_salary[i];
    aStream >> post_salary[i];
    aStream >> age_salary[i];
    aStream >> allowance[i];
    aStream >> post_sub[i];
    aStream >> subsidy[i];
    aStream >> shelter_sub[i];
    aStream >> trans_sub[i];
    aStream >> m_totalsal[i];
    aStream >> tax[i];
    aStream >> Aftertax[i];
    }
    aStream >> TOTAL;
}


void Salary::CalculateTotalsal()
{   for(int i=0;i<12;i++)
    {
    m_totalsal[i]= base_salary[i]+ post_salary[i]+ age_salary[i]+ allowance[i]+ post_sub[i]+ subsidy[i]+ shelter_sub[i]+ trans_sub[i];

    }
    Tax();
    AfterTax();
    total();
}

void Salary::Tax()
{
    for(int i=0;i<12;i++)
    {
    tax[i] = 0;
    if(m_totalsal[i]<=800)
       tax[i] =  0;
    else if(m_totalsal[i]>800 && m_totalsal[i]<=1000)
       tax[i] = 0.05*(m_totalsal[i]-800);
    else if(m_totalsal[i]>1000 && m_totalsal[i]<=5000)
       tax[i] = (10+0.1*(m_totalsal[i]-1000));
    else
       tax[i] = (410+0.2*(m_totalsal[i]-5000));

    }

}

void Salary::AfterTax()
{
    for(int i=0;i<12;i++)
    {
    Aftertax [i]= 0;
    Aftertax [i] = m_totalsal[i] - tax[i];

    }

}

void Salary::total()
{
    for(int i=0;i<12;i++)
    {
    this->TOTAL += this->Aftertax[i];
    }

}
