#include "signupdialog.h"
#include "ui_signupdialog.h"

signupdialog::signupdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signupdialog)
{
    ui->setupUi(this);
}

signupdialog::~signupdialog()
{
    delete ui;
}

QString    signupdialog::num()           //工号
{
    return ui->lineEdit_num->text();
}

int        signupdialog::age()          //年龄
{
    return ui->lineEdit_age->text().toInt();
}

QString    signupdialog::tele()        //电话号码
{
    return ui->lineEdit_tele->text();
}

QDate      signupdialog::date()        //入职日期
{
    return ui->dateEdit_date->date();
}

QString    signupdialog::name()        //姓名
{
    return ui->lineEdit_name->text();
}

QString    signupdialog::addr()        //住址
{
    return ui->lineEdit_addr->text();
}
