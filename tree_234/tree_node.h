// *************************************************************************
// FILE NAME: tree_node.h                                                  *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 03/14/2002                                                   *
// UPDATED  : 04/08/2002                                                   *
// *************************************************************************

#ifndef TREE_NODE_H
#define TREE_NODE_H

template <class Item>
class Node
{
    public:
        Node (void);

        Item GetItem (int) const;
        Node *GetChild (int) const;
        Node *GetParent (void) const;
        int  GetNumItem (void) const;

        bool IsLeaf (void) const;
        bool IsFull (void) const;

        int  Find (const Item&) const;
        int  Insert (Item&);
        void Change (const Item&, int);
        Item *Delete (int);

        void Attach (int, Node *);
        Node *Detach (int);

        void Print (int, int, int) const;
        void Erasing (void) const;
        void Saving (int, fstream&) const;

    private:
        Node *_parent;
        Item *_item  [3];
        Node *_child [4];
};

#include "tree_node.cpp"

#endif
