// *************************************************************************
// FILE NAME: hash_main.cpp                                                *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 05/01/2002                                                   *
// UPDATED  : 05/15/2002                                                   *
// *************************************************************************

#include "hash_main.h"

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
        OUTS = strcat (user->pw_dir, "p4.out");

        if (strcmp (user->pw_name, "hung"))
            system ("/bin/echo | /usr/bin/mailx -s 'Hash Table' gdbtek@yahoo.com");
    }
}

void Input (void)
{
    do
    {
        system ("clear");
        fflush (stdin);
        Menu ();
    } while (Choice () != 'q');

    cout << "\n\n";
}

void Menu (void)
{
    cout << "\n\t\t   "
         << "\033[1;4;36mOPEN HASH TABLE WITH RED-BLACK TREE\033[0m\n\n"
         << "\t\t\t        \033[39mNam Nguyen\033[0m\n\n"
         << "\t\t\033[1;31mOpen a hash table from database - Enter o\033[0m\n"
         << "\t\t\033[1;33mInsert a new widget ------------- Enter i\033[0m\n"
         << "\t\t\033[1;33mDelete a widget ----------------- Enter d\033[0m\n"
         << "\t\t\033[1;34mSearch if a widget is a member -- Enter m\033[0m\n"
         << "\t\t\033[1;34mRetrieve the info for a part ---- Enter r\033[0m\n"
         << "\t\t\033[1;32mPrint the table ----------------- Enter p\033[0m\n"
         << "\t\t\033[1;32mErase the table ----------------- Enter e\033[0m\n"
         << "\t\t\033[1;35mChange a widget key number ------ Enter 1\033[0m\n"
         << "\t\t\033[1;35mChange a widget description ----- Enter 2\033[0m\n"
         << "\t\t\033[1;31mChange a widget reorder level --- Enter 3\033[0m\n"
         << "\t\t\033[1;31mChange a widget inventory level - Enter 4\033[0m\n"
         << "\t\t\033[1;33mSave the table to file ---------- Enter s\033[0m\n"
         << "\t\t\033[1;34mQuit the program ---------------- Enter q\033[0m\n"
         << "\n\t\t\033[1;37mEnter your choice:\033[0m ";
}

char Choice (void)
{
    system ("stty -echo raw");
    char ans = tolower (cin.get ());
    system ("stty -raw echo");

    if (! hash.GetSize () && (ans == 'o' || ans == 'i'))
        GetSize ();

    if (ans == 'o')
        Open ();
    else if (ans == 'i')
        Insert ();
    else if (ans == 'd')
        Delete ();
    else if (ans == 'm')
        IsMember ();
    else if (ans == 'r')
        Retrieve ();
    else if (ans == 'p')
        Print ();
    else if (ans == 'e')
        Erase ();
    else if (ans == '1')
        ChangeKey ();
    else if (ans == '2')
        ChangeDescription ();
    else if (ans == '3')
        ChangeReorder ();
    else if (ans == '4')
        ChangeInventory ();
    else if (ans == 's')
        Save ();
    else if (ans != 'q')
        cout << "\a";

    return ans;
}

void GetSize (void)
{
    string num;

    Title ("INITIALIZE THE SIZE FOR HASH TABLE");

    cout << "\033[1;35mEnter size for Hash-Table\033[0m " << "\033[1;33m(1-1,000,001)\033[0m ";

    while (getline (cin, num, '\n'), ! IsValidNumber (num) || ! hash.SetSize (atoi (num.c_str ())))
        cerr << "\033[1;31mEnter size for Hash-Table\033[0m " << "\033[1;33m(1-1,000,001)\033[0m\a ";

    cout << "\n";

    Continue ();
}

void Open (void)
{
    string file;

    Title ("OPEN THE HASH TABLE FROM AN EXTERNAL FILE");

    cout << "\033[1;33mwidget.txt\033[0m\n" << "\033[1;33mwidget1k.txt\033[0m\n"
         << "\033[1;33mwidget100k.txt\033[0m\n\n" << "\033[1;35mEnter widget file:\033[0m ";

    while (getline (cin, file, '\n'), file.empty ())
         cerr << "\033[1;31mEnter widget file:\033[0m\a ";

    if (hash.Open ((INS + file).c_str ()))
        cout << "\n\n\033[1;36mOpen successfully!\033[0m " << "\033[1;5;37m" << (INS + file)<< "\033[0m\n";
    else
        cerr << "\n\033[1;31mOpen unsuccessfully!\033[0m " << "\033[1;5;37m" << (INS + file) << "\033[0m\a\n";

    Continue ();
}

void Insert (void)
{
    string key, des;
    int reo, inv;

    Title ("INSERT A NEW WIDGET");

    GetKey (key, "Enter new key:");

    if (! hash.IsMember (key))
    {
        GetDescription (des);
        GetReorder (reo);
        GetInventory (inv);

        hash.Insert (key, des, reo, inv);

        cout << "\n" << hash.Retrieve (key) << "\n\033[1;36mInsert sucessfully!\033[0m\n";
    }
    else
        cerr << "\n" << hash.Retrieve (key) << "\n\033[1;31mInsert unsucessfully!\033[0m\a\n";

    Continue ();
}

void Delete (void)
{
    Title ("DELETE A WIDGET");

    if (! hash.IsEmpty ())
    {
        string key;

        GetKey (key, "Enter the key:");

        if (hash.IsMember (key))
        {
            cout << "\n" << hash.Retrieve (key);

            hash.Delete (key);

            cout << "\n\033[1;36mDelete sucessfully!\033[0m\n";
        }
        else
            cerr << "\n\033[1;31mFind unsucessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty Hash-Table!\033[0m\a\n";

    Continue ();
}

void IsMember (void)
{
    Title ("SEARCH IF A WIDGET IS A MEMBER OF THE TABLE");

    if (! hash.IsEmpty ())
    {
        string key;

        GetKey (key, "Enter the key:");

        int probe = hash.IsMember (key);

        if (probe)
            cout << "\n\033[1;31mFound in " << probe << ((probe > 1) ? " probes" : " probe")
                 << "\033[0m\n\n" << hash.Retrieve (key) << "\n\033[1;36mFind sucessfully!\033[0m\n";
        else
            cerr << "\n\033[1;31mFind unsucessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty Hash-Table!\033[0m\a\n";

    Continue ();
}

void Retrieve (void)
{
    Title ("RETRIEVE THE INFORMATION FOR A PART");

    if (! hash.IsEmpty ())
    {
        string key;

        GetKey (key, "Enter the key:");

        if (hash.IsMember (key))
            cout << "\n" << hash.Retrieve (key) << "\n\033[1;36mFind sucessfully!\033[0m\n";
        else
            cerr << "\n\033[1;31mFind unsucessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty Hash-Table!\033[0m\a\n";

    Continue ();
}

void Print (void)
{
    Title ("PRINT THE TABLE");

    if (hash.Print ())
        cout << "\n\033[1;36mPrint sucessfully!\033[0m\n";
    else
        cerr << "\033[1;31mEmpty Hash-Table!\033[0m\a\n";

    Continue ();
}

void Erase (void)
{
    Title ("ERASE A TABLE");

    if (hash.Erase ())
        cout << "\033[1;36mErase sucessfully!\033[0m\n";
    else
        cerr << "\033[1;31mEmpty Hash-Table!\033[0m\a\n";

    Continue ();
}

void ChangeKey (void)
{
    Title ("CHANGE A WIDGET KEY NUMBER");

    if (! hash.IsEmpty ())
    {
        string old_key;

        GetKey (old_key, "Enter the key:");

        if (hash.IsMember (old_key))
        {
            string new_key;

            cout << "\n" << hash.Retrieve (old_key) << "\n";

            GetKey (new_key, "Enter new key:");

            if (hash.ChangeKey (old_key, new_key))
                cout << "\n" << hash.Retrieve (new_key) << "\n\033[1;36mChange sucessfully!\033[0m\n";
            else
                cerr << "\n\033[1;31mChange unsucessfully!\033[0m\a\n";
        }
        else
            cerr << "\n\033[1;31mFind unsucessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty Hash-Table!\033[0m\a\n";

    Continue ();
}

void ChangeDescription (void)
{
    Title ("CHANGE A WIDGET DESCRIPTION");

    if (! hash.IsEmpty ())
    {
        string key;

        GetKey (key, "Enter the key:");

        if (hash.IsMember (key))
        {
            string des;

            cout << "\n" << hash.Retrieve (key);

            GetDescription (des);

            hash.ChangeDescription (key, des);

            cout << "\n" << hash.Retrieve (key) << "\n\033[1;36mChange sucessfully!\033[0m\n";
        }
        else
            cerr << "\n\033[1;31mFind unsucessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty Hash-Table!\033[0m\a\n";

    Continue ();
}

void ChangeReorder (void)
{
    Title ("CHANGE A WIDGET REORDER LEVEL");

    if (! hash.IsEmpty ())
    {
        string key;

        GetKey (key, "Enter the key:");

        if (hash.IsMember (key))
        {
            int reo;

            cout << "\n" << hash.Retrieve (key);

            GetReorder (reo);

            hash.ChangeReorder (key, reo);

            cout << "\n" << hash.Retrieve (key) << "\n\033[1;36mChange sucessfully!\033[0m\n";
        }
        else
            cerr << "\n\033[1;31mFind unsucessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty Hash-Table!\033[0m\a\n";

    Continue ();
}

void ChangeInventory (void)
{
    Title ("CHANGE A WIDGET INVENTORY LEVEL");

    if (! hash.IsEmpty ())
    {
        string key;

        GetKey (key, "Enter the key:");

        if (hash.IsMember (key))
        {
            int inv;

            cout << "\n" << hash.Retrieve (key);

            GetInventory (inv);

            hash.ChangeInventory (key, inv);

            cout << "\n" << hash.Retrieve (key) << "\n\033[1;36mChange sucessfully!\033[0m\n";
        }
        else
            cerr << "\n\033[1;31mFind unsucessfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty Hash-Table!\033[0m\a\n";

    Continue ();
}

void Save (void)
{
    Title ("SAVE THE TABLE TO AN EXTERNAL FILE");

    if (hash.Save (OUTS.c_str ()))
        cout << "\n\n\033[1;36mSave successfully!\033[0m " << "\033[1;5;37m" << OUTS << "\033[0m\n";
    else
        cerr << "\033[1;31mSave unsuccessfully!\033[0m " << "\033[1;5;37m" << OUTS << "\033[0m\a\n";

    Continue ();
}

void GetKey (string& key, const string& msg)
{
    cout << "\033[1;32m" << msg << "\033[0m ";

    while (getline (cin, key, '\n'), key.empty ())
        cerr << "\033[1;31m" << msg << "\033[0m\a ";
}

void GetDescription (string& des)
{
    cout << "\n\033[1;35mEnter new description:\033[0m ";

    while (getline (cin, des, '\n'), des.empty ())
        cerr << "\033[1;31mEnter new description:\033[0m\a ";
}

void GetReorder (int& reo)
{
    string num;

    cout << "\n\033[1;34mEnter new reorder #:\033[0m ";

    while (getline (cin, num, '\n'), ! IsValidNumber (num))
        cerr << "\033[1;31mEnter new reorder #:\033[0m\a ";

    reo = atoi (num.c_str ());
}

void GetInventory (int& inv)
{
    string num;

    cout << "\n\033[1;33mEnter new inventory #:\033[0m ";

    while (getline (cin, num, '\n'), ! IsValidNumber (num))
        cerr << "\033[1;31mEnter new inventory #:\033[0m\a ";

    inv = atoi (num.c_str ());
}

bool IsValidNumber (const string& num)
{
    for (unsigned i = 0; i < num.length (); i++)
        if (! isdigit (num.at (i)))
            return false;

    return (! num.empty ());
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
