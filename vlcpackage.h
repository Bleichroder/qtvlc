#ifndef VLCPACKAGE_H
#define VLCPACKAGE_H

#include <vlc.h>
#include <QWidget>

class vlcpackage
{
private:
    //vlc指针
    libvlc_instance_t * inst;
    libvlc_media_player_t *player;
    libvlc_media_t *media;

public:
    vlcpackage();
    ~vlcpackage();

    void setMedia(bool isfile, char *address);
    void setWid(WId id);
    void setVolume(int);
    int volume();

    //播放控制方法：播放、暂停、停止
    void play();
    void pauseresume(bool);
    void stop();
};

#endif // VLCPACKAGE_H
