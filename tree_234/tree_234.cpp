// *************************************************************************
// FILE NAME: tree_234.cpp                                                 *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 03/14/2002                                                   *
// UPDATED  : 04/08/2002                                                   *
// *************************************************************************

template <class Item>
Tree_234<Item>::Tree_234 (void)
{
    _root = new Node<Item>;
}

template <class Item>
Tree_234<Item>::~Tree_234 (void)
{
    _Erase (_root, 0);
}

template <class Item>
bool Tree_234<Item>::Open (char *file)
{
    fstream ins (file, ios::in);

    if (ins.bad ())
        return false;

    Item item;

    while (ins >> item, ! ins.eof ())
        if (Insert (item))
            cout << "\033[1;35mInserting...\033[0m " << item << "\n";
        else
            cerr << "\033[1;31mInsert un-successfully!\033[0m " << "\033[1;31mDuplicate\033[0m " << item << "\n";

    ins.close ();

    return true;
}

template <class Item>
bool Tree_234<Item>::Erase (void)
{
    if (IsEmpty ())
        return false;

    _Erase (_root, 1);
    _root = new Node<Item>;

    return true;
}

template <class Item>
bool Tree_234<Item>::Insert (const Item& k)
{
    if (Find (k) != -1)
        return false;

    Node<Item> *curNode = _root;

    while (true)
        if (curNode->IsFull ())
        {
            _Split (curNode);

            curNode = curNode->GetParent ();
            curNode = _NextNode (curNode, k);
        }
        else if (curNode->IsLeaf ())
            break;
        else
            curNode = _NextNode (curNode, k);

    curNode->Insert (*(new Item (k)));

    return true;
}

template <class Item>
bool Tree_234<Item>::Delete (Item& k)
{
    int i;

    Node<Item> *curNode = _root;

    while (true)
    {
        i = curNode->Find (k);
        if (i != -1)
        {
            if (curNode->IsLeaf ())
                curNode->Delete (i);
            else
            {
                curNode->Change (curNode->GetChild (i + 1)->GetItem (0), i);
                curNode = curNode->GetChild (i + 1);
                curNode->Delete (0);
            }

            if (curNode->GetNumItem () == 0)
                _Fix (curNode);

            return true;
        }
        else if (curNode->IsLeaf ())
            return false;
        else
            curNode = _NextNode (curNode, k);
    }
}

template <class Item>
int Tree_234<Item>::Find (const Item& k)
{
    Node<Item> *curNode = _root;

    while (true)
        if (curNode->Find (k) != -1)
            return curNode->Find (k);
        else if (curNode->IsLeaf ())
            return -1;
        else
            curNode = _NextNode (curNode, k);
}

template <class Item>
void Tree_234<Item>::Change (Item& k, int i)
{
    Node<Item> *curNode = _root;

    while (true)
        if (curNode->Find (k) != -1)
            break;
        else
            curNode = _NextNode (curNode, k);

    curNode->Change (k, i);
}

template <class Item>
bool Tree_234<Item>::Print (void)
{
    return Preorder ();
}

template <class Item>
bool Tree_234<Item>::Save (char *file)
{
    fstream outs (file, ios::out);

    if (outs.bad ())
        return false;

    _Save (_root, outs);
    outs.close ();

    return true;
}

template <class Item>
bool Tree_234<Item>::Preorder (void)
{
    if (IsEmpty ())
        return false;

    _Preorder (_root, 0);

    return true;
}

template <class Item>
bool Tree_234<Item>::Inorder (void)
{
    if (IsEmpty ())
        return false;

    _Inorder (_root, 0);

    return true;
}

template <class Item>
bool Tree_234<Item>::Postorder (void)
{
    if (IsEmpty ())
        return false;

    _Postorder (_root, 0);

    return true;
}

template <class Item>
bool Tree_234<Item>::LevelByLevel (void)
{
    if (IsEmpty ())
        return false;

    queue<Node<Item> *> q;

    q.push (_root);

    while (! q.empty ())
    {
        Node<Item> *curNode = q.front ();
        q.pop ();

        curNode->Print (0, curNode->GetNumItem (), 0);

        if (curNode->GetChild (0))
            q.push (curNode->GetChild (0));

        if (curNode->GetChild (1))
            q.push (curNode->GetChild (1));

        if (curNode->GetChild (2))
            q.push (curNode->GetChild (2));

        if (curNode->GetChild (3))
            q.push (curNode->GetChild (3));
    }

    return true;
}

template <class Item>
bool Tree_234<Item>::IsEmpty (void) const
{
    return (! _root->GetNumItem ());
}

template <class Item>
Item Tree_234<Item>::GetItem (const Item& k, int i)
{
    Node<Item> *curNode = _root;

    while (true)
        if (curNode->Find (k) != -1)
            return curNode->GetItem (i);
        else
            curNode = _NextNode (curNode, k);
}

template <class Item>
void Tree_234<Item>::_Preorder (Node<Item> *curNode, int level)
{
    curNode->Print (0, curNode->GetNumItem (), level);

    for (int i = 0; i < curNode->GetNumItem () + 1; i++)
    {
        if (curNode->GetChild (i) == NULL)
            break;

        _Preorder (curNode->GetChild (i), level + 1);
    }
}

template <class Item>
void Tree_234<Item>::_Inorder (Node<Item> *curNode, int level)
{
    if (curNode)
    {
        _Inorder (curNode->GetChild (0), level + 1);
        if (curNode->GetNumItem () > 0)
            curNode->Print (0, 1, level);

        _Inorder (curNode->GetChild (1), level + 1);
        if (curNode->GetNumItem () > 1)
            curNode->Print (1, 2, level);

        _Inorder (curNode->GetChild (2), level + 1);
        if (curNode->GetNumItem () > 2)
            curNode->Print (2, 3, level);

        _Inorder (curNode->GetChild (3), level + 1);
    }
}

template <class Item>
void Tree_234<Item>::_Postorder (Node<Item> *curNode, int level)
{
    for (int i = 0; i < curNode->GetNumItem () + 1; i++)
    {
        if (curNode->GetChild (i) == NULL)
            break;

        _Postorder (curNode->GetChild (i), level + 1);
    }

    curNode->Print (0, curNode->GetNumItem (), level);
}

template <class Item>
void Tree_234<Item>::_Erase (Node<Item> *&curNode, int mode)
{
    for (int i = 0; i < curNode->GetNumItem () + 1; i++)
    {
        Node<Item> *nextNode = curNode->GetChild (i);

        if (nextNode == NULL)
            break;

        _Erase (nextNode, mode);
    }

    if (mode)
        curNode->Erasing ();

    delete curNode;
    curNode = NULL;
}

template <class Item>
void Tree_234<Item>::_Save (Node<Item> *curNode, fstream& outs)
{
    if (curNode)
    {
        _Save (curNode->GetChild (0), outs);
        if (curNode->GetNumItem () > 0)
            curNode->Saving (0, outs);

        _Save (curNode->GetChild (1), outs);
        if (curNode->GetNumItem () > 1)
            curNode->Saving (1, outs);

        _Save (curNode->GetChild (2), outs);
        if (curNode->GetNumItem () > 2)
            curNode->Saving (2, outs);

        _Save (curNode->GetChild (3), outs);
    }
}

template <class Item>
void Tree_234<Item>::_Split (Node<Item> *curNode)
{
    Item *lItem = curNode->Delete (2);
    Item *mItem = curNode->Delete (1);

    Node<Item> *rmChild = curNode->Detach (2);
    Node<Item> *rChild  = curNode->Detach (3);
    Node<Item> *newNode = new Node<Item>;
    Node<Item> *parent;

    if (curNode == _root)
    {
        _root = new Node<Item>;
        parent = _root;
        _root->Attach (0, curNode);
    }
    else
        parent = curNode->GetParent ();

    int index = parent->Insert (*mItem);

    for (int i = parent->GetNumItem () - 1; i > index; i--)
        parent->Attach (i + 1, parent->Detach (i));

    parent->Attach (index + 1, newNode);

    newNode->Insert (*lItem);
    newNode->Attach (0, rmChild);
    newNode->Attach (1, rChild);
}

template <class Item>
void Tree_234<Item>::_Fix (Node<Item> *curNode)
{
    if (curNode != _root)
    {
        // To be continue.
    }
}

template <class Item>
Node<Item> *Tree_234<Item>::_NextNode (Node<Item> *curNode, const Item& k)
{
    int i = 0;

    for (i = 0; i < curNode->GetNumItem (); i++)
        if (k < curNode->GetItem (i))
            return curNode->GetChild (i);

    return curNode->GetChild (i);
}
