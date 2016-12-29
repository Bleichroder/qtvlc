#include "system.h"

vlcsystem::vlcsystem(QObject *parent) : QObject(parent)
{
    //初始化vlc
    vlcp = new vlcpackage();

    //初始化窗口
    video = new VLCPlayer();
    list = new listDialog();

    islistopen = false;

    video->show();
    vlcp->setWid(video->getWinID());

    //播放功能
    connect(video, SIGNAL(play()), this, SLOT(play()));
    connect(video, SIGNAL(pauseresume(bool)), this, SLOT(pauseresume(bool)));
    connect(video, SIGNAL(stop()), this, SLOT(stop()));
    connect(video, SIGNAL(previous()), this, SLOT(previous()));
    connect(video, SIGNAL(next()), this, SLOT(next()));
    connect(video, SIGNAL(setvolume(int)), this, SLOT(setvolume(int)));
    connect(video, SIGNAL(setMedia(bool,char*)), this, SLOT(setMedia(bool,char*)));
    connect(video, SIGNAL(showList()), this, SLOT(showList()));
    connect(video, SIGNAL(checklist()), this, SLOT(checklist()));
    connect(video, SIGNAL(additem(QString, QString)), list, SLOT(additem(QString, QString)));
    connect(video, SIGNAL(videoclose()), this, SLOT(videoclose()));
    connect(list, SIGNAL(listPlay(bool, QString)), this, SLOT(listPlay(bool, QString)));
    connect(list, SIGNAL(listclose()), this, SLOT(listclose()));
}

vlcsystem::~vlcsystem()
{
    delete vlcp;
    delete video;
    delete list;
}

void vlcsystem::play()
{
    vlcp->play();
}

void vlcsystem::pauseresume(bool isplay)
{
    vlcp->pauseresume(isplay);
}

void vlcsystem::stop()
{
    vlcp->stop();
}

void vlcsystem::previous()
{
    int pos = list->ldmedialist.indexOf(video->currpath) - 1;     //将当前位置减一，得到上一个位置。

    if (pos < 0)    //如果原位置是第一个，上一个位置就会为负值，此时循环至列表末位位置。
        pos = list->ldmedialist.count() - 1;              //设置为末位的位置。
    QString cm = list->ldmedialist.at(pos);
    QByteArray ba = cm.toLatin1();
    char *add = ba.data();
    QVariant tempValue = list->ldboollist.at(pos);
    bool tempFinished = tempValue.toBool();
    vlcp->setMedia(tempFinished, add);
    video->currpath = cm;
    vlcp->play();
}

void vlcsystem::next()
{
    int pos = list->ldmedialist.indexOf(video->currpath) + 1;     //将当前位置加一，得到下一个位置。

    if (pos == list->ldmedialist.count())    //如果原位置是最后一个，下一个位置就会越界，此时循环至列表首位位置。
        pos = 0;                            //设置为首位的位置。
    QString cm = list->ldmedialist.at(pos);
    QByteArray ba = cm.toLatin1();
    char *add = ba.data();
    QVariant tempValue = list->ldboollist.at(pos);
    bool tempFinished = tempValue.toBool();
    vlcp->setMedia(tempFinished, add);
    video->currpath = cm;
    vlcp->play();
}

void vlcsystem::setMedia(bool isfile, char *address)
{
    vlcp->setMedia(isfile, address);
}

void vlcsystem::showList()
{
    if(!islistopen)
    {
        listFromVideo();
        list->list();
        list->show();
        islistopen = !islistopen;
    }
    else
    {
        list->hide();
        islistopen = !islistopen;
    }
}

void vlcsystem::listFromVideo()
{
    int x = video->x() + video->width() + 5;
    int y = video->y() + (video->height()-list->height())/2;

    list->move(x, y);
}

void vlcsystem::listPlay(bool isfile, QString address)
{
    QByteArray ba = address.toLatin1();
    char *add = ba.data();
    vlcp->setMedia(isfile, add);
    video->isplay = true;
    video->changeStatus();
    video->currpath = address;
    vlcp->play();
}

void vlcsystem::checklist()
{
    if(islistopen)
        list->list();
}

void vlcsystem::setvolume(int volume)
{
    vlcp->setVolume(volume);
}

void vlcsystem::videoclose()
{
    video->close();
    list->close();
    qApp->quit();
}

void vlcsystem::listclose()
{
    list->hide();
    islistopen = false;
}
