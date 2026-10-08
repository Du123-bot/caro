#pragma once
#include<conio.h>
#include<Windows.h>
#include<iostream>
using namespace std;

extern bool isEnglish; 
extern bool isSoundOn;

void SetColor(int);
void ShowInstructions();
void StartModeTwoPlayer(char[][50], int&, char&);
void StartModePlayWithBot(char[][50],int&,char&,char&);
int ProcessMainMenu(char[][50], int&, char&, char&, char&);
void EnterTwoPlayerName(string&, string&);
void EnterPlayerName(string&);
void ShowTwoPlayerName(string, string,bool,int);
void ShowPlayerName(string, int, int);
void ContinueTwoPlayer(int, char[][50], char, int,string,string);
void ContinuePlayWithBot(int, char[][50], char, int, int, string,int);
void HideCursor();
void box(int, int, int, int, int, int, const string&);
int GetMainMenuChoice2();
int GetModeMenuChoice2();
int GetSizeMenuChoice2();
int GetPieceMenuChoice();
int GetPlayAgainMenuChoice();
int GetSaveGameMenuChoice();
int GetLoadGameMenuChoice();
int GetAskToSaveGameMenuChoice();
int GetLevel3x3MenuChoice();
int GetLevel12x12MenuChoice();
int ShowMenu(string[], int, int, int, int, int, int);
void HandleSettings();