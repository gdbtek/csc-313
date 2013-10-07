// *************************************************************************
// FILE NAME: tree_node.cpp                                                *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 03/14/2002                                                   *
// UPDATED  : 04/08/2002                                                   *
// *************************************************************************

template <class Item>
Node<Item>::Node (void)
{
    for (int i = 0; i < 3; i++)
        _item [i] = NULL;

    for (int i = 0; i < 4; i++)
        _child [i] = NULL;
}

template <class Item>
Item Node<Item>::GetItem (int i) const
{
    return *_item [i];
}

template <class Item>
Node<Item> *Node<Item>::GetChild (int i) const
{
    return _child [i];
}

template <class Item>
Node<Item> *Node<Item>::GetParent (void) const
{
    return _parent;
}

template <class Item>
int Node<Item>::GetNumItem (void) const
{
    int count = 0;

    for (int i = 0; i < 3; i++)
        if (_item [i] != NULL)
            count++;

    return count;
}

template <class Item>
bool Node<Item>::IsLeaf (void) const
{
    return (_child [0] == NULL);
}

template <class Item>
bool Node<Item>::IsFull (void) const
{
    return (GetNumItem () == 3);
}

template <class Item>
int Node<Item>::Find (const Item& k) const
{
    for (int i = 0; i < 3; i++)
        if (_item [i] == NULL)
            break;
        else if (*_item [i] == k)
            return i;

    return -1;
}

template <class Item>
int Node<Item>::Insert (Item& k)
{
    for (int i = 2; i >= 0; i--)
        if (_item [i] == NULL)
            continue;
        else if (k < *_item [i])
            _item [i + 1] = _item [i];
        else
        {
            _item [i + 1] = &k;
            return (i + 1);
        }

    _item [0] = &k;

    return 0;
}

template <class Item>
void Node<Item>::Change (const Item& k, int i)
{
    *_item [i] = k;
}

template <class Item>
Item *Node<Item>::Delete (int i)
{
    Item *delItem = _item [i];

    if (GetNumItem () == 3 && i == 0)
    {
        *_item [0] = *_item [1];
        *_item [1] = *_item [2];
        _item [2] = NULL;
    }
    else if (GetNumItem () == 3 && i == 1)
    {
        *_item [1] = *_item [2];
        _item [2] = NULL;
    }
    else if (GetNumItem () == 2 && i == 0)
    {
        *_item [0] = *_item [1];
        _item [1] = NULL;
    }
    else
        _item [i] = NULL;

    return delItem;
}

template <class Item>
void Node<Item>::Attach (int i, Node *node)
{
    _child [i] = node;

    if (node != NULL)
        node->_parent = this;
}

template <class Item>
Node<Item> *Node<Item>::Detach (int i)
{
    Node<Item> *detNode = _child [i];
    _child [i] = NULL;

    return detNode;
}

template <class Item>
void Node<Item>::Print (int beg, int end, int level) const
{
    string blank (8, ' ');

    for (int i = blank.length (), count = level; (count /= 10) != 0; i++)
        blank += ' ';

    for (int i = beg; i < end; i++)
    {
        if (level != 0)
            cout << setw (4 * level) << " ";

        if (i == 0)
            cout << "\033[1;31mLevel " << level << "\033[0m " << "\033[1;37mChild " << i << "\033[0m ";
        else if (i == 1)
            cout << blank << "\033[1;36mChild " << i << "\033[0m ";
        else
            cout << blank << "\033[1;33mChild " << i << "\033[0m ";

        cout << *_item [i] << "\n";
    }
}

template <class Item>
void Node<Item>::Erasing (void) const
{
    for (int i = 0; i < GetNumItem (); i++)
        cout << "\033[1;35mErasing...\033[0m " << *_item [i] << "\n";
}

template <class Item>
void Node<Item>::Saving (int i, fstream& outs) const
{
    cout << "\033[1;35mSaving...\033[0m " << *_item [i] << "\n";

    outs << _item [i]->GetFName () << " " << _item [i]->GetLName () << " "
         << setprecision (2) << setiosflags (ios::showpoint | ios::fixed)
         << _item [i]->GetId ()  << " " << _item [i]->GetBalance () << endl;
}
