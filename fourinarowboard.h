#ifndef FOURINAROWBOARD_H
#define FOURINAROWBOARD_H

#include <QSize>
#include <player.h>
#include <QPair>
#include <QVector>

class FourInARowBoard : public QObject
{
    Q_OBJECT
public:
    enum { BoardWidth = 7, BoardHeight = 6};
    FourInARowBoard();
    QColor getNexttPalyerColor();
    //QSize sizeHint() const override;
    //QSize minimumSizeHint() const override;
    //void changeColorInPiece(int row, int column, QColor);

public slots:
    void continueSlot();
    void reset();
    void tryToDropTokenInFirstLine();
    void tryToDropTokenInSecondLine();
    void tryToDropTokenInThirdLine();
    void tryToDropTokenInFourthLine();
    void tryToDropTokenInFifthLine();
    void tryToDropTokenInSixthLine();
    void tryToDropTokenInSeventhLine();

signals:
    void changeColorInCell(int, int, QColor);
    void playerChanged(QColor);
    void updateScores(Player, Player);

protected:
    //void paintEvent(QPaintEvent* event) override;

private:
    void tryToDropTokenInLine(int column);
    void clearBoard();
    bool doesPlayerWin();
    bool checkHorizontal(int row, int column, QColor color);
    bool checkVertical(int row, int column, QColor color);
    bool checkNWDiagonal(int row, int column, QColor color);
    bool checkNEDiagonal(int row, int column, QColor color);
    bool isPossibleAnotherMove();
    QColor getCurrentPalyerColor();
    void playerWin();
    void noMoreMoves();

    int WIN_CELLS = 4;
    QColor backgroundColor = Qt::white;
    bool isStopped;
    QPair<Player, Player> players;
    int curPlayer;
    QVector<QVector<QColor>> board;

};

#endif // FOURINAROWBOARD_H
