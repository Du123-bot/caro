#include "Display.h"
#include "MenuGame.h"
#include "SoundEffect.h"
#include "LogicGame.h"

using namespace std;

void SetColor(int color)
{
    switch (color)
    {
    case 0: cout << "\033[30;107m"; break; // chu den, nen trang
    case 1: cout << "\033[32;107m"; break; //chu xanh la, nen trang
    case 2: cout << "\033[33;107m"; break; //chu vang, nen trang
    case 3: cout << "\033[36;107m"; break; //chu xanh nuoc bien,nen trang
    case 4: cout << "\033[37;107m"; break; //chu trang, nen trang
    case 5: cout << "\033[31;107m"; break; //chu do, nen trang
    }
}

void GoToXY(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { (short)x, (short)y };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void SetBackGround()
{
    SetConsoleOutputCP(437);
    system("Color F0");
}

void CenterText(string text, int y)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int startX = (width - text.length()) / 2;
    GoToXY(startX, y);
    cout << text;
}

void ClearScreen()
{
    system("cls");
}

void DrawXO(int StartX, int StartY, int i, int j, char Board[][50], bool Check)
{
    int tx = StartX + 2 + (j - 1) * 4;
    int ty = StartY + 1 + (i - 1) * 2;

    GoToXY(tx, ty);

    if (Check)
    {
        cout << "\033[100m" << " ";
    }
    else
    {
        if (Board[i][j] == 'X')
        {
            cout << Theme::RedColor << "X";
        }
        else
        if (Board[i][j] == 'O')
        {
            cout << Theme::BlueColor << "O";
        }
        else
        {
            cout << Theme::BaseColor << " ";
        }
    }

}

const int width = 3;
void PrintRepeatedChar(unsigned char c, int count)
{
    for (int i = 0; i < count; ++i) cout << c;
}
void DrawBoardGame(int BoardSize, int& StartX, int& StartY)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int cellWidth = 3;
    int cellHeight = 1;

    int boardWidth = BoardSize * cellWidth + (BoardSize + 1);
    int boardHeight = BoardSize * cellHeight + (BoardSize + 1);

    StartX = (w - boardWidth) / 2;
    StartY = (h - boardHeight) / 2;

    SetConsoleOutputCP(437);
    system("Color F0");
    GoToXY(StartX, StartY);
    cout << (unsigned char)218;
    for (int j = 0; j < BoardSize; j++)
    {
        PrintRepeatedChar(196, width);
        if (j < BoardSize - 1) cout << (unsigned char)194;
    }
    cout << (unsigned char)191 << endl;
    for (int i = 0; i < BoardSize; i++)
    {
        for (int h = 0;h < cellHeight;h++)
        {
            GoToXY(StartX, StartY + 1 + i * (cellHeight + 1) + h);
            cout << (unsigned char)179;
            for (int j = 0; j < BoardSize; j++)
            {
                PrintRepeatedChar(' ', width);
                cout << (unsigned char)179;
            }
            cout << endl;
        }
        if (i < BoardSize - 1)
        {
            GoToXY(StartX, StartY + (i + 1) * (cellHeight + 1));
            cout << (unsigned char)195; 
            for (int j = 0; j < BoardSize; j++) 
            {
                PrintRepeatedChar(196, width); 
                if (j < BoardSize - 1) cout << (unsigned char)197; 
            }
            cout << (unsigned char)180 << endl; 
        }
    }
    GoToXY(StartX, StartY + boardHeight - 1);
    cout << (unsigned char)192; 
    for (int j = 0; j < BoardSize; j++) 
    {
        PrintRepeatedChar(196, width); 
        if (j < BoardSize - 1) cout << (unsigned char)193; 
    }
    cout << (unsigned char)217 << endl; 
}

void EffectWin(int type, int x, int y, char c, char board[][50], int n, int StartX, int StartY)
{
    playWinSound();
    pair<int, int>Pos[50];
    if (type == 1)
    {
        // Win theo hang ngang
        int left = y - 1;//right = y + 1;
        while (board[x][left] == c && left > 0) left--;

        for (int i = 1;i <= 5;i++)
        {
            Pos[i] = { x,left + i };
        }
        //playWinSound();
        
        for (int i = 1;i <=5;i++)
        {
            int a = Pos[i].first;
            int b = Pos[i].second;

            int tx = StartX + 2 + (b - 1) * 4;
            int ty = StartY + 1 + (a - 1) * 2;

            GoToXY(tx, ty);
            cout <<Theme::YellowColor << board[a][b];

            Sleep(150);

        }
       // playWinSound();
        //Sleep(5000);
        //TurnOnBackGroundMusic();
    }
    else
    if (type == 2)
    {
        int top = x - 1;//bottom = x + 1;
        while (board[top][y] == c && top > 0) top--;

        for (int i = 1;i <= 5;i++)
        {
            Pos[i] = { top + i,y };
        }

       // playWinSound();

        for (int i = 1;i <= 5;i++)
        {
            int a = Pos[i].first;
            int b = Pos[i].second;

            int tx = StartX + 2 + (b - 1) * 4;
            int ty = StartY + 1 + (a - 1) * 2;

            GoToXY(tx, ty);
            cout << Theme::YellowColor << board[a][b];

            Sleep(150);
        }
    } 
    else
    if (type == 3)
    {

        Coord RightTop = { x - 1, y + 1 }; //LeftBottom = { x + 1, y - 1 };
        int Count = 0;
        while (board[RightTop.x][RightTop.y] == c && RightTop.x>0 && RightTop.y<=n)
        {
            RightTop.x--;
            RightTop.y++;
           // if (RightTop.x < 0 || RightTop.y > n) break;
           // Count++;
        }

        //cout << RightTop.x << " " << RightTop.y << endl;

        for (int i = 1;i <=5;i++)
        {
            Pos[i] = { RightTop.x + i,RightTop.y - i };
        }

        //playWinSound();

       for (int i =1;i<=5;i++)
       {
            int a = Pos[i].first;
            int b = Pos[i].second;

            int tx = StartX + 2 + (b - 1) * 4;
            int ty = StartY + 1 + (a - 1) * 2;

            GoToXY(tx, ty);
            cout << Theme::YellowColor << board[a][b];

            Sleep(150);
       }  
    }
    else
    if (type == 4)
    {
        Coord TopLeft = { x - 1, y - 1 };
        while (board[TopLeft.x][TopLeft.y] == c && TopLeft.x>0 && TopLeft.y>0)
        {
            TopLeft.x--;
            TopLeft.y--;
            //cnt++;
        }

        for (int i = 1;i <=5; i++)
        {
            Pos[i] = { TopLeft.x + i,TopLeft.y + i };
        }

       // playWinSound();

        for (int i = 1;i <=5;i++)
        {
            int a = Pos[i].first;
            int b = Pos[i].second;

            int tx = StartX + 2 + (b - 1) * 4;
            int ty = StartY + 1 + (a - 1) * 2;

            GoToXY(tx, ty);
            cout << Theme::YellowColor << board[a][b];

            Sleep(150);
        }
    }
    Sleep(1500);
}
void PrintCaroGame()
{
    SetBackGround();
    unsigned char Game[] = {
        32, 219, 219, 219, 219, 219, 219, 187, 32, 219, 219, 219, 219, 219, 187, 32, 219, 219, 219, 219, 219, 219, 187, 32, 32, 219, 219, 219, 219, 219,219, 187, 32,  32,219,219,219,219,219,219,187,  32, 219, 219, 219, 219, 219, 187, 32,   201,219,219,219,32,32,32,219,219,219,187,32,   201,219,219,219,219,219,219,187,
219, 219, 201, 205, 205, 205,205, 188, 219, 219, 201, 205, 205, 219, 219, 187, 219, 219, 201, 205, 205, 219, 219, 187, 219, 219, 201, 205, 205, 205, 219, 219, 187, 219,219,201,205,205,205,205,188, 219, 219, 201, 205, 205, 219, 219, 187, 219,219,219,219,219,32,219,219,219,219,219,32, 219,219,201,205,205,205,205,188,
219, 219, 186, 32, 32, 32, 32,32, 219, 219, 219, 219, 219, 219, 219, 186, 219, 219, 219, 219, 219, 219, 201, 188, 219, 219, 186, 32, 32, 32, 219, 219, 186, 219,219,186,32,219,219,219,187, 219, 219, 219, 219, 219, 219, 219, 186,  219,219,32,219,219,219,219,219,32,219,219,32,  219,219,219,219,219,219,219,187,
219, 219, 186, 32, 32, 32, 32,32, 219, 219, 201, 205, 205, 219, 219, 186, 219, 219, 201, 205, 205, 219, 219, 187, 219, 219, 186, 32, 32, 32, 219, 219, 186, 219,219,186,32,32,32,219,186, 219, 219, 201, 205, 205, 219, 219, 186 ,   219,219,32,32,219,219,219,32,32,219,219,32,    219,219,201,205,205,205,205,188,
200, 219, 219, 219, 219, 219, 219, 187, 219, 219, 186, 32, 32, 219, 219, 186, 219, 219, 186, 32, 32, 219, 219, 186, 200, 219, 219, 219, 219, 219, 219, 201, 188,200,219,219,219,219,219,219,186, 219, 219, 186, 32, 32, 219, 219, 186,   219,219,32,32,186,32,186,32,32,219,219,32,     219,219,219,219,219,219,219,187,
32, 200, 205, 205, 205, 205, 205, 188, 200, 205, 188, 32, 32, 200, 205, 188, 200, 205, 188, 32, 32, 200, 205, 188, 32, 200, 205, 205, 205, 205, 205, 188, 32,32,32,200,205,205,205,205,188,200, 205, 188, 32, 32, 200, 205, 188,      200,205,205,205,188,32,200,205,205,205,188,32, 32,200,205,205,205,205,205,188,200
    };
    int num_lines = 6, num_chars = 69;
    int top = 1, left = (GetConsoleWidth() - num_chars) / 2;
    if (left < 0) left = 0;
    for (int i = 0; i < num_lines; i++)
    {
        GoToXY(left, i + top);
        for (int j = 0; j < num_chars; j++)
            putchar(Game[i * num_chars + j]);
    }
}

void PrintModeGame()
{
    SetBackGround();
    unsigned char Game[] = {
        220, 219, 219, 219, 32, 32, 32, 32, 219, 219, 219, 220, 32, 32, 220, 219, 219, 219, 219, 219, 219, 219, 220, 32, 32, 219, 219, 219, 219, 219, 219, 219, 220, 32,32, 32, 219, 219, 219, 219, 219, 219, 219,
        219, 219, 219, 219, 219, 32, 32, 219, 219, 219, 219, 219, 32, 219, 219, 219, 223, 32, 32, 32, 223, 219, 219, 219, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 219, 219, 219, 223, 223, 223, 223, 32,
        219, 219, 219, 32, 219, 219, 219, 219, 32, 219, 219, 219, 32, 219, 219, 219, 32, 32, 32, 32, 32, 219, 219, 219,  32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 219, 219, 219, 219, 219, 219, 32, 32,
        219, 219, 219, 32, 32, 219, 219, 32, 32, 219, 219, 219, 32, 219, 219, 219, 220, 32, 32, 32, 220, 219, 219, 219, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 219, 219, 219, 220, 220, 220, 220, 32,
        219, 219, 219, 32, 32, 32, 32, 32, 32, 219, 219, 219, 32, 32, 223, 219, 219, 219, 219, 219, 219, 219, 223, 32, 32, 219, 219, 219, 219, 219, 219, 219, 223, 32, 32,32,219, 219, 219, 219, 219, 219, 219
    };
    int num_lines = 5, num_chars = 43;
    int top = 4, left = (GetConsoleWidth() - num_chars) / 2;
    if (left < 0) left = 0;
    for (int i = 0; i < num_lines; i++)
    {
        GoToXY(left, i + top);
        for (int j = 0; j < num_chars; j++)
            putchar(Game[i * num_chars + j]);
    }
}

void PrintSizeGame()
{
    SetBackGround();
    unsigned char Game[] = {
    220, 219, 219, 219, 219, 219, 220, 32, 219, 219, 219, 219, 219, 219, 219, 32, 219, 219, 219, 219, 219, 219, 219, 32, 32, 219, 219, 219, 219, 219, 219,
     219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 219, 219, 219, 32, 32, 32, 32, 32, 32, 32, 220, 219, 219, 32, 219, 219, 219, 223, 223, 223, 32,            
     223, 219, 219, 219, 219, 219, 220, 32, 32, 32, 219, 219, 219, 32, 32, 32, 32, 32, 220, 219, 219, 223, 32, 32, 219, 219, 219, 219, 219, 32, 32 ,
     32, 32, 32, 32, 32, 219, 219, 32, 32, 32, 219, 219, 219, 32, 32, 32, 220, 219, 219, 223, 32, 32, 32, 32, 219, 219, 219, 220, 220, 220, 32,
     223, 219, 219, 219, 219, 219, 223, 32, 219, 219, 219, 219, 219, 219, 219, 32, 219, 219, 219, 219, 219, 219, 219, 32, 32, 219, 219, 219, 219, 219, 219
};
    int num_lines = 5, num_chars = 31;
    int top = 4, left = (GetConsoleWidth() - num_chars) / 2;
    if (left < 0) left = 0;
    for (int i = 0; i < num_lines; i++)
    {
        GoToXY(left, i + top);
        for (int j = 0; j < num_chars; j++)
            putchar(Game[i * num_chars + j]);
    }
}

void DrawX(int x, int y) 
{
    for (int i = 0; i < 3; i++) {
        GoToXY(x + 1 + i, y);
        putchar(220);
        GoToXY(x + 7 + i, y);
        putchar(220);
    }
    GoToXY(x, y + 1);		putchar(219);
    GoToXY(x + 4, y + 1);	putchar(219);
    GoToXY(x + 6, y + 1);	putchar(219);
    GoToXY(x + 10, y + 1);	putchar(219);
    GoToXY(x, y + 2);		putchar(219);
    GoToXY(x + 10, y + 2);	putchar(219);
    GoToXY(x, y + 3);		putchar(223);
    GoToXY(x + 10, y + 3);	putchar(223);
    GoToXY(x, y + 4);		putchar(219);
    GoToXY(x + 10, y + 4);	putchar(219);
    GoToXY(x + 10, y + 5);	putchar(219);
    GoToXY(x, y + 5);		putchar(219);
    GoToXY(x + 5, y + 5);	putchar(223);
    GoToXY(x, y + 6);		putchar(223);
    GoToXY(x + 10, y + 6);	putchar(223);
    for (int i = 0; i < 3; i++) {
        GoToXY(x + 1 + i, y + 1);
        putchar(32);
        GoToXY(x + 7 + i, y + 1);
        putchar(32);
        GoToXY(x + 2 + i, y + 2);
        putchar(32);
        GoToXY(x + 6 + i, y + 2);
        putchar(32);
        GoToXY(x + 3 + i, y + 3);
        putchar(32);
        GoToXY(x + 6 + i, y + 3);
        putchar(32);
        GoToXY(x + 1 + i, y + 4);
        putchar(32);
        GoToXY(x + 7 + i, y + 4);
        putchar(32);
        GoToXY(x + 1 + i, y + 5);
        putchar(220);
        GoToXY(x + 7 + i, y + 5);
        putchar(220);
    }
    GoToXY(x + 1, y + 2);	putchar(220);
    GoToXY(x + 9, y + 2);	putchar(220);
    GoToXY(x + 2, y + 3);	putchar(223);
    GoToXY(x + 8, y + 3);	putchar(223);
    GoToXY(x + 4, y + 4);	putchar(220);
    GoToXY(x + 5, y + 4);	putchar(219);
    GoToXY(x + 6, y + 4);	putchar(220);

    GoToXY(x + 5, y + 2);	putchar(223);
    GoToXY(x + 1, y + 3);	putchar(220);
    GoToXY(x + 9, y + 3);	putchar(220);
    GoToXY(x + 4, y + 5);	putchar(220);
    GoToXY(x + 6, y + 5);	putchar(220);
    for (int i = 0; i < 3; i++) {
        GoToXY(x + 1 + i, y + 6);
        putchar(220);
        GoToXY(x + 7 + i, y + 6);
        putchar(220);
    }
}

void DrawO(int x, int y) 
{
    for (int i = 0; i < 6; i++) {
        GoToXY(x + 2 + i, y);
        putchar(220);
    }
    GoToXY(x, y + 1);		putchar(220);
    GoToXY(x + 9, y + 1);	putchar(220);
    GoToXY(x, y + 2);		putchar(219);
    GoToXY(x + 9, y + 2);	putchar(219);
    GoToXY(x + 9, y + 3);	putchar(219);
    GoToXY(x, y + 3);		putchar(219);
    GoToXY(x + 4, y + 3);	putchar(219);
    GoToXY(x + 5, y + 3);	putchar(219);
    GoToXY(x + 9, y + 4);	putchar(219);
    GoToXY(x, y + 4);		putchar(219);
    GoToXY(x + 9, y + 5);	putchar(219);
    GoToXY(x, y + 5);		putchar(219);
    GoToXY(x + 1, y + 6);	putchar(223);
    GoToXY(x + 8, y + 6);	putchar(223);
    for (int i = 0; i < 6; i++) {
        GoToXY(x + 2 + i, y + 1);
        putchar(32);
        GoToXY(x + 2 + i, y + 5);
        putchar(220);
    }
    for (int i = 0; i < 3; i++) {
        GoToXY(x + 1 + i, y + 2);
        putchar(32);
        GoToXY(x + 6 + i, y + 2);
        putchar(32);
        GoToXY(x + 1 + i, y + 3);
        putchar(32);
        GoToXY(x + 6 + i, y + 3);
        putchar(32);
        GoToXY(x + 6 + i, y + 4);
        putchar(32);
        GoToXY(x + 1 + i, y + 4);
        putchar(32);
    }
    GoToXY(x + 4, y + 2);	putchar(219);
    GoToXY(x + 5, y + 2);	putchar(219);
    GoToXY(x + 8, y + 5);	putchar(219);
    GoToXY(x + 1, y + 5);	putchar(219);
    GoToXY(x + 1, y + 1);	putchar(223);
    GoToXY(x + 8, y + 1);	putchar(223);
    GoToXY(x + 4, y + 4);	putchar(223);
    GoToXY(x + 5, y + 4);	putchar(223);
    for (int i = 0; i < 6; i++) {
        GoToXY(x + 2 + i, y + 6);
        putchar(220);
    }
}

int GetConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
int GetConsoleHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void PrintXWin() 
{
    unsigned char Win[] = {
        219,219,219,32,32,32,32,219,219,219,32, 32, 219, 219, 219, 219, 219, 32, 219, 219, 219, 32, 219, 219, 219, 219, 219, 32, 219, 219, 219, 219, 32, 32, 219, 219, 219, 219, 219, 219, 219, 219, 32, 32,
        32,219,219,32,32,32,32,219,219,32 ,32,32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32,
        32,32,32,219,219,219,219,32,32,32,32,32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32,
        32,219,219,219,32,32,219,219,219,32,32,32, 32, 32, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 32, 32, 32, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32,
        219,219,219,32,32,32,32,219,219,219,32,32,32, 32, 32, 32, 219, 219, 219, 219, 32, 219, 219, 219, 219, 32, 32, 32, 32, 219, 219, 219, 219, 219, 32, 219, 219, 219, 219, 32, 219, 219, 219, 219, 219
    };
    int num_lines = 5, num_chars = 44;
    int top = 2, left = (GetConsoleWidth() - num_chars) / 2;
    if (left < 0) left = 0;

    for (int blink = 1; blink < 7; blink++) { // Nhấp nháy 6 lần (3 giây)
        if (blink % 2 == 0) {
            for (int i = 0; i < num_lines; i++) {
                GoToXY(left, i + top);

                for (int j = 0; j < num_chars; j++) {
                    putchar(Win[i * num_chars + j]);
                }
            }
        }
        else {
            for (int i = 0; i < num_lines; i++) {
                GoToXY(left, i + top);
                for (int j = 0; j < num_chars; j++) {
                    putchar(' '); // Xóa bằng cách in khoảng trắng
                }
            }
        }
        Sleep(300); // Dừng 500ms giữa các lần
    }
}

void PrintOWin() 
{
    unsigned char Win[] = {
        32,32,219,219,219,219,219,219,219,219,32,32,32, 219, 219, 219, 219, 219, 32, 219, 219, 219, 32, 219, 219, 219, 219, 219, 32, 219, 219, 219, 219, 32, 32, 219, 219, 219, 219, 219, 219, 219, 219, 32, 32,
        219,219,219,32,32,32,32,32,32,219,219,219,32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32,
        219,219,219,32,32,32,32,32,32,219,219,219,32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32,
        219,219,219,32,32,32,32,32,32,219,219,219,32, 32, 32, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 32, 32, 32, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32,
        32,32,219,219,219,219,219,219,219,219,32,32,32, 32, 32, 32, 219, 219, 219, 219, 32, 219, 219, 219, 219, 32, 32, 32, 32, 219, 219, 219, 219, 219, 32, 219, 219, 219, 219, 32, 219, 219, 219, 219, 219
    };
    int num_lines = 5, num_chars = 45;
    int top = 2, left = (GetConsoleWidth() - num_chars) / 2;
    if (left < 0) left = 0;


    for (int blink = 1; blink < 7; blink++) { // Nhấp nháy 6 lần (3 giây)
        if (blink % 2 == 0) {
            for (int i = 0; i < num_lines; i++) {
                GoToXY(left, i + top);

                for (int j = 0; j < num_chars; j++) {
                    putchar(Win[i * num_chars + j]);
                }
            }
        }
        else {
            for (int i = 0; i < num_lines; i++) {
                GoToXY(left, i + top);
                for (int j = 0; j < num_chars; j++) {
                    putchar(' '); // Xóa bằng cách in khoảng trắng
                }
            }
        }
        Sleep(300); // Dừng 500ms giữa các lần
    }
}

void PrintWin(char WhoWin)
{
    if (WhoWin == 'X')
    {
        PrintXWin();
    }
    else
    if (WhoWin=='O')
    {
        PrintOWin();
    }
}

void PrintDraw() {
    unsigned char Draw[] = {
        32, 32, 32, 32, 219, 219, 219, 219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 219, 219, 219, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 219, 219, 219, 219, 219, 219, 219, 32, 219, 219, 219, 219, 219, 219, 219, 219, 32, 32, 219, 219, 219, 219, 219, 219, 32, 32,219, 219, 219, 219, 219, 32, 219, 219, 219, 32, 219, 219, 219, 219, 219,
        219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 32, 32, 32, 219, 219, 219, 32,32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219,32,
        219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 32, 32, 32, 32, 219, 219, 219, 219, 219, 219, 219, 32,32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32,
        219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 32, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32,32, 32, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 32,32,
        32, 219, 219, 219, 219, 219, 219, 219, 219, 32, 219, 219, 219, 219, 32, 32, 32, 32, 32, 219, 219, 219, 219, 219, 219, 219, 219, 32, 32, 32, 219, 219, 219, 219, 32, 219, 219, 219, 219, 32, 32, 32
    };

    int num_lines = 7, num_chars = 42;
    int top = 1, left = (GetConsoleWidth() - num_chars) / 2;
    if (left < 0) left = 0;

    for (int blink = 1; blink < 7; blink++) { // Nhấp nháy 6 lần (3 giây)
        if (blink % 2 == 0) {
            for (int i = 0; i < num_lines; i++) {
                GoToXY(left, i + top);

                for (int j = 0; j < num_chars; j++) {
                    putchar(Draw[i * num_chars + j]);
                }
            }
        }
        else {
            for (int i = 0; i < num_lines; i++) {
                GoToXY(left, i + top);
                for (int j = 0; j < num_chars; j++) {
                    putchar(' '); // Xóa bằng cách in khoảng trắng
                }
            }
        }
        Sleep(300); // Dừng 500ms giữa các lần
    }
}

void PrintSaveGame()
{
    SetBackGround();
    unsigned char Game[] = {
    220,219,219,219,219,219,220,32,32,220,219,219,219,219,219,220,32,32,220,219,219,32,32,32,219,219,220,32,220,219,219,219,219,219,219,32,   32, 220, 219, 219, 219, 219, 219, 220, 32, 32, 220, 219, 219, 219, 219, 219, 219, 219, 220, 32, 220, 219, 219, 219, 32, 32, 32, 32, 32, 219, 219, 219, 220, 32, 32, 219, 219, 219, 219, 219, 219,
    219,219,32,32,32,32,32,32,219,219,219,32,32,32,219,219,219,32,219,219,219,32,32,32,219,219,219,32,219,219,219,223,223,223,32,32,          219, 219, 219, 32, 32, 32, 32, 32, 32, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 219, 219, 219, 219, 219, 32, 32, 32, 219, 219, 219, 219, 219, 32, 219, 219, 219, 223, 223, 223, 32,
    223,219,219,219,219,219,220,32,219,219,219,219,219,219,219,219,219,32,219,219,219,220,32,220,219,219,219,32,219,219,219,219,219,32,32,32, 219, 219, 219, 32, 32, 219, 219, 219, 220, 32, 219, 219, 219, 219, 219, 219, 219, 219, 219, 32, 219, 219, 219, 32, 219, 219, 219, 219, 219, 32, 219, 219, 219, 32, 219, 219, 219, 219, 219, 32, 32,
    32,32,32,32,32,219,219,32,219,219,219,32,32,32,219,219,219,32,219,219,219,219,219,219,219,219,219,32,219,219,219,220,220,220,32,32,       219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 32, 219, 219, 219, 220, 220, 220, 32,
    223,219,219,219,219,219,223,32,219,219,219,32,32,32,219,219,219,32,32,223,219,219,219,219,219,223,32,32,223,219,219,219,219,219,219,32,   32, 223, 219, 219, 219, 219, 219, 223, 32, 32, 219, 219, 219, 32, 32, 32, 219, 219, 219, 32, 219, 219, 219, 32, 32, 32, 32, 32, 32, 32, 219, 219, 219, 32, 32, 219, 219, 219, 219, 219, 219
    };
    //printColoredRectangle(39, 2, 41, 10, 0);
    //SetColor(0, x);
    int num_lines = 5, num_chars = 77;
    int top = 4, left = (GetConsoleWidth() - num_chars) / 2;
    if (left < 0) left = 0;
    for (int i = 0; i < num_lines; i++)
    {
        GoToXY(left, i + top);
        for (int j = 0; j < num_chars; j++)
            putchar(Game[i * num_chars + j]);
    }
}

void PrintLevelGame()
{
    SetBackGround();
    unsigned char Game[] = {
    219,219,219,32,32,32,32,220,219,219,219,219,219,219,32,220,219,219,32,32,32,219,219,220,32,220,219,219,219,219,219,219,32,219,219,219,32,32,32,
    219,219,219,32,32,32,32,219,219,219,223,223,223,32,32,219,219,219,32,32,32,219,219,219,32,219,219,219,223,223,223,32,32,219,219,219,32,32,32,
    219,219,219,32,32,32,32,219,219,219,219,219,32,32,32,219,219,219,220,32,220,219,219,219,32,219,219,219,219,219,32,32,32,219,219,219,32,32,32,
    219,219,219,220,220,220,32,219,219,219,220,220,220,32,32,219,219,219,219,219,219,219,219,219,32,219,219,219,220,220,220,32,32,219,219,219,220,220,220,
    219,219,219,219,219,219,32,223,219,219,219,219,219,219,32,32,223,219,219,219,219,219,223,32,32,223,219,219,219,219,219,219,32,219,219,219,219,219,219
    };
    int num_lines = 5, num_chars = 39;
    int top = 4, left = (GetConsoleWidth() - num_chars) / 2;
    if (left < 0) left = 0;
    for (int i = 0; i < num_lines; i++)
    {
        GoToXY(left, i + top);
        for (int j = 0; j < num_chars; j++)
            putchar(Game[i * num_chars + j]);
    }
}

void PrintSelectionXO()
{
    SetBackGround();
    unsigned char Game[] = {
   219,219,219,32,32,32,219,219,219,32,32,32,220,219,219,219,219,220,32,32,219,219,219,219,219,219,220,32,32,32,32,220,219,219,219,219,219,219,220,32,
   32,219,219,219,32,219,219,219,32,32,32,219,219,219,32,32,219,219,219,32,219,219,219,32,32,219,219,219,32,32,219,219,219,223,32,32,223,219,219,219,
   32,32,219,219,219,219,219,32,32,32,32,219,219,219,32,32,219,219,219,32,219,219,219,219,219,219,219,219,32,32,219,219,219,32,32,32,32,219,219,219,
   32,219,219,219,32,219,219,219,32,32,32,219,219,219,32,32,219,219,219,32,219,219,219,32,223,219,219,219,32,32,219,219,219,220,32,32,220,219,219,219,
   219,219,219,32,32,32,219,219,219,32,32,32,223,219,219,219,219,223,32,32,219,219,219,32,32,219,219,219,32,32,32,223,219,219,219,219,219,219,223,32
    };
    int num_lines = 5, num_chars = 40;
    int top = 4, left = (GetConsoleWidth() - num_chars) / 2;
    if (left < 0) left = 0;
    for (int i = 0; i < num_lines; i++)
    {
        GoToXY(left, i + top);
        for (int j = 0; j < num_chars; j++)
            putchar(Game[i * num_chars + j]);
    }
}

void PrintNotOverGame()
{
    unsigned char Game[] = {
    219,219,219,220,32,32,32,219,219,220,32,32,220,219,219,219,219,219,220,32,32,220,219,219,219,219,219,219,219,220,32,32,32,32,220,219,219,219,219,220,32,32,220,219,219,32,32,32,219,219,220,32,220,219,219,219,219,219,219,32,219,219,219,219,219,219,220,32,
    219,219,219,219,219,220,32,219,219,219,32,219,219,219,32,32,32,219,219,219,32,32,32,32,219,219,219,32,32,32,32,32,32,219,219,219,32,32,219,219,219,32,219,219,219,32,32,32,219,219,219,32,219,219,219,223,223,223,32,32,219,219,219,32,32,219,219,219,
    219,219,219,219,219,219,219,219,219,219,32,219,219,219,32,32,32,219,219,219,32,32,32,32,219,219,219,32,32,32,32,32,32,219,219,219,32,32,219,219,219,32,219,219,219,220,32,220,219,219,219,32,219,219,219,219,219,32,32,32,219,219,219,219,219,219,219,219,
    219,219,219,32,223,219,219,219,219,219,32,219,219,219,32,32,32,219,219,219,32,32,32,32,219,219,219,32,32,32,32,32,32,219,219,219,32,32,219,219,219,32,219,219,219,219,219,219,219,219,219,32,219,219,219,220,220,220,32,32,219,219,219,32,223,219,219,219,
    223,219,219,32,32,32,223,219,219,219,32,32,223,219,219,219,219,219,223,32,32,32,32,32,219,219,219,32,32,32,32,32,32,32,223,219,219,219,219,223,32,32,32,223,219,219,219,219,219,223,32,32,223,219,219,219,219,219,219,32,219,219,219,32,32,219,219,219
    };
    int num_lines = 5, num_chars = 68;
    int top = 4, left = (GetConsoleWidth() - num_chars) / 2;
    if (left < 0) left = 0;
    for (int i = 0; i < num_lines; i++)
    {
        GoToXY(left, i + top);
        for (int j = 0; j < num_chars; j++)
            putchar(Game[i * num_chars + j]);
    }
}
void PrintHowToPlay()
{
    unsigned char Game[] = {
    219,219,219,32,32,219,219,219,32,220,219,219,219,219,219,219,220,32,219,219,219,32,32,32,219,219,219,32,32,220,219,219,219,219,219,219,219,220,32,220,219,219,219,219,219,219,220,32,32,220,219,219,219,219,219,219,220,32,219,219,219,32,32,32,32,220,219,219,219,219,219,220,32,219,219,219,32,219,219,219,32,32,
    219,219,219,32,32,219,219,219,32,219,219,219,32,32,219,219,219,32,219,219,219,32,32,32,219,219,219,32,32,223,223,223,219,219,219,223,223,223,32,219,219,219,32,32,219,219,219,32,32,219,219,219,32,32,32,219,219,32,219,219,219,32,32,32,32,219,219,219,32,219,219,219,32,219,219,219,32,219,219,219,32,32,
    219,219,219,219,219,219,219,219,32,219,219,219,32,32,219,219,219,32,219,219,219,32,219,32,219,219,219,32,32,32,32,32,219,219,219,32,32,32,32,219,219,219,32,32,219,219,219,32,32,219,219,219,219,219,219,219,223,32,219,219,219,32,32,32,32,219,219,219,219,219,219,219,32,32,219,219,219,219,219,32,32,32,
    219,219,219,32,32,219,219,219,32,219,219,219,32,32,219,219,219,32,219,219,219,219,219,219,219,219,219,32,32,32,32,32,219,219,219,32,32,32,32,219,219,219,32,32,219,219,219,32,32,219,219,219,32,32,32,32,32,32,219,219,219,220,220,220,32,219,219,219,32,219,219,219,32,32,223,219,219,219,223,32,32,32,
    219,219,219,32,32,219,219,219,32,223,219,219,219,219,219,219,223,32,32,223,219,219,219,219,219,223,32,32,32,32,32,32,219,219,219,32,32,32,32,223,219,219,219,219,219,219,223,32,32,219,219,219,32,32,32,32,32,32,219,219,219,219,219,219,32,219,219,219,32,219,219,219,32,32,32,219,219,219,32,32,32,32
    };
    int num_lines = 5, num_chars = 82;
    int top = 4, left = (GetConsoleWidth() - num_chars) / 2;
    if (left < 0) left = 0;
    for (int i = 0; i < num_lines; i++)
    {
        GoToXY(left, i + top);
        for (int j = 0; j < num_chars; j++)
            putchar(Game[i * num_chars + j]);
    }
}