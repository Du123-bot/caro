#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include<string>
#include<vector>
#include<Windows.h>
#include<iostream>

//using namespace std;
struct GameRecord 
{
    int boardSize=0;
    int mode=0;
    std::vector<std::vector<char>> board{};
    char winner=' ';
    int modeXO = 0;
    int modeLevel = 0;
    std::string NameOfPlayer1="";
    std::string NameOfPlayer2="";
};

void deleteSavedGame();
void showSavedGames();
void askToSaveGame(char, int, int, char[50][50],int,const std::string&,const std::string&,int);
int GetSelectGameMenuChoice(const std::string&);
#endif
