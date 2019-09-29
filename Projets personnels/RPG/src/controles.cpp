#include "controles.h"

using namespace std;

void getkey(int& c)
{
    c = 0;
    if (kbhit())
    {
        c = getch();
    }
}

void AfficherCurseurEmplacement(int choix, int place)
{
    if (choix == place)
    {
        cout << ">";
    }
    else
    {
        cout << " ";
    }
}
