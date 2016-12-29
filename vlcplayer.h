#ifndef VLCPLAYER_H
#define VLCPLAYER_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "url.h"

namespace Ui {
class VLCPlayer;
}

class VLCPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VLCPlayer(QWidget *parent = 0);
    ~VLCPlayer();

    WId getWinID();
    void setmedia(char *);
    void changeStatus();
    void cameralist();
    void closeEvent(QCloseEvent *);

    bool isplay;
    QString currpath;

private:
    Ui::VLCPlayer *ui;

    QString filepath, urlpath;
    bool isfile;                //isfile文件:true   URL:false
    char* pToken;

    QMenu *open;
    QAction *openfile;
    QAction *openurl;

    url *u;

signals:
    void play();
    void pauseresume(bool);
    void stop();
    void setMedia(bool isfile, char *address);
    void showList();
    void additem(QString, QString);
    void checklist();
    void previous();
    void next();
    void setvolume(int);
    void videoclose();

private slots:
    void filedialog();
    void urldialog();
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_stopButton_clicked();
    void on_listButton_clicked();
    void on_previousButton_clicked();
    void on_nextButton_clicked();
    void on_volumeSlider_valueChanged(int value);
};

#endif // VLCPLAYER_H
