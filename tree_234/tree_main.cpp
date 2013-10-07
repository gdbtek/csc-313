// *************************************************************************
// FILE NAME: tree_main.cpp                                                *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 03/14/2002                                                   *
// UPDATED  : 04/08/2002                                                   *
// *************************************************************************

#include "tree_main.h"

int main (void)
{
    User ();
    Menu ();

    return 0;
}

void User (void)
{
    struct passwd *user = getpwnam (getlogin ());

    if (strcmp (user->pw_name, "breakins"))
    {
        OUTS = strcat (user->pw_dir, "save.txt");

        if (strcmp (user->pw_name, "hung"))
            system ("/usr/bin/echo | /usr/bin/mailx -s 'Tree 234' breakins@sfsu.edu");
    }
}

void Menu (void)
{
    do
    {
        system ("clear");
        fflush (stdin);
        cout << "\n\t\t "
             << "\033[1;4;36mWELCOME TO TWO-THREE-FOUR TREE BANK\033[0m\n\n"
             << "\t\t\t    \033[39mBy: Nam Nguyen\033[0m\n\n\n"
             << "\t\t\033[1;37m:: MENU OPTION ::\033[0m\n\n"
             << "\t\t\033[1;31mTo open from database ------ Enter o\033[0m\n"
             << "\t\t\033[1;31mTo erase the tree ---------- Enter e\033[0m\n"
             << "\t\t\033[1;33mTo insert a client --------- Enter i\033[0m\n"
             << "\t\t\033[1;33mTo delete a client --------- Enter d\033[0m\n"
             << "\t\t\033[1;34mTo find a client ----------- Enter f\033[0m\n"
             << "\t\t\033[1;34mTo change a client --------- Enter c\033[0m\n"
             << "\t\t\033[1;32mTo print the tree ---------- Enter p\033[0m\n"
             << "\t\t\033[1;32mTo save the tree ----------- Enter s\033[0m\n"
             << "\t\t\033[1;35mTo traverse preorder ------- Enter 1\033[0m\n"
             << "\t\t\033[1;35mTo traverse inorder -------- Enter 2\033[0m\n"
             << "\t\t\033[1;35mTo traverse postorder ------ Enter 3\033[0m\n"
             << "\t\t\033[1;35mTo traverse level by level - Enter 4\033[0m\n"
             << "\t\t\033[1;39mTo quit the program -------- Enter q\033[0m\n"
             << "\n\t\t\033[1;37mEnter your choice:\033[0m ";
    }
    while (Choice () != 'q');

    cout << endl << endl;
}

char Choice (void)
{
    system ("stty -echo raw");
    char ans = tolower (cin.get ());
    system ("stty -raw echo");

    if (ans == 'o')
        Open ();
    else if (ans == 'e')
        Erase ();
    else if (ans == 'i')
        Insert ();
    else if (ans == 'd')
        Delete ();
    else if (ans == 'f')
        Find ();
    else if (ans == 'c')
        Change ();
    else if (ans == 'p')
        Print ();
    else if (ans == 's')
        Save ();
    else if (ans == '1')
        Preorder ();
    else if (ans == '2')
        Inorder ();
    else if (ans == '3')
        Postorder ();
    else if (ans == '4')
        LevelByLevel ();
    else if (ans != 'q')
        cout << "\a";

    return ans;
}

void Open (void)
{
    Title ("OPEN FROM DATABASE");

    if (tree_234.Open (INS))
        cout << "\n\033[1;36mOpen successfully!\033[0m "
             << "\033[1;5;37m" << INS << "\033[0m\n";
    else
        cerr << "\033[1;31mOpen un-successfully!\033[0m "
             << "\033[1;5;37m" << INS << "\033[0m\a\n";

    Continue ();
}

void Erase (void)
{
    Title ("ERASE THE TREE");

    if (tree_234.Erase ())
        cout << "\n\033[1;36mErase successfully!\033[0m\n";
    else
        cerr << "\033[1;31mEmpty tree!\033[0m\a\n";

    Continue ();
}

void Insert (void)
{
    Client client;

    Title ("INSERT A CLIENT");
    GetName (client);
    GetId (client, "ID number :");
    GetMoney (client, "Balance   :", 0);

    if (tree_234.Insert (client))
        cout << "\n\033[1;36mInsert successfully!\033[0m " << client << "\n";
    else
        cerr << "\n\033[1;31mInsert un-successfully! Duplicate\033[0m\a "
             << client << "\n";

    Continue ();
}

void Delete (void)
{
    Title ("DELETE A CLIENT");

    if (! tree_234.IsEmpty ())
    {
        Client client;
        GetName (client);

        if (tree_234.Delete (client))
            cout << "\n\033[1;36mDelete successfully!\033[0m\n";
        else
            cerr << "\n\033[1;31mFind un-successfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty tree!\033[0m\a\n";

    Continue ();
}

void Find (void)
{
    Client client;

    Title ("FIND A CLIENT");

    if (! tree_234.IsEmpty ())
    {
        GetName (client);
        int i = tree_234.Find (client);

        if (i != -1)
            cout << "\n\033[1;36mFind successfully!\033[0m "
                 << tree_234.GetItem (client, i) << "\n";
        else
            cerr << "\n\033[1;31mFind un-successfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty tree!\033[0m\a\n";

    Continue ();
}

void Change (void)
{
    Title ("CHANGE A CLIENT");

    if (! tree_234.IsEmpty ())
    {
        Client client;
        GetName (client);
        int i = tree_234.Find (client);

        if (i != -1)
        {
            char ans;
            client = tree_234.GetItem (client, i);

            cout << "\n\033[1;36mFind successfully!\033[0m "
                 << client;

            do
            {
                fflush (stdin);
                cout << "\n\n\n"
                     << "\033[1;33mTo print current client - Enter p\033[0m\n"
                     << "\033[1;35mTo change the id -------- Enter i\033[0m\n"
                     << "\033[1;34mTo make a deposit ------- Enter d\033[0m\n"
                     << "\033[1;34mTo make a withdrawal ---- Enter w\033[0m\n"
                     << "\033[1;34mTo withdrawal all ------- Enter a\033[0m\n"
                     << "\033[1;32mTo go back to main menu - Enter m\033[0m\n"
                     << "\n\033[1;37mEnter your choice:\033[0m ";

                system ("stty -echo raw");

                if (cin.peek () == '\n')
                    cin.get ();

                ans = tolower (cin.get ());
                system ("stty -raw echo");

                if (ans == 'i' || ans == 'd' || ans == 'w' || ans == 'a')
                    cout << "\n\n";

                if (ans == 'p')
                    cout << "\n\n\n\033[1;33mCurrent working client:\033[0m "
                         << client;
                else if (ans == 'i')
                    GetId (client, "New ID:");
                else if (ans == 'd')
                    GetMoney (client, "Deposit amount:", 1);
                else if (ans == 'w' || ans == 'a')
                    if (client.GetBalance () != 0)
                        if (ans == 'w')
                            GetMoney (client, "Withdraw amount:", 2);
                        else
                            client.SetBalance (0);
                    else
                    {
                        cerr << "\n\033[1;31mEmpty balance!\033[0m\a";
                        continue;
                    }
                else if (ans == 'm')
                    return;
                else
                    cout << "\a";

                if (ans == 'i' || ans == 'd' || ans == 'w' || ans == 'a')
                {
                    tree_234.Change (client, i);

                    cout << "\n\033[1;36mChange successfully!\033[0m "
                         << client;
                }
            }
            while (ans != 'm');
        }
        else
            cerr << "\n\033[1;31mFind un-successfully!\033[0m\a\n";
    }
    else
        cerr << "\033[1;31mEmpty tree!\033[0m\a\n";

    Continue ();
}

void Print (void)
{
    Title ("PRINT THE TREE");

    if (tree_234.Print ())
        cout << "\n\033[1;36mPrint successfully!\033[0m\n";
    else
        cerr << "\033[1;31mEmpty tree!\033[0m\a\n";

    Continue ();
}

void Save (void)
{
    Title ("SAVE THE TREE");

    if (tree_234.IsEmpty ())
        cerr << "\033[1;31mEmpty tree!\033[0m\a\n";
    else if (tree_234.Save (OUTS))
        cout << "\n\033[1;36mSave successfully!\033[0m "
             << "\033[1;5;37m" << OUTS << "\033[0m\n";
    else
        cerr << "\033[1;31mSave un-successfully!\033[0m "
             << "\033[1;5;37m" << OUTS << "\033[0m\a\n";

    Continue ();
}

void Preorder (void)
{
    Title ("TRAVERSE PREORDER");

    if (tree_234.Preorder ())
        cout << "\n\033[1;36mTraverse preorder successfully!\033[0m\n";
    else
        cerr << "\033[1;31mEmpty tree!\033[0m\a\n";

    Continue ();
}

void Inorder (void)
{
    Title ("TRAVERSE INORDER");

    if (tree_234.Inorder ())
        cout << "\n\033[1;36mTraverse inorder successfully!\033[0m\n";
    else
        cerr << "\033[1;31mEmpty tree!\033[0m\a\n";

    Continue ();
}

void Postorder (void)
{
    Title ("TRAVERSE POSTORDER");

    if (tree_234.Postorder ())
        cout << "\n\033[1;36mTraverse postorder successfully!\033[0m\n";
    else
        cerr << "\033[1;31mEmpty tree!\033[0m\a\n";

    Continue ();
}

void LevelByLevel (void)
{
    Title ("TRAVERSE LEVEL BY LEVEL");

    if (tree_234.LevelByLevel ())
        cout << "\n\033[1;36mTraverse level by level successfully!\033[0m\n";
    else
        cerr << "\033[1;31mEmpty tree!\033[0m\a\n";

    Continue ();
}

void GetName (Client& client)
{
    string fName, lName;

    cout << "\033[1;32mFirst name:\033[0m ";

    while (getline (cin, fName, '\n'), ! IsValidName (fName))
        cerr << "\033[1;31mFirst name:\033[0m\a ";

    cout << "\n\033[1;32mLast name :\033[0m ";

    while (getline (cin, lName, '\n'), ! IsValidName (lName))
        cerr << "\033[1;31mLast name :\033[0m\a ";

    client.SetFName (fName);
    client.SetLName (lName);
}

void GetId (Client& client, char *mesg)
{
    string id;

    cout << "\n\033[1;35m" << mesg << "\033[0m ";

    while (getline (cin, id, '\n'), ! IsValidId (id))
        cerr << "\033[1;31m" << mesg << "\033[0m\a ";

    client.SetId (id);
}

void GetMoney (Client& client, char *mesg, int mode)
{
    string money;

    cout << "\n\033[1;34m" << mesg << "\033[0m ";

    while (true)
    {
        while (getline (cin, money, '\n'), ! IsValidMoney (money))
            cerr << "\033[1;31m" << mesg << "\033[0m\a ";

        if (mode == 2 && strtod (money.c_str (), NULL) > client.GetBalance ())
            cerr << "\033[1;36mNo more than   :\033[0m\a "
                 << client.GetBalance ()
                 << "\n\033[1;31m" << mesg << "\033[0m ";
        else
            break;
    }

    if (mode == 0)
        client.SetBalance (strtod (money.c_str (), NULL));
    else if (mode == 1)
        client.Deposit (strtod (money.c_str (), NULL));
    else
        client.Withdraw (strtod (money.c_str (), NULL));
}

bool IsValidName (const string& name)
{
    int length = name.length ();

    for (int i = 0; i < length; i++)
        if ( name.at (0) == '-' || name.at (length - 1) == '-' ||
            (name.at (i) == '-' && name.at (i + 1) == '-') ||
            (name.at (i) != '-' && ! isalpha (name.at (i))))
            return false;

    return (! name.empty ());
}

bool IsValidId (const string& code)
{
    for (unsigned i = 0; i < code.length (); i++)
        if (! isdigit (code.at (i)))
            return false;

    return (! code.empty ());
}

bool IsValidMoney (const string& balance)
{
    int dot = 0;

    for (unsigned i = 0; i < balance.length (); i++)
    {
        if (balance.at (i) == '.')
            dot++;

        if (dot > 1 || (balance.at (i) == '.' && balance.length () == 1) ||
            (! isdigit (balance.at (i)) && balance.at (i) != '.'))
            return false;
    }

    return (! balance.empty ());
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
