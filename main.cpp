#include "include.h"

int main(int argc, char * argv[])
{
    Surface surface(W, H);
    Event event;

    QuadTree q(4, 100);
    Ball * ball;
    ball->set_surface(&surface);
    q.set_surface(&surface);
    std::list< Ball * > balls(0);
    bool s_pressed = false;
    // rand() % 4
    bool r_pressed = false;

    int RATE = 1000 / 60;
    
    while(1)
    {
        if (event.poll() && event.type() == QUIT) break;
        KeyPressed keypressed = get_keypressed();
        int START = getTicks();
        if (!s_pressed && keypressed[SPACE])
        {
            ball = new Ball(rand() % W, rand() % H);
            balls.push_back(ball);
            q.objects_.push_back(ball);
            s_pressed = true;
        }
        if (!keypressed[SPACE])
        {
            s_pressed = false;
        }
        // if (!r_pressed && keypressed[SDLK_r])
        // {
        //     q.objects_.push_back(new Ball(rand() % W, rand() % H));
        //     s_pressed = true;
        // }
        // if (!keypressed[SPACE])
        // {
        //     s_pressed = false;
        // }
        q.run();
        surface.lock();
        surface.fill(BLACK);
        q.draw();
        for (std::list<Ball *>::iterator p = balls.begin();
             p != balls.end(); ++p)
        {
            (*p)->draw();
        } 
        surface.unlock();
        surface.flip();

        int END = getTicks();
        int dt = RATE - END + START;
        if (dt > 0) delay(dt);
        //delay(10);
    }
    
    return 0;
}
