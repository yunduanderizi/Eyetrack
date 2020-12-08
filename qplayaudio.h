#ifndef QPLAYAUDIO_H
#define QPLAYAUDIO_H

#include <QObject>
#include<QMediaPlayer>
#include<QDebug>
class QPlayAudio:public QObject
{
    Q_OBJECT
public:
    QPlayAudio();
    void PlayeAudio(QString sPath,int volume);
    bool ifFinished(){return Finished;}
private slots:
    void SlotPosionChanged(qint64 position);
signals:
    void SigFinishedPlay();
private:
    QMediaPlayer * player;
    int AudioLength; //文件长度 ms
    bool Finished;
};

#endif // QPLAYAUDIO_H
