#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "staff.h"
#include "readonlydelegate.h"
#include "signupdialog.h"
#include "findstaff.h"
#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ShowInfotableView->setSelectionMode(QAbstractItemView::SingleSelection); //单次选择
    ui->ShowInfotableView->setSelectionBehavior(QAbstractItemView::SelectItems); //选中一个item
    //New一个QStandardItemModel的对象并与QTableView资源建立关联；
    staffInforModel = new QStandardItemModel();
    //建立关联
    ui->ShowInfotableView->setModel(staffInforModel);
    ui->ShowInfotableView->setSelectionMode(QAbstractItemView::SingleSelection); //单次选择
    ui->ShowInfotableView->setSelectionBehavior(QAbstractItemView::SelectItems); //选中一个item

     connect(ui->ShowInfotableView->itemDelegate(), &QAbstractItemDelegate::closeEditor, this, &MainWindow::on_ShowInfotableView_changed);

    ui->ShowInfotableView->setContextMenuPolicy(Qt::CustomContextMenu); //可弹出右键菜单
    //菜单等事件
    RightClickMenu = new QMenu();               //右键点击菜单
    deleteAction = new QAction("删除",this);               //单行删除事件
    RightClickMenu->addAction(deleteAction);    //将action添加到菜单内
    //信号槽连接
    connect(ui->ShowInfotableView,&QTableView::customContextMenuRequested,this,&MainWindow::onGetMousePos);
    connect(RightClickMenu,&QMenu::triggered,this,&MainWindow::onMenuAction);
 }

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionwrite_in_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "另存为一个文件";
    QString filter = "文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if(aFileName.isEmpty())
        return;
    m_InfoTable.SaveStaffToFile(aFileName);


}

void MainWindow::ShowSignupTable()
{
    m_iCurTable = SignupTable; //表示当前显示的是职工信息

    staffInforModel->clear();
    staffInforModel->setColumnCount(7);
    //表头
    QStringList templist;
    templist.append("工号");
    templist.append("姓名");
    templist.append("入职日期");
    templist.append("年龄");
    templist.append("电话号码");
    templist.append("住址");
    templist.append("总工资");
    staffInforModel->setHorizontalHeaderLabels(templist);

    int RowCnt = m_InfoTable.GetStaffNum(); //行数（不含标题）
    staffInforModel->setRowCount(RowCnt);

    //遍历，插入数据
    QStandardItem *aTempItem; //临时的item
    QString tempStr;
    for(int i=0; i<RowCnt; ++i)
    {
        Staff tempstaff=m_InfoTable.GetStaff(i);
        aTempItem = new QStandardItem(tempstaff.num);
        staffInforModel->setItem(i, 0, aTempItem);
        aTempItem = new QStandardItem(tempstaff.name);
        staffInforModel->setItem(i, 1, aTempItem);
        tempStr = tempstaff.date.toString("yyyy-MM-dd");
        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 2, aTempItem);
        tempStr = QString::number(tempstaff.age);
        aTempItem = new QStandardItem(tempStr);
         staffInforModel->setItem(i, 3, aTempItem);
        aTempItem = new QStandardItem(tempstaff.tele);
        staffInforModel->setItem(i, 4, aTempItem);
        aTempItem = new QStandardItem(tempstaff.addr);
        staffInforModel->setItem(i, 5, aTempItem);
        tempStr = QString::number(tempstaff.sal.TOTAL);
        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 6, aTempItem);
    }
    //设置号码为只读
    readonlydelegate* readOnlyDelegate = new readonlydelegate(this);
    ui->ShowInfotableView->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->ShowInfotableView->setItemDelegateForColumn(1, readOnlyDelegate);
    ui->ShowInfotableView->setItemDelegateForColumn(2, readOnlyDelegate);


    connect(ui->ShowInfotableView,&QTableView::clicked,this,&MainWindow::on_table_clicked);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //父类的保持
    QMainWindow::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();

    //窗口改变大小的时候列表控件跟着改变
    ui->ShowInfotableView->setGeometry(5,5,x*0.99,y*0.99);
}

void MainWindow::on_actionread_out_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择一个文件";
    QString filter = "文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if(aFileName.isEmpty())
        return;
    //创建成功，打开文件
    m_InfoTable.ReadStaffFromFile(aFileName);
    ShowSignupTable();
}


void MainWindow::on_actionAddStaff_triggered()
{
    signupdialog dlgSignup(this);
    int ret = dlgSignup.exec(); //以模态方式显示对话框
    if(ret==QDialog::Accepted)//OK按钮被按下
    {
        Staff tempstaff;
        tempstaff.name = dlgSignup.name();
        tempstaff.num = dlgSignup.num();
        tempstaff.date = dlgSignup.date();
        tempstaff.age = dlgSignup.age();
        tempstaff.tele = dlgSignup.tele();
        tempstaff.addr = dlgSignup.addr();
        m_InfoTable.AddStaff(tempstaff);
        ShowSignupTable();
    }
}

void MainWindow::on_ShowInfotableView_changed()
{
    QModelIndex index = ui->ShowInfotableView->currentIndex();
    int iRow = index.row(); //哪个职工
    int iCol = index.column(); //哪个列



    Salary& sal = m_InfoTable.m_staff[m_staff_index].sal;
    QVariant data; //数据



    switch (m_iCurTable) //根据当前选择的表格不同进行对应的职工信息的修改
    {
    case SignupTable:
    {
        //当前是职工信息表
        //修改职工对应的数值
        Staff & staff = m_InfoTable.m_staff[iRow]; //获取当前，一定要是引用
        data = staffInforModel->data(index);//获取数值

        switch (iCol)
        {
        case 0:
            staff.num = data.toString();
            break;
        case 1:
            staff.name = data.toString();
            break;
        case 2:
            staff.age = data.toInt();
            break;
        case 3:
            staff.date = data.toDate();
            break;
        case 4:
            staff.tele = data.toString();
            break;
        case 5:
            staff.addr =data.toString();
            break;
        default:
            break;
        }

        break;
    }
    case SalaryTable://当前是职工工资
    {
        data = staffInforModel->data(index);//获取数值

        switch (iCol)
        {
        case 3: //基本工资
            sal.base_salary[iRow] = data.toDouble();
            break;
        case 4://岗位工资
            sal.post_salary[iRow] = data.toDouble();

            break;
        case 5://工龄工资
            sal.age_salary[iRow] = data.toDouble();
            break;
        case 6://津贴
            sal.allowance[iRow] = data.toDouble();
            break;
        case 7:// 岗位补贴
            sal.post_sub[iRow] = data.toDouble();
            break;
        case 8: //补贴
            sal.subsidy[iRow] = data.toDouble();
            break;
        case 9: //住房补贴
            sal.shelter_sub[iRow] = data.toDouble();
            break;
        case 10: //交通补贴
            sal.trans_sub[iRow] = data.toDouble();
            break;
        default:
            break;
        }
        sal.CalculateTotalsal();

        ShowSalaryTable(m_staff_index); //重新显示，更新数据
        break;
    }
    }

}

void MainWindow::on_table_clicked(const QModelIndex &index)
{

    if(m_iCurTable == SignupTable)
    {
        if(index.column()!=6)
            return;
        int row = index.row();
        this->ShowSalaryTable(row);
    }
}

void MainWindow::ShowSalaryTable(int index)
{
    m_staff_index = index;
    m_iCurTable = SalaryTable;
    Staff tempstaff = m_InfoTable.m_staff[index];

    staffInforModel->clear();

    staffInforModel->setColumnCount(13);
    //表头
    QStringList templist;
    templist.append("工号");
    templist.append("姓名");
    templist.append("月份");
    templist.append("基本工资");
    templist.append("岗位工资");
    templist.append("工龄工资");
    templist.append("津贴");
    templist.append("岗位补贴");
    templist.append("补贴");
    templist.append("住房补贴");
    templist.append("交通补贴");
    templist.append("个人所得税");
    templist.append("税后收入");
    staffInforModel->setHorizontalHeaderLabels(templist);


    staffInforModel->setRowCount(12);

    //遍历，插入数据
    QStandardItem *aTempItem; //临时的item
    QString tempStr;
    for(int i=0; i<12; ++i)
    {


        aTempItem = new QStandardItem(tempstaff.num);

        staffInforModel->setItem(i, 0, aTempItem);
        aTempItem = new QStandardItem(tempstaff.name);
        staffInforModel->setItem(i, 1, aTempItem);

        tempStr = QString::number(tempstaff.sal.month[i]);

        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 2, aTempItem);
        tempStr = QString::number(tempstaff.sal.base_salary[i]);
        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 3, aTempItem);
        tempStr = QString::number(tempstaff.sal.post_salary[i]);
        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 4, aTempItem);
        tempStr = QString::number(tempstaff.sal.age_salary[i]);
        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 5, aTempItem);
        tempStr = QString::number(tempstaff.sal.allowance[i]);
        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 6, aTempItem);
        tempStr = QString::number(tempstaff.sal.post_sub[i]);
        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 7, aTempItem);
        tempStr = QString::number(tempstaff.sal.subsidy[i]);
        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 8, aTempItem);
        tempStr = QString::number(tempstaff.sal.shelter_sub[i]);
        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 9, aTempItem);
        tempStr = QString::number(tempstaff.sal.trans_sub[i]);
        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 10, aTempItem);
        tempStr = QString::number(tempstaff.sal.tax[i]);
        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 11, aTempItem);
        tempStr = QString::number(tempstaff.sal.Aftertax[i]);
        aTempItem = new QStandardItem(tempStr);
        staffInforModel->setItem(i, 12, aTempItem);

    }
    //设置号码为只读

    readonlydelegate* readOnlyDelegate = new readonlydelegate(this);
    ui->ShowInfotableView->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->ShowInfotableView->setItemDelegateForColumn(1, readOnlyDelegate);
    ui->ShowInfotableView->setItemDelegateForColumn(2, readOnlyDelegate);
    ui->ShowInfotableView->setItemDelegateForColumn(11, readOnlyDelegate);
    ui->ShowInfotableView->setItemDelegateForColumn(12, readOnlyDelegate);
}

void MainWindow::on_actionfind_triggered()
{
    FindStaff fsDlg(this);
    int ret = fsDlg.exec();
    if(ret == FindStaff::Accepted)
    {
        int findBy = fsDlg.FindByWhat();
        QString Find = fsDlg.Find();
        int pos = -1;
        if(findBy == 0)
        {
            pos = this->m_InfoTable.findByNum(Find);
        }
        else
        {
            pos = this->m_InfoTable.findByName(Find);
        }

        if(pos == -1)
        {
            QMessageBox msb(this);
            msb.setText("抱歉，该职工不存在");
            msb.exec();
        }
        else
        {
            this->ShowSalaryTable(pos);
        }
    }
}

//获取位置信息
void MainWindow::onGetMousePos(QPoint pos)
{
    QModelIndex index = ui->ShowInfotableView->indexAt(pos);    //找到tableview当前位置信息
    seletMouseRow = index.row();    //获取到了当前右键所选的行数
    if(index.isValid())        //如果行数有效，则显示菜单
        RightClickMenu->exec(QCursor::pos());

}
//实现菜单删除操作函数
void MainWindow::onMenuAction(QAction *act)
{
    //删除本行数据
    if(act->text() == "删除")                        //看选中了删除这个菜单
    { staffInforModel->removeRow(seletMouseRow);    //删除掉了表格信息
        m_InfoTable.RemoveStaff(seletMouseRow);     //需要增加一行处理m_InfoTable
    }
}



void MainWindow::on_actionreturn_triggered()
{
     this->ShowSignupTable();
}

void MainWindow::on_actionsort_triggered()
{
     this->m_InfoTable.sortStaff();
     this->ShowSignupTable();
}











































