#ifndef TREENODE_H
#define TREENODE_H

#include "GameObject.h"
#include <list>
#include <vector>
#include <list>

class Node
{
public:
    Node(const std::vector< Ball * > & objects, Node * parent = NULL)
        : objects_(objects), parent_(parent), has_children(false)
    {
        if (parent != NULL)
        {
            depth_ = parent_->depth_ + 1;
        }
        else
        {
            depth_ = 0;
        }
    }
    Node(int minx_, int maxx_,
         int miny_, int maxy_,
         Node * parent = NULL)
        : parent_(parent),
          has_children(false),
          minx(minx_), maxx(maxx_),
          miny(miny_), maxy(maxy_),
          depth_(0), children_(0),
          objects_(0)
    {
        if (parent != NULL)
        {
            depth_ = parent_->depth_ + 1;
        }
    }
    Node * parent()
    {
        return parent_;
    }
    // Node * parent() const
    // {
    //     return parent_;
    // }
    Node * child_placement(Ball * x);
    void insert();
    void check_colision();
    void split(int, int,
               std::list< Node * > &,
               std::list< Node * >::iterator &);
    void draw(Surface &);
    void insert(Ball *);
    void erase_child();
    void delete_children();
    void delete_objects();
    bool child()
    {
        return has_children;
    }
    int obj_size()
    {
        return objects_.size();
    }
    int size()
    {
        int size_ = 0;
        for (int i = 0; i < children_.size(); ++i)
        {
            size_ += children_[i]->objects_.size();
        }
        return size_;
    }
    void remove()
    {
        objects_.resize(0);
    }
    void collide();
    
private:
    int minx, maxx, miny, maxy;
    std::vector< Ball * > objects_;
    bool has_children;
    std::vector< Node * > children_;
    Node * parent_;
    int depth_;
};

#endif
