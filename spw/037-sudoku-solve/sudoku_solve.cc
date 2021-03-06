#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

/**
 * Problem: shudu solve
 * Solve: 1. three flag vector
 *        2. scan from left to right, from top to down
 *        3. use a flag varibale to identify that we find an solution
 * Tips: 1. every row and column we have 9 digits: 1...9
 *       2. before we dfs next time we find next place, we must save the
 *          previous x, y, then we can backtrace.
 *
 */
bool row[10][10];
bool col[10][10];
bool lattice[10][10];
bool find = false;

void dfs(vector<vector<char> > &board, int x, int y)
{
    //if (find) return;
    // find the first board[x][y] is empty
    while (x < 9) {
        while (y < 9) {
            if (board[x][y] != '.') ++y;
            else break;
        }

        if (y == 9) {++x; y = 0;}
        else break;
    }
    if (x == 9) {
        find = true;
        return;
    }

    int lp = (x / 3) * 3 + y / 3;
    for (int digit = 1; digit <= 9; ++digit) {
        if (!row[x][digit] && !col[y][digit] && !lattice[lp][digit]) {
            row[x][digit] = col[y][digit] = lattice[lp][digit] = true;
            board[x][y] = digit + '0';

            if (x == 8 && y == 8) {
                find = true;
                return;
            }
            // use temp variable
            int tx = x, ty = y;
            if (ty < 8) ++ty;
            else if (tx < 8){
                ty = 0; ++tx;
            }
            dfs(board, tx, ty);
            if (find) return;

            board[x][y] = '.';
            row[x][digit] = col[y][digit] = lattice[lp][digit] = false;
        }
    }

}

void solveSudoku(vector<vector<char> >& board)
{
    memset(row, false, sizeof(row));
    memset(col, false, sizeof(col));
    memset(lattice, false, sizeof(lattice));

    // i < 9 not 10 because we have 9 digits
    // but the range is 1...9
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            char now = board[i][j];
            if (now == '.') continue;
            int digit = now - '0';
            int lp = (i / 3) * 3 + j / 3;

            row[i][digit] = true;
            col[j][digit] = true;
            lattice[lp][digit] = true;
        }
    }

    dfs(board, 0, 0);
    return;
}

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        vector<vector<char> > board;
        for (int i = 0; i < 9; ++i) {
            vector<char> row;
            for (int j = 0; j < 9; ++j) {
                int now;
                scanf("%c", &now);
                row.push_back(now);
            }
            board.push_back(row);
        }
    }
}
class Solution {
    bool row[9][9];
    bool col[9][9];
    bool grid[9][9];
    public:
    bool finish = false;
    void dfs(vector<vector<char>>& board, int x, int y) {
        if (finish) return;

        // if y == 9, then we will move x and set y = 0 here.
        while (x < 9) {
            while (y < 9 && board[x][y] != '.')
                ++y;
            if (y < 9) break;
            else y = 0, x++;
        }

        if (x == 9) {
            finish = true;
            return;
        }

        int g = (x / 3) * 3 + y / 3;
        for (char d = '1'; d <= '9'; ++d) {
            int pos = d - '1';
            if (row[x][pos] || col[y][pos] || grid[g][pos]) continue;

            board[x][y] = d;
            row[x][pos] = col[y][pos] = grid[g][pos] = true;

            // just pass y+1
            dfs(board, x, y+1);
            if (finish) return;

            row[x][pos] = col[y][pos] = grid[g][pos] = false;
        }

        // important !! if its ancestor try is wrong, then all the
        // try are wrong. then we should restore ., all we will not
        // find the empty place in the beginning of the method.
        board[x][y] = '.';

    }

    void solveSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char now = board[i][j];
                if (now == '.')  continue;

                int pos = now - '1', g = i / 3 * 3 + j / 3;
                row[i][pos] = col[j][pos] = grid[g][pos] = true;
            }
        }
        dfs(board, 0, 0);
    }
};
