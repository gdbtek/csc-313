// *************************************************************************
// FILE NAME: graph.h                                                      *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 04/10/2002                                                   *
// UPDATED  : 05/01/2002                                                   *
// *************************************************************************

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <limits.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <queue>
#include <stack>

using namespace std;

#define MAX DBL_MAX

struct Node
{
    string name;
    int visited;
    double cost;

    Node *vertex, *edge;
};

class Graph
{
    public:
        Graph (void);
        ~Graph (void);

        bool Open (char *);
        bool Save (char *);

        bool InsertVertex (const string&);
        bool InsertEdge (const string&, const string&, double);

        bool DeleteVertex (const string&);
        bool DeleteEdge (const string&, const string&);
        bool DeleteGraph (void);

        bool Print (void);
        bool PrintBFS (const string&);
        bool PrintDFS (const string&);

        bool ShortestPath (const string&, const string&);
        bool ShortestTable (void);
        bool MinSpanTree (const string&);

        bool IsEmpty (void) const;

    protected:
        Node *_FindVertex (const string&) const;
        Node *_FindEdge (const Node *, const string&) const;

        void _Reset (void) const;
        void _PrintDFS (Node *) const;

        void _Floyd (double **&, double **&) const;
        void _Initialize (double **&, double **&, double **&) const;
        int  _Index (const string&) const;
        Node *_Position (double) const;
        void _Path (double **, int, int) const;

    private:
        int _vertex, _edge;

        Node *_graph;
};

#endif
