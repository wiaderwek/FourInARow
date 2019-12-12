#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <QObject>
#include <QColor>
#include <player.h>
#include <QVector>

class BoardController : public QObject
{
        Q_OBJECT
public:
    BoardController();

public slots:
    void continueGame();
    void reset();
    void tryToDropTokenInColumn(const int column);

signals:
    void playerChanged(QColor);
    void updateScores(Player, Player);
    void gameStopped();
    void dropToken(const int, const int);

private:
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

    enum { BoardWidth = 7, BoardHeight = 6};
    const int WIN_CELLS = 4;
    const QColor BACKGROND_COLOR = Qt::white;
    bool isStopped;
    QPair<Player, Player> players;
    int curPlayer;
    QVector<QVector<QColor>> board;
};

#endif // BOARDCONTROLLER_H
