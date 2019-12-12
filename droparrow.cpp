#include "droparrow.h"
#include <QPainter>
#include <QRect>

DropArrow::DropArrow(QWidget* parent)
    :QPushButton(parent)
{
    color = Qt::red;
}

void DropArrow::setColor(QColor& newColor)
{
    color = newColor;
    update();
}

void DropArrow::paintEvent(QPaintEvent* event)
{
    QPushButton::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::darkBlue);
    painter.setBrush(Qt::darkBlue);
    QRect rect = event->rect();
    painter.drawRect(rect);
    painter.setBrush(color);
    painter.drawEllipse(rect.center(), rect.width()/2 - 5, rect.height()/2 - 5);

}
