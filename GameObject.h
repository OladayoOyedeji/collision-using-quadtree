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
        : radius_(10), dx(rand() % 5 + 1),
          dy(rand() % 5 + 1), x_(x), y_(y),
          r_(0), b_(200), g_(0),
          color(RED)
    {}
    void draw()
    {
        surface_->put_circle(x_, y_, radius_, color);
        //surface_->put_circle(x_, y_, radius_, color.r, g_, b_);
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
    //int vector_;
    Color color;
    static Surface * surface_;
};

inline
bool eq(const Color & c1, const Color c2)
{
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}

#endif
