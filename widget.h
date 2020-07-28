#ifndef WIDGET_H
#define WIDGET_H

#include "slider.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QTime>
#include <QFileDialog>
#include <QToolButton>
#include <QKeyEvent>
#include <QDebug>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void OpenFile();
    void DoingReload();
    void ListDisplay();
    void ListOnDoubleClicked(QListWidgetItem*);
    void OnSoundClicked();
    void OnVolumeSliderMoved(int);
    void TimeDuration(qint64);
    void TimePosition(qint64);

private:
    QVBoxLayout vboxlayout;
    QHBoxLayout hboxlayout1, hboxlayout2;

    QLabel timelabel;
    QTime durationtime, positiontime;
    QString format;

    QMediaPlayer mediaplayer;
    QMediaPlaylist mediaplaylist;
    QVideoWidget videowidget;
    QListWidget listwidget;
    Slider slider;
    QToolButton open, reload, play, pause, stop, sound, list;

    QWidget volumewidget;
    QVBoxLayout volumelayout;
    QSlider volumeslider;
    QLabel volumelabel;
};
#endif // WIDGET_H
