// *************************************************************************
// FILE NAME: tree_234.h                                                   *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 03/14/2002                                                   *
// UPDATED  : 04/08/2002                                                   *
// *************************************************************************

#ifndef TREE_234_H
#define TREE_234_H

#include <queue>
#include "tree_node.h"

template <class Item>
class Tree_234
{
    public:
        Tree_234 (void);
        ~Tree_234 (void);

        bool Open (char *);
        bool Erase (void);

        bool Insert (const Item&);
        bool Delete (Item&);

        int  Find (const Item&);
        void Change (Item&, int);

        bool Print (void);
        bool Save (char *);

        bool Preorder (void);
        bool Inorder (void);
        bool Postorder (void);
        bool LevelByLevel (void);

        bool IsEmpty (void) const;
        Item GetItem (const Item&, int);

    protected:
        void _Preorder  (Node<Item> *, int);
        void _Inorder   (Node<Item> *, int);
        void _Postorder (Node<Item> *, int);

        void _Erase (Node<Item> *&, int);
        void _Save  (Node<Item> *, fstream&);

        void _Split (Node<Item> *);
        void _Fix (Node<Item> *);

        Node<Item> *_NextNode (Node<Item> *, const Item&);

    private:
        Node<Item> *_root;
};

#include "tree_234.cpp"

#endif
