#include "game.h"

Game::Game(QWidget *parent):QGraphicsView(parent)
{
    //making the view or window
    setFixedSize(SIZE_X,SIZE_Y);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //making the game scene
    gameScene = new QGraphicsScene(this);
    gameScene->setSceneRect(0,0,SIZE_X,SIZE_Y);
    QGraphicsPixmapItem *bg = new QGraphicsPixmapItem();
    bg->setPixmap(QPixmap(":/images/bg.jpg").scaled(SIZE_X,SIZE_Y));
    gameScene->addItem(bg);
    //adding the gameScene to the view
    setScene(gameScene);
    score = new Score();
    gameScene->addItem(score);
    snake2 = NULL;
    snake = NULL;

}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(snake)
    snake->keyPressEvent(event);
    else
        QGraphicsView::keyPressEvent(event);
}

void Game::displayMainMenu(QString title,QString play)
{
  //Create the title
    titleText = new QGraphicsTextItem(title);
    QFont titleFont("arial" , 50);
    titleText->setFont( titleFont);
    int xPos1 = width()/2 - titleText->boundingRect().width()/2;
    int yPos1 = 150;
    titleText->setPos(xPos1,yPos1);
    gameScene->addItem(titleText);

    //create Button
    Button * playButton = new Button(play,titleText);
    int xPos2 = 100 ;
    int yPos2 = 160;
    playButton->setPos(xPos2,yPos2);

    connect(playButton,SIGNAL(clicked()) , this , SLOT(start()));


    //Create Show Score Button
    Button * scoreButton = new Button("Show Score",titleText);
    int xPos3 = 100;
    int yPos3 = 230;
    scoreButton->setPos(xPos3,yPos3);
    connect(scoreButton, SIGNAL(clicked()),this,SLOT(scoreTab()));

    //Create Speed Button
    Button * speedButton = new Button(sSPEED,titleText);
    int xPos4 = 100;
    int yPos4 = 300;
    speedButton->setPos(xPos4,yPos4);
    connect(speedButton, SIGNAL(clicked()),this,SLOT(speed()));

    //Create Board Button
    Button * boardButton = new Button(sBOARD,titleText);
    int xPos5 = 100;
    int yPos5 = 370;
    boardButton->setPos(xPos5,yPos5);
    connect(boardButton, SIGNAL(clicked()),this,SLOT(board()));

    //Create Quit Button
    Button * quitButton = new Button("Quit",titleText);
    int qxPos = 100;
    int qyPos = 440;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));


}
void Game::start(){
    snake = new MoveSnake();
    snake->setFlag(QGraphicsItem::ItemIsFocusable);
    if(bBOARD)
    {
      snake->makeBoard();
    }
    snake->setFocus();
    score->setVisible(true);
    score->setScore(0);
    gameScene->addItem(snake);
    gameScene->removeItem(titleText);
    delete titleText;
    if (snake2)
    snake2->deleteLater();
    snake2 = snake;


}
void Game::addScore()
{
      gameScene->removeItem(snake);
    //Create the title
      titleText = new QGraphicsTextItem("Write your nick");
      QFont titleFont("arial" , 50);
      titleText->setFont( titleFont);
      int xPos1 = width()/2 - titleText->boundingRect().width()/2;
      int yPos1 = 150;
      titleText->setPos(xPos1,yPos1);
      gameScene->addItem(titleText);

      //create Button
      Button * playButton = new Button("Save",titleText);
      int xPos2 = 100 ;
      int yPos2 = 160;
      playButton->setPos(xPos2,yPos2);

      result = "Nick";
      result = QInputDialog::getText(0, "Nick", "Write your nick:");


      connect(playButton,SIGNAL(clicked()) , this , SLOT(gameOver()));
}
void Game::gameOver(){
    gameScene->removeItem(titleText);
    delete titleText;

    QString filename="Data.txt";
    QFile file( filename );
    if ( file.open(QIODevice::Append) )
    {
        QTextStream stream( &file );
        stream << result<<" "<< score->getScore() << endl;
    }

    displayMainMenu("Game Over!","Play");
    //gameScene->removeItem(snake);
}
void Game::scoreTab()
{
    addScore();

}
void Game::speed()
{
    if(sSPEED == "Speed Low")
    {
        sSPEED="Speed Medium";
        SPEED=70;
    }
    else if(sSPEED == "Speed Medium")
    {
        sSPEED="Speed Hight";
        SPEED=10;
    }
    else
    {
        sSPEED="Speed Low";
        SPEED=90;
    }
    gameScene->removeItem(titleText);
    delete titleText;
    displayMainMenu("Snake Game","Play");

}
void Game::board()
{
    if(bBOARD)
    {
        bBOARD=false;
        sBOARD = "With no Board";
    }
    else
    {
        bBOARD=true;
        sBOARD = "With Board";
    }
    gameScene->removeItem(titleText);
    delete titleText;
    displayMainMenu("Snake Game","Play");
}
