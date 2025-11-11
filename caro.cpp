#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<ctime>
#include<vector>
#include<fstream>
#include<string>

using namespace std;




const char start1 = 'X';
const char start2 = 'O';
int x, y, n, turn, mode, bestMoveX, bestMoveY;
char BOARD_SIZE[509][509], currentPlayerMark, humanPlayerMark, aiPlayerMark;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//ham
void gotoxy(int x, int y) {
    COORD coord; coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int color) { SetConsoleTextAttribute(hConsole, color); }

void centerText(string text, int y) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int startX = (width - text.length()) / 2;
    gotoxy(startX, y);
    cout << text;
}

void clearScreen() { system("cls"); }

void reset_boardgame() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            BOARD_SIZE[i][j] = '.';
}

//checkketqua
bool check_row(char c, int x, int y) {
    int i = y - 1, j = y + 1, cnt = 0;
    while (BOARD_SIZE[x][i] == c && i > 0)
    {
        i--;
        cnt++;
    }
    while (BOARD_SIZE[x][j] == c && j <= n)
    {
        j++;
        cnt++;
    }
    if (n == 3) return (cnt + 1 >= 3);
    else return (cnt + 1 >= 5);
}
bool check_col(char c, int x, int y) {
    int i = x - 1, j = x + 1, cnt = 0;
    while (BOARD_SIZE[i][y] == c && i > 0)
    {
        i--;
        cnt++;
    }
    while (BOARD_SIZE[j][y] == c && j <= n)
    {
        j++;
        cnt++;
    }
    if (n == 3) return (cnt + 1 >= 3);
    else return (cnt + 1 >= 5);
}
bool check_diag1(char c, int x, int y) {
    int i1 = x - 1, j1 = y + 1, i2 = x + 1, j2 = y - 1, cnt = 0;
    while (BOARD_SIZE[i1][j1] == c)
    {
        if (i1 < 0 || j1 > n)
            break;
        i1--;
        j1++;
        cnt++;
    }
    while (BOARD_SIZE[i2][j2] == c)
    {
        if (i2 > n || j2 < 0)
            break;
        i2++;
        j2--;
        cnt++;
    }
    if (n == 3) return (cnt + 1 >= 3);
    else return (cnt + 1 >= 5);
}
bool check_diag2(char c, int x, int y) {
    int i1 = x - 1, j1 = y - 1, i2 = x + 1, j2 = y + 1, cnt = 0;
    while (BOARD_SIZE[i1][j1] == c)
    {
        if (i1 < 0 || j1 < 0)
            break;
        i1--;
        j1--;
        cnt++;
    }
    while (BOARD_SIZE[i2][j2] == c)
    {
        if (i2 > n || j2 > n)
            break;
        i2++;
        j2++;
        cnt++;
    }
    if (n == 3) return (cnt + 1 >= 3);
    else return (cnt + 1 >= 5);
}
bool check_draw() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (BOARD_SIZE[i][j] == '.') return false;
    return true;
}
bool check_win(char c, int x, int y) {
    return (check_row(c, x, y) || check_col(c, x, y) || check_diag1(c, x, y) || check_diag2(c, x, y));
}

void drawboard(int cx, int cy) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    int cellWidth = 4;
    int cellHeight = 2;
    int boardWidth = n * cellWidth + 1;
    int boardHeight = n * cellHeight + 1;

    int startX = (w - boardWidth) / 2;
    int startY = (h - boardHeight) / 2;

    gotoxy(startX, startY);
    for (int j = 0; j < n; j++) cout << "----";
    cout << "-" << endl;

    for (int i = 1; i <= n; i++) {
        gotoxy(startX, startY + (i - 1) * 2 + 1);
        for (int j = 1; j <= n; j++) {
            SetColor(7);
            cout << "|";
            if (cx == i && cy == j) SetColor(14);
            else if (BOARD_SIZE[i][j] == 'X') SetColor(12);
            else if (BOARD_SIZE[i][j] == 'O') SetColor(9);
            else SetColor(7);

            if (cx == i && cy == j)
                cout << "[" << BOARD_SIZE[i][j] << "]";
            else
                cout << " " << BOARD_SIZE[i][j] << " ";
        }
        SetColor(7);
        cout << "|" << endl;

        gotoxy(startX, startY + (i * 2));
        for (int j = 0; j < n; j++) cout << "----";
        cout << "-" << endl;
    }
}
int showEndGameMenu(string message) {
    clearScreen();
    SetColor(6);
    centerText(message, 8);
    SetColor(7);
    int selection = 0;
    while (true)
    {
        if (selection == 0) SetColor(10);
        centerText("--> Choi lai", 11);
        SetColor(7);
        if (selection == 1) SetColor(12);
        centerText("--> Tro ve man hinh chinh", 12);
        SetColor(7);
        char key = _getch();
        if (key == 72)
        {
            selection = (selection == 0 ? 1 : 0);
        }
        else
            if (key == 80)
            {
                selection = (selection == 1 ? 0 : 1);
            }
            else
                if (key == 13) return selection;

        clearScreen();
        SetColor(6);
        centerText(message, 8);
        SetColor(7);
    }
}

void showInstructions() {
    clearScreen();
    SetColor(11);
    centerText("==============================", 3);
    centerText("      HUONG DAN CHOI      ", 4);
    centerText("==============================", 5);
    SetColor(7);
    int y = 8;
    centerText("Phim dieu khien:", y++);
    centerText("- W: Di chuyen len", y++);
    centerText("- A: Di chuyen trai", y++);
    centerText("- S: Di chuyen xuong", y++);
    centerText("- D: Di chuyen phai", y++);
    centerText("- ENTER: Dat quan co", y++);
    centerText("- Q: Thoat tro choi khi dang trong che do choi", y++);
    centerText("", y++);
    centerText("Luat choi:", y++);
    centerText("-Voi ban co kich thuoc tu kich thuoc 5x5 tro len dat 5 quan lien tiep la thang.", y++);
    centerText("-Voi ban co kich thuoc 3x3 dat 3 quan lien tiep la thang.", y++);
    centerText("- Ban co khi khong con nuoc di -> Hoa.", y++);
    SetColor(10);
    centerText("Nhan phim bat ky de quay lai menu chinh...", y + 2);
    SetColor(7);
    _getch();
}

void drawMainMenu(int selection) {
    clearScreen();
    SetColor(14);
    centerText("==============================", 3);
    centerText("     TRO CHOI CO CARO      ", 4);
    centerText("==============================", 5);
    SetColor(7);

    int baseY = 8;
    if (selection == 0) SetColor(10);
    centerText("--> 1. Bat dau choi", baseY);
    SetColor(7);
    if (selection == 1) SetColor(11);
    centerText("--> 2. Huong dan", baseY + 1);
    SetColor(7);
    if (selection==2) SetColor(13);
    centerText("-->3.Xem lai van dau",baseY+2);
    SetColor(7);
    if (selection == 3) SetColor(12);
    centerText("--> 4. Thoat", baseY + 3);
    SetColor(7);
    centerText("Su dung phim len/xuong, Enter de chon.", baseY + 5);
}
int getMainMenuChoice() {
    int selection = 0;
    drawMainMenu(selection);
    while (true) {
        char key = _getch();
        if (key == 72)
        {
            selection = (selection == 0 ? 3 : selection - 1);
            drawMainMenu(selection);
        }
        else
            if (key == 80)
            {
                selection = (selection == 3 ? 0 : selection + 1);
                drawMainMenu(selection);
            }
            else
                if (key == 13) return selection;
    }
}

void drawModeMenu(int selection) {
    clearScreen();
    SetColor(14);
    centerText("==============================", 3);
    centerText("     CHON CHE DO CHOI      ", 4);
    centerText("==============================", 5);
    SetColor(7);

    int baseY = 8;
    if (selection == 0) SetColor(10);
    centerText("--> 1. 2 nguoi choi", baseY);
    SetColor(7);
    if (selection == 1) SetColor(11);
    centerText("--> 2. Choi voi may", baseY + 1);
    SetColor(7);
    if (selection == 2) SetColor(12);
    centerText("--> 3. Quay lai trang chinh", baseY + 2);
    SetColor(7);
    centerText("Su dung phim len/xuong, Enter de chon.", baseY + 5);

}
int getModeMenuChoice()
{
    int selection = 0;
    drawModeMenu(selection);
    while (true)
    {
        char key = _getch();
        if (key == 72)
        {
            selection = (selection == 0 ? 2 : selection - 1);
            drawModeMenu(selection);
        }
        else
            if (key == 80)
            {
                selection = (selection == 2 ? 0 : selection + 1);
                drawModeMenu(selection);
            }
            else
                if (key == 13) return selection;
    }
}

void setupNewGame() {
    centerText("Chon 1 de danh X truoc, 2 de danh O truoc: ", 12);
    cin >> turn;
    clearScreen();

}

char checkMinimaxWin(char currentBoardState[509][509])
{
    for (int i = 1; i <= 3; i++)
    {
        if (currentBoardState[i][1] == currentBoardState[i][2] && currentBoardState[i][2] == currentBoardState[i][3] && currentBoardState[i][3] != '.') return currentBoardState[i][1];
    }

    for (int i = 1; i <= 3; i++)
    {
        if (currentBoardState[1][i] == currentBoardState[2][i] && currentBoardState[2][i] == currentBoardState[3][i] && currentBoardState[3][i] != '.') return currentBoardState[1][i];
    }

    if (currentBoardState[1][1] == currentBoardState[2][2] && currentBoardState[2][2] == currentBoardState[3][3] && currentBoardState[3][3] != '.') return currentBoardState[1][1];

    if (currentBoardState[1][3] == currentBoardState[2][2] && currentBoardState[2][2] == currentBoardState[3][1] && currentBoardState[3][1] != '.') return currentBoardState[1][3];

    return '.';
}

bool isMinimaxBoardFull(char currentBoardState[509][509])
{
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++) if (currentBoardState[i][j] == '.') return false;
    }
    return true;
}

int minimax(char currentBoardState[509][509], int depth, bool is_max)
{
    char winner;
    int bestScore, score;
    winner = checkMinimaxWin(currentBoardState);
    if (winner == aiPlayerMark) return 10 - depth;
    else
        if (winner == humanPlayerMark) return depth - 10;
        else
            if (isMinimaxBoardFull(currentBoardState)) return 0;

    if (is_max)
    {
        bestScore = -1e9;
        for (int i = 1; i <= 3; i++)
        {
            for (int j = 1; j <= 3; j++)
            {
                if (currentBoardState[i][j] == '.')
                {
                    currentBoardState[i][j] = aiPlayerMark;
                    score = minimax(currentBoardState, depth + 1, false);
                    currentBoardState[i][j] = '.';
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    }
    else
    {
        bestScore = 1e9;
        for (int i = 1; i <= 3; i++)
        {
            for (int j = 1; j <= 3; j++)
            {
                if (currentBoardState[i][j] == '.')
                {
                    currentBoardState[i][j] = humanPlayerMark;
                    score = minimax(currentBoardState, depth + 1, true);
                    currentBoardState[i][j] = '.';
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

void best_move()
{
    int bestScore = -1e9, moveScore;
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            if (BOARD_SIZE[i][j] == '.')
            {
                BOARD_SIZE[i][j] = aiPlayerMark;
                moveScore = minimax(BOARD_SIZE, 0, false);
                BOARD_SIZE[i][j] = '.';
                if (moveScore > bestScore)
                {
                    bestScore = moveScore;
                    bestMoveX = i; bestMoveY = j;
                }
            }
        }
    }
}

void delay_time()
{
    int tmp = 0;
    for (int u = 1; u <= 100000; u++)
    {
        for (int v = 1; v <= 10000; v++) tmp++;
    }
}

void machine_turn()
{
    if (n == 3)
    {
        best_move();
        BOARD_SIZE[bestMoveX][bestMoveY] = aiPlayerMark;
        x = bestMoveX; y = bestMoveY;
    }
    else
    {
        srand(time(0));
        int i, j;
        do
        {
            i = rand() % n + 1;
            j = rand() % n + 1;
        } while (BOARD_SIZE[i][j] != '.');
        BOARD_SIZE[i][j] = aiPlayerMark;
        x = i; y = j;
    }

}

struct GameRecord {
    int boardSize;
    int mode;
    vector<vector<char>> board;
    char winner;
};



vector<GameRecord> savedGames;

void deleteSavedGame() {
    clearScreen();

    ifstream fin("saved_list.txt");
    if (!fin.is_open()) {
        centerText("Chua co van dau nao duoc luu!", 10);
        _getch();
        return;
    }

    vector<string> savedFiles;
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) savedFiles.push_back(line);
    }
    fin.close();

    if (savedFiles.empty()) {
        centerText("Chua co van dau nao duoc luu!", 10);
        _getch();
        return;
    }

    int y = 5;
    centerText("=== XOA VAN DAU ===", y++);
    y++;
    for (int i = 0; i < savedFiles.size(); i++) {
        string s = to_string(i + 1) + ". " + savedFiles[i];
        centerText(s, y++);
    }

    y += 2;
    centerText("Nhap so thu tu van dau muon XOA: ", y);
    int choice;
    cin >> choice;

    if (choice < 1 || choice > savedFiles.size()) {
        centerText("Lua chon khong hop le!", y + 2);
        _getch();
        return;
    }

    string toDelete = savedFiles[choice - 1];

    // Xóa file vật lý
    if (remove(toDelete.c_str()) == 0) {
        // Xóa tên trong danh sách
        ofstream fout("saved_list.txt");
        for (int i = 0; i < savedFiles.size(); i++) {
            if (i != choice - 1)
                fout << savedFiles[i] << endl;
        }
        fout.close();

        centerText("Da xoa file: " + toDelete, y + 2);
    } else {
        centerText("Khong the xoa file nay!", y + 2);
    }

    _getch();
}




void showSavedGames() {
    clearScreen();

    ifstream fin("saved_list.txt");
    if (!fin.is_open()) {
        centerText("Chua co van dau nao duoc luu!", 10);
        _getch();
        return;
    }

    vector<string> savedFiles;
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) savedFiles.push_back(line);
    }
    fin.close();

    if (savedFiles.empty()) {
        centerText("Chua co van dau nao duoc luu!", 10);
        _getch();
        return;
    }

    int y = 4;
    centerText("=== DANH SACH CAC VAN DAU ===", y++);
    y++;
    for (int i = 0; i < savedFiles.size(); i++) {
        string s = to_string(i + 1) + ". " + savedFiles[i];
        centerText(s, y++);
    }

    y += 2;
    centerText("1. Xem van dau", y++);
    centerText("2. Xoa van dau", y++);
    centerText("3. Thoat", y++);
    centerText("Lua chon cua ban: ", y + 1);

    int option;
    cin >> option;

    if (option == 2) {
        deleteSavedGame();
        return;
    } else if (option == 3) {
        return;
    }
    y+=3;
    centerText("Nhap so thu tu van dau ban muon xem: ", y);
    int choice;
    cin >> choice;

    if (choice < 1 || choice > savedFiles.size()) {
        centerText("Lua chon khong hop le!", y + 2);
        _getch();
        return;
    }

    string chosenFile = savedFiles[choice - 1];
    ifstream fin2(chosenFile, ios::binary);
    if (!fin2.is_open()) {
        centerText("Khong the mo file nay!", y + 2);
        _getch();
        return;
    }

    GameRecord game;
    fin2.read((char*)&game.boardSize, sizeof(int));
    fin2.read((char*)&game.mode, sizeof(int));
    fin2.read((char*)&game.winner, sizeof(char));

    game.board.resize(game.boardSize, vector<char>(game.boardSize));

    for (int i = 0; i < game.boardSize; i++) {
        for (int j = 0; j < game.boardSize; j++) {
            fin2.read((char*)&game.board[i][j], sizeof(char));
        }
    }
    fin2.close();

    clearScreen();
    centerText("Ban co kich thuoc " + to_string(game.boardSize) + "x" + to_string(game.boardSize), 3);
    centerText("Nguoi thang: " + string(1, game.winner), 5);
    cout << endl;

    for (int i = 0; i < game.boardSize; i++) {
        for (int j = 0; j < game.boardSize; j++) {
            cout << game.board[i][j] << " ";
        }
        cout << endl;
    }

    _getch();
}



bool askToSaveGame(char winner, int n, int mode, char board[509][509]) {
    clearScreen();
    centerText("BAN CO MUON LUU LAI VAN DAU NAY KHONG?", 10);
    centerText("1. Co", 12);
    centerText("2. Khong", 13);
    centerText("Lua chon cua ban: ", 15);
    int choice;
    cin >> choice;

    if (choice == 1) {
        clearScreen();
        centerText("Nhap ten file de luu (VD: tran1): ", 10);
        string filename;
        cin >> filename;

        if (filename.find(".dat") == string::npos)
            filename += ".dat";

        // Ghi file ván đấu nhị phân
        ofstream fout(filename, ios::binary);
        if (!fout.is_open()) {
            centerText("Khong the mo file de luu!", 13);
            _getch();
            return false;
        }

        fout.write((char*)&n, sizeof(int));     // ghi kích thước bàn
        fout.write((char*)&mode, sizeof(int));  // ghi chế độ
        fout.write((char*)&winner, sizeof(char)); // ghi người thắng

        // ghi toàn bộ bàn cờ thật
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                fout.write((char*)&board[i][j], sizeof(char));

        fout.close();

        // Ghi tên file vào danh sách
        ofstream listOut("saved_list.txt", ios::app);
        listOut << filename << endl;
        listOut.close();

        centerText("Da luu van dau vao file: " + filename, 13);
        _getch();
        return true;
    } else {
        centerText("Khong luu van dau.", 17);
        _getch();
        return false;
    }
}




int main()
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci; GetConsoleCursorInfo(hout, &ci);
    ci.bVisible = FALSE; SetConsoleCursorInfo(hout, &ci);

    while (true)
    {
        int mainChoice = getMainMenuChoice();
        if (mainChoice == 3)
        {
            clearScreen();
            centerText("Ban da thoat chuong trinh.", 12);
            return 0;
        }
        else
            if (mainChoice == 1)
            {
                showInstructions();
                continue;
            }
            else
                if (mainChoice == 0)
                {
                    int modeChoice = getModeMenuChoice();
                    if (modeChoice == 2) continue;
                    mode = modeChoice;

                    clearScreen();
                    centerText("Moi ban nhap kich thuoc ban co: ", 10);
                    cin >> n;
                    reset_boardgame();
                    setupNewGame();

                    x = 1; y = 1;
                    bool isGameFinished = false;
                    while (!isGameFinished)
                    {
                        drawboard(x, y);
                        char key = _getch();
                        if (key == 'w' && x > 1) x--;
                        else if (key == 'a' && y > 1) y--;
                        else if (key == 's' && x < n) x++;
                        else if (key == 'd' && y < n) y++;
                        else if (key == 13)
                        {
                            if (BOARD_SIZE[x][y] == '.')
                            {
                                if (mode == 1)
                                {
                                    if (turn % 2 != 0)
                                    {
                                        humanPlayerMark = start1;
                                        aiPlayerMark = start2;
                                    }
                                    else
                                    {
                                        humanPlayerMark = start2;
                                        aiPlayerMark = start1;
                                    }
                                }
                                if (turn % 2 != 0) currentPlayerMark = 'X'; else currentPlayerMark = 'O';
                                BOARD_SIZE[x][y] = currentPlayerMark;

                                if (check_win(currentPlayerMark, x, y))
                                {
                                    drawboard(x, y);
                                    delay_time();
                                    int endGameChoice = showEndGameMenu("Nguoi choi " + string(1, currentPlayerMark) + " thang!");
                                    askToSaveGame(currentPlayerMark, n, mode, BOARD_SIZE);

                                    if (endGameChoice == 0)
                                    {
                                        reset_boardgame();
                                        setupNewGame();
                                        if (mode == 1)
                                        {
                                            if (turn % 2 != 0)
                                            {
                                                humanPlayerMark = start1;
                                                aiPlayerMark = start2;
                                            }
                                            else
                                            {
                                                humanPlayerMark = start2;
                                                aiPlayerMark = start1;
                                            }
                                        }
                                    }
                                    else
                                        if (endGameChoice == 1)
                                        {
                                            isGameFinished = true;
                                            break;
                                        }
                                }
                                else if (check_draw()) {
                                    drawboard(x, y);
                                    delay_time();
                                    int endGameChoice = showEndGameMenu("Hoa!");
                                    askToSaveGame('.', n, mode, BOARD_SIZE);

                                    if (endGameChoice == 0)
                                    {
                                        reset_boardgame();
                                        setupNewGame();
                                        if (mode == 1)
                                        {
                                            if (turn % 2 != 0)
                                            {
                                                humanPlayerMark = start1;
                                                aiPlayerMark = start2;
                                            }
                                            else
                                            {
                                                humanPlayerMark = start2;
                                                aiPlayerMark = start1;
                                            }
                                        }
                                    }
                                    else
                                        if (endGameChoice == 1)
                                        {
                                            isGameFinished = true;
                                            break;
                                        }
                                }
                                else
                                {
                                    turn++;
                                    if (mode == 1)
                                    {
                                        machine_turn();
                                        if (check_win(aiPlayerMark, x, y))
                                        {
                                            drawboard(x, y);
                                            delay_time();
                                            int endGameChoice = showEndGameMenu("May thang!");
                                            askToSaveGame(aiPlayerMark, n, mode, BOARD_SIZE);

                                            if (endGameChoice == 0)
                                            {
                                                reset_boardgame();
                                                setupNewGame();
                                                if (mode == 1)
                                                {
                                                    if (turn % 2 != 0)
                                                    {
                                                        humanPlayerMark = start1;
                                                        aiPlayerMark = start2;
                                                    }
                                                    else
                                                    {
                                                        humanPlayerMark = start2;
                                                        aiPlayerMark = start1;
                                                    }
                                                }
                                            }
                                            else if (endGameChoice == 1)
                                            {
                                                isGameFinished = true;
                                                break;
                                            }
                                        }
                                        else
                                            if (check_draw())
                                            {
                                                drawboard(x, y);
                                                delay_time();
                                                int endGameChoice = showEndGameMenu("Hoa!");
                                                if (endGameChoice == 0)
                                                {
                                                    reset_boardgame();
                                                    setupNewGame();
                                                    if (mode == 1)
                                                    {
                                                        if (turn % 2 != 0)
                                                        {
                                                            humanPlayerMark = start1;
                                                            aiPlayerMark = start2;
                                                        }
                                                        else
                                                        {
                                                            humanPlayerMark = start2;
                                                            aiPlayerMark = start1;
                                                        }
                                                    }
                                                }
                                                else if (endGameChoice == 1)
                                                {
                                                    isGameFinished = true;
                                                    break;
                                                }
                                            }
                                        turn++;
                                    }
                                }
                            }
                        }
                        else if (key == 'q') { isGameFinished = true; break; }
                    }
                }
                else if(mainChoice==2){
                    showSavedGames();
                    continue;
                }
    }

}