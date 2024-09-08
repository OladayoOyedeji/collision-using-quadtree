#include "TreeNode.h"

Node * Node::child_placement(Ball * ball)
{
    Node * placement = NULL;
    if (!has_children)
    {
        for (int i = 0; i < objects_.size(); ++i)
        {
            if (ball == objects_[i])
            {
                return NULL;
            }
        }
    }
    if (ball->x() >= minx && ball->x() <= maxx
        && ball->y() >= miny && ball->y() <= maxy)
    {
        if (has_children)
        {
            for (int i = 0; i < children_.size(); ++i)
            {
                placement = children_[i]->child_placement(ball);
                if (placement != NULL)
                {
                    return placement;
                }
            }
        }
        else return this;
        
    }
    return placement;
}

void Node::insert()
{
    
}

void Node::check_colision()
{
    for (int i = 0; i < objects_.size(); ++i)
    {
        // if one collides with another
        // i am thinking of a more linear
        // movement rather than random
        // so there are things that happen tho
    }
}

void Node::split(int t, int depth,
                 std::list< Node * > & leafs,
                 std::list< Node * >::iterator & p)
{
    // if (objects_.size() <= t)
    // {
    //     if (*p != this)
    //     {
    //         leafs.insert(p, this);
    //         //leafs.erase(p);
    //     }
    //     return;
    // }
    if (depth_ < depth && !has_children)
    {
        has_children = true;
        int x0 = minx;
        int x1 = maxx;
        int xm = x0 + (x1 - x0) / 2;
        int y0 = miny;
        int y1 = maxy;
        int ym = y0 + (y1 - y0) / 2;
        
        std::list< Node * >::iterator q = p;
        if (p != leafs.end())
        q++;
        children_.resize(4);

        children_[0] = new Node(x0, xm, y0, ym, this);
        //children_[0]->split(t, depth, leafs, q);
        leafs.insert(q, children_[0]);
        //++q;
        
        children_[1] = new Node(xm, x1, y0, ym, this);
        //children_[1]->split(t, depth, leafs, q);
        leafs.insert(q, children_[1]);
        //++q;
        
        children_[2] = new Node(x0, xm, ym, y1, this);
        //children_[2]->split(t, depth, leafs, q);
        leafs.insert(q, children_[2]);
        //++q;
        
        children_[3] = new Node(xm, x1, ym, y1, this);
        //children_[3]->split(t, depth, leafs, q);
        leafs.insert(q, children_[3]);
        //++q;
    }
}

void Node::draw(Surface & surface)
{
    surface.put_line(minx, miny, maxx, miny, 255, 215, 0);
    surface.put_line(minx, miny, minx, maxy, 255, 215, 0);
    surface.put_line(minx, maxy, maxx, maxy, 255, 215, 0);
    surface.put_line(maxx, miny, maxx, maxy, 255, 215, 0);
    for(int i = 0; i < children_.size(); ++i)
    {
        children_[i]->draw(surface);
    }
}

void Node::insert(Ball * ball)
{
    objects_.push_back(ball);
    
}

void Node::erase_child()
{
    int size = 0;
    for (int i = 0; i < children_.size(); ++i)
    {
        size += children_[i]->objects_.size();
    }
    if (size == 0)
    {
        delete_children();
    }
}

void Node::delete_children()
{
    for (int i = children_.size() - 1; i >= 0; --i)
    {
        if (children_[i]->has_children)
        {
            children_[i]->delete_children();
            //children_[i]->has_children = false;
        }
        delete children_[i];
        children_[i] = NULL;
        children_.pop_back();
        
    }
    has_children = false;
}

void Node::delete_objects()
{
    for (std::vector< Ball * >::iterator p = objects_.begin();
         p < objects_.end(); ++p)
    {
        if ((*p)->x() <= minx || (*p)->x() >= maxx
            || (*p)->y() <= miny || (*p)->y() >= maxy)
            objects_.erase(p);
        
    }
}

void Node::collide()
{
    int col;
    for (int i = 0; i < objects_.size(); ++i)
    {
        for (int j = 0; j < objects_.size(); ++j)
        {
            if(i != j && !(objects_[i]->check_()) && !(objects_[j]->check_()) && objects_[i]->collide(objects_[j]))
            {
                objects_[j]->check();
                objects_[i]->check();
                //std::cout << i << "colide\n";
                // objects_[j]->dx = rand() % 10 - 5;
                // objects_[j]->dy = rand() % 10 - 5;
                int t_x = objects_[j]->dx;
                int t_y = objects_[j]->dy;
                objects_[j]->dx = objects_[i]->dx;
                objects_[j]->dy = objects_[i]->dy;

                objects_[i]->dx = t_x;
                objects_[i]->dy = t_y;
                int count = 0;
                while(objects_[i]->collide(objects_[j]))
                {
                    objects_[i]->move();
                    objects_[j]->move();
                    if (count > 2)
                    {
                        objects_[j]->dx = rand() % 10 - 5;
                        objects_[j]->dy = rand() % 10 - 5;
                        if (objects_[j]->dx == 0 && objects_[j]->dx == 0)
                        {
                            objects_[j]->dx = rand() % 5 - 5;
                            objects_[j]->dy = rand() % 5 - 5;
                        }
                        objects_[i]->dx = rand() % 10 - 5;
                        objects_[i]->dy = rand() % 10 - 5;
                        if (objects_[i]->dx == 0 && objects_[i]->dx == 0)
                        {
                            objects_[i]->dx = rand() % 5 - 5;
                            objects_[i]->dy = rand() % 5 - 5;
                        }
                        break;
                    }
                    // std::cout << 'i' << std::endl;
                    count++;
                }
                if (eq(objects_[i]->color, RED) && eq(objects_[j]->color, BLUE))
                {
                    objects_[i]->color = BLUE;
                }
                else if (eq(objects_[i]->color, BLUE) && eq(objects_[j]->color, RED))
                {
                    objects_[i]->color = RED;
                }
            }
        }
    }
}
