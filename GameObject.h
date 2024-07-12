#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <cmath>
#include "Surface.h"
#include "Constants.h"

class Ball
{
public:
    Ball()
    {}
    Ball(int x, int y)
        : radius_(2), dx(rand() % 4 - 1),
          dy(rand() % 4 + 1), x_(x), y_(y), r_(0), b_(200), g_(0)
    {}
    void draw()
    {
        surface_->put_rect(x_, y_, 3, 3, 200, 0, 0);
    }
    void move()
    {
        x_ += dx; y_ += dy;
    }
    int x() const
    {
        return x_;
    }
    int y() const
    {
        return y_;
    }
    int rad() const
    {
        return radius_;
    }

    bool collide(const Ball * ball) const;

    void run();
    static void set_surface(Surface *);
//private:
    int radius_, x_, y_, r_, b_, g_, dx, dy;
    static Surface * surface_;
};

#endif
