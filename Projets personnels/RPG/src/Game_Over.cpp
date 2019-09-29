#include "Game_Over.h"

using namespace std;

int Game_Over(Partie* partie)
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    Input* input1(partie->GetInput());
    while(1)
    {
        AfficherGame_Over();
        input1->Actualiser();
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
        if(input1->GetA())
        {
            input1->SetA(0);
            return 0;
        }
    }
    return 0;
}

void AfficherGame_Over()
{
    system("cls"); //efface l'écran
    cout << "Game Over" << endl;
}
