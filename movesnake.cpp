#include "movesnake.h"
#include "snakepart.h"
#include <QTimer>
#include <food.h>
#include <QDebug>
#include <QFont>
#include <define.h>
MoveSnake::MoveSnake(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    snakeHead = new SnakePart(this);
    snakeHead->setForward(NULL);
    snakeHead->setBackward(NULL);
    snakeHead->setPos(200,200);
    snakeHead->setDirection("RIGHT");
    snakeHead->part = "HEAD";
    snakeHead->setImage();
    snakeTail = snakeHead;
    timeSPEED=90;
    timeEatSPEED=3000;

    t = new QTimer();

    connect(t,SIGNAL(timeout()),this,SLOT(move()));

    foodTimer = new QTimer();
    connect(foodTimer,SIGNAL(timeout()),this,SLOT(makeFood()));



    direction = "RIGHT";


    text = new QGraphicsTextItem(this);
    text->setVisible(true);
    text->setPlainText("Press Space to continue");
    text->setPos(400,350);
    text->setFont(QFont("",14));


}

void MoveSnake::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Down && snakeHead->getDirection() != "UP")
    {
        direction = "DOWN";
    }
    else if(event->key() == Qt::Key_Up && snakeHead->getDirection() != "DOWN")
    {
        direction = "UP";
    }
    else if(event->key() == Qt::Key_Right && snakeHead->getDirection() != "LEFT")
    {
        direction = "RIGHT";
    }
    else if(event->key() == Qt::Key_Left && snakeHead->getDirection() != "RIGHT")
    {
        direction = "LEFT";
    }
    else if(event->key() == Qt::Key_Space)
    {
        if(t->isActive())
        {
        foodTimer->stop();

        t->stop();
        text->setVisible(true);
        }
        else{

            foodTimer->start(timeEatSPEED);
            t->start(timeSPEED);
            text->setVisible(false);
        }

    }
}

void MoveSnake::makeBoard()
{
    for(int i = 0 ;i <9*5;i++){
        for(int j = 0; j < 14*5; j++) {
            QGraphicsRectItem *rect= new QGraphicsRectItem(this);
            rect->setRect(j*40,i*40,40,40);
        }
    }



}

void MoveSnake::move() {
    snakeHead->setDirection(direction);
    moveSnake();

}

void MoveSnake::makeFood()
{
    food * f1 = new food(this,"APPLE");
    f1->setX(qrand() % (SIZE_X/40)* 40);
    f1->setY(qrand() % (SIZE_Y/40) * 40) ;

}

void MoveSnake::addPart(){
    SnakePart *part = new SnakePart(this);
    SnakePart *temp = snakeHead;
    while(temp->getBackward() != NULL) {
        temp = temp->getBackward();
    }
    temp->setBackward( part);
    part->setForward( temp);
    part->setBackward(NULL);
    part->addBehind();
    part->setDirection(temp->getDirection());
    snakeTail = part;
    part->part = "TAIL";
    if(temp != snakeHead)
    temp->part = "PART";
    part->setImage();
    temp->setImage();
}

void MoveSnake::moveSnake()
{
   SnakePart *temp = snakeTail;

   while(temp!=NULL) {
       temp->move();
       temp = temp->getForward();
   }
}

