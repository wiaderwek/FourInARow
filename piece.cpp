#include "piece.h"

#include <QPainter>
#include <iostream>

Piece::Piece(int side)
    : mSide(side), c(0)
{
}

QRectF Piece::boundingRect() const
{
    return QRectF(0, 0, mSide, mSide);
}

QPainterPath Piece::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Piece::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::darkBlue);
    painter->setBrush(Qt::darkBlue);

    QRect rect(0, 0, mSide, mSide);
    QPainterPath rectangle, circle, piece;
    rectangle.addRect(rect);
    circle.addEllipse(rect.center(), rect.width()/2 - 5, rect.height()/2 - 5);
    piece = rectangle - circle;
    painter->setClipPath(piece);
    painter->drawPath(piece);
}

int Piece::getSide() const
{
    return mSide;
}

void Piece::changeSize(const QRectF& rect)
{
    float newSide = rect.height()/6;
    double percent = abs(newSide - mSide) / (double) mSide;
    mSide = newSide;
    //std::cout << x() << "  " << percent << "   " << newSide << std::endl;
    //setPos(pos().rx() * percent, pos().ry()*percent);
    //update();
    std::cout << "elo " << c++ << "   " <<rect.height() << std::endl;

}
