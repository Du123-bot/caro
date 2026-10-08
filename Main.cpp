#include<iostream>
#include<conio.h>
#include "LogicGame.h"
#include "MenuGame.h"
#include "Display.h"
#include "SoundEffect.h"
using namespace std;

int turn, mode,x,y,n,ModeChoice;
char Board[50][50], CurrentPlayer, BotPlayer, HumanPlayer;
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{

    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci; GetConsoleCursorInfo(hout, &ci);
    ci.bVisible = FALSE; SetConsoleCursorInfo(hout, &ci);

    HideCursor();
    //srand(static_cast<unsigned int>(time(nullptr)));
    srand(time(0));

    //SetConsoleFullScreen();
    //backgroundMusicThread();
    playBackgroundMusic();
    while (true)
    {
        int Play = ProcessMainMenu(Board, n, CurrentPlayer, HumanPlayer, BotPlayer);
        if (Play == 4)
        {
            StopBackGroundMusic();
            return 0;
        }
    }
}