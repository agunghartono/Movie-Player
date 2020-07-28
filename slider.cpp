#include "slider.h"

Slider::Slider()
{
    setOrientation(Qt::Horizontal);
}

void Slider::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        double pressedLocationDouble=event->x()*(maximum()/static_cast<double>(width()));
        emit pressedSlider(static_cast<int>(pressedLocationDouble));
        event->accept();
    }
    QSlider::mousePressEvent(event);
}
