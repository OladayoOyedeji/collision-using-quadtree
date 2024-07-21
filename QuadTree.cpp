#include "QuadTree.h"

Surface * QuadTree::surface_ = NULL;

void QuadTree::set_surface(Surface * surface)
{
    surface_ = surface;
}


void QuadTree::run()
{
   
    // check collision

    
   
    bool delete_prev = false;
    std::list< Node * >::iterator p1;
    for (std::list< Node * >::iterator p = leafs_.begin();
         p != leafs_.end(); ++p)
    {
        //std::cout << "previous " << (p == p1) << std::endl;
        if (delete_prev)
        {
            leafs_.erase(p1);
        }
        //std::cout << (*p == NULL) << std::endl;
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
    if (delete_prev)
        leafs_.erase(p1);
    // for (std::list< Node * >::iterator p = leafs_.begin();
    //      p != leafs_.end(); ++p)
    // {
    //     std::cout << (*p)->depth() << ' ' << (*p)->child() << '\n';
    // }
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
            
        Node * parent = (*p)->parent_;
            
        // if (parent != NULL)
        // std::cout << parent->size() << std::endl;
        if (parent != NULL && parent->size() == 0)
        {
            std::list< Node * >::iterator q = p;
            leafs_.insert(p, parent);
            --q;
            bool delete_ = false;
            
            //for (std::list< Node * >::iterator r = v.begin(); )
            int i = 0;
            p = leafs_.begin();
            std::list< Node * >::iterator r;
            while (i < 4 && p != leafs_.end())
            {
                if ((*p)->parent() == parent)
                {
                    r = p;
                    p++;
                    leafs_.erase(r);
                    i++;
                }
                else
                {
                    p++;
                }
            }
            parent->delete_children();
            parent->remove();
            p = q;
        }
        else
        {
            
            (*p)->collide();
        }
    }
    //std::cout << leafs_.size() << std::endl;

    //for (int i = 0; i < leafs_.size)
    for (int i = 0; i < objects_.size(); ++i)
    {
        objects_[i]->run();
    } 
    //std::cout << "no baby\n"; oj dk j   jbdkj jkd  dxj dbi gj lfkn e nou og ojdn jd ogjb dj ogu b 
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
