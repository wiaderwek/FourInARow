#include "fourinarowpiece.h"

#include <QPainter>
#include <QRect>
#include <QPainterPath>
#include <QRegion>

FourInARowPiece::FourInARowPiece(QWidget* parent)
    : QFrame(parent)
{
    color = Qt::white;
}

void FourInARowPiece::setColor(QColor& newColor)
{
    color = newColor;
    update();
}

void FourInARowPiece::paintEvent(QPaintEvent* event)
{
    //QGraphicsView + spadanie
    //fitInView - argument do zachowywania proporcji
    //disable buttons jak nie mogę nic zrobić
    //siganl mapper, żeby guziki miały jedną funkcję obsługi
    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::darkBlue);
    painter.setBrush(Qt::darkBlue);
    QRect rect = event->rect();
//    painter.drawRect(rect);
//    painter.setBrush(color);
//    painter.drawEllipse(rect.center(), rect.width()/2 - 5, rect.height()/2 - 5);
    QPainterPath rectangle, circle, piece;
    rectangle.addRect(rect);
    circle.addEllipse(rect.center(), rect.width()/2 - 5, rect.height()/2 - 5);
    piece = rectangle - circle;
    painter.setClipPath(piece);
    painter.drawPath(piece);
}

void FourInARowPiece::resetColor()
{
    color = Qt::white;
    update();
}
