#ifndef GAME_H
#define GAME_H
#include <define.h>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "movesnake.h"
#include <QGraphicsRectItem>
//Text try********************************
#include <QInputDialog>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVector>
//*********************************************
#include "score.h"
#include "button.h"
class Game:public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    Score *score;
    QGraphicsScene *gameScene ;
    MoveSnake *snake;
    MoveSnake *snake2;
    void displayMainMenu(QString title, QString play);
    QGraphicsTextItem *titleText;
    Button *b;
    QString result;
    QListWidget *w;
public slots:
    void start();
    void scoreTab();
    void speed();
    void board();
    void gameOver();
};

#endif // GAME_H

