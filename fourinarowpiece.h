#ifndef FOURINAROWPIECE_H
#define FOURINAROWPIECE_H

#include <QColor>
#include <QFrame>
#include <QPaintEvent>


class FourInARowPiece: public QFrame
{
    Q_OBJECT

public:
    FourInARowPiece(QWidget* parent = nullptr);
    void setColor(QColor& newColor);
    void resetColor();
    void drawPiece();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void drawSquare(QPaintEvent* event, QPainter &painter);
    QColor color;
};

#endif // FOURINAROWPIECE_H
