#include "droppingball.h"

#include <QPainter>
#include <iostream>

DroppingBall::DroppingBall(const int size, const QColor& color, qreal stopPoint)
    : size(size), color(color), stopPoint(stopPoint), rect(QRectF(0, 0, size, size))
{
}

QRectF DroppingBall::boundingRect() const
{
    return rect;
}

QPainterPath DroppingBall::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void DroppingBall::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(color);
    painter->setBrush(color);

    QPainterPath rectangle, circle, piece;
    rectangle.addRect(rect);
    circle.addEllipse(rect.center(), rect.width()/2 - 5, rect.height()/2 - 5);
    painter->drawPath(circle);
}

QRectF DroppingBall::geometry() const
{
    std::cout << "geometry" << std::endl;
    return boundingRect();
}

void DroppingBall::setGeometry(const QRectF& rect)
{
    std::cout << "setGeometry: " << std::endl;
    this->rect = rect;
    update();
}
