#include "url.h"
#include "ui_url.h"

url::url(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::url)
{
    ui->setupUi(this);
    urltext = "";
}

url::~url()
{
    delete ui;
}

void url::on_OKButton_clicked()
{
    if(ui->urlEdit->text() != "")
        urltext = ui->urlEdit->text();
    else
        QMessageBox::information(NULL, tr("Warning"), tr("No URL has been input!"));
}
