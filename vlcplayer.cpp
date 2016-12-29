#include "vlcplayer.h"
#include "ui_vlcplayer.h"

VLCPlayer::VLCPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VLCPlayer)
{
    //菜单栏
    openfile = new QAction(tr("打开文件"), this);
    openfile->setStatusTip(tr("打开一个视频文件"));
    connect(openfile, SIGNAL(triggered(bool)), this, SLOT(filedialog()));
    openurl = new QAction(tr("打开url"), this);
    openurl->setStatusTip(tr("打开一个流"));
    connect(openurl, SIGNAL(triggered(bool)), this, SLOT(urldialog()));

    ui->setupUi(this);
    ui->playButton->show();
    ui->pauseButton->hide();

    open = ui->menuBar->addMenu(tr("打开"));
    open->addAction(openfile);
    open->addAction(openurl);
}

VLCPlayer::~VLCPlayer()
{
    delete ui;
}

void VLCPlayer::filedialog()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Choose File"), "/", tr("Image Files(*.wmv *.mp4 *.avi *.mkv *.rmvb)"));
    if(path.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }
    else {
        filepath = path.replace("/", "\\");
        QByteArray ba = filepath.toLatin1();
        char *add = ba.data();
        isfile = true;
        emit additem(filepath, QString(isfile));
        emit checklist();
        emit setMedia(isfile, add);
        isplay = true;
        changeStatus();
        currpath = filepath;
        emit play();
    }
}

void VLCPlayer::urldialog()
{
    u = new url();
    if(u->exec() == QDialog::Accepted)
    {
        urlpath = u->urltext;
    }
    else
        return;
    QByteArray ba = urlpath.toLatin1();
    char *add = ba.data();
    isfile = false;
    emit additem(urlpath, QString(isfile));
    emit checklist();
    emit setMedia(isfile, add);
    isplay = true;
    changeStatus();
    currpath = urlpath;
    emit play();
}

WId VLCPlayer::getWinID()
{
   return ui->displayWidget->winId();
}

void VLCPlayer::on_playButton_clicked()
{
    if(!isplay)
    {
        emit pauseresume(isplay);
        isplay = !isplay;
        changeStatus();
    }
}

void VLCPlayer::on_pauseButton_clicked()
{
    if(isplay)
    {
        emit pauseresume(isplay);
        isplay = !isplay;
        changeStatus();
    }
}

void VLCPlayer::on_stopButton_clicked()
{
    emit stop();
    ui->playButton->show();
    ui->pauseButton->hide();
    isplay = false;
}

void VLCPlayer::on_listButton_clicked()
{
    emit showList();
}

void VLCPlayer::changeStatus()
{
    if(isplay)
    {
        ui->playButton->hide();
        ui->pauseButton->show();
    }
    else
    {
        ui->playButton->show();
        ui->pauseButton->hide();
    }
}

void VLCPlayer::on_previousButton_clicked()
{
    emit previous();
    isplay = true;
    changeStatus();
}

void VLCPlayer::on_nextButton_clicked()
{
    emit next();
    isplay = true;
    changeStatus();
    //libvlc_vlm_change_media();
}

void VLCPlayer::on_volumeSlider_valueChanged(int value)
{
    ui->volumelabel->setText(QString("%1").arg(value));
    emit setvolume(value);
}

void VLCPlayer::closeEvent(QCloseEvent *event)
{
    emit videoclose();
}
