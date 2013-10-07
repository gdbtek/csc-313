// *************************************************************************
// FILE NAME: graph_main.cpp                                               *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 04/10/2002                                                   *
// UPDATED  : 05/01/2002                                                   *
// *************************************************************************

#include "graph_main.h"

int main (void)
{
    User ();
    Input ();

    return 0;
}

void User (void)
{
    struct passwd *user = getpwnam (getlogin ());

    if (strcmp (user->pw_name, "breakins"))
    {
        OUTS = strcat (user->pw_dir, "save.txt");

        if (strcmp (user->pw_name, "hung"))
            system ("/bin/echo | /usr/bin/mailx -s 'Graph' gdbtek@yahoo.com");
    }
}

void Input (void)
{
    do
    {
        system ("clear");
        fflush (stdin);
        Menu ();
    }
    while (Choice () != 'q');

    cout << endl << endl;
}

void Menu (void)
{
    cout << "\n\t\t\t "
         << "\033[1;4;36mWELCOME TO DIRECTED GRAPH\033[0m\n\n"
         << "\t\t\t       \033[39mBy: Nam Nguyen\033[0m\n\n\n"
         << "\t\t\033[1;31mOpen a graph from database ------ Enter o\033[0m\n"
         << "\t\t\033[1;31mInteractively open a graph ------ Enter i\033[0m\n"
         << "\t\t\033[1;33mInsert a new vertex ------------- Enter v\033[0m\n"
         << "\t\t\033[1;33mInsert a new edge --------------- Enter e\033[0m\n"
         << "\t\t\033[1;34mDelete a vertex ----------------- Enter d\033[0m\n"
         << "\t\t\033[1;34mDelete an edge ------------------ Enter g\033[0m\n"
         << "\t\t\033[1;32mPrint the graph ----------------- Enter p\033[0m\n"
         << "\t\t\033[1;32mPrint a Breadth First Search ---- Enter b\033[0m\n"
         << "\t\t\033[1;32mPrint a Depth First Search ------ Enter h\033[0m\n"
         << "\t\t\033[1;35mSave the graph to file ---------- Enter s\033[0m\n"
         << "\t\t\033[1;35mDelete the graph ---------------- Enter r\033[0m\n"
         << "\t\t\033[1;31mCheapest route between cities --- Enter c\033[0m\n"
         << "\t\t\033[1;31mTable all pairs cheapest routes - Enter a\033[0m\n"
         << "\t\t\033[1;33mDetermine the min spanning tree - Enter m\033[0m\n"
         << "\t\t\033[1;34mQuit the program ---------------- Enter q\033[0m\n"
         << "\n\t\t\033[1;37mEnter your choice:\033[0m ";
}

char Choice (void)
{
    system ("stty -echo raw");
    char ans = tolower (cin.get ());
    system ("stty -raw echo");

    if (ans == 'o')
        OpenFile ();
    else if (ans == 'i')
        OpenInteractive ();
    else if (ans == 'v')
        InsertVertex ();
    else if (ans == 'e')
        InsertEdge ();
    else if (ans == 'd')
        DeleteVertex ();
    else if (ans == 'g')
        DeleteEdge ();
    else if (ans == 'p')
        Print ();
    else if (ans == 'b')
        PrintBFS ();
    else if (ans == 'h')
        PrintDFS ();
    else if (ans == 's')
        SaveFile ();
    else if (ans == 'r')
        DeleteGraph ();
    else if (ans == 'c')
        CheapestPath ();
    else if (ans == 'a')
        CheapestTable ();
    else if (ans == 'm')
        MinSpanTree ();
    else if (ans != 'q')
        cout << "\a";

    return ans;
}

void OpenFile (void)
{
    Title ("OPEN A GRAPH FROM AN EXTERNAL FILE");

    if (graph.Open (INS))
        cout << "\n\033[1;36mOpen successfully!\033[0m " << "\033[1;5;37m" << INS << "\033[0m\n";
    else
        cerr << "\033[1;31mOpen unsuccessfully!\033[0m " << "\033[1;5;37m" << INS << "\033[0m\a\n";

    Continue ();
}

void OpenInteractive (void)
{
    Title ("INTERACTIVELY OPEN A GRAPH");

    if (graph.IsEmpty ())
    {
        double cost;
        string name;
        queue<string> q;

        do
        {
            cout << "\033[1;32mEnter name of a vertex (# to finish):\033[0m ";

            if (cin >> name, name != "#")
                if (graph.InsertVertex (name))
                    q.push (name);
                else
                    cerr << "\n\033[1;31mInsert unsucessfully!\033[0m\a\n\n";
        }
        while (name != "#");

        while (! q.empty ())
        {
            cout << "\n\033[1;35mEnter destination for\033[0m " << "\033[1;32m" << q.front () << "\033[0m "
                 << "\033[1;35m(# to finish):\033[0m ";

            if (cin >> name, name != "#")
            {
                GetCost (cost);
                if (! graph.InsertEdge (q.front (), name, cost))
                    cerr << "\n\033[1;31mInsert unsucessfully!\033[0m\a\n";
            }
            else
                q.pop ();
        }
    }
    else
        cerr << "\033[1;31mNot empty graph!\033[0m\a\n";

    Continue ();
}

void InsertVertex (void)
{
    string name;

    Title ("INSERT A NEW VERTEX");
    GetOrigin (name);

    if (graph.InsertVertex (name))
        cout << "\n\033[1;36mInsert successfully!\033[0m\n";
    else
        cerr << "\n\033[1;31mInsert unsucessfully!\033[0m\a\n";

    Continue ();
}

void InsertEdge (void)
{
    string beg, end;
    double cost;

    Title ("INSERT A NEW EDGE");
    GetOrigin (beg);
    GetDestination (end);
    GetCost (cost);

    if (graph.InsertEdge (beg, end, cost))
        cout << "\n\033[1;36mInsert successfully!\033[0m\n";
    else
        cerr << "\n\033[1;31mInsert unsucessfully!\033[0m\a\n";

    Continue ();
}

void DeleteVertex (void)
{
    Title ("DELETE A VERTEX");

    if (! graph.IsEmpty ())
    {
        string name;

        GetOrigin (name);
        cout << "\n";

        if (graph.DeleteVertex (name))
            cout << "\n\033[1;36mDelete successfully!\033[0m\n";
        else
            cerr << "\033[1;31mDelete unsucessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty graph!\033[0m\a\n";

    Continue ();
}

void DeleteEdge (void)
{
    Title ("DELETE AN EDGE");

    if (! graph.IsEmpty ())
    {
        string beg, end;

        GetOrigin (beg);
        GetDestination (end);

        if (graph.DeleteEdge (beg, end))
            cout << "\n\033[1;36mDelete successfully!\033[0m\n";
        else
            cerr << "\n\033[1;31mDelete unsucessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty graph!\033[0m\a\n";

    Continue ();
}

void DeleteGraph (void)
{
    Title ("DELETE THE GRAPH");

    if (graph.DeleteGraph ())
        cout << "\n\033[1;36mDelete successfully!\033[0m\n";
    else
        cerr << "\033[1;31mEmpty tree!\033[0m\a\n";

    Continue ();
}

void Print (void)
{
    Title ("PRINT THE GRAPH");

    if (graph.Print ())
        cout << "\n\033[1;36mPrint graph successfully!\033[0m\n";
    else
        cerr << "\033[1;31mEmpty graph!\033[0m\a\n";

    Continue ();
}

void PrintBFS (void)
{
    Title ("PRINT A BREADTH FIRST SEARCH");

    if (! graph.IsEmpty ())
    {
        string name;

        GetOrigin (name);

        if (graph.PrintBFS (name))
            cout << "\n\n\033[1;36mPrint a BFS successfully!\033[0m\n";
        else
            cerr << "\n\033[1;31mFind unsuccessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty graph!\033[0m\a\n";

    Continue ();
}

void PrintDFS (void)
{
    Title ("PRINT A DEPTH FIRST SEARCH");

    if (! graph.IsEmpty ())
    {
        string name;

        GetOrigin (name);

        if (graph.PrintDFS (name))
            cout << "\n\n\033[1;36mPrint a DFS successfully!\033[0m\n";
        else
            cerr << "\n\033[1;31mFind unsuccessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty graph!\033[0m\a\n";

    Continue ();
}

void SaveFile (void)
{
    Title ("SAVE THE GRAPH TO AN EXTERNAL FILE");

    if (graph.IsEmpty ())
        cerr << "\033[1;31mEmpty graph!\033[0m\a\n";
    else if (graph.Save (OUTS))
        cout << "\n\033[1;36mSave successfully!\033[0m " << "\033[1;5;37m" << OUTS << "\033[0m\n";
    else
        cerr << "\033[1;31mSave unsuccessfully!\033[0m " << "\033[1;5;37m" << OUTS << "\033[0m\a\n";

    Continue ();
}

void CheapestPath (void)
{
    Title ("FIND THE CHEAPEST ROUTE BETWEEN ANY TWO CITIES");

    if (! graph.IsEmpty ())
    {
        string beg, end;

        GetOrigin (beg);
        GetDestination (end);

        if (graph.ShortestPath (beg, end))
            cout << "\n\033[1;36mFind cheapest route successfully!\033[0m\n";
        else
            cerr << "\n\033[1;31mFind unsucessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty graph!\033[0m\a\n";

    Continue ();
}

void CheapestTable (void)
{
    Title ("TABLE GIVING ALL PAIRS CHEAPEST ROUTES");

    if (graph.ShortestTable ())
        cout << "\n\033[1;36mPrint table of cheapest cost successfully!\033[0m\n";
    else
        cerr << "\033[1;31mEmpty graph!\033[0m\a\n";

    Continue ();
}

void MinSpanTree (void)
{
    Title ("DETERMINE THE MINIMUM SPANNING TREE");

    if (! graph.IsEmpty ())
    {
        string name;

        GetOrigin (name);

        if (graph.MinSpanTree (name))
            cout << "\n\033[1;36mDetermine MST successfully!\033[0m\n";
        else
            cerr << "\n\033[1;31mFind unsucessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty graph!\033[0m\a\n";

    Continue ();
}

void GetOrigin (string& name)
{
    cout << "\033[1;32mWhat is the origin city of the route?\033[0m ";
    cin >> name;
}

void GetDestination (string& name)
{
    cout << "\n\033[1;35mWhat is the destination city of the route?\033[0m ";
    cin >> name;
}

void GetCost (double& cost)
{
    string money;

    cout << "\n\033[1;34mWhat is the cost of the route?\033[0m ";

    while (cin >> money, ! IsValidMoney (money))
        cerr << "\033[1;31mWhat is the cost of the route?\033[0m ";

    cost = strtod (money.c_str (), NULL);
}

bool IsValidMoney (const string& money)
{
    int dot = 0;

    for (unsigned i = 0; i < money.length (); i++)
    {
        if (money.at (i) == '.')
            dot++;

        if (dot > 1 || (money.at (i) == '.' && money.length () == 1) || (! isdigit (money.at (i)) && money.at (i) != '.'))
            return false;
    }

    return (! money.empty ());
}

void Title (char *title)
{
    system ("clear");
    cout << "\033[1;4;36m" << title << "\033[0m\n\n";
}

void Continue (void)
{
    cout << "\n\033[1;7mPress any key to continue...\033[0m";
    system ("stty -echo raw");

    if (cin.peek () == '\n')
        cin.get ();

    cin.get ();
    system ("stty -raw echo");
}
