#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "GameObject.h"
#include "QuadTree.h"
#include "TreeNode.h"

void slow_method(std::list<Ball * > & balls)
{
    for (std::list< Ball * >::iterator q = balls.begin();
         q != balls.end(); ++q)
    {
        for (std::list< Ball * >::iterator p = balls.begin();
             p != balls.end(); ++p)
        {
            if(q != p && !((*q)->check_()) && !((*p)->check_()) && (*q)->collide((*p)))
            {
                (*p)->check();
                (*q)->check();
                
                int t_x = (*p)->dx;
                int t_y = (*p)->dy;
                (*p)->dx = (*q)->dx;

                (*p)->dy = (*q)->dy;
                
                (*q)->dx = t_x;
                (*q)->dy = t_y;
                
                int count = 0;
                while((*q)->collide((*p)))
                {
                    (*q)->move();
                    (*p)->move();
                    if (count > 2)
                    {
                        (*p)->dx = rand() % 10 - 5;
                        (*p)->dy = rand() % 10 - 5;
                        if ((*p)->dx == 0 && (*p)->dx == 0)
                        {
                            (*p)->dx = rand() % 5 - 5;
                            (*p)->dy = rand() % 5 - 5;
                        }
                        (*q)->dx = rand() % 10 - 5;
                        (*q)->dy = rand() % 10 - 5;
                        if ((*q)->dx == 0 && (*q)->dx == 0)
                        {
                            (*q)->dx = rand() % 5 - 5;
                            (*q)->dy = rand() % 5 - 5;
                        }
                        break;
                    }
                    // std::cout << 'i' << std::endl;
                    count++;
                }
                if (eq((*q)->color, RED) && eq((*p)->color, BLUE))
                {
                    (*q)->color = BLUE;
                }
                else if (eq((*q)->color, BLUE) && eq((*p)->color, RED))
                {
                    (*q)->color = RED;
                }
            }
        }
        
    }
}
