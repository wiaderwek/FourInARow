#include "fourinarowwindow.h"

#include <QPainter>
#include <iostream>
#include <QFont>
#include <string>
#include <iostream>
#include <cstdlib>

FourInARowWindow::FourInARowWindow(QWidget *parent)
    : QMainWindow(parent)
{
    board = new FourInARowBoard();
    boardLayout = createBoard();
    boardLayout->setSpacing(0);
    QGridLayout* mainLayout = new QGridLayout();
    QFont buttonFont("Times", 16, QFont::Bold);
    QFont scoreFont("Times", 28, QFont::Bold);

    dropButton1 = new QPushButton(tr("&DROP"));
    dropButton1->setFont(buttonFont);
    dropButton2 = new QPushButton(tr("&DROP"));
    dropButton2->setFont(buttonFont);
    dropButton3 = new QPushButton(tr("&DROP"));
    dropButton3->setFont(buttonFont);
    dropButton4 = new QPushButton(tr("&DROP"));
    dropButton4->setFont(buttonFont);
    dropButton5 = new QPushButton(tr("&DROP"));
    dropButton5->setFont(buttonFont);
    dropButton6 = new QPushButton(tr("&DROP"));
    dropButton6->setFont(buttonFont);
    dropButton7 = new QPushButton(tr("&DROP"));
    dropButton7->setFont(buttonFont);

    QPushButton* resetButton = new QPushButton(tr("&RESET"));
    resetButton->setFont(buttonFont);
    QPushButton* continueButton = new QPushButton(tr("&CONTINUE"));
    continueButton->setFont(buttonFont);

    QLabel* scoreLabel = new QLabel(tr("SCORE"));
    scoreLabel->setFont(buttonFont);

    QLabel* colon = new QLabel(":");
    colon->setFont(scoreFont);

    redScore = new QLabel("0");
    redScore->setFont(scoreFont);
    redScore->setStyleSheet("color: red");

    yellowScore = new QLabel("0");
    yellowScore->setFont(scoreFont);
    yellowScore->setStyleSheet("color: yellow");

    changeDropButtonsColor(Qt::red);

    connect(dropButton1, &QPushButton::clicked, board, &FourInARowBoard::tryToDropTokenInFirstLine);
    connect(dropButton2, &QPushButton::clicked, board, &FourInARowBoard::tryToDropTokenInSecondLine);
    connect(dropButton3, &QPushButton::clicked, board, &FourInARowBoard::tryToDropTokenInThirdLine);
    connect(dropButton4, &QPushButton::clicked, board, &FourInARowBoard::tryToDropTokenInFourthLine);
    connect(dropButton5, &QPushButton::clicked, board, &FourInARowBoard::tryToDropTokenInFifthLine);
    connect(dropButton6, &QPushButton::clicked, board, &FourInARowBoard::tryToDropTokenInSixthLine);
    connect(dropButton7, &QPushButton::clicked, board, &FourInARowBoard::tryToDropTokenInSeventhLine);
    connect(board, &FourInARowBoard::changeColorInCell, this, &FourInARowWindow::changeColorInBoard);
    connect(resetButton, &QPushButton::clicked, this, &FourInARowWindow::resetWindow);
    connect(this, &FourInARowWindow::resetGame, board, &FourInARowBoard::reset);
    connect(continueButton, &QPushButton::clicked, this, &FourInARowWindow::resetBoard);
    connect(this, &FourInARowWindow::continueGame, board, &FourInARowBoard::continueSlot);
    connect(board, &FourInARowBoard::updateScores, this, &FourInARowWindow::updateScores);

    mainLayout->addWidget(dropButton1, 0, 0);
    mainLayout->addWidget(dropButton2, 0, 1);
    mainLayout->addWidget(dropButton3, 0, 2);
    mainLayout->addWidget(dropButton4, 0, 3);
    mainLayout->addWidget(dropButton5, 0, 4);
    mainLayout->addWidget(dropButton6, 0, 5);
    mainLayout->addWidget(dropButton7, 0, 6);
    mainLayout->addLayout(boardLayout, 1, 0, board->BoardHeight, board->BoardWidth);
    mainLayout->addWidget(resetButton, 3, 8, Qt::AlignCenter);
    mainLayout->addWidget(continueButton, 4, 8, Qt::AlignCenter);
    mainLayout->addWidget(scoreLabel, 0, 8, Qt::AlignCenter);
    mainLayout->addWidget(redScore, 1, 7, Qt::AlignCenter);
    mainLayout->addWidget(colon, 1, 8, Qt::AlignCenter);
    mainLayout->addWidget(yellowScore, 1, 9, Qt::AlignCenter);


    QWidget* centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);

    setWindowTitle(tr("Four In A Row"));
    resize(800, 600);
}

QGridLayout* FourInARowWindow::createBoard()
{
    QGridLayout *layout = new QGridLayout();
    for(int i = 0; i < board->BoardHeight; ++i)
    {
        QVector<FourInARowPiece*> row;
        for(int j = 0; j < board->BoardWidth; ++j)
        {
            FourInARowPiece* piece = new FourInARowPiece();
            row.append(piece);
            layout->addWidget(piece, i, j);
        }
        pieces.append(row);
    }

    return layout;
}

void FourInARowWindow::changeColorInBoard(int row, int column, QColor newColor)
{
    pieces[row][column]->setColor(newColor);
    changeDropButtonsColor(board->getNexttPalyerColor());
}

void FourInARowWindow::changeDropButtonsColor(QColor newColor)
{
    QString buttonStyleShit = QString("background-color: %1").arg(newColor.name());
    dropButton1->setStyleSheet(buttonStyleShit);
    dropButton2->setStyleSheet(buttonStyleShit);
    dropButton3->setStyleSheet(buttonStyleShit);
    dropButton4->setStyleSheet(buttonStyleShit);
    dropButton5->setStyleSheet(buttonStyleShit);
    dropButton6->setStyleSheet(buttonStyleShit);
    dropButton7->setStyleSheet(buttonStyleShit);
}

void FourInARowWindow::resetWindow()
{
    changeDropButtonsColor(Qt::red);
    clearBoard();
    redScore->setText("0");
    yellowScore->setText("0");
    emit resetGame();
}

void FourInARowWindow::resetBoard()
{
    changeDropButtonsColor(Qt::red);
    clearBoard();
    emit continueGame();
}

void FourInARowWindow::clearBoard()
{
    for(int i = 0; i < board->BoardHeight; ++i)
    {
        for(int j = 0; j < board->BoardWidth; ++j)
        {
            pieces[i][j]->resetColor();
        }
    }

}

void FourInARowWindow::updateScores(Player redPlayer, Player yellowPlayer)
{
    redScore->setText(std::to_string(redPlayer.getScore()).c_str());
    yellowScore->setText(std::to_string(yellowPlayer.getScore()).c_str());
}
