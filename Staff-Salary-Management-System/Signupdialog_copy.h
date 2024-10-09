#ifndef SIGNUPDIALOG_COPY_H
#define SIGNUPDIALOG_COPY_H
#include<QString>
#include<QDate>
#include<QDialog>

namespace ui
{
class signupdialog;
}
class signupdialog : public QDialog
{
    Q_OBJECT
public:


    int           num();           //工号
    int           age();           //年龄
    QString       tele();          //电话号码
    QDate         date();          //入职日期
    QString       name();          //姓名
    QString       addr();          //住址

};

#endif // SIGNUPDIALOG_COPY_H
