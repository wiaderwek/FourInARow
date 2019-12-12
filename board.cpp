#include "board.h"

Board::Board(int pieceSize)
{
    this->pieceSize = pieceSize;
}

QRectF Board::boundingRect() const
{
    return QRectF(0, 0, WIDTH*pieceSize, HIGHT*pieceSize);
}

QPainterPath Board::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Board::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::darkBlue);
    painter->setBrush(Qt::darkBlue);

    for(int i = 0; i < WIDTH; ++i)
    {
        for(int j = 0; j < HIGHT; ++j)
        {
            QPainterPath rectangle, circle, piece;
            QRect rect(i*pieceSize, j*pieceSize, pieceSize, pieceSize);
            rectangle.addRect(rect);
            circle.addEllipse(rect.center(), rect.width()/2 - 5, rect.height()/2 - 5);
            piece = rectangle - circle;
            painter->drawPath(piece);
        }
    }
}

int Board::getPieceSize() const
{
    return pieceSize;
}
