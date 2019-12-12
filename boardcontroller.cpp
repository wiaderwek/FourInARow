#include "boardcontroller.h"

BoardController::BoardController()
{
    players.first = Player(Qt::red);
    players.second = Player(Qt::yellow);
    isStopped = false;
    clearBoard();
}

void BoardController::clearBoard()
{
    board.clear();
    for(int i = 0; i < BoardHeight; ++i)
    {
        QVector<QColor> row;
        for (int j = 0; j < BoardWidth; ++j)
        {
            row.append(BACKGROND_COLOR);
        }
        board.append(row);
    }
}

void BoardController::continueGame()
{
    isStopped = false;
    clearBoard();
    curPlayer = 0;
    emit updateScores(players.first, players.second);
}

void BoardController::reset()
{
    clearBoard();
    curPlayer = 0;
    players.first.resetScore();
    players.second.resetScore();
    isStopped = false;
}

void BoardController::tryToDropTokenInColumn(int column)
{
    if(isStopped) return;

    for(int i = BoardHeight - 1; i >= 0; --i)
    {
        if(board[i][column] == BACKGROND_COLOR)
        {
            board[i][column] = getCurrentPalyerColor();

            if(doesPlayerWin())
            {
                noMoreMoves();
                playerWin();

            }
            else if(!isPossibleAnotherMove())
            {
                noMoreMoves();
            }

            emit dropToken(i, column);
            curPlayer = (curPlayer + 1) % 2;
            emit playerChanged(getCurrentPalyerColor());
            return;
        }
    }
}

QColor BoardController::getCurrentPalyerColor()
{
    if(curPlayer == 0) return players.first.getColor();
    else return players.second.getColor();
}

bool BoardController::doesPlayerWin()
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
            }
        }
    }
    return false;
}

bool BoardController::checkHorizontal(int row, int column, QColor color)
{
    int j, count;

    j = column;
    for (count = 0; count < WIN_CELLS && j < BoardWidth && board[row][j] == color; ++j, count++);

    if (count == WIN_CELLS) return true;
    else return false;
}

bool BoardController::checkVertical(int row, int column, QColor color)
{
    int i, count;

    i = row;
    for (count = 0; count < WIN_CELLS && i < BoardHeight && board[i][column] == color; ++i)
        count++;

    if (count == WIN_CELLS) return true;
    else return false;
}

bool BoardController::checkNWDiagonal(int row, int column, QColor color)
{
    int i, j, count;

    i = row; j = column;
    for (count = 0; count < WIN_CELLS && i < BoardHeight && j >= 0 && board[i][j] == color; i++, j--)
        count++;

    if (count == WIN_CELLS) return true;
    else return false;
}

bool BoardController::checkNEDiagonal(int row, int column, QColor color)
{
    int i, j, count;

    i = row; j = column;
    for (count = 0; count < WIN_CELLS && i < BoardHeight && j < BoardWidth && board[i][j] == color; i++, j++)
        count++;

    if (count == WIN_CELLS) return true;
    else return false;
}

bool BoardController::isPossibleAnotherMove()
{
    for(int i = 0; i < BoardWidth; ++i)
    {
        if(board[0][i] == BACKGROND_COLOR) return true;
    }
    noMoreMoves();
    return false;
}

void BoardController::noMoreMoves()
{
    isStopped = true;
    emit gameStopped();
}

void BoardController::playerWin()
{
    if (curPlayer == 0) players.first.win();
    else players.second.win();
}
