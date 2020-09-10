#ifndef BODY_H
#define BODY_H

class Body
{
private:
    int mX;
    int mY;
    const int mSize;

public:
    Body(int x, int y, int size);
    int x() const;
    int y() const;
    int size() const;
    void setX(int x);
    void setY(int y);

};

#endif // BODY_H
