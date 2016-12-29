#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class listDialog;
}

class listDialog : public QDialog
{
    Q_OBJECT

public:
    explicit listDialog(QWidget *parent = 0);
    ~listDialog();

    QStringList ldmedialist, ldboollist;

    void list();
    void closeEvent(QCloseEvent *);

private:
    Ui::listDialog *ui;
    QStandardItemModel *medialist_model;

signals:
    void listPlay(bool, QString);
    void listclose();

private slots:
    void additem(QString, QString);
    void on_listtableView_doubleClicked(const QModelIndex &index);
};

#endif // LISTDIALOG_H
