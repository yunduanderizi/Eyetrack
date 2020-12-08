#include "qplayaudio.h"
#include<QMediaPlayer>
QPlayAudio::QPlayAudio()
{
    AudioLength=0;
    Finished = false;
    player = new QMediaPlayer;
    void(QMediaPlayer::*positionChanged)(qint64) = (&QMediaPlayer::positionChanged);
    connect(player,positionChanged,this,&QPlayAudio::SlotPosionChanged);
}
void QPlayAudio::SlotPosionChanged(qint64 position)
{
    qDebug()<<"positionNow:"<<position<<"FileLength::"<<AudioLength;
    if(position>=AudioLength)
        emit SigFinishedPlay();
}
void QPlayAudio::PlayeAudio(QString sPath,int volume)
{
   Finished = false;

   player->setMedia(QUrl::fromLocalFile(sPath));
   player->setVolume(volume);
   AudioLength = player->duration();
   player->play();
}

