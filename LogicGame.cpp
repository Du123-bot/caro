#include "LogicGame.h"
#include "MenuGame.h"
#include<limits>

char BotPlayerMark,HumanPlayerMark,BotPlayermark,HumanPlayermark;

void ResetBoardGame(char Board[][50] ,int n)
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            Board[i][j] = ' ';
}

bool CheckRow(char c, int x, int y, char board[][50], int n)
{
    int i = y - 1, j = y + 1, cnt = 0;
    while (board[x][i] == c && i > 0)
    {
        i--;
        cnt++;
    }
    while (board[x][j] == c && j <= n)
    {
        j++;
        cnt++;
    }
    if (n == 3) return (cnt + 1 >= 3);
    return (cnt + 1 >= 5);
}
bool CheckCol(char c, int x, int y, char board[][50], int n)
{
    int i = x - 1, j = x + 1, cnt = 0;
    while (board[i][y] == c && i > 0)
    {
        i--;
        cnt++;
    }
    while (board[j][y] == c && j <= n)
    {
        j++;
        cnt++;
    }
    if (n == 3) return (cnt + 1 >= 3);
    return (cnt + 1 >= 5);
}
bool CheckDiag1(char c, int x, int y, char board[][50], int n)
{
    int i1 = x - 1, j1 = y + 1, i2 = x + 1, j2 = y - 1, cnt = 0;
    while (board[i1][j1] == c)
    {
        if (i1 < 0 || j1 > n) break;
        i1--;
        j1++;
        cnt++;
    }
    while (board[i2][j2] == c)
    {
        if (i2 > n || j2 < 0) break;
        i2++;
        j2--;
        cnt++;
    }
    if (n == 3) return (cnt + 1 >= 3);
    return (cnt + 1 >= 5);
}
bool CheckDiag2(char c, int x, int y, char board[][50], int n)
{
    int i1 = x - 1, j1 = y - 1, i2 = x + 1, j2 = y + 1, cnt = 0;
    while (board[i1][j1] == c)
    {
        if (i1 < 0 || j1 < 0)
            break;
        i1--;
        j1--;
        cnt++;
    }
    while (board[i2][j2] == c)
    {
        if (i2 > n || j2 > n)
            break;
        i2++;
        j2++;
        cnt++;
    }
    if (n == 3) return (cnt + 1 >= 3);
    return (cnt + 1 >= 5);
}
bool CheckDraw(char board[][50], int n)
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (board[i][j] == ' ') return false;
    return true;
}
bool CheckWin(char c, int x, int y, char board[][50], int n)
{
    return (CheckRow(c, x, y,board,n) || CheckCol(c, x, y,board,n) || CheckDiag1(c, x, y,board,n) || CheckDiag2(c, x, y,board,n));
}

int CheckWin2(char c, int x, int y, char board[][50], int n)
{
    if (CheckRow(c, x, y, board, n)) return 1;
    if (CheckCol(c, x, y, board, n)) return 2;
    if (CheckDiag1(c, x, y, board, n)) return 3;
    if (CheckDiag2(c, x, y, board, n)) return 4;
    return -1;
}

char CheckMinimaxWin(char CurrentBoard[][50])
{
    for (int i = 1; i <= 3; i++)
    {
        if (CurrentBoard[i][1] == CurrentBoard[i][2] && CurrentBoard[i][2] == CurrentBoard[i][3] && CurrentBoard[i][3] != ' ')
            return CurrentBoard[i][1];
    }

    for (int i = 1; i <= 3; i++)
    {
        if (CurrentBoard[1][i] == CurrentBoard[2][i] && CurrentBoard[2][i] == CurrentBoard[3][i] && CurrentBoard[3][i] != ' ')
            return CurrentBoard[1][i];
    }

    if (CurrentBoard[1][1] == CurrentBoard[2][2] && CurrentBoard[2][2] == CurrentBoard[3][3] && CurrentBoard[3][3] != ' ')
        return CurrentBoard[1][1];

    if (CurrentBoard[1][3] == CurrentBoard[2][2] && CurrentBoard[2][2] == CurrentBoard[3][1] && CurrentBoard[3][1] != ' ')
        return CurrentBoard[1][3];

    return ' ';
}

bool IsMinimaxBoardFull(char CurrentBoard[][50])
{
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
            if (CurrentBoard[i][j] == ' ') return false;
    }
    return true;
}

void DefineBotPlayer(int Selection)
{
    if (Selection == 0)
    {
        BotPlayerMark = 'O';
        HumanPlayerMark = 'X';
    }
    else
    if (Selection==1)
    {
        BotPlayerMark = 'X';
        HumanPlayerMark = 'O';
    }
}

int Minimax(char CurrentBoard[][50], int depth, bool IsMax,int k)
{
    char Winner;
    int bestScore=-1e9, score;
    DefineBotPlayer(k);
    Winner = CheckMinimaxWin(CurrentBoard);

    if (Winner == BotPlayerMark) return 10 - depth;
    else
        if (Winner == HumanPlayerMark) return depth - 10;
        else
            if (IsMinimaxBoardFull(CurrentBoard)) return 0;

    if (IsMax)
    {
        bestScore = -1e9;
        for (int i = 1; i <= 3; i++)
        {
            for (int j = 1; j <= 3; j++)
            {
                if (CurrentBoard[i][j] == ' ')
                {
                    CurrentBoard[i][j] = BotPlayerMark;
                    score = Minimax(CurrentBoard, depth + 1, false,k);
                    CurrentBoard[i][j] = ' ';
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
                if (CurrentBoard[i][j] == ' ')
                {
                    CurrentBoard[i][j] = HumanPlayerMark;
                    score = Minimax(CurrentBoard, depth + 1, true,k);
                    CurrentBoard[i][j] = ' ';
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

Coord BestMove(char CurrentBoard[][50], int k)
{
    int BestScore=-1e9, MoveScore;
    Coord CurrentBest{};
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            if (CurrentBoard[i][j] == ' ')
            {
                CurrentBoard[i][j] = BotPlayerMark;
                MoveScore = Minimax(CurrentBoard, 0, false,k);
                CurrentBoard[i][j] = ' ';
                if (MoveScore > BestScore)
                {
                    BestScore = MoveScore;
                    CurrentBest.x = i; CurrentBest.y = j;
                }
            }
        }
    }
    return CurrentBest;
}

Coord BlockThree(int n, char Board[][50], int tx, int ty, char HumanPlayer)
{
    // Chan dong 
    int i, j, l, r, cnt;
    cnt = 0;
    i = ty - 1;
    while (Board[tx][i] == HumanPlayer && i > 0)
    {
        i--;
        cnt++;
    }
    int LeftRow = i;
    i = ty + 1;
    while (Board[tx][i] == HumanPlayer && i <= n)
    {
        i++;
        cnt++;
    }
    int RightRow = i;
    if (cnt+1 >= 3)
    {
        if (LeftRow > 0 && Board[tx][LeftRow] == ' ') return { tx,LeftRow };
        if (RightRow <= n && Board[tx][RightRow] == ' ') return { tx,RightRow };
    }
    // chan cot
    j = tx - 1;
    while (Board[j][ty] == HumanPlayer && j > 0)
    {
        j--;
        cnt++;
    }
    int UpCol = j;
    j = tx + 1;
    while (Board[j][ty] == HumanPlayer && j <= n)
    {
        j++;
        cnt++;
    }
    int EndCol = j;
    if (cnt + 1 >= 3)
    {
        if (UpCol > 0 && Board[UpCol][ty] == ' ') return { UpCol,ty };
        if (EndCol <= n && Board[EndCol][ty] == ' ') return { EndCol,ty };
    }
    // chan cheo 1
    l = tx - 1;
    r = ty + 1;
    cnt = 0;
    while (Board[l][r] == HumanPlayer)
    {
        if (l < 0 || r > n) break;
        l--;
        r++;
        cnt++;
    }
    Coord UpDiag1 = { l,r };
    l = tx + 1;
    r = ty - 1;
    while (Board[l][r] == HumanPlayer)
    {
        if (l > n || r < 0) break;
        l++;
        r--;
        cnt++;
    }
    Coord EndDiag1 = { l,r };
    if (cnt + 1 >= 3)
    {
        if (UpDiag1.x - 1 > 0 && UpDiag1.y + 1 <= n && Board[UpDiag1.x][UpDiag1.y] == ' ') return { UpDiag1.x,UpDiag1.y };
        if (EndDiag1.x + 1 <= n && EndDiag1.y - 1 > 0 && Board[EndDiag1.x][EndDiag1.y] == ' ') return { EndDiag1.x,EndDiag1.y };
    }
    // Chan cheo 2
    cnt = 0;
    l = tx - 1;
    r = ty - 1;
    while (Board[l][r] == HumanPlayer)
    {
        if (l < 0 || r < 0)
            break;
        l--;
        r--;
        cnt++;
    }
    Coord UpDiag2 = { l,r };
    l = tx + 1;
    r = ty + 1;
    while (Board[l][r] == HumanPlayer)
    {
        if (l > n || r > n)
            break;
        l++;
        r++;
        cnt++;
    }
    Coord EndDiag2 = { l,r };
    if (cnt + 1 >= 3)
    {
        if (UpDiag2.x - 1 > 0 && UpDiag2.y - 1 > 0 && Board[UpDiag2.x][UpDiag2.y] == ' ') return {UpDiag2.x, UpDiag2.y};
        if (EndDiag2.x + 1 <= n && EndDiag2.y + 1 <= n && Board[EndDiag2.x][EndDiag2.y] == ' ') return { EndDiag2.x, EndDiag2.y };
    }
    return { -1,-1 };
}

bool IsValidMove(int r, int c, int n, char Board[][50]) 
{
    return (r >= 1 && r <= n && c >= 1 && c <= n && Board[r][c] == ' ');
}
Coord GetBestAttackMove(int n, char Board[][50], char BotPlayer) 
{
    std::vector<Coord> myPieces;
    // 1. Lấy danh sách tất cả các quân cờ của Bot hiện có
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (Board[i][j] == BotPlayer) {
                myPieces.push_back({ i, j });
            }
        }
    }

    if (myPieces.empty()) return { -1, -1 };

    Coord bestMove = { -1, -1 };
    int maxStreak = -1; // Số quân liên tiếp dài nhất tìm được

    // Các hướng di chuyển: {dx, dy}
    // 0: Ngang, 1: Dọc, 2: Chéo chính, 3: Chéo phụ
    int dx[4] = { 0, 1, 1, 1 };
    int dy[4] = { 1, 0, 1, -1 };

    // 2. Duyệt qua từng quân cờ của Bot để kiểm tra 4 hướng
    for (Coord p : myPieces) 
    {
        for (int dir = 0; dir < 4; dir++) 
        {
            int count = 1; // Đếm quân hiện tại là 1

            // Kiểm tra hướng xuôi (dương)
            int r = p.x + dx[dir];
            int c = p.y + dy[dir];
            while (r >= 1 && r <= n && c >= 1 && c <= n && Board[r][c] == BotPlayer) {
                count++;
                r += dx[dir];
                c += dy[dir];
            }
            Coord tailPos = { r, c }; // Vị trí đuôi (có thể là ô trống hoặc bị chặn)

            // Kiểm tra hướng ngược (âm)
            r = p.x - dx[dir];
            c = p.y - dy[dir];
            while (r >= 1 && r <= n && c >= 1 && c <= n && Board[r][c] == BotPlayer) {
                count++;
                r -= dx[dir];
                c -= dy[dir];
            }
            Coord headPos = { r, c }; // Vị trí đầu

            // 3. Nếu dây này dài hơn dây tốt nhất từng tìm thấy
            // VÀ có thể đánh thêm vào đầu hoặc đuôi
            if (count > maxStreak || (count == maxStreak && rand() % 2 == 0)) {
                bool canExtendTail = IsValidMove(tailPos.x, tailPos.y, n, Board);
                bool canExtendHead = IsValidMove(headPos.x, headPos.y, n, Board);

                if (canExtendTail || canExtendHead) {
                    maxStreak = count;
                    // Ưu tiên chọn đầu nào trống, nếu cả 2 trống thì random
                    if (canExtendTail && canExtendHead) {
                        bestMove = (rand() % 2 == 0) ? tailPos : headPos;
                    }
                    else if (canExtendTail) {
                        bestMove = tailPos;
                    }
                    else {
                        bestMove = headPos;
                    }
                }
            }
        }
    }

    // Nếu chỉ có các quân lẻ tẻ (maxStreak <= 1), trả về -1 để chuyển sang chế độ random hướng
    // để tạo sự đa dạng, tránh việc Bot cứ đánh dính chùm một chỗ quá mức khi mới bắt đầu.
    if (maxStreak > 1) return bestMove;

    return { -1, -1 };
}
Coord RandomDirectionMove(int n, char Board[][50], char BotPlayer) {
    std::vector<Coord> myPieces;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (Board[i][j] == BotPlayer) myPieces.push_back({ i, j });

    if (myPieces.empty()) return { -1, -1 };

    // Thử random xung quanh quân cờ bất kỳ (8 hướng)
    int dx[8] = { -1, 1, 0, 0, -1, 1, -1, 1 };
    int dy[8] = { 0, 0, -1, 1, -1, 1, 1, -1 };
    int attempts = 50;
    while (attempts > 0) {
        int idx = rand() % myPieces.size();
        int dir = rand() % 8;
        int nx = myPieces[idx].x + dx[dir];
        int ny = myPieces[idx].y + dy[dir];
        if (IsValidMove(nx, ny, n, Board)) return { nx, ny };
        attempts--;
    }
    return { -1, -1 };
}

Coord BotTurn(char Board[][50], int n, int k, char PlayerHuman, int cx, int cy, int level)
{
    if (n == 3)
    {
        if (level == 0)
        {
            int i, j;
            while (true)
            {
                i = rand() % 3 + 1;
                j = rand() % 3 + 1;
                if (Board[i][j] == ' ') break;
            }
            return { i,j };
        }
        else
        if (level==1) return BestMove(Board, k);
    }
    else
    if (n==12)
    {
        if (level == 0) //Level Easy
        {
            int i, j;
            while (true)
            {
                i = rand() % 12 + 1;
                j = rand() % 12 + 1;
                if (Board[i][j] == ' ') break;
            }
            return { i,j };
        }
        else
        if (level==1) // Level Medium
        {
            // 1. PHÒNG THỦ: Chặn 3 (Quan trọng nhất)
            Coord tmp = BlockThree(n, Board, cx, cy, PlayerHuman);
            if (tmp.x != -1 && tmp.y != -1) return tmp;

            char CurrentBotPlayer = (PlayerHuman == 'X') ? 'O' : 'X';

            // 2. TẤN CÔNG THÔNG MINH: Ưu tiên nối dài dây đang có nhiều quân nhất
            Coord attackMove = GetBestAttackMove(n, Board, CurrentBotPlayer);
            if (attackMove.x != -1 && attackMove.y != -1) return attackMove;

            // 3. TẤN CÔNG MỞ RỘNG: Nếu chưa có dây dài (chỉ có quân lẻ), đánh random xung quanh quân mình
            Coord randomExt = RandomDirectionMove(n, Board, CurrentBotPlayer);
            if (randomExt.x != -1 && randomExt.y != -1) return randomExt;

            int i, j;
            while (true)
            {
                i = rand() % 12 + 1;
                j = rand() % 12 + 1;
                if (Board[i][j] == ' ') break;
            }
            return { i,j };

        }
        else
        if (level == 2)
        {
            return BestMoveHard(Board);
           // return findBestMove(Board, 3);
        }
       
    }
}

int CheckTypeWin(char CurrentBoard[][50])
{
    for (int i = 1; i <= 3; i++)
    {
        if (CurrentBoard[i][1] == CurrentBoard[i][2] && CurrentBoard[i][2] == CurrentBoard[i][3] && CurrentBoard[i][3] != ' ')
            return 1;
    }

    for (int i = 1; i <= 3; i++)
    {
        if (CurrentBoard[1][i] == CurrentBoard[2][i] && CurrentBoard[2][i] == CurrentBoard[3][i] && CurrentBoard[3][i] != ' ')
            return 2;
    }

    if (CurrentBoard[1][3] == CurrentBoard[2][2] && CurrentBoard[2][2] == CurrentBoard[3][1] && CurrentBoard[3][1] != ' ')
        return 3;

    if (CurrentBoard[1][1] == CurrentBoard[2][2] && CurrentBoard[2][2] == CurrentBoard[3][3] && CurrentBoard[3][3] != ' ')
        return 4;

    
    return -1;
}

const int BOARD_SIZE = 12;
const char BOT_MARK = 'O';
const char HUMAN_MARK = 'X';

int CountPiece(char Board[][50], char type, int len)
{
    int ans = 0;
    for (int i = 1; i <= 12; i++)
    {
        for (int j = 1; j <= 12; j++)
        {
            if (Board[i][j] != type) continue;

            if (j + len <= 12 && Board[i][j - 1] != type && Board[i][j + len] == ' ' && CountRow(type, i, j, Board, 12) >= len)
                ans++;
            if (i + len <= 12 && Board[i - 1][j] != type && Board[i + len][j] == ' ' && CountCol(type, i, j, Board, 12) >= len)
                ans++;
            if (i + len <= 12 && j + len <= 12 && Board[i - 1][j - 1] != type &&  Board[i + len][j + len] == ' ' &&  CountDiag2(type, i, j, Board, 12) >= len)
                ans++;
            if (i - len >= 0 && j + len <= 12 && Board[i + 1][j - 1] != type && Board[i - len][j + len] == ' ' && CountDiag1(type, i, j, Board, 12) >= len)
                ans++;
        }
    }
    return ans;
}


int CountRow(char c, int x, int y, char board[][50], int n)
{
    int i = y - 1, j = y + 1, cnt = 1;
    while (i > 0 && board[x][i] == c)
    {
        i--;
        cnt++;
    }
    while (j <= n && board[x][j] == c)
    {
        j++;
        cnt++;
    }
    return cnt;
}
int CountCol(char c, int x, int y, char board[][50], int n)
{
    int i = x - 1, j = x + 1, cnt = 1;
    while (i > 0 && board[i][y] == c)
    {
        i--;
        cnt++;
    }
    while (j <= n && board[j][y] == c)
    {
        j++;
        cnt++;
    }
    return cnt;
}
int CountDiag1(char c, int x, int y, char board[][50], int n)
{
    int i1 = x - 1, j1 = y + 1, i2 = x + 1, j2 = y - 1, cnt = 1;
    while (i1 > 0 && j1 <= n && board[i1][j1] == c)
    {
        i1--;
        j1++;
        cnt++;
    }
    while (j2 > 0 && i2 <= n && board[i2][j2] == c)
    {
        i2++;
        j2--;
        cnt++;
    }
    return cnt;
}
int CountDiag2(char c, int x, int y, char board[][50], int n)
{
    int i1 = x - 1, j1 = y - 1, i2 = x + 1, j2 = y + 1, cnt = 1;
    while (i1 > 0 && j1 > 0 && board[i1][j1] == c)
    {
        i1--;
        j1--;
        cnt++;
    }
    while (i2 <= n && j2 <= n && board[i2][j2] == c)
    {
        i2++;
        j2++;
        cnt++;
    }
    return cnt;
}
int Value(char Board[][50], char BotMark, char PlayerMark)
{
    int res = 0;
    res += CountPiece(Board,BotMark,4) * 1000000;
    res += CountPiece(Board,BotMark,3) * 100000;
    res += CountPiece(Board,BotMark,2) * 10000;

    res -= CountPiece(Board, PlayerMark, 4) * 90000;
    res -= CountPiece(Board, PlayerMark, 3) * 90000;
    res -= CountPiece(Board, PlayerMark, 2) * 9000;

    return res;

}

// 1. Hàm kiểm tra lân cận (Đã sửa biên 1-12)
bool IsNearPiece(int x, int y, char Board[][50])
{
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            if (dx == 0 && dy == 0) continue;

            int Dx = x + dx;
            int Dy = y + dy;

            if (Dx >= 1 && Dx <= 12 && Dy >= 1 && Dy <= 12) 
            {
                if (Board[Dx][Dy] != ' ') return true;
            }
        }
    }
    return false;
}

// 2. Hàm AlphaBeta (Đã sửa vòng lặp 1-12)
int AlphaBetaPruning(char CurrentBoard[][50], int alpha, int beta, int depth, bool IsMax)
{
    if (depth == 2) // Độ sâu tìm kiếm
        return Value(CurrentBoard, BOT_MARK, HUMAN_MARK);

    if (IsMax) // Lượt BOT
    {
        int maxScore = -1e9; // Dùng số nhỏ đủ lớn thay vì -INF để tránh lỗi tràn số nếu cộng trừ
        bool hasMove = false;

        // SỬA LỖI: Chạy từ 1 đến 12 (thay vì 0 đến < 12)
        for (int i = 1; i <= 12; i++) {
            for (int j = 1; j <= 12; j++) {

                if (CurrentBoard[i][j] == ' ' && IsNearPiece(i, j, CurrentBoard)) 
                {
                    hasMove = true;
                    CurrentBoard[i][j] = BOT_MARK;

                    // Check thắng ngay
                    if (CheckWin(BOT_MARK, i, j, CurrentBoard, 12)) {
                        CurrentBoard[i][j] = ' ';
                        return 100000000 - depth;
                    }

                    int score = AlphaBetaPruning(CurrentBoard, alpha, beta, depth + 1, false);
                    CurrentBoard[i][j] = ' '; // Backtrack

                    if (score > maxScore) maxScore = score;
                    if (maxScore > alpha) alpha = maxScore;
                    if (beta <= alpha) return maxScore;
                }
            }
        }
        if (!hasMove) return Value(CurrentBoard, BOT_MARK, HUMAN_MARK);
        return maxScore;
    }
    else // Lượt NGƯỜI
    {
        int minScore = 1e9;
        bool hasMove = false;

        // SỬA LỖI: Chạy từ 1 đến 12
        for (int i = 1; i <= 12; i++) 
        {
            for (int j = 1; j <= 12; j++) 
            {

                if (CurrentBoard[i][j] == ' ' && IsNearPiece(i, j, CurrentBoard)) 
                {
                    hasMove = true;
                    CurrentBoard[i][j] = HUMAN_MARK;

                    // Check người thắng
                    if (CheckWin(HUMAN_MARK, i, j, CurrentBoard, 12)) {
                        CurrentBoard[i][j] = ' ';
                        return -100000000 + depth;
                    }

                    int score = AlphaBetaPruning(CurrentBoard, alpha, beta, depth + 1, true);
                    CurrentBoard[i][j] = ' '; // Backtrack

                    if (score < minScore) minScore = score;
                    if (minScore < beta) beta = minScore;
                    if (beta <= alpha) return minScore;
                }
            }
        }
        if (!hasMove) return Value(CurrentBoard, BOT_MARK, HUMAN_MARK);
        return minScore;
    }
}

Coord BestMoveHard(char CurrentBoard[][50])
{
    long long BestScore = -1e18; // Khởi tạo số rất nhỏ
    Coord CurrentBest = { -1, -1 };

    // SỬA LỖI: Chạy từ 1 đến 12
    for (int i = 1; i <= 12; i++)
    {
        for (int j = 1; j <= 12; j++)
        {
            if (CurrentBoard[i][j] == ' ' && IsNearPiece(i,j,CurrentBoard))
            {
                CurrentBoard[i][j] = BOT_MARK;

                // 1. Check thắng ngay lập tức
                if (CheckWin(BOT_MARK, i, j, CurrentBoard, 12)) {
                    CurrentBoard[i][j] = ' ';
                    return { i, j };
                }

                // 2. Tính điểm Minimax
                long long MoveScore = AlphaBetaPruning(CurrentBoard, -1e9, 1e9, 0, false);
                CurrentBoard[i][j] = ' ';

                if (MoveScore > BestScore)
                {
                    BestScore = MoveScore;
                    CurrentBest.x = i;
                    CurrentBest.y = j;
                }
            }
        }
    }

    // CHỐT CHẶN AN TOÀN (Safe Guard):
    // Nếu thuật toán lỗi trả về {-1, -1} hoặc nước đi ngoài biên, tìm ô trống đầu tiên hợp lệ trong vùng 1-12
    if (CurrentBest.x < 1 || CurrentBest.x > 12 || CurrentBest.y < 1 || CurrentBest.y > 12)
    {
        for (int i = 1; i <= 12; i++)
            for (int j = 1; j <= 12; j++)
                if (CurrentBoard[i][j] == ' ') return { i, j };
    }

    return CurrentBest;
}