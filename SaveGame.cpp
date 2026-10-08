#include "SaveGame.h"
#include "Display.h"
#include "MenuGame.h"
#include<iostream>
#include<conio.h>
#include <cstdio>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

int GetSelectGameMenuChoice(const vector<string>& savedFiles)
{
    SetBackGround();
    string SelectGameMenuChoice[100];

    for (int i = 0;i < savedFiles.size();i++)
    {
        SelectGameMenuChoice[i] = savedFiles[i];
    }

    int choice = ShowMenu(SelectGameMenuChoice, savedFiles.size(), 30, 3,11,1,9);

    return choice;

}

void deleteSavedGame()
{
    ClearScreen();
    ifstream fin("saved_list.txt");
    if (!fin.is_open())
    {
        CenterText(isEnglish ? "NO SAVED MATCHES" : "CHUA CO VAN DAU NAO DUOC LUU", 10);
        return;
    }


    vector<string> savedFiles;
    string line;
    while (getline(fin, line))
    {
        if (!line.empty()) savedFiles.push_back(line);
    }
    fin.close();


    if (savedFiles.empty())
    {
        CenterText(isEnglish ? "NO SAVED MATCHES" : "CHUA CO VAN DAU NAO DUOC LUU", 10);
        Sleep(2000);
        return;
    }


    int y = 5;

    int choice = GetSelectGameMenuChoice(savedFiles);

    string toDelete = savedFiles[choice];

    // Xóa file vật lý
    if (remove(toDelete.c_str()) == 0)
    {
        // Xóa tên trong danh sách
        ofstream fout("saved_list.txt");
        for (int i = 0; i < savedFiles.size(); i++) 
        {
            if (i != choice)
             fout << savedFiles[i] << endl;
        }
        fout.close();

        ClearScreen();
        SetBackGround();
        CenterText(isEnglish ? "Game deleted " : "Da xoa van dau ten " + toDelete, y + 2);
        Sleep(2000);
        //CenterText("Press any key to return MAIN MENU ...", y + 4);
        //char tmp=_getch();
    }
    else
    {
        CenterText(isEnglish ? "Unable to delete this game" : "Loi khi xoa van dau", y + 2);
        Sleep(2000);
        return;
    }
}

void showSavedGames()
{
    ClearScreen();
    SetBackGround();
    PrintSaveGame();
    ifstream fin("saved_list.txt");
    if (!fin.is_open())
    {
        CenterText(isEnglish ? "NO SAVED MATCHES" : "CHUA CO VAN DAU NAO DUOC LUU", 10);
        Sleep(2000);
        return;
    }


    vector<string> savedFiles;
    string line;
    while (getline(fin, line)) 
    {
        if (!line.empty()) savedFiles.push_back(line);
    }
    fin.close();


    if (savedFiles.empty())
    {
        CenterText(isEnglish ? "NO SAVED MATCHES" : "CHUA CO VAN DAU NAO DUOC LUU", 10);
        Sleep(2000);
        return;
    }

    int Choice = GetSaveGameMenuChoice();
    if (Choice == 0)
    {
        // Tiep tuc choi
       ClearScreen();
       // int choice = GetMenuSelectGame(savedFiles);

        int choice = GetSelectGameMenuChoice(savedFiles);

        string chosenFile = savedFiles[choice];
        ifstream fin2(chosenFile, ios::binary);
        if (!fin2.is_open())
        {
            CenterText(isEnglish ? "Unable to open this game" : "Loi khi mo van dau", 12);
            Sleep(2000);
            return;
        }


        GameRecord game;
        fin2.read((char*)&game.boardSize, sizeof(int));
        fin2.read((char*)&game.mode, sizeof(int));
        fin2.read((char*)&game.winner, sizeof(char));
        fin2.read((char*)&game.modeXO, sizeof(int));
        fin2.read((char*)&game.modeLevel, sizeof(int));

        int len1, len2;

        fin2.read((char*)&len1, sizeof(int));
        game.NameOfPlayer1.resize(len1);
        fin2.read(&game.NameOfPlayer1[0], len1);


        fin2.read((char*)&len2, sizeof(int));
        game.NameOfPlayer2.resize(len2);
        fin2.read(&game.NameOfPlayer2[0], len2);

       game.board.resize(game.boardSize, vector<char>(game.boardSize));

        for (int i = 0; i < game.boardSize; i++) 
        {
            for (int j = 0; j < game.boardSize; j++) 
            {
                fin2.read((char*)&game.board[i][j], sizeof(char));
            }
        }
        fin2.close();

        //ClearScreen();

        int CntX = 0, CntO = 0;
        char a[50][50];
        for (int i = 0; i < game.boardSize; i++)
        {
            for (int j = 0; j < game.boardSize; j++)
            {
                a[i + 1][j + 1] = game.board[i][j];
                if (a[i + 1][j + 1] == 'X') CntX++;
                else
                    if (a[i + 1][j + 1] == 'O') CntO++;
            }
        }

        if (game.winner == 'q')
        {
            int TmpModeXO = game.modeXO;
            SetBackGround();
            ClearScreen();
            PrintNotOverGame();
            int MenuLoadGameChoice = GetLoadGameMenuChoice();
            if (MenuLoadGameChoice == 0)
            {
                ClearScreen();
                // tiep tuc choi 2 nguoi choi
                if (game.mode == 0)
                {
                    ClearScreen();
                    if (CntX == CntO)
                    {
                        // game.modeXO=0 la X di truoc
                        if (game.modeXO == 0)
                        {
                            // tiep tuc tu luot X
                            char ContinuePlayer = 'X';
                            ContinueTwoPlayer(game.boardSize, a, ContinuePlayer, game.modeXO, game.NameOfPlayer1, game.NameOfPlayer2);
                        }
                        else
                        {
                            // tiep tuc tu luot O
                            char ContinuePlayer = 'O';
                            ContinueTwoPlayer(game.boardSize, a, ContinuePlayer, game.modeXO, game.NameOfPlayer1, game.NameOfPlayer2);
                        }
                    }
                    else
                    if (CntX > CntO)
                    {
                           // tiep tuc tu luot cua O
                            char ContinuePlayer = 'O';
                            ContinueTwoPlayer(game.boardSize, a, ContinuePlayer, game.modeXO, game.NameOfPlayer1, game.NameOfPlayer2);

                    }
                    else
                    {
                            // tiep tuc tu luot cua X
                            char ContinuePlayer = 'X';
                            ContinueTwoPlayer(game.boardSize, a, ContinuePlayer, game.modeXO, game.NameOfPlayer1, game.NameOfPlayer2);

                    }

                }
                else
                if (game.mode == 1)
                {
                    ClearScreen();
                    // tiep tuc choi o che do choi voi may
                    if (CntX == CntO)
                    {
                        if (game.modeXO == 0)
                        {
                           
                            ContinuePlayWithBot(game.boardSize, a, 'O', 1, game.modeXO, game.NameOfPlayer1,game.modeLevel);
                            // nguoi choi di truoc va di quan X
                            // tiep tuc luot choi moi tu luot may voi quan O
                        }
                        else
                        {
                            ContinuePlayWithBot(game.boardSize, a, 'X', 1, game.modeXO, game.NameOfPlayer1,game.modeLevel);
                            //nguoi choi di truoc va di quan O
                            // tiep tuc luot choi moi tu luot may voi quan X
                        }

                    }
                    else
                    if (CntX > CntO)
                    {
                        if (game.modeXO == 0)
                        {
                            ContinuePlayWithBot(game.boardSize, a, 'O', 1, game.modeXO, game.NameOfPlayer1,game.modeLevel);
                            //tiep tuc tu luot choi cua may voi quan O
                        }
                        else
                        {
                            ContinuePlayWithBot(game.boardSize, a, 'X', 0, game.modeXO, game.NameOfPlayer1,game.modeLevel);
                            // tiep tuc tu luot choi cua nguoi choi voi quan X
                        }
                    }
                    else
                    if (CntX < CntO)
                    {
                        if (game.modeXO == 0)
                        {
                            ContinuePlayWithBot(game.boardSize, a, 'X', 0, game.modeXO, game.NameOfPlayer1,game.modeLevel);
                            // tiep tuc tu luot cua nguoi choi voi quan X
                        }
                        else
                        {
                            ContinuePlayWithBot(game.boardSize, a, 'X', 1, game.modeXO, game.NameOfPlayer1,game.modeLevel);
                            // tiep tuc tu luot cua may voi quan X
                        }
                    }
                }
            }
            else
            if (MenuLoadGameChoice==1)
            {
                ClearScreen();
                ShowTwoPlayerName(game.NameOfPlayer1, game.NameOfPlayer2, true, 0);
                int startx = 0, stary = 0;
                DrawBoardGame(game.boardSize, startx, stary);
                for (int i = 0; i < game.boardSize; i++)
                {
                    for (int j = 0; j < game.boardSize; j++)
                    {
                        DrawXO(startx, stary, i + 1, j + 1, a, false);
                    }
                }
                 CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            int h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

            int cellHeight = 1;

            int boardHeight = game.boardSize * cellHeight + (game.boardSize + 1);

            
            int StartY = (h - boardHeight) / 2;
            CenterText(isEnglish ? "Press any key to back to HOME ..." : "Nhan phim bat ky de tro ve man hinh chinh ...", StartY + boardHeight);
            char t = _getch();   
            }
        }

        else
        {
            ClearScreen();
            SetBackGround();
            if (game.winner == ' ')
            {
                PrintDraw();
            }
            else
            {
                PrintWin(game.winner);
            }
            if (game.mode == 0) ShowTwoPlayerName(game.NameOfPlayer1, game.NameOfPlayer2, true, 0);
            else
                if (game.mode == 1)
                    ShowPlayerName(game.NameOfPlayer1, 1, 1);
            int startx = 0, stary = 0;
            DrawBoardGame(game.boardSize, startx, stary);
            for (int i = 0; i < game.boardSize; i++)
            {
                for (int j = 0; j < game.boardSize; j++)
                {
                    DrawXO(startx, stary, i + 1, j + 1, a, false);
                }
            }
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            int h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

            int cellHeight = 1;

           
            int boardHeight = game.boardSize * cellHeight + (game.boardSize + 1);

            
            int StartY = (h - boardHeight) / 2;
            CenterText(isEnglish ? "Press any key to back to HOME ..." : "Nhan phim bat ky de tro ve man hinh chinh ...", StartY + boardHeight);
            char t = _getch();   
            
        }
        
    }
    else
    if (Choice == 1)
    {
        // Chon delete van dau
        ClearScreen();
        deleteSavedGame();
    }
    else
    if (Choice == 2)
    {
            //Chon back to home
        ClearScreen();
        return;
    }

}

void askToSaveGame(char winner, int n, int mode, char board[50][50], int modeXO, const string& Player1, const string& Player2, int modeLevel)
{
    ClearScreen();
    SetBackGround();
    PrintSaveGame();
    int SaveGameChoice = GetAskToSaveGameMenuChoice();
    if (SaveGameChoice == 0)
    {
        ClearScreen();
        //PrintSaveGame();
        SetBackGround();
        CenterText(isEnglish ? "Enter the match name to save: " : "Nhap ten van dau de luu: ", 10);
        string filename;
        cin >> filename;


        if (filename.find(".dat") == string::npos)
            filename += ".dat";


        // Ghi file ván đấu nhị phân
        ofstream fout(filename, ios::binary);
        if (!fout.is_open())
        {
            CenterText(isEnglish ? "Unable to open this game" : "Loi khi xem lai van dau", 13);
            Sleep(2000);
            //char tmp=_getch();
            //return false;
            return;
        }
        
        fout.write((char*)&n, sizeof(int));     // ghi kích thước bàn
        fout.write((char*)&mode, sizeof(int));  // ghi chế độ
        fout.write((char*)&winner, sizeof(char)); // ghi người thắng
        fout.write((char*)&modeXO, sizeof(int));//ghi lựa chọn XO ban đầu của player1
        fout.write((char*)&modeLevel, sizeof(int));

        int len1 = Player1.size();
        int len2 = Player2.size();


        fout.write((char*)&len1, sizeof(int));
        fout.write(Player1.c_str(), len1);


        fout.write((char*)&len2, sizeof(int));
        fout.write(Player2.c_str(), len2);


        // ghi toàn bộ bàn cờ thật
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                fout.write((char*)&board[i][j], sizeof(char));


        fout.close();


        // Ghi tên file vào danh sách
        ofstream listOut("saved_list.txt", ios::app);
        listOut << filename << endl;
        listOut.close();

        ClearScreen();
        SetBackGround();
        CenterText(isEnglish ? "Match saved to file " : "Tran dau duoc luu voi ten " + filename, 10);
        SetColor(3);
        Sleep(2000);
        ClearScreen();
        return;
       // CenterText("Press any key to return main menu ... ", 12);
        //char tmp=_getch();
        // return true;
    }
    else
        if (SaveGameChoice == 1)
        {
            ClearScreen();
            //char tmp=_getch();
            return;
        }
}

