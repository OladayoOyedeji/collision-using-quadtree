#include "GameObject.h"

Surface * Ball::surface_ = NULL;

bool Ball::collide(const Ball * ball) const
{
    int distx = abs(ball->x() - x_);
    int disty = abs(ball->y() - y_);
    int dist = sqrt(distx * distx + disty * disty);
    return dist <= ball->rad() + radius_;
}

void Ball::run()
{
    move();
    if (x_ < 0)
    {
        x_ = 0;
        dx *= -1;
    }
    if (x_ > W)
    {
        x_ = W;
        dx *= -1;
    }
    if (y_ < 0)
    {
        y_ = 0;
        dy *= -1;
    }
    if (y_ > H)
    {
        y_ = H;
        dy *= -1;
    }
}

void Ball::set_surface(Surface * surface)
{
    surface_ = surface;
}
