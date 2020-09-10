#include "body.h"

Body::Body(int x, int y, int size) : mX(x), mY(y), mSize(size){}

int Body::x() const
{
    return mX;
}

int Body::y() const
{
    return mY;
}

int Body::size() const
{
    return mSize;
}

void Body::setX(int x)
{
    mX = x;
}

void Body::setY(int y)
{
    mY = y;
}
