#ifndef SLIDER_H
#define SLIDER_H

#include <QObject>
#include <QSlider>
#include <QMouseEvent>

class Slider : public QSlider
{
    Q_OBJECT
public:
    Slider();
    void mousePressEvent(QMouseEvent*);
signals:
    void pressedSlider(int);
private:

};

#endif // SLIDER_H
