#include "widget.h"

Widget::Widget() : snakeMove(2)
{
    srand(time(0));
    int size = 20;
    this->setFixedSize(size * 35, size * 30);

    mSnake.push_back(new Body(0, 0, size));
    mSnake.push_back(new Body(size, 0, size));
    mSnake.push_back(new Body(size * 2, 0, size));
    mSnake.push_back(new Body(size * 3, 0, size));
    mSnake.push_back(new Body(size * 4, 0, size));
    mSnake.push_back(new Body(size * 5, 0, size));

    mTimerSnakeMove = new QTimer(this);
    connect(mTimerSnakeMove, &QTimer::timeout, this, &Widget::onTimeOutSnakeMove);
    mTimerSnakeMove->start(80);

    mFood = new Body(size * 10, size * 17, size);
}

Widget::~Widget()
{
    delete mTimerSnakeMove;
    delete mFood;

    while (mSnake.size() > 0)
    {
        Body *b = mSnake.front();
        delete b;
        mSnake.pop_front();
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(mFood->x(), mFood->y(), mFood->size(), mFood->size());

    painter.setBrush(QBrush(Qt::green));
    for (int i = 0; i < mSnake.size(); ++i)
    {
        painter.drawEllipse(mSnake.at(i)->x(), mSnake.at(i)->y(),
                            mSnake.at(i)->size(), mSnake.at(i)->size());
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        this->close();
    }
    else
    if (event->key() == Qt::Key_2)
    {
        if (snakeMove != 8)
            snakeMove = 2;
    }
    else
    if (event->key() == Qt::Key_8)
    {
        if (snakeMove != 2)
            snakeMove = 8;
    }
    else
    if (event->key() == Qt::Key_4)
    {
        if (snakeMove != 6)
            snakeMove = 4;
    }
    else
    if (event->key() == Qt::Key_6)
    {
        if (snakeMove != 4)
            snakeMove = 6;
    }
}

void Widget::setSnakeMove()
{
    if (snakeMove == 2)
        mSnake.front()->setY(mSnake.front()->y() + mSnake.front()->size());
    else
    if (snakeMove == 4)
        mSnake.front()->setX(mSnake.front()->x() - mSnake.front()->size());
    else
    if (snakeMove == 8)
        mSnake.front()->setY(mSnake.front()->y() - mSnake.front()->size());
    else
    if (snakeMove == 6)
        mSnake.front()->setX(mSnake.front()->x() + mSnake.front()->size());
}

void Widget::changeSnakeBody()
{
    //create copy of snake's coordinates
    for (int i = 0; i < mSnake.size(); ++i)
        mSnakeCopy.push_back(new Body(0, 0, 0));
    for (int i = 0; i < mSnake.size(); ++i)
    {
        mSnakeCopy.at(i)->setX(mSnake.at(i)->x());
        mSnakeCopy.at(i)->setY(mSnake.at(i)->y());
    }

    xLastBody = mSnakeCopy.back()->x();
    yLastBody = mSnakeCopy.back()->y();

    //set coordinates for all bodies
    for (int i = 1; i < mSnake.size(); ++i)
    {
        mSnake.at(i)->setX(mSnakeCopy.at(i - 1)->x());
        mSnake.at(i)->setY(mSnakeCopy.at(i - 1)->y());
    }

    //delete snake's copy
    while (mSnakeCopy.size() > 0)
    {
        Body *b = mSnakeCopy.front();
        delete b;
        mSnakeCopy.pop_front();
    }
}

void Widget::ifSnakeOnBorder()
{
    if (mSnake.front()->x() < 0)
        mSnake.front()->setX(this->width() - mSnake.front()->size());
    else
    if (mSnake.front()->x() >= this->width())
        mSnake.front()->setX(0);
    else
    if (mSnake.front()->y() < 0)
        mSnake.front()->setY(this->height() - mSnake.front()->size());
    else
    if (mSnake.front()->y() >= this->height())
        mSnake.front()->setY(0);
}

void Widget::ifSnakeEatItself()
{
    for (int i = 1; i < mSnake.size(); ++i)
    {
        if (mSnake.front()->x() == mSnake.at(i)->x() && mSnake.front()->y() == mSnake.at(i)->y())
        {
            this->close();
        }
    }

    if (mSnake.front()->x() == xLastBody && mSnake.front()->y() == yLastBody)
        this->close();
}

void Widget::ifSnakeEatFood()
{
    if (mSnake.front()->x() == mFood->x() && mSnake.front()->y() == mFood->y())
    {
        mSnake.push_back(new Body(mSnake.back()->x(), mSnake.back()->y(), mSnake.back()->size()));
        int x = rand() % this->width();
        int y = rand() % this->height();
        int size = mFood->size();

        x = (x / mFood->size()) * mFood->size();
        y = (y / mFood->size()) * mFood->size();

        while (true)
        {
            bool isBody = false;
            for (int i = 0; i < mSnake.size(); ++i)
            {
                if (x == mSnake.at(i)->x() && y == mSnake.at(i)->y())
                {
                    isBody = true;
                    break;
                }
            }

            if (!isBody)
            {
                delete mFood;
                mFood = new Body(x, y, size);
                break;
            }
            else
            {
                x = rand() % this->width();
                y = rand() % this->height();
                x = (x / mFood->size()) * mFood->size();
                y = (y / mFood->size()) * mFood->size();
            }
        }
    }
}

void Widget::onTimeOutSnakeMove()
{
    changeSnakeBody();
    setSnakeMove();
    ifSnakeOnBorder();
    ifSnakeEatItself();
    ifSnakeEatFood();


    this->update();
}
