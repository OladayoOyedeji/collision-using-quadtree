#include "TreeNode.h"

Node * Node::child_placement(Ball * ball)
{
    // if the ball is between maxx-minx
    // and between maxy-miny then if the
    // node has a children look for the
    // child placement in the children
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
    if (objects_.size() <= t)
    {
        if (*p != this)
        {
            leafs.insert(p, this);
            //leafs.erase(p);
        }
        return;
    }
    if (depth_ < depth && !has_children)
    {
        has_children = true;
        int distance_x = (maxx - minx) / 2;
        int distance_y = (maxy - miny) / 2;
        int x0 = minx;
        int x1;
        int y0 = miny;
        int y1;
        std::list< Node * >::iterator q = p;
        children_.resize(4);
        children_[0] = new Node(x0, x0 + distance_x, y0, y0 + distance_y, this);
        children_[0]->split(t, depth, leafs, q);
        children_[1] = new Node(x0 + distance_x, x0 + 2 * distance_x, y0, y0 + distance_y, this);
        children_[1]->split(t, depth, leafs, q);
        children_[2] = new Node(x0, x0 + distance_x, y0 + distance_y, y0 + 2 * distance_y, this);
        children_[2]->split(t, depth, leafs, q);
        children_[3] = new Node(x0 + distance_x, x0 + 2 * distance_x, y0 + distance_y, y0 + 2 * distance_y, this);
        children_[3]->split(t, depth, leafs, q);
        // for (int i = 0; i < 2; ++i)
        // {
        //     x1 = x0 + distance_x;
        //     y1 = y0 + distance_y;
        //     children_.push_back(new Node(x0, x1, y0, y1, this));
        //     children_[children_.size() - 1]->split(t, depth, leafs, ++q);
        //     x0 = x1;
        //     y0 = y1;
        // }
        // for (int i = 0; i < children_.size(); ++i)
        // {
            
        // }
    }
}

void Node::draw(Surface & surface)
{
    surface.put_line(minx, miny, maxx, miny, 255, 215, 0);
    surface.put_line(minx, miny, minx, maxy, 255, 215, 0);
    surface.put_line(minx, maxy, maxx, maxy, 255, 215, 0);
    surface.put_line(maxx, miny, maxx, maxy, 255, 215, 0);
    // if (!has_children)
    // {
    //     for (int i = 0; i < objects_.size(); ++i)
    //     {
    //         objects_[i]->draw();
    //     }
    // }
    // else
    // {
    for(int i = 0; i < children_.size(); ++i)
    {
        children_[i]->draw(surface);
    }
    // }
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
            children_[i]->has_children = false;
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
        // ball->x() > minx && ball->x() < maxx
        // && ball->y() > miny && ball->y() < maxy
        if ((*p)->x() <= minx || (*p)->x() >= maxx
            || (*p)->y() <= miny || (*p)->y() >= maxy)
            objects_.erase(p);
        
    }
}

void Node::collide()
{
    for (int i = 0; i < objects_.size(); ++i)
    {
        for (int j = 0; j < objects_.size(); ++j)
        {
            if(i != j && objects_[i]->collide(objects_[j]))
            {
                objects_[j]->dx = rand() % 10 - 5;
                objects_[j]->dy = rand() % 10 - 5;
                //if (objects_[i]->r_ == )
            }
        }
    }
}
