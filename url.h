#ifndef URL_H
#define URL_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class url;
}

class url : public QDialog
{
    Q_OBJECT

public:
    explicit url(QWidget *parent = 0);
    ~url();
    QString urltext;

private slots:
    void on_OKButton_clicked();

private:
    Ui::url *ui;
};

#endif // URL_H
