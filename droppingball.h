#ifndef DROPPINGBALL_H
#define DROPPINGBALL_H


#include <QGraphicsItem>
#include <QRectF>
#include <QObject>
#include <QPainterPath>
#include <QColor>
#include <QGraphicsObject>
#include <QWidget>

class DroppingBall : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
public:
    DroppingBall(const int size, const QColor& color, qreal stopPoint);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF geometry() const;
    void setGeometry(const QRectF& rect);

private:
    int size;
    QColor color;
    qreal stopPoint;
    QRectF rect;
};

#endif // DROPPINGBALL_H
