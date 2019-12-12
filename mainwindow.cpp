#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    boardController = new BoardController();
    view = ui->graphicsView;
    scene = new QGraphicsScene();
    curColor = new QColor(Qt::red);
    board = new Board(PIECE_SIZE);

    ui->continueButton->setEnabled(false);

    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->addItem(board);

    view->setScene(scene);

    //connect drop buttons
    signalMapper = new QSignalMapper(this);
    connect(ui->dropButton1, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->dropButton1, 0);
    connect(ui->dropButton2, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->dropButton2, 1);
    connect(ui->dropButton3, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->dropButton3, 2);
    connect(ui->dropButton4, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->dropButton4, 3);
    connect(ui->dropButton5, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->dropButton5, 4);
    connect(ui->dropButton6, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->dropButton6, 5);
    connect(ui->dropButton7, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->dropButton7, 6);
    connect(signalMapper, SIGNAL(mapped(int)), boardController, SLOT(tryToDropTokenInColumn(int)));

    //connect reset button
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetGame()));
    connect(this, SIGNAL(resetBoard()), boardController, SLOT(reset()));

    connect(ui->continueButton, SIGNAL(clicked()), boardController, SLOT(continueGame()));

    connect(boardController, SIGNAL(dropToken(int, int)), this, SLOT(dropToken(int, int)));

    connect(boardController, SIGNAL(playerChanged(QColor)), this, SLOT(changeColor(QColor)));

    connect(boardController, SIGNAL(gameStopped()), this, SLOT(lockDropButtons()));

    connect(boardController, SIGNAL(updateScores(Player, Player)), this, SLOT(updateScores(Player, Player)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete curColor;
    delete scene;
    delete view;
    delete animation;
    delete signalMapper;
    delete boardController;
    delete board;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    view->fitInView(scene->sceneRect());
}

void MainWindow::resetGame()
{
    resetWindow();
    resetScores();
    emit resetBoard();
}

void MainWindow::resetWindow()
{
    scene->clear();
    scene->addItem(new Board(PIECE_SIZE));
    changeColor(Qt::red);
    setEnableDropButtons(true);
    ui->continueButton->setEnabled(false);
}

void MainWindow::dropToken(const int row, const int column)
{
    QRect rect(column*PIECE_SIZE, 0, PIECE_SIZE, PIECE_SIZE);
    Token* token = new Token(rect, *curColor, row*PIECE_SIZE);
    token->setZValue(-1);
    scene->addItem(token);
    animation = new QPropertyAnimation(token, "geometry");
    animation->setDuration(FALLING_TIME * row);
    animation->setStartValue(rect);
    animation->setEndValue(QRect(column*PIECE_SIZE, row*PIECE_SIZE, PIECE_SIZE, PIECE_SIZE));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void MainWindow::changeColor(QColor newColor)
{
    curColor = new QColor(newColor);
    changeDropButtonsColor();
}

void MainWindow::changeDropButtonsColor()
{
    QString dropButtonStyleShit = QString("background-color: %1").arg(curColor->name());
    ui->dropButton1->setStyleSheet(dropButtonStyleShit);
    ui->dropButton2->setStyleSheet(dropButtonStyleShit);
    ui->dropButton3->setStyleSheet(dropButtonStyleShit);
    ui->dropButton4->setStyleSheet(dropButtonStyleShit);
    ui->dropButton5->setStyleSheet(dropButtonStyleShit);
    ui->dropButton6->setStyleSheet(dropButtonStyleShit);
    ui->dropButton7->setStyleSheet(dropButtonStyleShit);
}

void MainWindow::lockDropButtons()
{
    setEnableDropButtons(false);
    ui->continueButton->setEnabled(true);
}

void MainWindow::setEnableDropButtons(bool enable)
{
    ui->dropButton1->setEnabled(enable);
    ui->dropButton2->setEnabled(enable);
    ui->dropButton3->setEnabled(enable);
    ui->dropButton4->setEnabled(enable);
    ui->dropButton5->setEnabled(enable);
    ui->dropButton6->setEnabled(enable);
    ui->dropButton7->setEnabled(enable);
}

void MainWindow::updateScores(Player redPlayer, Player yellowPlayer)
{
    ui->redScore->setText(std::to_string(redPlayer.getScore()).c_str());
    ui->yellowScore->setText(std::to_string(yellowPlayer.getScore()).c_str());
    resetWindow();
}

void MainWindow::resetScores()
{
    ui->redScore->setText("0");
    ui->yellowScore->setText("0");
}
