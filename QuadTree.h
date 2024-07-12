#ifndef QUADTREE_H
#define QUADTREE_H

#include "TreeNode.h"
#include "Constants.h"

class QuadTree
{
public:
    QuadTree(int t, int depth)
        : t_(t), max_depth_(depth), root_(new Node(0, W - 1, 0, H - 1))
    {
        
        leafs_.push_front(root_);
    }
    void run();
    void insert_object(Ball *);
    void draw();
    // void remove(Ball *);
    static void set_surface(Surface *);
    Node * root_;
    int t_;
    int max_depth_;
    std::vector< Ball * > objects_;
    std::list< Node * > leafs_;
    static Surface * surface_;
};

#endif
