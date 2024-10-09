#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDialog>
#include<QStandardItemModel>
#include "infotable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    virtual void resizeEvent(QResizeEvent *event) override;
    enum ShowType
    {
        SignupTable, SalaryTable
    };
    ShowType m_iCurTable; //表示当前表格显示的信息

     QStandardItemModel * staffInforModel; //显示表格信息数据模型

    void ShowSignupTable();

    void ShowSalaryTable(int index);

    InfoTable m_InfoTable; //数据汇总类

    int m_staff_index = 0;

    QMenu *RightClickMenu;                          //右键点击菜单
    QAction *deleteAction;                          //单行删除事件
    int     seletMouseRow;                          //选择到的表格的行数信息


private slots:
    void on_actionwrite_in_triggered();

    void on_actionread_out_triggered();

    void on_actionAddStaff_triggered();
    void on_ShowInfotableView_changed();

    void on_table_clicked(const QModelIndex &index);

    void on_actionfind_triggered();

    void onGetMousePos(QPoint pos);               //菜单点击后获取当前位置
    void onMenuAction(QAction *act);              //事件操作
    void on_actionreturn_triggered();

    void on_actionsort_triggered();

signals:
    void showmain();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
