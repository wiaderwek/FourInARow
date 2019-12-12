#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QSignalMapper>
#include <boardcontroller.h>
#include <QColor>
#include <board.h>
#include <QApplication>
#include <QWidget>
#include <QObject>
#include <token.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent* event) override;
public slots:
    void resetGame();
    void dropToken(const int, const int);
    void changeColor(QColor);
    void lockDropButtons();
    void updateScores(Player, Player);

signals:
    void resetBoard();

private:
    void resetWindow();
    void changeDropButtonsColor();
    void setEnableDropButtons(bool enable);
    void resetScores();
    const int PIECE_SIZE = 100;
    const int FALLING_TIME = 100;

    Ui::MainWindow *ui;
    QColor* curColor;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QPropertyAnimation* animation;
    QSignalMapper* signalMapper;
    BoardController* boardController;
    Board* board;

};

#endif // MAINWINDOW_H
