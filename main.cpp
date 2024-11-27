#include "include.h"

int main(int argc, char * argv[])
{
    std::cout << "how many you want to spawn??";
    int size = 0;
    std::cin >> size;
    
    Surface surface(W, H);
    Event event;
    
    srand((unsigned int) time(NULL));
    QuadTree::set_surface(&surface);
    Ball::set_surface(&surface);
    QuadTree q(4, 100);
    
    std::list< Ball * > balls(0);
    for (int i = 0; i < size; ++i)
    {
        Ball * ball = new Ball(rand() % W, rand() % H);
        balls.push_back(ball);
        q.objects_.push_back(ball);
    }
    
    bool s_pressed = false;
    bool r_pressed = false;

    int RATE = 1000 / 60;
    bool quadtree = true;
    while(1)
    {
        
        if (event.poll() && event.type() == QUIT) break;
        //std::cout << "hey baby ";
        KeyPressed keypressed = get_keypressed();
        int START = getTicks();
        if (!s_pressed && keypressed[SPACE])
        {
            quadtree = !quadtree;
            s_pressed = true;
        }
        if (!keypressed[SPACE])
        {
            s_pressed = false;
        }
        if (quadtree)
            q.run();
        else
            slow_method(balls);

        for (std::list< Ball * >::iterator q = balls.begin();
             q != balls.end(); ++q)
        {
            (*q)->run();
        } 
        
        surface.lock();
        surface.fill(WHITE);
        if (quadtree)
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

    for (std::list<Ball *>::iterator p = balls.begin();
         p != balls.end(); ++p)
    {
        delete *p;
    } 
    
    return 0;
}
