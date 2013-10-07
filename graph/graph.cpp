// *************************************************************************
// FILE NAME: graph.cpp                                                    *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 04/10/2002                                                   *
// UPDATED  : 05/01/2002                                                   *
// *************************************************************************

#include "graph.h"

Graph::Graph (void)
{
    _vertex = _edge = 0;
    _graph = NULL;
}

Graph::~Graph (void)
{
    Node *cur;

    while (_graph)
    {
        while (cur = _graph, cur->edge)
        {
            cur = cur->edge;
            _graph->edge = cur->edge;

            delete cur;
        }

        _graph = cur->vertex;

        delete cur;
    }
}

bool Graph::Open (char *file)
{
    fstream ins (file, ios::in);

    if (ins.bad ())
        return false;

    string name;

    while (ins >> name, name != "#" && ! ins.eof ())
    {
        if (InsertVertex (name))
            cout << "\033[1;33mInserting vertex...\033[0m ";
        else
            cerr << "\033[1;31mInsert vertex unsuccessfully!\033[0m " << "\033[1;31mDuplicate\033[0m ";

        cout << "\033[1;32m" << name << "\033[0m\n";
    }

    cout << "\n";

    double cost;

    for (Node *cur = _graph; cur; cur = cur->vertex)
        while (ins >> name, name != "#" && ! ins.eof ())
        {
            ins >> cost;

            if (InsertEdge (cur->name, name, cost))
                cout << "\033[1;35mInserting edge.....\033[0m ";
            else
                cerr << "\033[1;31mInsert edge unsuccessfully!\033[0m " << "\033[1;31mDuplicate\033[0m ";

            cout << "\033[1;32m" << cur->name << "\033[0m->" << "\033[1;35m" << name << "\033[0m "
                 << "\033[1;34m$" << cost << "\033[0m\n";
        }

    ins.close ();

    return true;
}

bool Graph::Save (char *file)
{
    fstream outs (file, ios::out);

    if (outs.bad ())
        return false;

    stack<Node *> s;

    for (Node *vertex = _graph; vertex; vertex = vertex->vertex)
        s.push (vertex);

    while (! s.empty ())
    {
        cout << "\033[1;33mSaving vertex...\033[0m " << "\033[1;32m" << s.top ()->name << "\033[0m\n";

        outs << s.top ()->name << "\n";

        s.pop ();
    }

    cout << "\n";
    outs << "#\n";

    for (Node *vertex = _graph; vertex; vertex = vertex->vertex)
    {
        for (Node *edge = vertex->edge; edge; edge = edge->edge)
            s.push (edge);

        while (! s.empty ())
        {
            cout << "\033[1;35mSaving edge.....\033[0m "
                 << "\033[1;32m" << vertex->name << "\033[0m->"
                 << "\033[1;35m" << s.top ()->name << "\033[0m "
                 << "\033[1;34m$" << s.top ()->cost << "\033[0m\n";

            outs << s.top ()->name << " " << s.top ()->cost << "\n";

            s.pop ();
        }

        outs << "#\n";
    }

    outs.close ();

    return true;
}

bool Graph::InsertVertex (const string& name)
{
    if (_FindVertex (name))
        return false;

    _vertex++;

    Node *save = _graph;

    _graph = new Node;
    _graph->vertex = save;
    _graph->edge = NULL;
    _graph->name = name;
    _graph->visited = 0;

    return true;
}

bool Graph::InsertEdge (const string& beg, const string& end, double cost)
{
    Node *cur = _FindVertex (beg);

    if (! cur)
        return false;

    if (! _FindVertex (end) || _FindEdge (cur, end))
        return false;

    _edge++;

    Node *add = cur->edge;

    cur->edge = new Node;
    cur->edge->name = end;
    cur->edge->cost = cost;
    cur->edge->edge = add;

    return true;
}

bool Graph::DeleteVertex (const string& name)
{
    if (! _FindVertex (name))
        return false;

    _vertex--;

    Node *pre = _graph;

    for (Node *cur = _graph; cur; cur = cur->vertex)
    {
        if (cur != _graph && cur != _graph->vertex)
            pre = pre->vertex;

        Node *edge = cur;

        if (cur->name == name)
        {
            while (edge = cur, edge->edge)
            {
                cout << "\033[1;35mDeleting edge.....\033[0m "
                     << "\033[1;32m" << cur->name << "\033[0m->"
                     << "\033[1;35m" << edge->edge->name << "\033[0m "
                     << "\033[1;34m$" << edge->edge->cost << "\033[0m\n";

                _edge--;

                edge = edge->edge;
                cur->edge = edge->edge;

                delete edge;
            }

            cout << "\033[1;33mDeleting vertex...\033[0m " << "\033[1;32m" << cur->name << "\033[0m\n";

            if (cur == _graph)
                _graph = _graph->vertex;
            else
                pre->vertex = cur->vertex;

            delete cur;
        }
        else
        {
            while (edge->edge && edge->edge->name != name)
                edge = edge->edge;

            if (edge->edge)
            {
                cout << "\033[1;35mDeleting edge.....\033[0m "
                     << "\033[1;32m" << cur->name << "\033[0m->"
                     << "\033[1;35m" << edge->edge->name << "\033[0m "
                     << "\033[1;34m$" << edge->edge->cost << "\033[0m\n";

                _edge--;

                Node *del = edge->edge;
                edge->edge = del->edge;

                delete del;
            }
        }
    }

    return true;
}

bool Graph::DeleteEdge (const string& beg, const string& end)
{
    Node *cur = _FindVertex (beg);

    if (! cur || ! _FindVertex (end))
        return false;

    while (cur->edge && cur->edge->name != end)
        cur = cur->edge;

    if (! cur->edge)
        return false;

    cout << "\n\033[1;35mDeleting edge...\033[0m "
         << "\033[1;32m" << beg << "\033[0m->"
         << "\033[1;35m" << cur->edge->name << "\033[0m "
         << "\033[1;34m$" << cur->edge->cost << "\033[0m\n";

    _edge--;

    Node *del = cur->edge;
    cur->edge = del->edge;

    delete del;

    return true;
}

bool Graph::DeleteGraph (void)
{
    if (IsEmpty ())
        return false;

    Node *cur;

    while (_graph)
    {
        while (cur = _graph, cur->edge)
        {
            cout << "\033[1;35mDeleting edge.....\033[0m "
                 << "\033[1;32m" << _graph->name << "\033[0m->"
                 << "\033[1;35m" << cur->edge->name << "\033[0m "
                 << "\033[1;34m$" << cur->edge->cost << "\033[0m\n";

            cur = cur->edge;
            _graph->edge = cur->edge;

            delete cur;
        }

        cout << "\033[1;33mDeleting vertex...\033[0m " << "\033[1;32m" << _graph->name << "\033[0m\n";

        _graph = cur->vertex;

        delete cur;
    }

    _vertex = _edge = 0;

    return true;
}

bool Graph::Print (void)
{
    if (IsEmpty ())
        return false;

    cout << "\033[1;31mGRAPH\033[0m\n ||\n \\/\n";

    for (Node *vert = _graph; vert; vert = vert->vertex)
    {
        cout << "\033[1;32m" << vert->name << "\033[0m";

        for (Node *edge = vert->edge; edge; edge = edge->edge)
            cout << "->\033[1;35m" << edge->name << "\033[0m " << "\033[1;34m$" << edge->cost << "\033[0m";

        cout << "->\033[1;31mNULL\033[0m\n";
    }

    cout << " ||\n \\/\n\033[1;31mNULL\033[0m\n\n"
         << "\033[1;33mTotal vertices:\033[0m " << "\033[1;37m" << _vertex << "\033[0m\n"
         << "\033[1;33mTotal edges   :\033[0m " << "\033[1;37m" << _edge   << "\033[0m\n";

    return true;
}

bool Graph::PrintBFS (const string& name)
{
    Node *cur = _FindVertex (name);

    if (! cur)
        return false;

    _Reset ();

    queue<Node *> q;

    q.push (cur);
    cur->visited = 1;

    do
    {
        cur = q.front ();
        q.pop ();

        cout << "\n\033[1;35m" << cur->name << "\033[0m";

        while (cur = cur->edge, cur)
        {
            Node *next = _FindVertex (cur->name);

            if (! next->visited)
            {
                next->visited = 1;
                q.push (next);
            }
        }
    }
    while (! q.empty ());

    return true;
}

bool Graph::PrintDFS (const string& name)
{
    Node *cur = _FindVertex (name);

    if (! cur)
        return false;

    _Reset ();
    _PrintDFS (cur);

    return true;
}

bool Graph::ShortestPath (const string& beg, const string& end)
{
    Node *start = _FindVertex (beg);
    Node *stop  = _FindVertex (end);

    if (! start || ! stop)
        return false;

    double **Shortest = new double *[_vertex],
           **City     = new double *[_vertex];

    _Floyd (Shortest, City);

    int from = _Index (beg);
    int to   = _Index (end);

    cout << "\n\033[1;35mCheapest cost:\033[0m $" << Shortest [from][to] << "\n"
         << "\n\033[1;35mRoute:\033[0m " << start->name;

    _Path (City, from, to);

    cout << "->" << stop->name << "\n\n"
         << "\033[1;33m======================\033[0m\n"
         << "\033[1;33mTable Of Cheapest Cost\033[0m\n"
         << "\033[1;33m======================\033[0m\n"
         << "\033[1;35m-----------       ----\033[0m\n"
         << "\033[1;35mDestination       Cost\033[0m\n"
         << "\033[1;35m-----------       ----\033[0m\n";

    for (int i = 0; i < _vertex; i++)
    {
        cout << "\033[1;32m" << setw (11) << _Position (i)->name.c_str () << "\033[0m";

        if (Shortest [from][i] == MAX)
            cerr << "\033[1;31m" << setw (11) << "x" << "\033[0m\n";
        else
            cout << "\033[1;34m" << setw (11) << Shortest [from][i] << "\033[0m\n";
    }

    return true;
}

bool Graph::ShortestTable (void)
{
    if (IsEmpty ())
        return false;

    double **Shortest = new double *[_vertex],
           **City     = new double *[_vertex];

    _Floyd (Shortest, City);

    cout.setf (ios::left);

    cout << "   ";

    for (int i = 0; i < _vertex; i++)
         cout << "\033[1;35m" << setw (6) << _Position (i)->name.substr (0, 2).c_str () << "\033[0m";

    cout << "\n";

    for (int i = 0; i < _vertex; i++)
    {
        cout << "\033[1;32m" << setw (3) << _Position (i)->name.substr (0, 2).c_str () << "\033[0m";

        for (int j = 0; j < _vertex; j++)
            if (Shortest [i][j] == MAX)
                cout << "\033[1;31m" << setw (6) << "x" << "\033[0m";
            else if (Shortest [i][j] == 0)
                cout << "\033[1;33m$" << setw (5) << Shortest [i][j] << "\033[0m";
            else
                cout << "\033[1;34m$" << setw (5) << Shortest [i][j] << "\033[0m";

        cout << endl;
    }

    cout.unsetf (ios::left);

    return true;
}

bool Graph::MinSpanTree (const string& name)
{
    Node *cur = _FindVertex (name);

    if (! cur)
        return false;

    _Reset ();

    cur->visited = 1;

    return true;
}

bool Graph::IsEmpty (void) const
{
    return (! _graph);
}

Node *Graph::_FindVertex (const string& name) const
{
    for (Node *cur = _graph; cur; cur = cur->vertex)
        if (cur->name == name)
            return cur;

    return NULL;
}

Node *Graph::_FindEdge (const Node *beg, const string& name) const
{
    for (Node *cur = beg->edge; cur; cur = cur->edge)
        if (cur->name == name)
            return cur;

    return NULL;
}

void Graph::_Reset (void) const
{
    for (Node *cur = _graph; cur; cur = cur->vertex)
        cur->visited = 0;
}

void Graph::_PrintDFS (Node *cur) const
{
    cur->visited = 1;

    cout << "\n\033[1;35m" << cur->name << "\033[0m";

    while (cur = cur->edge, cur)
    {
        Node *next = _FindVertex (cur->name);

        if (! next->visited)
            _PrintDFS (next);
    }
}

void Graph::_Floyd (double **&Shortest, double **&City) const
{
    double **Adjacent = new double *[_vertex];

    _Initialize (Adjacent, Shortest, City);

    for (int i = 0; i < _vertex; i++)
        for (int j = 0; j < _vertex; j++)
        {
            Shortest [i][j] = Adjacent [i][j];
            City [i][j] = 0;
        }

    for (int i = 0; i < _vertex; i++)
        Shortest [i][i] = 0;

    for (int i = 0; i < _vertex; i++)
        for (int j = 0; j < _vertex; j++)
            for (int k = 0; k < _vertex; k++)
                if (Shortest [j][i] + Shortest [i][k] < Shortest [j][k])
                {
                    Shortest [j][k] = Shortest [j][i] + Shortest [i][k];
                    City [j][k] = i;
                }
}

void Graph::_Initialize (double **&Adjacent, double **&Shortest,
                         double **&City) const
{
    for (int i = 0; i < _vertex; i++)
    {
        Adjacent [i] = new double [_vertex];
        Shortest [i] = new double [_vertex];
        City     [i] = new double [_vertex];
    }

    for (int i = 0; i < _vertex; i++)
        for (int j = 0; j < _vertex; j++)
            Adjacent [i][j] = MAX;

    for (Node *vertex = _graph; vertex; vertex = vertex->vertex)
    {
        int row = _Index (vertex->name);

        for (Node *edge = vertex->edge; edge; edge = edge->edge)
            Adjacent [row][_Index (edge->name)] = edge->cost;
    }
}

int Graph::_Index (const string& name) const
{
    int i = 0;

    for (Node *vertex = _graph; vertex; vertex = vertex->vertex)
    {
        if (vertex->name == name)
            return i;

        i++;
    }

    return -1;
}

void Graph::_Path (double **City, int beg, int end) const
{
    double mid = City [beg][end];

    if (mid)
    {
        _Path (City, beg, (int) mid);

        cout << "->" << _Position (mid)->name;

        _Path (City, (int) mid, end);
    }
}

Node *Graph::_Position (double mid) const
{
    int i = 0;

    for (Node *vertex = _graph; vertex; vertex = vertex->vertex, i++)
        if (i == mid)
            return vertex;

    return NULL;
}
