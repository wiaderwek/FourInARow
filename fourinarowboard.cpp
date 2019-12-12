#include "fourinarowboard.h"
#include <QPainter>
#include <QGridLayout>
#include <fourinarowpiece.h>

FourInARowBoard::FourInARowBoard()
{
    players.first = Player(Qt::red);
    players.second = Player(Qt::yellow);
    isStopped = false;
    clearBoard();
}

void FourInARowBoard::continueSlot()
{
    if (isStopped)
    {
        isStopped = false;
        clearBoard();
        curPlayer = 0;
        emit updateScores(players.first, players.second);
    }
}

void FourInARowBoard::reset()
{
    clearBoard();
    curPlayer = 0;
    players.first.resetScore();
    players.second.resetScore();
    isStopped = false;
}

void FourInARowBoard::tryToDropTokenInFirstLine()
{
    tryToDropTokenInLine(0);
}

void FourInARowBoard::tryToDropTokenInSecondLine()
{
    tryToDropTokenInLine(1);
}

void FourInARowBoard::tryToDropTokenInThirdLine()
{
    tryToDropTokenInLine(2);
}

void FourInARowBoard::tryToDropTokenInFourthLine()
{
    tryToDropTokenInLine(3);
}

void FourInARowBoard::tryToDropTokenInFifthLine()
{
    tryToDropTokenInLine(4);
}

void FourInARowBoard::tryToDropTokenInSixthLine()
{
    tryToDropTokenInLine(5);
}

void FourInARowBoard::tryToDropTokenInSeventhLine()
{
    tryToDropTokenInLine(6);
}

void FourInARowBoard::tryToDropTokenInLine(int column)
{
    if(isStopped) return;

    for(int i = BoardHeight - 1; i >= 0; --i)
    {
        if(board[i][column] == backgroundColor)
        {
            board[i][column] = getCurrentPalyerColor();
            emit changeColorInCell(i, column, getCurrentPalyerColor());

            if(doesPlayerWin()) playerWin();
            else if(!isPossibleAnotherMove()) noMoreMoves();

            curPlayer = (curPlayer + 1) % 2;
            emit playerChanged(getCurrentPalyerColor());
            return;
        }
    }
}

void FourInARowBoard::clearBoard()
{
    board.clear();
    for(int i = 0; i < BoardHeight; ++i)
    {
        QVector<QColor> row;
        for (int j = 0; j < BoardWidth; ++j)
        {
            row.append(Qt::white);
        }
        board.append(row);
    }
}

QColor FourInARowBoard::getCurrentPalyerColor()
{
    if(curPlayer == 0) return players.first.getColor();
    else return players.second.getColor();
}

QColor FourInARowBoard::getNexttPalyerColor()
{
    if((curPlayer + 1) % 2 == 0) return players.first.getColor();
    else return players.second.getColor();
}

bool FourInARowBoard::doesPlayerWin()
{
    for (int i = 0; i < BoardHeight; ++i)
    {
        for (int j = 0; j < BoardWidth; j++)
        {
            if (board[i][j] == getCurrentPalyerColor())
            {
                if (checkHorizontal(i, j, board[i][j])) return true;
                else if (checkVertical(i, j, board[i][j])) return true;
                else if (checkNWDiagonal(i, j, board[i][j])) return true;
                else if (checkNEDiagonal(i, j, board[i][j])) return true;
                else return false;
            }
        }
    }
}

bool FourInARowBoard::checkHorizontal(int row, int column, QColor color)
{
    int j, count;

    j = column;
    for (count = 0; count < WIN_CELLS && j < BoardWidth && board[row][j] == color; j++)
        count++;

    if (count == WIN_CELLS) return true;
    else return false;
}

bool FourInARowBoard::checkVertical(int row, int column, QColor color)
{
    int i, count;

    i = row;
    for (count = 0; count < WIN_CELLS && i < BoardHeight && board[i][column] == color; ++i)
        count++;

    if (count == WIN_CELLS) return true;
    else return false;
}

bool FourInARowBoard::checkNWDiagonal(int row, int column, QColor color)
{
    int i, j, count;

    i = row; j = column;
    for (count = 0; count < WIN_CELLS && i < BoardHeight && j >= 0 && board[i][j] == color; i++, j--)
        count++;

    if (count == WIN_CELLS) return true;
    else return false;
}

bool FourInARowBoard::checkNEDiagonal(int row, int column, QColor color)
{
    int i, j, count;

    i = row; j = column;
    for (count = 0; count < WIN_CELLS && i < BoardHeight && j < BoardWidth && board[i][j] == color; i++, j++);
        count++;

    if (count == WIN_CELLS) return true;
    else return false;
}

bool FourInARowBoard::isPossibleAnotherMove()
{
    for(int i = 0; i < BoardWidth; ++i)
    {
        if(board[0][i] == Qt::white) return true;
    }
    return false;
}

void FourInARowBoard::noMoreMoves()
{
    isStopped = true;
}

void FourInARowBoard::playerWin()
{
    if (curPlayer == 0) players.first.win();
    else players.second.win();

    noMoreMoves();
}
