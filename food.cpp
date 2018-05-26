#include "food.h"

#include <QBrush>


food::food(QGraphicsItem *parent,QString name):QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/food.png").scaled(40,40));
    score = 1;

}
