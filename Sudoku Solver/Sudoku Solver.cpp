#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
vector<unordered_map<char, int>> mp = vector<unordered_map<char, int>>(9);
bool isValid1(vector<vector<char>> &board, int row, int col, char ch)
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i][col] == ch && i != row)
            return false;
    }
    for (int j = 0; j < 9; j++)
    {
        if (board[row][j] == ch && j != col)
            return false;
    }
    return true;
}
bool isValidSudoku(vector<vector<char>> &board)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '.')
            {
                if (i >= 0 && i <= 2)
                {
                    mp[j / 3][board[i][j]]++;
                    if (mp[j / 3][board[i][j]] == 2)
                        return false;
                }
                else if (i >= 3 && i <= 5)
                {
                    mp[3 + j / 3][board[i][j]]++;
                    if (mp[3 + j / 3][board[i][j]] == 2)
                        return false;
                }
                else
                {
                    mp[6 + j / 3][board[i][j]]++;
                    if (mp[6 + j / 3][board[i][j]] == 2)
                        return false;
                }
            }
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '.')
                if (!isValid1(board, i, j, board[i][j]))
                    return false;
        }
    }
    return true;
}

bool isValid(vector<vector<char>> &board, int row, int col, char ch)
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i][col] == ch)
            return false;
    }
    for (int j = 0; j < 9; j++)
    {
        if (board[row][j] == ch)
            return false;
    }
    if (row >= 0 && row <= 2)
    {
        if (mp[col / 3][ch] == 1)
        {
            return false;
        }
    }
    else if (row >= 3 && row <= 5)
    {
        if (mp[3 + col / 3][ch] == 1)
        {
            return false;
        }
    }
    else
    {
        if (mp[6 + col / 3][ch] == 1)
        {
            return false;
        }
    }
    return true;
}
void Sudoku(vector<vector<char>> &board, int row, int col, vector<vector<char>> &ans)
{
    if (row == 8 && col == 9)
    {
        ans = board;
        return;
    }
    if (col == 9)
    {
        Sudoku(board, row + 1, 0, ans);
        return;
    }
    if (board[row][col] == '.')
    {
        int flag = 0;
        for (int i = 1; i <= 9; i++)
        {
            char ch = i + '0';
            if (isValid(board, row, col, ch))
            {
                flag = 1;
                board[row][col] = ch;
                if (row >= 0 && row <= 2)
                {
                    mp[col / 3][ch]++;
                }
                else if (row >= 3 && row <= 5)
                {
                    mp[3 + col / 3][ch]++;
                }
                else
                {
                    mp[6 + col / 3][ch]++;
                }
                Sudoku(board, row, col + 1, ans);
                if (!ans.empty())
                {
                    return;
                }
                board[row][col] = '.';
                if (row >= 0 && row <= 2)
                {
                    mp[col / 3][ch]--;
                }
                else if (row >= 3 && row <= 5)
                {
                    mp[3 + col / 3][ch]--;
                }
                else
                {
                    mp[6 + col / 3][ch]--;
                }
            }
        }
        if (flag == 0)
            return;
    }
    else
    {
        Sudoku(board, row, col + 1, ans);
    }
}
void solveSudoku(vector<vector<char>> &board)
{
    vector<vector<char>> ans;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '.')
            {
                if (i >= 0 && i <= 2)
                {
                    mp[j / 3][board[i][j]]++;
                }
                else if (i >= 3 && i <= 5)
                {
                    mp[3 + j / 3][board[i][j]]++;
                }
                else
                {
                    mp[6 + j / 3][board[i][j]]++;
                }
            }
        }
    }
    Sudoku(board, 0, 0, ans);
    board = ans;
}
int main()
{
    vector<vector<char>> board(9, vector<char>(9));
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> board[i][j];
        }
    }
    if (isValidSudoku(board))
    {
        mp = vector<unordered_map<char, int>>(9);
        solveSudoku(board);
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Not a Valid Sudoku" << endl;
    }
}