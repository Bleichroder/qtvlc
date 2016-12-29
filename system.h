#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QApplication>
#include "vlcplayer.h"
#include "listdialog.h"
#include "vlcpackage.h"

class vlcsystem : public QObject
{
    Q_OBJECT
public:
    explicit vlcsystem(QObject *parent = 0);
    ~vlcsystem();

private:
    //VLC指针
    vlcpackage *vlcp;

    //视频窗口和列表窗口指针
    VLCPlayer *video;
    listDialog *list;

    bool islistopen;

public slots:
    //播放功能
    void setMedia(bool isfile, char *address);
    void play();
    void pauseresume(bool);
    void stop();
    void previous();
    void next();
    void setvolume(int);
    void videoclose();
    void listclose();

    //列表窗口操作
    void showList();
    void listFromVideo();
    void listPlay(bool, QString);
    void checklist();
};

#endif // SYSTEM_H
