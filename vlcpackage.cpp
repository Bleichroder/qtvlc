#include "vlcpackage.h"

vlcpackage::vlcpackage()
{
    //初始化vlc
    inst = libvlc_new (0, NULL);
    player = libvlc_media_player_new(inst);
    media = NULL;
}

vlcpackage::~vlcpackage()
{
    libvlc_media_player_release(player);
    libvlc_media_release(media);
    libvlc_release(inst);
}

void vlcpackage::setMedia(bool isfile, char *address)
{
    libvlc_media_release(media);
    if(isfile)
        media = libvlc_media_new_path (inst, address);
    else
        media = libvlc_media_new_location (inst, address);
    libvlc_media_player_set_media(player, media);
}

void vlcpackage::setWid(WId id)
{
    libvlc_media_player_set_hwnd(player, (void *)id);
}

void vlcpackage::play()
{
    libvlc_media_player_play(player);
}

void vlcpackage::pauseresume(bool isplay)
{
    libvlc_media_player_set_pause(player, int(isplay));
}

void vlcpackage::stop()
{
    libvlc_media_player_stop(player);
}

void vlcpackage::setVolume(int volume)
{
    libvlc_audio_set_volume(player, volume);
}

int vlcpackage::volume()
{
    return libvlc_audio_get_volume(player);
}
