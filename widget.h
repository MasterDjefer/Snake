#ifndef WIDGET_H
#define WIDGET_H
#include "body.h"
#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <ctime>
#include <cstdlib>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget();
    ~Widget();

private:
    QVector<Body*> mSnake;
    QVector<Body*> mSnakeCopy;
    QTimer *mTimerSnakeMove;
    Body *mFood;
    int snakeMove;
    int xLastBody;
    int yLastBody;

private:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void setSnakeMove();
    void changeSnakeBody();
    void ifSnakeOnBorder();
    void ifSnakeEatItself();
    void ifSnakeEatFood();

private slots:
    void onTimeOutSnakeMove();
};

#endif // WIDGET_H
