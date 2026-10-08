#pragma once
#include <iostream>
#include <vector>
#include <string> 
#include <sstream> 
#include<Windows.h>

using namespace std;

namespace Theme
{
    const string BaseColor = "\033[30;107m";
    const string RedColor = "\033[31;107m";
    const string BlueColor = "\033[34;107m"; 
    const string YellowColor = "\033[33;107m";
    const string GreyColor = "\033[90;107m";
}

void ClearScreen();
void GoToXY(int, int);
void CenterText(string, int);
void DrawXO(int, int, int, int, char[][50], bool);
void PrintRepeatedChar(unsigned char, int);
void DrawBoardGame(int, int&, int&);
void PrintWin(char);
void EffectWin(int, int, int, char, char[][50], int, int, int);
void SetBackGround();
void PrintCaroGame();
void PrintModeGame();
void PrintSizeGame();
void DrawX(int, int);
void DrawO(int, int);
int GetConsoleWidth();
int GetConsoleHeight();
void PrintXWin();
void PrintOWin();
void PrintWin(char);
void PrintDraw();
void PrintSaveGame();
void PrintLevelGame();
void PrintSelectionXO();
void PrintNotOverGame();
void PrintHowToPlay();