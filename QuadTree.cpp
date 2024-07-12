#include "QuadTree.h"

Surface * QuadTree::surface_ = NULL;

void QuadTree::set_surface(Surface * surface)
{
    surface_ = surface;
}


void QuadTree::run()
{
   
    // check collision

    
    //
    bool delete_prev = false;
    std::list< Node * >::iterator p1;
    for (std::list< Node * >::iterator p = leafs_.begin();
         p != leafs_.end(); ++p)
    {
        if (delete_prev)
        {
            leafs_.erase(p1);
        }
        if ((*p)->obj_size() > t_)
        {
            (*p)->split(t_, max_depth_, leafs_, p);
           }
        if ((*p)->child())
        {
            p1 = p;
            delete_prev = true;
        }
        else
        {
            delete_prev = false;
        }
    }
    //draw();

     Node * q = NULL;
    for (int i = 0; i < objects_.size(); ++i)
    { 
        q = root_->child_placement(objects_[i]);
        if (q != NULL)
        {
            q->insert(objects_[i]);
        }
    }
    
    for (std::list< Node * >::iterator p = leafs_.begin();
         p != leafs_.end(); ++p)
    {
        (*p)->delete_objects();
    }
    //std::cout << leafs_.size() << std::endl;;

    for (std::list< Node * >::iterator p = leafs_.begin();
         p != leafs_.end(); ++p)
    {
        Node * parent = (*p)->parent();
        // if (parent != NULL)
        // std::cout << parent->size() << std::endl;
        if (parent != NULL && parent->size() == 0)
        {
            std::list< Node * >::iterator q = p;
            ++q;
            std::list< Node * >::iterator r = q;
            ++r;
            std::list< Node * >::iterator s = r;
            ++s;
            leafs_.erase(q);
            leafs_.erase(r);
            leafs_.erase(s);
            leafs_.insert(p, parent);
            q = p;
            ++q;
            parent->delete_children();
            parent->remove();
            leafs_.erase(p);
            p = q;
        }
        else
        {
            (*p)->collide();
        }
    }

    //for (int i = 0; i < leafs_.size)
    for (int i = 0; i < objects_.size(); ++i)
    {
        objects_[i]->run();
    } 
}

void QuadTree::insert_object(Ball * ball)
{
    objects_.push_back(ball);
    Node * node = root_->child_placement(ball);
    if (node != NULL)
        node->insert(ball);
    
}

void QuadTree::draw()
{
    root_->draw(*surface_);
    
}
