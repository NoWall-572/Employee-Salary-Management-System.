#include "findstaff.h"
#include "ui_findstaff.h"

FindStaff::FindStaff(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindStaff)
{
    ui->setupUi(this);

    ui->comboBox->addItem("按职工工号查找");
    ui->comboBox->addItem("按职工姓名查找");
    ui->comboBox->setCurrentIndex(0);
}

FindStaff::~FindStaff()
{
    delete ui;
}

QString FindStaff::Find()
{
    return ui->lineEdit_find->text();
}

int FindStaff::FindByWhat()
{
    return ui->comboBox->currentIndex();
}
