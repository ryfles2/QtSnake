#include "snakepart.h"
#include <QBrush>
#include <QDebug>
#include "game.h"
#include "food.h"
#include <typeinfo>
extern Game *game;
SnakePart::SnakePart(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setZValue(1);

}

SnakePart *SnakePart::getForward()
{
    return forward;
}

void SnakePart::setForward(SnakePart *value)
{
    forward = value;
}

SnakePart *SnakePart::getBackward()
{
    return backward;
}

void SnakePart::setBackward(SnakePart *value)
{
    backward = value;
}

QString SnakePart::getDirection()
{
    return direction;
}

void SnakePart::setDirection( QString value)
{
    direction = value;
}


void SnakePart::move() {
    static int first;

    if (direction == "DOWN")
        this->setY(this->y()+40);
    else if(direction == "UP")
        this->setY(this->y()-40);
    else if(direction == "LEFT")
        this->setX(this->x()-40);
    else if(direction == "RIGHT")
        this->setX(this->x()+40);
    if(this->getForward()!= NULL)
        direction = this->getForward()->direction;
    if(first){
    if(this->y() >= SIZE_Y ){
        this->setY(0);
    }
    else if(this->y()<0){
        this->setY(SIZE_Y);
    }
    else if(this->x() < 0){
        this->setX(SIZE_X);
    }
    else if(this->x() >= SIZE_X){
        this->setX(0);
    }

    }
    first++;
    if(part == "HEAD")
        checkCollidingObjects();
    setImage();

}

void SnakePart::addBehind() {
    int x;
    int y;
    if(this->getForward()->getDirection() == "UP"){
        x = this->getForward()->x();
        y = this->getForward()->y() + 40;
    }
    else if(this->getForward()->getDirection() == "DOWN"){
        x = this->getForward()->x();
        y = this->getForward()->y() - 40;
    }
    else if(this->getForward()->getDirection() == "RIGHT"){
        y = this->getForward()->y();
        x = this->getForward()->x() - 40;
    }
    else if(this->getForward()->getDirection() == "LEFT"){
        y = this->getForward()->y();
        x = this->getForward()->x() + 40;
    }
    setPos(x,y);


}

void SnakePart::setImage() {
    if(part == "HEAD"){

        if(direction == "UP"){
          setPixmap(QPixmap(":/images/headup.png").scaled(40,40));
        }else if(direction == "DOWN"){
           setPixmap(QPixmap(":/images/headDown.png").scaled(40,40));
        }else if(direction == "LEFT"){
            setPixmap(QPixmap(":/images/headLeft.png").scaled(40,40));
        }else if(direction == "RIGHT"){
            setPixmap(QPixmap(":/images/head.png").scaled(40,40,Qt::KeepAspectRatio));
        }
        setZValue(2);

    }
    else {
        setPixmap(QPixmap(":/images/tail.png").scaled(40,40));
    }

}

void SnakePart::checkCollidingObjects() {
    QList <QGraphicsItem *> coll = this->collidingItems();

    for(int i = 0,n = coll.length(); i < n; i++) {
        food *f = dynamic_cast<food *>(coll[i]);
        if(f) {
            QPointF thisCenter(x()+10,y()+10);
            QPointF foodCenter(f->x()+10,f->y()+10);
            QLineF ln(thisCenter,foodCenter);
            if(ln.length() == 0){

           game->snake->addPart();
           game->gameScene->removeItem(f);
           game->score->setScore(game->score->getScore()+f->score);
           delete f;
            }
        }
        else if(coll[i]) {
            if(typeid(*coll[i])== typeid(SnakePart))
            game->addScore();
            //game->gameOver();
            return;

        }
    }
}
