#ifndef FOURINAROWWINDOW_H
#define FOURINAROWWINDOW_H

#include <QFrame>
#include <fourinarowboard.h>
#include <fourinarowpiece.h>
#include <QGridLayout>
#include <QVector>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <player.h>

class FourInARowWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void changeColorInBoard(int row, int column, QColor newColor);
    void resetWindow();
    void resetBoard();
    void updateScores(Player, Player);

signals:
    void resetGame();
    void continueGame();

public:
    explicit FourInARowWindow(QWidget *parent = nullptr);

private:
    QGridLayout* createBoard();
    void changeDropButtonsColor(QColor newColor);
    void clearBoard();

    FourInARowBoard* board;
    QGridLayout* boardLayout;
    QPushButton* dropButton1;
    QPushButton* dropButton2;
    QPushButton* dropButton3;
    QPushButton* dropButton4;
    QPushButton* dropButton5;
    QPushButton* dropButton6;
    QPushButton* dropButton7;
    QLabel* redScore;
    QLabel* yellowScore;
    QVector<QVector<FourInARowPiece*>> pieces;
};

#endif // FOURINAROWWINDOW_H
