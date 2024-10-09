#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>

namespace Ui {
class signupdialog;
}

class signupdialog : public QDialog
{
    Q_OBJECT

public:
    explicit signupdialog(QWidget *parent = nullptr);
    ~signupdialog();

    QString       num();           //工号
    int           age();           //年龄
    QString       tele();          //电话号码
    QDate         date();          //入职日期
    QString       name();          //姓名
    QString       addr();          //住址
private:
    Ui::signupdialog *ui;
};

#endif // SIGNUPDIALOG_H
