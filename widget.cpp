#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);
    videowidget.setPalette(pal);
    videowidget.setAutoFillBackground(true);

    listwidget.setMaximumWidth(200);

    vboxlayout.setContentsMargins(0,0,0,3);
    vboxlayout.setSpacing(3);
    hboxlayout1.setMargin(0);
    hboxlayout2.setMargin(0);

    open.setIcon(style()->standardPixmap(QStyle::SP_DirIcon));
    reload.setIcon(QIcon("://icons/reload.png"));
    play.setIcon(style()->standardPixmap(QStyle::SP_MediaPlay));
    pause.setIcon(style()->standardPixmap(QStyle::SP_MediaPause));
    stop.setIcon(style()->standardPixmap(QStyle::SP_MediaStop));
    sound.setIcon(style()->standardPixmap(QStyle::SP_MediaVolume));
    list.setIcon(style()->standardPixmap(QStyle::SP_ArrowRight));

    hboxlayout1.addWidget(&videowidget);
    hboxlayout1.addWidget(&listwidget);
    hboxlayout2.addSpacing(3);
    hboxlayout2.addWidget(&open);
    hboxlayout2.addWidget(&reload);
    hboxlayout2.addWidget(&play);
    hboxlayout2.addWidget(&pause);
    hboxlayout2.addWidget(&stop);
    hboxlayout2.addWidget(&slider);
    hboxlayout2.addWidget(&sound);
    hboxlayout2.addWidget(&list);
    hboxlayout2.addWidget(&timelabel);
    hboxlayout2.addSpacing(3);

    timelabel.setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    timelabel.setText("hh:mm:ss");

    vboxlayout.addLayout(&hboxlayout1);
    vboxlayout.addLayout(&hboxlayout2);
    setLayout(&vboxlayout);

    mediaplayer.setPlaylist(&mediaplaylist);
    mediaplayer.setVideoOutput(&videowidget);

    volumewidget.setWindowFlag(Qt::ToolTip);
    volumelayout.addWidget(&volumelabel,0,Qt::AlignHCenter);
    volumelayout.addWidget(&volumeslider,0,Qt::AlignHCenter);
    volumewidget.setLayout(&volumelayout);
    volumelayout.setMargin(2);

    volumeslider.setMaximum(100);
    volumeslider.setValue(mediaplayer.volume());
    volumelabel.setText(QString::number(mediaplayer.volume()));

    connect (&open, SIGNAL(clicked()), this, SLOT(OpenFile()));
    connect (&reload, SIGNAL(clicked()), this, SLOT(DoingReload()));
    connect (&list, SIGNAL(clicked()), this, SLOT(ListDisplay()));
    connect (&sound, SIGNAL(clicked()), this, SLOT(OnSoundClicked()));
    connect (&volumeslider, SIGNAL(sliderMoved(int)), this, SLOT(OnVolumeSliderMoved(int)));
    connect (&listwidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(ListOnDoubleClicked(QListWidgetItem*)));

    connect (&play, SIGNAL(clicked()), &mediaplayer, SLOT(play()));
    connect (&pause, SIGNAL(clicked()), &mediaplayer, SLOT(pause()));
    connect (&stop, SIGNAL(clicked()), &mediaplayer, SLOT(stop()));

    connect (&mediaplayer, &QMediaPlayer::durationChanged, &slider, &Slider::setMaximum);
    connect (&mediaplayer, &QMediaPlayer::positionChanged, &slider, &Slider::setValue);
    connect (&slider, &Slider::sliderMoved, &mediaplayer, &QMediaPlayer::setPosition);
    connect (&slider, &Slider::pressedSlider, &mediaplayer, &QMediaPlayer::setPosition);

    connect (&mediaplayer, &QMediaPlayer::durationChanged, this, &Widget::TimeDuration);
    connect (&mediaplayer, &QMediaPlayer::positionChanged, this, &Widget::TimePosition);
}

void Widget::OpenFile()
{
    QStringList filestringlist = QFileDialog::getOpenFileNames(this,"Open Videos","","Video Files (*.mkv *.mp4 *.flv)");
    if (!filestringlist.isEmpty())
    {
        foreach (QFileInfo fileinfo, filestringlist) {
            mediaplaylist.addMedia(QUrl::fromLocalFile(fileinfo.filePath()));
            listwidget.addItem(fileinfo.fileName());
        }
    }
}

void Widget::DoingReload()
{
    int videoindex = mediaplaylist.currentIndex();
    mediaplayer.setMedia(QUrl::fromLocalFile(""));
    mediaplayer.setPlaylist(&mediaplaylist);
    mediaplaylist.setCurrentIndex(videoindex);
    mediaplayer.setVideoOutput(&videowidget);
}

void Widget::ListDisplay()
{
    if (listwidget.isHidden())
    {
        listwidget.show();
        list.setIcon(style()->standardPixmap(QStyle::SP_ArrowRight));
    }
    else
    {
        listwidget.hide();
        list.setIcon(style()->standardPixmap(QStyle::SP_ArrowLeft));
    }
}

void Widget::ListOnDoubleClicked(QListWidgetItem *item)
{
    mediaplaylist.setCurrentIndex(listwidget.row(item));
    mediaplayer.setVideoOutput(&videowidget);
}

void Widget::OnSoundClicked()
{
//    volumewidget.setGeometry(x()+sound.x()+5,y()+size().height()-160,30,150);
    if (volumewidget.isHidden())
    {
        volumewidget.move(x()+sound.x()+5,y()+size().height()-110);
        volumewidget.show();
    }
    else
    {
        volumewidget.hide();
    }
}

void Widget::OnVolumeSliderMoved(int value)
{
    mediaplayer.setVolume(value);
    volumelabel.setText(QString::number(mediaplayer.volume()));
}

void Widget::TimeDuration(qint64 duration)
{
    duration = duration/1000;
    durationtime = QTime ((duration/3600)%1000, (duration/60)%60, duration%60);

    if (duration<3600) format = "mm:ss";
    else format = "hh:mm:ss";
}

void Widget::TimePosition(qint64 position)
{
    position /= 1000;
    positiontime = QTime ((position/3600)%1000, (position/60)%60, position%60);

    timelabel.setText(positiontime.toString(format)+"/"+durationtime.toString(format));
}

Widget::~Widget()
{
}

