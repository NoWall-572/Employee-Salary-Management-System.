#ifndef FINDSTAFF_H
#define FINDSTAFF_H

#include <QDialog>

namespace Ui {
class FindStaff;
}

class FindStaff : public QDialog
{
    Q_OBJECT

public:
    explicit FindStaff(QWidget *parent = nullptr);
    ~FindStaff();

    QString Find();
    int FindByWhat();


private:
    Ui::FindStaff *ui;
};

#endif // FINDSTAFF_H
