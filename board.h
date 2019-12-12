#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsItem>
#include <QRectF>
#include <QObject>
#include <QPainterPath>
#include <QPainter>

class Board : public QGraphicsItem
{
public:
    Board(int pieceSize);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    int getPieceSize() const;

private:
    const int WIDTH = 7;
    const int HIGHT = 6;
    int pieceSize;
};

#endif // BOARD_H
