#include "MenuGame.h"
#include "LogicGame.h"
#include "Display.h"
#include "SaveGame.h"
#include "SoundEffect.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

bool isEnglish = true;
bool isSoundOn = true;

void HandleSettings() 
{
    while (true) {
        string settingsMenu[3];

        if (isEnglish) {
            settingsMenu[0] = "LANGUAGE: " + string(isEnglish ? "ENGLISH" : "TIENG VIET");
            settingsMenu[1] = "SOUND: " + string(isSoundOn ? "ON" : "OFF");
            settingsMenu[2] = "BACK TO MAIN MENU";
        }
        else {
            settingsMenu[0] = "NGON NGU: " + string(isEnglish ? "ENGLISH" : "TIENG VIET");
            settingsMenu[1] = "AM THANH: " + string(isSoundOn ? "BAT" : "TAT");
            settingsMenu[2] = "QUAY LAI";
        }

        int selection = ShowMenu(settingsMenu, 3, 40, 3, 11, 1, 9);

        if (selection == 0) {
          
            isEnglish = !isEnglish;
            playClickMenuSound();
        }
        else if (selection == 1) {
            isSoundOn = !isSoundOn;

            if (!isSoundOn) StopBackGroundMusic();
            else ContinuePlayBackGroundMusic();

            playClickMenuSound();
        }
        else {
            playClickMenuSound();
            ClearScreen();
            break;
        }
    }
}

void ShowInstructions()
{
    ClearScreen();
    SetBackGround();

    PrintHowToPlay();

    int y = 10;
    SetColor(5);
    CenterText(isEnglish ? "CONTROLS" : "CAC PHIM NHAN", y++);
    SetColor(0);
    CenterText(isEnglish ? " Press w: Move Up" : "Nhan w: Di len", y++);
    CenterText(isEnglish ? " Press s: Move Down" : "Nhan s: Di xuong", y++);
    CenterText(isEnglish ? " Press a: Move Left" : "Nhan a: Sang trai", y++);
    CenterText(isEnglish ? " Press d: Move Right" : "Nhan d: Sang phai", y++);
    CenterText(isEnglish ? " Press ENTER: Place your piece" : "Nhan ENTER: Dat quan vao o", y++);
    CenterText(isEnglish ? " Press q: Quit the game during play" : "Nhan q: Thoat tro choi khi dang choi", y++);
    SetColor(5);
    CenterText(isEnglish ? "RULES" : "LUAT CHOI", y++);
    SetColor(0);
    CenterText(isEnglish ? "Connect 5 pieces (for 12x12) or 3 pieces (for 3x3) in a row, column, or diagonal to win" : "Co 5 quan (voi ban co 12x12) hoac 3 quan (voi ban co 3x3) cung mot dong, mot cot hoac mot duong cheo la thang", y++);
    CenterText(isEnglish ? "Draw occurs when no more moves are available" : "Hoa neu khong con nuoc di tren ban co", y++);
    SetColor(5);
    CenterText("GVHD: TRUONG TOAN THINH",y++);
    CenterText(isEnglish ? "ABOUT TEAM 5" : "VE NHOM 5", y++);
    SetColor(0);
    CenterText("1.DUONG THANH BINH", y++);
    CenterText("2.TRINH DANG NHAT MINH", y++);
    CenterText("3.HUYNH QUANG DUNG", y++);
    CenterText("4.DOAN TAN PHAT", y++);
    CenterText("5.NGUYEN DIEN DU", y++);
    CenterText("6.PHAM NGUYEN THANH DAT", y++);

    SetColor(1);
    CenterText(isEnglish ? "Press any key to back to HOME ... " : "Nhan phim bat ky de quay ve man hinh chinh", y + 2);

    char s = _getch();
}

void StartModeTwoPlayer(char Board[][50], int& n, char& CurrentPlayer)
{
    SetBackGround();
    int ModeSize, ModeXO, EndGameChoice;
    bool IsCurrent = true, IsEndGame = true;
    int x = 1, y = 1;
    ClearScreen();
    PrintSizeGame();
    ModeSize = GetSizeMenuChoice2();
    if (ModeSize == 2)
    {
        ClearScreen();
        return;
    }
    else
        if (ModeSize == 0) n = 3;
        else
            if (ModeSize == 1) n = 12;
    ClearScreen();
    SetConsoleOutputCP(437);
    system("Color F0");
    PrintSelectionXO();
    ModeXO = GetPieceMenuChoice();
    if (ModeXO == 0)
    {
        CurrentPlayer = 'X';
        IsCurrent = true;
    }
    else
        if (ModeXO == 1)
        {
            CurrentPlayer = 'O';
            IsCurrent = false;
        }
        else return;

    ClearScreen();
    string name1, name2;
    EnterTwoPlayerName(name1, name2);
    ClearScreen();
    ResetBoardGame(Board, n);
    int StartX, StartY;
    DrawBoardGame(n, StartX, StartY);

    for (int i1 = 1;i1 <= n;i1++)
    {
        for (int j1 = 1;j1 <= n;j1++)
            DrawXO(StartX, StartY, i1, j1, Board, false);
    }

    DrawXO(StartX, StartY, x, y, Board, true);
    while (IsEndGame)
    {
        ShowTwoPlayerName(name1, name2, IsCurrent, ModeXO);
        char key = _getch();
        int PreX = x, PreY = y;
        if (key == 'w' && x > 1) x--;
        else if (key == 'a' && y > 1) y--;
        else if (key == 's' && x < n) x++;
        else if (key == 'd' && y < n) y++;
        DrawXO(StartX, StartY, PreX, PreY, Board, false);
        // highlight o moi
        DrawXO(StartX, StartY, x, y, Board, true);

        //playClickSound();

        if (key == 13 && Board[x][y] == ' ')
        {
            playClickSound();

            if (IsCurrent)
            {
                CurrentPlayer = 'X';
                IsCurrent = false;

            }
            else
                if (!IsCurrent)
                {
                    CurrentPlayer = 'O';
                    IsCurrent = true;

                }

            Board[x][y] = CurrentPlayer;
            DrawXO(StartX, StartY, x, y, Board, false);
            if (CheckWin2(CurrentPlayer, x, y, Board, n) != -1)
            {
                int Tmp = CheckWin2(CurrentPlayer, x, y, Board, n);

                EffectWin(Tmp, x, y, CurrentPlayer, Board, n, StartX, StartY);

                ClearScreen();
                PrintWin(CurrentPlayer);
                ContinuePlayBackGroundMusic();
                EndGameChoice = GetPlayAgainMenuChoice();
                if (EndGameChoice == 0)
                {
                    ClearScreen();
                    StartModeTwoPlayer(Board, n, CurrentPlayer);
                    return;
                }
                else
                    if (EndGameChoice == 1)
                    {
                        ClearScreen();
                        PrintSaveGame();
                        askToSaveGame(CurrentPlayer, n, 0, Board, ModeXO, name1, name2, 0);
                        IsEndGame = false;
                    }
                    else
                    {
                        ClearScreen();
                        IsEndGame = false;
                    }

            }
            else
                if (CheckDraw(Board, n))
                {
                    DrawXO(StartX, StartY, x, y, Board, false);
                    ClearScreen();
                    PrintDraw();
                    ContinuePlayBackGroundMusic();
                    EndGameChoice = GetPlayAgainMenuChoice();
                    if (EndGameChoice == 0)
                    {
                        ClearScreen();
                        StartModeTwoPlayer(Board, n, CurrentPlayer);
                        return;
                    }
                    else
                        if (EndGameChoice == 1)
                        {
                            ClearScreen();
                            PrintSaveGame();
                            askToSaveGame(' ', n, 0, Board, ModeXO, name1, name2, 0);
                            IsEndGame = false;
                        }
                        else
                        {
                            ClearScreen();
                            IsEndGame = false;
                        }
                }
        }
        else
            if (key == 'q')
            {
                SetConsoleOutputCP(437);
                system("Color F0");
                ClearScreen();
                PrintSaveGame();
                // Voi ham startmodetwoplayer thi dat level=0 cung khong anh huong gi het
                askToSaveGame('q', n, 0, Board, ModeXO, name1, name2, 0);
                IsEndGame = false;
            }
    }
}

void StartModePlayWithBot(char Board[][50], int& n, char& HumanPlayer, char& BotPlayer)
{
    SetBackGround();
    int ModeSize, ModeXO, EndGameChoice;
    bool IsCurrent = true, IsEndGame = true;
    ClearScreen();
    PrintSizeGame();
    ModeSize = GetSizeMenuChoice2();
    if (ModeSize == 2)
    {
        ClearScreen();
        return;
    }
    else
        if (ModeSize == 0) n = 3;
        else n = 12;
    int ModeLevel = 0;
    ClearScreen();
    PrintLevelGame();
    if (n == 3)
    {
        ModeLevel = GetLevel3x3MenuChoice();
        if (ModeLevel == 2) return;
    }
    else
    {
        ModeLevel = GetLevel12x12MenuChoice();
        if (ModeLevel == 3) return;
    }
    ClearScreen();
    PrintSelectionXO();
    ModeXO = GetPieceMenuChoice();
    if (ModeXO == 0)
    {
        HumanPlayer = 'X';
        BotPlayer = 'O';
    }
    else
        if (ModeXO == 1)
        {
            HumanPlayer = 'O';
            BotPlayer = 'X';
        }
        else return;

    IsEndGame = true;
    int x = 1, y = 1;
    Coord Current;
    int cnt = 0;
    ClearScreen();
    string name;
    EnterPlayerName(name);
    ClearScreen();
    ResetBoardGame(Board, n);
    int StartX, StartY;
    DrawBoardGame(n, StartX, StartY);

    for (int i1 = 1;i1 <= n;i1++)
    {
        for (int j1 = 1;j1 <= n;j1++)
            DrawXO(StartX, StartY, i1, j1, Board, false);
    }

    DrawXO(StartX, StartY, x, y, Board, true);

    while (IsEndGame)
    {
        ShowPlayerName(name, cnt, ModeXO);
        char key = _getch();
        int PreX = x, PreY = y;
        if (key == 'w' && x > 1) x--;
        else if (key == 'a' && y > 1) y--;
        else if (key == 's' && x < n) x++;
        else if (key == 'd' && y < n) y++;

        DrawXO(StartX, StartY, PreX, PreY, Board, false);
        // highlight o moi
        DrawXO(StartX, StartY, x, y, Board, true);

        if (key == 13 && Board[x][y] == ' ')
        {
            playClickSound();
            cnt++;
            Board[x][y] = HumanPlayer;
            int preX = x, preY = y;
            DrawXO(StartX, StartY, x, y, Board, false);

            //Check result
            if (n == 12)
            {
                if (CheckWin2(HumanPlayer, preX, preY, Board, n) != -1)
                {
                    int Tmp = CheckWin2(HumanPlayer, preX, preY, Board, n);

                    EffectWin(Tmp, preX, preY, HumanPlayer, Board, n, StartX, StartY);

                    ClearScreen();
                    PrintWin(HumanPlayer);
                    ContinuePlayBackGroundMusic();

                    EndGameChoice = GetPlayAgainMenuChoice();
                    // EndGameChoice = ShowEndGameMenu(Board, HumanPlayer);
                    if (EndGameChoice == 0)
                    {
                        ClearScreen();
                        StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                        return;
                    }
                    else
                        if (EndGameChoice == 1)
                        {
                            ClearScreen();
                            PrintSaveGame();
                            askToSaveGame(HumanPlayer, n, 1, Board, ModeXO, name, "SUPPERBOT", ModeLevel);
                            IsEndGame = false;
                        }
                        else IsEndGame = false;

                }
                else
                    if (CheckDraw(Board, n))
                    {
                        //DrawBoard(x, y, Board, n);
                        DrawXO(StartX, StartY, x, y, Board, false);
                        //DelayTime();
                        ClearScreen();
                        PrintDraw();
                        ContinuePlayBackGroundMusic();

                        EndGameChoice = GetPlayAgainMenuChoice();
                        //EndGameChoice = ShowEndGameMenu(Board, 'H');
                        if (EndGameChoice == 0)
                        {
                            ClearScreen();
                            StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                            return;
                        }
                        else
                            if (EndGameChoice == 1)
                            {
                                ClearScreen();
                                PrintSaveGame();
                                askToSaveGame(' ', n, 1, Board, ModeXO, name, "SUPPERBOT", ModeLevel);
                                IsEndGame = false;
                            }
                            else
                            {
                                ClearScreen();
                                IsEndGame = false;
                            }
                    }
            }
            else
                if (n == 3)
                {
                    if (CheckMinimaxWin(Board) != ' ')
                    {
                        EffectWin(CheckTypeWin(Board), x, y, CheckMinimaxWin(Board), Board, n, StartX, StartY);

                        ClearScreen();
                        PrintWin(CheckMinimaxWin(Board));
                        ContinuePlayBackGroundMusic();
                        EndGameChoice = GetPlayAgainMenuChoice();
                        //EndGameChoice = ShowEndGameMenu(Board, CheckMinimaxWin(Board));
                        if (EndGameChoice == 0)
                        {
                            StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                            return;
                        }
                        else
                            if (EndGameChoice == 1)
                            {
                                PrintSaveGame();
                                askToSaveGame(' ', n, 1, Board, ModeXO, name, "SUPPERBOT", ModeLevel);
                                IsEndGame = false;
                            }
                            else
                            {
                                ClearScreen();
                                IsEndGame = false;
                            }
                    }
                    else
                        if (IsMinimaxBoardFull(Board))
                        {
                            Sleep(2000);
                            ClearScreen();
                            PrintDraw();
                            EndGameChoice = GetPlayAgainMenuChoice();
                            ContinuePlayBackGroundMusic();
                            //EndGameChoice = ShowEndGameMenu(Board, 'H');
                            if (EndGameChoice == 0)
                            {
                                StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                                return;
                            }
                            else
                                if (EndGameChoice == 1)
                                {
                                    ClearScreen();
                                    PrintSaveGame();
                                    askToSaveGame(' ', n, 1, Board, ModeXO, name, "SUPPERBOT", ModeLevel);
                                    IsEndGame = false;
                                }
                                else
                                {
                                    ClearScreen();
                                    IsEndGame = false;
                                }
                        }
                }

            Coord Best = BotTurn(Board, n, ModeXO, HumanPlayer, x, y, ModeLevel);


            Board[Best.x][Best.y] = BotPlayer;
            x = Best.x; y = Best.y;
            playClickSound();

            DrawXO(StartX, StartY, Best.x, Best.y, Board, false);

            if (n == 12)
            {

                if (CheckWin2(BotPlayer, x, y, Board, n) != -1)
                {
                    int Tmp = CheckWin2(BotPlayer, x, y, Board, n);

                    EffectWin(Tmp, x, y, BotPlayer, Board, n, StartX, StartY);

                    ClearScreen();
                    PrintWin(BotPlayer);
                    ContinuePlayBackGroundMusic();

                    EndGameChoice = GetPlayAgainMenuChoice();

                    if (EndGameChoice == 0)
                    {
                        ClearScreen();
                        StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                        return;
                    }
                    else
                        if (EndGameChoice == 1)
                        {
                            ClearScreen();
                            PrintSaveGame();
                            askToSaveGame(BotPlayer, n, 1, Board, ModeXO, name, "SUPPERBOT", ModeLevel);
                            IsEndGame = false;
                        }
                        else
                        {
                            ClearScreen();
                            IsEndGame = false;
                        }
                }
                else
                    if (CheckDraw(Board, n))
                    {

                        DrawXO(StartX, StartY, x, y, Board, false);

                        Sleep(3000);
                        ClearScreen();
                        PrintDraw();
                        ContinuePlayBackGroundMusic();
                        EndGameChoice = GetPlayAgainMenuChoice();

                        if (EndGameChoice == 0)
                        {
                            ClearScreen();
                            StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                            return;
                        }
                        else
                            if (EndGameChoice == 1)
                            {
                                ClearScreen();
                                PrintSaveGame();
                                askToSaveGame(' ', n, 1, Board, ModeXO, name, "SUPPERBOT", ModeLevel);
                                IsEndGame = false;
                            }
                            else
                            {
                                ClearScreen();
                                IsEndGame = false;
                            }
                    }
            }
            else
                if (n == 3)
                {
                    if (CheckMinimaxWin(Board) != ' ')
                    {


                        EffectWin(CheckTypeWin(Board), x, y, CheckMinimaxWin(Board), Board, n, StartX, StartY);

                        ClearScreen();
                        PrintWin(CheckMinimaxWin(Board));
                        ContinuePlayBackGroundMusic();
                        EndGameChoice = GetPlayAgainMenuChoice();
                        //EndGameChoice = ShowEndGameMenu(Board, CheckMinimaxWin(Board));
                        if (EndGameChoice == 0)
                        {
                            StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                            return;
                        }
                        else
                            if (EndGameChoice == 1)
                            {
                                ClearScreen();
                                PrintSaveGame();
                                askToSaveGame(' ', n, 1, Board, ModeXO, name, "SUPPERBOT", ModeLevel);
                                IsEndGame = false;
                            }
                            else
                            {
                                ClearScreen();
                                IsEndGame = false;
                            }
                    }
                    else
                        if (IsMinimaxBoardFull(Board))
                        {
                            Sleep(3000);
                            ClearScreen();
                            PrintDraw();
                            ContinuePlayBackGroundMusic();
                            EndGameChoice = GetPlayAgainMenuChoice();
                            //EndGameChoice = ShowEndGameMenu(Board, 'H');
                            if (EndGameChoice == 0)
                            {
                                StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                                return;
                            }
                            else
                                if (EndGameChoice == 1)
                                {
                                    PrintSaveGame();
                                    askToSaveGame(' ', n, 1, Board, ModeXO, name, "SUPPERBOT", ModeLevel);
                                    IsEndGame = false;
                                }
                                else
                                {
                                    ClearScreen();
                                    IsEndGame = false;
                                }
                        }
                }
        }
        else
            if (key == 'q')
            {
                /*SetConsoleOutputCP(437);
                system("Color F0"); */
                ClearScreen();
                PrintSaveGame();
                askToSaveGame('q', n, 1, Board, ModeXO, name, "SUPPERBOT", ModeLevel);
                IsEndGame = false;
            }
    }
}

int ProcessMainMenu(char Board[][50], int& n, char& CurrentPlayer, char& HumanPlayer, char& BotPlayer)
{
    ClearScreen();
    SetBackGround();
    PrintCaroGame();
    int MainChoice, ModeChoice;
    MainChoice = GetMainMenuChoice2();
    if (MainChoice == 4) { // EXIT
        ClearScreen();
        SetColor(6);
        CenterText(isEnglish ? "YOU HAVE EXITED. SEE YOU NEXT TIME!" : "BAN DA THOAT. HEN GAP LAI!", 12);
        return 4;
    }
    else if (MainChoice == 3) 
    { 
        ClearScreen();
        SetBackGround();
        HandleSettings();
        return 3;
    }
    else
        if (MainChoice == 1)
        {
            ShowInstructions();
            ClearScreen();
            return 1;
        }
        else
            if (MainChoice == 0)
            {
                ClearScreen();
                PrintModeGame();
                ModeChoice = GetModeMenuChoice2();
                if (ModeChoice == 2)
                {
                    ClearScreen();
                    return 0;
                }

                else
                    if (ModeChoice == 0)
                    {
                        StartModeTwoPlayer(Board, n, CurrentPlayer);
                    }
                    else
                        if (ModeChoice == 1)
                        {
                            StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                        }
            }
            else
                if (MainChoice == 2)
                {
                    ClearScreen();
                    PrintSaveGame();
                    showSavedGames();
                    return 2;
                }
    return 0;
}

//ModeGame de biet o che do choi nao
void EnterTwoPlayerName(string& Player1, string& Player2)
{
    SetConsoleOutputCP(437);
    system("Color F0");
    ClearScreen();
    //Che do hai nguoi choi
    CenterText(isEnglish ? "Enter the name of the first player: " : "Nhap ten nguoi choi thu nhat: ", 8);
    cin >> Player1;
    CenterText(isEnglish ? "Enter the name of the second player: ": "Nhap ten nguoi choi thu hai: ", 10);
    cin >> Player2;
}

void EnterPlayerName(string& PlayerName)
{
    SetConsoleOutputCP(437);
    system("Color F0");
    ClearScreen();
    CenterText(isEnglish ? "Enter the name of player: " : "Nhap ten nguoi choi: ", 8);
    cin >> PlayerName;
}

void ShowPlayerName(string PlayerName, int Dem, int First)
{
    //SetConsoleOutputCP(437);
    //system("Color F0");
    char Player1, Player2;
    bool TmpCheck;
    if (First == 0)
    {
        Player1 = 'X';
        Player2 = 'O';
        if (Dem % 2 == 1) TmpCheck = true;
        else TmpCheck = false;
    }
    else
    {
        Player1 = 'O';
        Player2 = 'X';
        if (Dem % 2 == 0) TmpCheck = true;
        else TmpCheck = false;
    }

    int Size1 = 15, Size2 = 15;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    SetColor(0);
    GoToXY(1, 1);

    cout << (unsigned char)218;
    for (int i = 0;i < Size1;i++) cout << (unsigned char)196;
    cout << (unsigned char)191;
    GoToXY(1, 2);
    cout << (unsigned char)179;
    GoToXY(5, 2);
    cout << PlayerName;
    GoToXY(Size1 + 2, 2);
    cout << (unsigned char)179;

    for (int u = 3;u <= 10;u++)
    {
        GoToXY(1, u);
        cout << (unsigned char)179;
    }
    if (TmpCheck) SetColor(2);
    else SetColor(0);

    if (Player1 == 'X')
    {
        DrawX(4, 4);
    }
    else
        if (Player1 == 'O')
        {
            DrawO(4, 4);
        }
    SetColor(0);
    for (int u = 3;u <= 10;u++)
    {
        GoToXY(Size1 + 2, u);
        cout << (unsigned char)179;
    }

    GoToXY(1, 11);
    cout << (unsigned char)192;
    for (int i = 0;i < Size1;i++) cout << (unsigned char)196;
    cout << (unsigned char)217;


    SetColor(0);

    GoToXY(width - Size2 - 3, 1);
    cout << (unsigned char)218;
    for (int i = 0;i < Size2;i++) cout << (unsigned char)196;
    cout << (unsigned char)191;

    GoToXY(width - Size2 - 3, 2);
    cout << (unsigned char)179;
    GoToXY(width - Size2 - 1, 2);
    cout << " SUPPER BOT ";
    GoToXY(width - 2, 2);
    cout << (unsigned char)179;

    for (int u = 3;u <= 10;u++)
    {
        GoToXY(width - Size2 - 3, u);
        cout << (unsigned char)179;
    }

    if (!TmpCheck) SetColor(2);
    else SetColor(0);

    if (Player2 == 'O')
    {
        DrawO(width - 16 + 1, 4);
    }
    else
        if (Player2 == 'X')
        {
            DrawX(width - 16 + 1, 4);
        }

    SetColor(0);

    for (int u = 3;u <= 10;u++)
    {
        GoToXY(width - 2, u);
        cout << (unsigned char)179;
    }

    GoToXY(width - Size2 - 3, 11);
    cout << (unsigned char)192;
    for (int i = 0;i < Size2;i++) cout << (unsigned char)196;
    cout << (unsigned char)217;
}

void ShowTwoPlayerName(string NamePlayer1, string NamePlayer2, bool Check, int First)
{
    char Player1, Player2;
    bool TmpCheck;
    if (First == 0)
    {
        Player1 = 'X';
        Player2 = 'O';
        if (Check) TmpCheck = true;
        else TmpCheck = false;
    }
    else
    {
        Player1 = 'O';
        Player2 = 'X';
        if (!Check) TmpCheck = true;
        else TmpCheck = false;
    }

    int Size1 = 15, Size2 = 15;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    SetColor(0);
    GoToXY(1, 1);

    cout << (unsigned char)218;
    for (int i = 0;i < Size1;i++) cout << (unsigned char)196;
    cout << (unsigned char)191;
    GoToXY(1, 2);
    cout << (unsigned char)179;
    GoToXY(7, 2);
    cout << NamePlayer1;
    GoToXY(Size1 + 2, 2);
    cout << (unsigned char)179;

    for (int u = 3;u <= 10;u++)
    {
        GoToXY(1, u);
        cout << (unsigned char)179;
    }
    if (TmpCheck) SetColor(2);
    else SetColor(0);

    if (Player1 == 'X')
    {
        DrawX(4, 4);
    }
    else
        if (Player1 == 'O')
        {
            DrawO(4, 4);
        }
    SetColor(0);
    for (int u = 3;u <= 10;u++)
    {
        GoToXY(Size1 + 2, u);
        cout << (unsigned char)179;
    }

    GoToXY(1, 11);
    cout << (unsigned char)192;
    for (int i = 0;i < Size1;i++) cout << (unsigned char)196;
    cout << (unsigned char)217;

    SetColor(0);

    GoToXY(width - Size2 - 3, 1);
    cout << (unsigned char)218;
    for (int i = 0;i < Size2;i++) cout << (unsigned char)196;
    cout << (unsigned char)191;

    GoToXY(width - Size2 - 3, 2);
    cout << (unsigned char)179;
    GoToXY(width - Size2 + 2, 2);
    cout << NamePlayer2;
    GoToXY(width - 2, 2);
    cout << (unsigned char)179;

    for (int u = 3;u <= 10;u++)
    {
        GoToXY(width - Size2 - 3, u);
        cout << (unsigned char)179;
    }

    if (!TmpCheck) SetColor(2);
    else SetColor(0);

    if (Player2 == 'O')
    {
        DrawO(width - 16 + 1, 4);
    }
    else
        if (Player2 == 'X')
        {
            DrawX(width - 16 + 1, 4);
        }

    SetColor(0);

    for (int u = 3;u <= 10;u++)
    {
        GoToXY(width - 2, u);
        cout << (unsigned char)179;
    }

    GoToXY(width - Size2 - 3, 11);
    cout << (unsigned char)192;
    for (int i = 0;i < Size2;i++) cout << (unsigned char)196;
    cout << (unsigned char)217;
}

void ContinueTwoPlayer(int n, char Board[][50], char ContinuePlayer, int modeXO, string P1, string P2)
{
    ClearScreen();
    char CurrentPlayer;
    bool IsCurrent;

    if (ContinuePlayer == 'X')
    {
        CurrentPlayer = 'X';
        IsCurrent = true;
    }
    else
    {
        CurrentPlayer = 'O';
        IsCurrent = false;
    }

    int x = 1, y = 1;
    int StartX, StartY, EndGameChoice;
    bool IsEndGame = true;
    DrawBoardGame(n, StartX, StartY);

    for (int i1 = 1;i1 <= n;i1++)
    {
        for (int j1 = 1;j1 <= n;j1++)
            DrawXO(StartX, StartY, i1, j1, Board, false);
    }

    DrawXO(StartX, StartY, x, y, Board, true);
    while (IsEndGame)
    {
        ShowTwoPlayerName(P1, P2, IsCurrent, modeXO);
        char key = _getch();
        int PreX = x, PreY = y;
        if (key == 'w' && x > 1) x--;
        else if (key == 'a' && y > 1) y--;
        else if (key == 's' && x < n) x++;
        else if (key == 'd' && y < n) y++;
        DrawXO(StartX, StartY, PreX, PreY, Board, false);
        // highlight o moi
        DrawXO(StartX, StartY, x, y, Board, true);

        if (key == 13 && Board[x][y] == ' ')
        {
            playClickSound();
            if (IsCurrent)
            {
                CurrentPlayer = 'X';
                IsCurrent = false;

            }
            else
                if (!IsCurrent)
                {
                    CurrentPlayer = 'O';
                    IsCurrent = true;

                }

            Board[x][y] = CurrentPlayer;
            DrawXO(StartX, StartY, x, y, Board, false);
            if (CheckWin2(CurrentPlayer, x, y, Board, n) != -1)
            {
                int Tmp = CheckWin2(CurrentPlayer, x, y, Board, n);
                EffectWin(Tmp, x, y, CurrentPlayer, Board, n, StartX, StartY);

                ClearScreen();

                PrintWin(CurrentPlayer);
                ContinuePlayBackGroundMusic();
                EndGameChoice = GetPlayAgainMenuChoice();

                if (EndGameChoice == 0)
                {
                    ClearScreen();
                    StartModeTwoPlayer(Board, n, CurrentPlayer);
                    return;
                }
                else
                    if (EndGameChoice == 1)
                    {
                        ClearScreen();
                        PrintSaveGame();
                        askToSaveGame(CurrentPlayer, n, 0, Board, modeXO, P1, P2, 0);
                        ClearScreen();
                        IsEndGame = false;
                    }
                    else IsEndGame = false;

            }
            else
                if (CheckDraw(Board, n))
                {
                    DrawXO(StartX, StartY, x, y, Board, false);
                    ClearScreen();
                    PrintDraw();

                    ContinuePlayBackGroundMusic();
                    EndGameChoice = GetPlayAgainMenuChoice();
                    if (EndGameChoice == 0)
                    {
                        ClearScreen();
                        StartModeTwoPlayer(Board, n, CurrentPlayer);
                        return;
                    }
                    else
                        if (EndGameChoice == 1)
                        {
                            //(char winner, int n, int mode, char board[50][50], int modeXO, const string& Player1, const string& Player2)
                            ClearScreen();
                            PrintSaveGame();
                            askToSaveGame(' ', n, 0, Board, modeXO, P1, P2, 0);
                            ClearScreen();
                            IsEndGame = false;
                        }
                        else IsEndGame = false;
                }
        }
        else
            if (key == 'q')
            {
                SetConsoleOutputCP(437);
                system("Color F0");
                ClearScreen();
                PrintSaveGame();
                askToSaveGame('q', n, 0, Board, modeXO, P1, P2, 0);
                IsEndGame = false;
            }
    }
}

void ContinuePlayWithBot(int n, char Board[][50], char ContinuePlayer, int NextTurn, int ModeXO, string P, int level)
{
    char HumanPlayer, BotPlayer;
    if (NextTurn == 0)
    {
        // tiep tuc tu luot cua nguoi choi
        if (ContinuePlayer == 'X')
        {
            HumanPlayer = 'X';
            BotPlayer = 'O';
        }
        else
        {
            HumanPlayer = 'O';
            BotPlayer = 'X';
        }
    }
    else
    {
        // tiep tuc tu luot cua may 
        if (ContinuePlayer == 'X')
        {
            BotPlayer = 'X';
            HumanPlayer = 'O';
        }
        else
        {
            BotPlayer = 'O';
            HumanPlayer = 'X';
        }
    }



    bool IsEndGame = true;
    int x = 1, y = 1;
    //bool Check;
    int cnt = 0;
    ClearScreen();
    int StartX, StartY;
    int EndGameChoice;
    DrawBoardGame(n, StartX, StartY);

    for (int i1 = 1;i1 <= n;i1++)
    {
        for (int j1 = 1;j1 <= n;j1++)
            DrawXO(StartX, StartY, i1, j1, Board, false);
    }

    DrawXO(StartX, StartY, x, y, Board, true);

    while (IsEndGame)
    {
        ShowPlayerName(P, cnt, ModeXO);
        char key = _getch();
        int PreX = x, PreY = y;
        if (key == 'w' && x > 1) x--;
        else if (key == 'a' && y > 1) y--;
        else if (key == 's' && x < n) x++;
        else if (key == 'd' && y < n) y++;

        DrawXO(StartX, StartY, PreX, PreY, Board, false);
        // highlight o moi
        DrawXO(StartX, StartY, x, y, Board, true);

        if (key == 13 && Board[x][y] == ' ')
        {
            playClickSound();
            cnt++;
            Board[x][y] = HumanPlayer;
            int preX = x, preY = y;
            DrawXO(StartX, StartY, x, y, Board, false);

            //Check result
            if (n == 12)
            {
                if (CheckWin2(HumanPlayer, preX, preY, Board, n) != -1)
                {
                    int Tmp = CheckWin2(HumanPlayer, preX, preY, Board, n);

                    EffectWin(Tmp, preX, preY, HumanPlayer, Board, n, StartX, StartY);

                    ClearScreen();
                    PrintWin(HumanPlayer);
                    ContinuePlayBackGroundMusic();
                    EndGameChoice = GetPlayAgainMenuChoice();
                    // EndGameChoice = ShowEndGameMenu(Board, HumanPlayer);
                    if (EndGameChoice == 0)
                    {
                        ClearScreen();
                        StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                        return;
                    }
                    else
                        if (EndGameChoice == 1)
                        {
                            ClearScreen();
                            PrintSaveGame();
                            askToSaveGame(HumanPlayer, n, 1, Board, ModeXO, P, "SUPPERBOT", level);
                            IsEndGame = false;
                        }
                        else IsEndGame = false;

                }
                else
                    if (CheckDraw(Board, n))
                    {
                        //DrawBoard(x, y, Board, n);
                        DrawXO(StartX, StartY, x, y, Board, false);
                        //DelayTime();
                        ClearScreen();
                        PrintDraw();
                        ContinuePlayBackGroundMusic();
                        EndGameChoice = GetPlayAgainMenuChoice();

                        if (EndGameChoice == 0)
                        {
                            ClearScreen();
                            StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                            return;
                        }
                        else
                            if (EndGameChoice == 1)
                            {
                                ClearScreen();
                                PrintSaveGame();
                                askToSaveGame(' ', n, 1, Board, ModeXO, P, "SUPPERBOT", level);
                                IsEndGame = false;
                            }
                            else IsEndGame = false;
                    }
            }
            else
                if (n == 3)
                {
                    if (CheckMinimaxWin(Board) != ' ')
                    {


                        EffectWin(CheckTypeWin(Board), x, y, CheckMinimaxWin(Board), Board, n, StartX, StartY);
                        Sleep(4000);
                        ClearScreen();
                        PrintWin(CheckMinimaxWin(Board));
                        ContinuePlayBackGroundMusic();
                        EndGameChoice = GetPlayAgainMenuChoice();
                        //EndGameChoice = ShowEndGameMenu(Board, CheckMinimaxWin(Board));
                        if (EndGameChoice == 0)
                        {
                            StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                            return;
                        }
                        else
                            if (EndGameChoice == 1)
                            {
                                PrintSaveGame();
                                askToSaveGame(' ', n, 1, Board, ModeXO, P, "SUPPERBOT", level);
                                IsEndGame = false;
                            }
                            else IsEndGame = false;
                    }
                    else
                        if (IsMinimaxBoardFull(Board))
                        {
                            Sleep(3000);
                            ClearScreen();
                            PrintDraw();
                            ContinuePlayBackGroundMusic();
                            EndGameChoice = GetPlayAgainMenuChoice();
                            //EndGameChoice = ShowEndGameMenu(Board, 'H');
                            if (EndGameChoice == 0)
                            {
                                StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                                return;
                            }
                            else
                                if (EndGameChoice == 1)
                                {
                                    ClearScreen();
                                    PrintSaveGame();
                                    askToSaveGame(' ', n, 1, Board, ModeXO, P, "SUPPERBOT", level);
                                    IsEndGame = false;
                                }
                                else IsEndGame = false;
                        }
                }

            Coord Best = BotTurn(Board, n, ModeXO, HumanPlayer, x, y, level);
            //cout << "ModeLevel la: " << ModeLevel;

           //cout << Best.x << " " << Best.y << endl;
            Board[Best.x][Best.y] = BotPlayer;
            x = Best.x; y = Best.y;
            playClickSound();

            DrawXO(StartX, StartY, Best.x, Best.y, Board, false);

            if (n == 12)
            {

                if (CheckWin2(BotPlayer, x, y, Board, n) != -1)
                {
                    int Tmp = CheckWin2(BotPlayer, x, y, Board, n);

                    EffectWin(Tmp, x, y, BotPlayer, Board, n, StartX, StartY);

                    Sleep(4000);
                    // DrawXO(StartX, StartY, x, y, Board, false);
                     //DrawBoard(x, y, Board, n);
                    // DelayTime();
                    ClearScreen();
                    PrintWin(BotPlayer);
                    ContinuePlayBackGroundMusic();
                    EndGameChoice = GetPlayAgainMenuChoice();
                    //EndGameChoice = ShowEndGameMenu(Board, BotPlayer);    
                    if (EndGameChoice == 0)
                    {
                        ClearScreen();
                        StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                        return;
                    }
                    else
                        if (EndGameChoice == 1)
                        {
                            ClearScreen();
                            PrintSaveGame();
                            askToSaveGame(BotPlayer, n, 1, Board, ModeXO, P, "SUPPERBOT", level);
                            IsEndGame = false;
                        }
                        else IsEndGame = false;
                }
                else
                    if (CheckDraw(Board, n))
                    {
                        //DrawBoard(x, y, Board, n);
                        DrawXO(StartX, StartY, x, y, Board, false);
                        //DelayTime();
                        Sleep(3000);
                        ClearScreen();
                        PrintDraw();
                        ContinuePlayBackGroundMusic();
                        EndGameChoice = GetPlayAgainMenuChoice();
                        //EndGameChoice = ShowEndGameMenu(Board, 'H');
                        if (EndGameChoice == 0)
                        {
                            ClearScreen();
                            StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                            return;
                        }
                        else
                            if (EndGameChoice == 1)
                            {
                                ClearScreen();
                                PrintSaveGame();
                                askToSaveGame(' ', n, 1, Board, ModeXO, P, "SUPPERBOT", level);
                                IsEndGame = false;
                            }
                            else IsEndGame = false;
                    }
            }
            else
                if (n == 3)
                {
                    if (CheckMinimaxWin(Board) != ' ')
                    {
                        //DrawBoard(x, y, Board, n);
                        //DrawXO(StartX, StartY, x, y, Board, false);
                       // DelayTime();

                        //int Tmp = CheckTypeWin(Board);

                        //cout << Tmp << endl;

                        //system("pause");

                        EffectWin(CheckTypeWin(Board), x, y, CheckMinimaxWin(Board), Board, n, StartX, StartY);
                        Sleep(3000);
                        ClearScreen();
                        PrintWin(CheckMinimaxWin(Board));
                        ContinuePlayBackGroundMusic();
                        EndGameChoice = GetPlayAgainMenuChoice();
                        //EndGameChoice = ShowEndGameMenu(Board, CheckMinimaxWin(Board));
                        if (EndGameChoice == 0)
                        {
                            StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                            return;
                        }
                        else
                            if (EndGameChoice == 1)
                            {
                                ClearScreen();
                                PrintSaveGame();
                                askToSaveGame(' ', n, 1, Board, ModeXO, P, "SUPPERBOT", level);
                                IsEndGame = false;
                            }
                            else IsEndGame = false;
                    }
                    else
                        if (IsMinimaxBoardFull(Board))
                        {
                            Sleep(3000);
                            ClearScreen();
                            PrintDraw();
                            ContinuePlayBackGroundMusic();
                            EndGameChoice = GetPlayAgainMenuChoice();
                            //EndGameChoice = ShowEndGameMenu(Board, 'H');
                            if (EndGameChoice == 0)
                            {
                                StartModePlayWithBot(Board, n, HumanPlayer, BotPlayer);
                                return;
                            }
                            else
                                if (EndGameChoice == 1)
                                {
                                    PrintSaveGame();
                                    askToSaveGame(' ', n, 1, Board, ModeXO, P, "SUPPERBOT", level);
                                    IsEndGame = false;
                                }
                                else IsEndGame = false;
                        }
                }
        }
        else
            if (key == 'q')
            {
                /*SetConsoleOutputCP(437);
                system("Color F0"); */
                ClearScreen();
                PrintSaveGame();
                askToSaveGame('q', n, 1, Board, ModeXO, P, "SUPPERBOT", level);
                IsEndGame = false;
            }
    }
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void SetColor2(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void box(int x, int y, int w, int h, int t_color, int b_color, const string& nd)
{
    // ---- GUARD ----
    if (w < 2 || h < 1) return;

    // ---- FILL BACKGROUND ----
    SetColor2(b_color << 4);
    for (int iy = y + 1; iy <= y + h - 1; iy++) {
        for (int ix = x + 1; ix <= x + w - 1; ix++) {
            GoToXY(ix, iy);
            cout << ' ';
        }
    }

    // ---- TEXT SAFE ----
    int maxLen = w - 1;
    if (maxLen < 0) maxLen = 0;

    int textLen = (int)nd.length();
    if (textLen > maxLen) textLen = maxLen;

    int textX = x + (w - textLen) / 2;
    if (textX < x) textX = x;
    int textY = y + h / 2;

    SetColor2((b_color << 4) | 15);
    GoToXY(textX, textY);
    cout << nd.substr(0, static_cast<size_t>(textLen));

    // ---- BORDER ----
    SetColor2(t_color);
    for (int ix = x + 1; ix <= x + w - 1; ix++) {
        GoToXY(ix, y);       cout << char(196);
        GoToXY(ix, y + h);   cout << char(196);
    }
    for (int iy = y + 1; iy <= y + h - 1; iy++) {
        GoToXY(x, iy);       cout << char(179);
        GoToXY(x + w, iy);   cout << char(179);
    }

    GoToXY(x, y);           cout << char(218);
    GoToXY(x + w, y);       cout << char(191);
    GoToXY(x, y + h);       cout << char(192);
    GoToXY(x + w, y + h);   cout << char(217);
}

// ================== SHOW MENU ==================
int ShowMenu(string menu[], int sl, int w = 20, int h = 2, int t_color = 11, int b_color = 1, int b_color_sang = 9)
{
    int padding = 2;
    int menuHeight = sl * h + (sl - 1);

    int x = (GetConsoleWidth() - w) / 2;
    int y = (GetConsoleHeight() - menuHeight) / 2 + 4;
    // ---- OUTER BOX ----
    box(x - padding, y - padding, w + padding * 2, menuHeight + padding * 2, 10, 2, "");

    // ---- DRAW ALL ----
    for (int i = 0; i < sl; i++)
    {
        box(x, y + i * (h + 1), w, h, t_color, b_color, menu[i]);
    }

    int selection = 0;

    // ---- HIGHLIGHT FIRST ----
    box(x, y, w, h, t_color, b_color_sang, menu[0]);

    // ---- CONTROL LOOP ----
    while (true)
    {
        int k = _getch();

        // handle extended key
        if (k == 224) k = _getch();

        int old = selection;

        if (k == 72)
        {
            // UP
            selection = (selection == 0) ? sl - 1 : selection - 1;
            playClickMenuSound();
        }
        else
            if (k == 80)
            {       // DOWN
                selection = (selection == sl - 1) ? 0 : selection + 1;
                playClickMenuSound();
            }
            else
                if (k == 13)
                {       // ENTER
                    playChooseMenuSound();
                    return selection;
                }
                else continue;

        // redraw old
        box(x, y + old * (h + 1), w, h, t_color, b_color, menu[old]);

        // redraw new
        box(x, y + selection * (h + 1), w, h, t_color, b_color_sang, menu[selection]);
    }
}

int GetMainMenuChoice2() 
{
    string MainMenu[5];
    if (isEnglish) 
    {
        MainMenu[0] = "START GAME";
        MainMenu[1] = "HOW TO PLAY";
        MainMenu[2] = "MATCH REPLAY";
        MainMenu[3] = "SETTINGS";
        MainMenu[4] = "EXIT";
    }
    else 
    {
        MainMenu[0] = "BAT DAU";
        MainMenu[1] = "HUONG DAN";
        MainMenu[2] = "XEM LAI";
        MainMenu[3] = "CAI DAT";  
        MainMenu[4] = "THOAT";
    }
    return ShowMenu(MainMenu, 5, 30, 3, 11, 1, 9);
}

int GetModeMenuChoice2()
{
    string ModeMenu[3];
    if (isEnglish)
    {
        ModeMenu[0] = "TWO PLAYERS";
        ModeMenu[1] = "PLAY WITH BOT";
        ModeMenu[2] = "BACK TO HOME";
    }
    else
    {
        ModeMenu[0] = "HAI NGUOI CHOI";
        ModeMenu[1] = "CHOI VOI MAY";
        ModeMenu[2] = "QUAY VE TRANG CHU";
    }

    int choice = ShowMenu(ModeMenu, 3, 30, 3);

    return choice;
}

int GetSizeMenuChoice2()
{
    string SizeMenu[3];
    if (isEnglish)
    {
        SizeMenu[0] = "3x3";
        SizeMenu[1] = "12x12";
        SizeMenu[2] = "BACK TO HOME";
    }
    else
    {
        SizeMenu[0] = "3x3";
        SizeMenu[1] = "12x12";
        SizeMenu[2] = "QUAY VE TRANG CHU";
    }

    int choice = ShowMenu(SizeMenu, 3, 30, 3);

    return choice;
}

int GetPieceMenuChoice()
{
    string PieceMenu[3];
    if (isEnglish)
    {
        PieceMenu[0] = "X";
        PieceMenu[1] = "O";
        PieceMenu[2] = "BACK TO HOME";
    }
    else
    {
        PieceMenu[0] = "X";
        PieceMenu[1] = "O";
        PieceMenu[2] = "QUAY VE TRANG CHU";
    }

    int choice = ShowMenu(PieceMenu, 3, 30, 3);

    return choice;
}

int GetPlayAgainMenuChoice()
{
    string PlayAgainMenu[3];
    if (isEnglish)
    {
        PlayAgainMenu[0] = "PLAY AGAIN";
        PlayAgainMenu[1] = "SAVE GAME";
        PlayAgainMenu[2] = "BACK TO HOME";
    }
    else
    {
        PlayAgainMenu[0] = "CHOI LAI";
        PlayAgainMenu[1] = "LUU VAN DAU";
        PlayAgainMenu[2] = "TRO VE TRANG CHU";
    }

    int choice = ShowMenu(PlayAgainMenu, 3, 30, 3);

    return choice;
}

int GetSaveGameMenuChoice()
{
    string SaveGameMenu[3];
    if (isEnglish)
    {
        SaveGameMenu[0] = "VIEW MATCH";
        SaveGameMenu[1] = "DELETE MATCH";
        SaveGameMenu[2] = "BACK TO HOME";
    }
    else
    {
        SaveGameMenu[0] = "XEM VAN DAU";
        SaveGameMenu[1] = "XOA VAN DAU";
        SaveGameMenu[2] = "TRO VE TRANG CHU";
    }

    int choice = ShowMenu(SaveGameMenu, 3, 30, 3);

    return choice;
}

int GetLoadGameMenuChoice()
{
    string LoadGameMenu[3];
    if (isEnglish)
    {
        LoadGameMenu[0] = "CONTINUE";
        LoadGameMenu[1] = "VIEW ONLY";
        LoadGameMenu[2] = "BACK TO HOME";
    }
    else
    {
        LoadGameMenu[0] = "TIEP TUC";
        LoadGameMenu[1] = "CHI XEM LAI";
        LoadGameMenu[2] = "TRO VE TRANG CHU";
    }

    int choice = ShowMenu(LoadGameMenu, 3, 30, 3);

    return choice;
}

int GetAskToSaveGameMenuChoice()
{
    string AskToSaveGameMenu[2];
    if (isEnglish)
    {
        AskToSaveGameMenu[0] = "YES";
        AskToSaveGameMenu[1] = "NO";
    }
    else
    {
        AskToSaveGameMenu[0] = "CO";
        AskToSaveGameMenu[1] = "KHONG";
    }

    int choice = ShowMenu(AskToSaveGameMenu, 2, 30, 3);

    return choice;
}

int GetLevel3x3MenuChoice()
{
    string Level3x3Menu[3];
    if (isEnglish)
    {
        Level3x3Menu[0] = "EASY";
        Level3x3Menu[1] = "HARD";
        Level3x3Menu[2] = "BACK TO HOME";
    }
    else
    {
        Level3x3Menu[0] = "DE";
        Level3x3Menu[1] = "KHO";
        Level3x3Menu[2] = "TRO VE TRANG CHU";
    }

    int choice = ShowMenu(Level3x3Menu, 3, 30, 3);

    return choice;
}

int GetLevel12x12MenuChoice()
{
    string Level12x12Menu[4];
    if (isEnglish)
    {
        Level12x12Menu[0] = "EASY";
        Level12x12Menu[1] = "MEDIUM";
        Level12x12Menu[2] = "HARD";
        Level12x12Menu[3] = "BACK TO HOME";
    }
    else
    {
        Level12x12Menu[0] = "DE";
        Level12x12Menu[1] = "TRUNG BINH";
        Level12x12Menu[2] = "KHO";
        Level12x12Menu[3] = "QUAY VE TRANG CHU";
    }

    int choice = ShowMenu(Level12x12Menu, 4, 30, 3);

    return choice;
}


