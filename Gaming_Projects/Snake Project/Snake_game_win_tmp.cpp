#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
    int conWid, conRow;
    int br=21, bc=42;
    #define cursor(wid, row) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){wid+conWid/2-bc/2, row+conRow/2-br/2})
void consolesize() 
{
    CONSOLE_SCREEN_BUFFER_INFO vejachokh;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &vejachokh);
    conWid = (int)vejachokh.srWindow.Right - vejachokh.srWindow.Left + 1;
    conRow = (int)vejachokh.srWindow.Bottom - vejachokh.srWindow.Top + 1;
}
vector<pair<int,int>> toChange;
char board[50][50];



main()
{
    consolesize();
    cursor(16,0);
    printf("a, \a");
    cout<<"🐸";
    cout<<conRow/2;
}
