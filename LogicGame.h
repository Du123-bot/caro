#pragma once
#include<iostream>
#include<algorithm>
#include<ctime>
#include<vector>
using namespace std;

struct Coord {
    int x, y;
};

struct Move {
    int row, col;
};

void DefineBotPlayer(int);
char CheckMinimaxWin(char[][50]);
bool IsMinimaxBoardFull(char[][50]);
int Minimax(char[][50], int, bool, int);
Coord BlockThree(int, char[][50], int, int, char);
Coord BestMove(char[][50], int);
Coord BotTurn(char[][50], int, int, char, int,int,int);

bool CheckRow(char, int, int, char[][50], int);
bool CheckCol(char, int, int, char[][50], int);
bool CheckDiag1(char, int, int, char[][50],int);
bool CheckDiag2(char, int, int,char[][50], int);
bool CheckDraw(char [][50],int );
bool CheckWin(char, int, int, char[][50],int);
void ResetBoardGame(char[][50], int);
int CheckWin2(char, int, int, char[][50], int);
int CheckTypeWin(char [][50]);
int AlphaBetaPruning(char [][50], int, int, int, bool);
Coord BestMoveHard(char [][50]);
int CountRow(char, int, int, char[][50], int);
int CountCol(char, int, int, char[][50], int);
int CountDiag1(char, int, int, char[][50], int);
int CountDiag2(char, int, int, char[][50], int);
int CountPiece(char [][50], char, int, int);
int Value(char[][50], char, char);
bool IsNearPiece(int, int, char[][50]);

