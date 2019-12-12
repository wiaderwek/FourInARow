#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsItem>
#include <QRectF>
#include <QObject>
#include <QPainterPath>

class Piece : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Piece(int side);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    int getSide() const;

public slots:
    void changeSize(const QRectF&);

private:
    int mSide;
    int c;
    QRectF geometry;
};

#endif // PIECE_H
