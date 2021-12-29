#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


void gotoXY(int y, int x) 
{
    CursorPosition.X = x ; 
    CursorPosition.Y = y ; 
    SetConsoleCursorPosition(console,CursorPosition); 
}

void csc(){
    gotoXY(0,0);
    cout << string( 1000, '\n' );
    gotoXY(0,0);
}
int point;
int snakeposr, snakeposc, snakelen;
int boardsize = 21;
int fruitposr = boardsize/3, fruitposc = boardsize/3;
char board[1000][1000], c, homed[1000][1000], ch;
int snake[1000][2];
int snakehead=2, snaketail=0;
int h=0;
bool gameover, cont;
void homepage();
void homedraw();
void continuegame();
void startgame(){
    memset(board, ' ', sizeof(board));
    for(int i=1; i<=boardsize; i++)board[1][i] = board[boardsize][i] = board[i][1] = board[i][boardsize] = '▀';
    point = 0;
    snakeposr = boardsize/2 + 1;
    snakeposc = boardsize/2;
    snakelen = 3;
    for(int i=0; i<snakelen; i++)
        snake[i][0] = snakeposr, snake[i][1] = snakeposc++;
    for(int i=0; i<snakelen; i++)board[snake[i][0]][snake[i][1]] = (i==snakelen-1? 'O': 'o');
    board[fruitposr][fruitposc] = '#';
}
void fruitposchange(){
    fruitposr = rand() % (boardsize-2) + 2;
    fruitposc = rand() % (boardsize-2) + 2;
    if(board[fruitposr][fruitposc] == 'O' or board[fruitposr][fruitposc]=='o'){
        fruitposchange();
    }
    else board[fruitposr][fruitposc]='#';
    
}
void move(){
    int tmpr = snake[snakelen-1][0], tmpc = snake[snakelen-1][1];
    ch = c;
    if(_kbhit()){
        c = _getch();
        if(c == 'x'){
            cont=1, continuegame();
            if(h == 6)return;
        }
        if(ch == 'w' and c == 's')c=ch;
        else if(ch == 's' and c == 'w')c=ch;
        else if(ch == 'a' and c == 'd')c=ch;
        else if(ch == 'd' and c == 'a')c=ch;
        else if(c-'w' and c-'s' and c-'a' and c-'d')c=ch;
    }
         if(c == 'w')tmpr--;
    else if(c == 's')tmpr++;
    else if(c == 'a')tmpc--;
    else if(c == 'd')tmpc++;

    if(tmpr == fruitposr and tmpc == fruitposc){
        board[snake[snakelen-1][0]][snake[snakelen-1][1]] = 'o';
        snake[snakelen][0] = tmpr;
        snake[snakelen++][1] = tmpc;
        board[tmpr][tmpc] = 'O';
        point += 10;
        fruitposchange();
        return;
    }

    else if(tmpr == boardsize or tmpc == boardsize or  tmpr == 1 or tmpc == 1)board[snake[snakelen-1][0]][snake[snakelen-1][1]]='X',gameover = 1;

    else{
        board[snake[0][0]][snake[0][1]] = ' ';
        board[snake[snakelen-1][0]][snake[snakelen-1][1]] = 'o';
        if(board[tmpr][tmpc] == ' ')
            board[tmpr][tmpc] = 'O';
        else board[tmpr][tmpc] = 'X', gameover = 1;
        
        for(int i=0; i<snakelen-1; i++)snake[i][0]=snake[i+1][0], snake[i][1]=snake[i+1][1];
        snake[snakelen-1][0] = tmpr;
        snake[snakelen-1][1] = tmpc;

    }
}
void printboard(){
    if(h==6)return;
    csc();
    for(int i=1; i<=boardsize; i++)
        for(int j = 1; j<=boardsize; cout<<board[i][j++]<<" \n"[j>boardsize]);
}
void ppq(){
    csc();
    cout<<"Press \'w\' to navigate up and \'s\' to navigate down\nPress \'x\' to enter.\n\n";
    for(int i=1; i<=boardsize; i++)
        for(int j = 1; j<=boardsize; cout<<homed[i][j++]<<" \n"[j>boardsize]);
}
void snakegame(){
    if(h==6)return;
    if(gameover){
        Sleep(500);
        csc();
        cout<<"Points = "<<point<<'\n'<<"\nPress x to go back to homepage\n";getch();
        snakelen = 3;
        gameover = 0;
        cont=0;
        homedraw();
    }
    else {
    move();
    printboard();
    cout<<"\n\n\n"<<"Point: "<<point;
    Sleep(100);
    snakegame();}
}
void newgame(){
    startgame();
    c='d';
    snakegame();
}
void continuegame(){
    h = -3;
    memset(homed, ' ', sizeof(homed));
    for(int i=1; i<=boardsize; i++)homed[1][i] = homed[boardsize][i] = homed[i][1] = homed[i][boardsize] = '▀';
    int i=boardsize/2-3, j=0;
    for(auto it: (string)"Continue")homed[i][i+j]=it, j++; j=-5, i+=3;
    for(auto it: (string)"Start New Game")homed[i][i+j]=it, j++;j=-4;i+=3;
    for(auto it: (string)"Help")homed[i][i+j]=it, j++;j=-7, i+=3;
    for(auto it: (string)"Exit")homed[i][i+j]=it, j++;
    if(h==-3)homed[boardsize/2-3][boardsize/2-3-1]='>';
    else if(h==0)homed[boardsize/2][boardsize/2-5-1]='>';
    else if(h==3)homed[boardsize/2+3][boardsize/2+3-4-1]='>';
    else homed[boardsize/2+6][boardsize/2+6-7-1]='>';
    ppq();
    homepage();
}
void continuemove(){
    if(h<-3)h=6;
    else if(h>6)h=-3;
    if(h == -3){
        homed[boardsize/2-3][boardsize/2-3-1]='>';
        homed[boardsize/2][boardsize/2-5-1]=' ';
        homed[boardsize/2+3][boardsize/2+3-4-1]=' ';
        homed[boardsize/2+6][boardsize/2+6-7-1]=' ';
    }
    else if(h == 0){
        homed[boardsize/2-3][boardsize/2-3-1]=' ';
        homed[boardsize/2][boardsize/2-5-1]='>';
        homed[boardsize/2+3][boardsize/2+3-4-1]=' ';
        homed[boardsize/2+6][boardsize/2+6-7-1]=' ';
    }
    else if(h == 3){
        homed[boardsize/2-3][boardsize/2-3-1]=' ';
        homed[boardsize/2][boardsize/2-5-1]=' ';
        homed[boardsize/2+3][boardsize/2+3-4-1]='>';
        homed[boardsize/2+6][boardsize/2+6-7-1]=' ';
    }
    else if(h == 6){
        homed[boardsize/2-3][boardsize/2-3-1]=' ';
        homed[boardsize/2][boardsize/2-5-1]=' ';
        homed[boardsize/2+3][boardsize/2+3-4-1]=' ';
        homed[boardsize/2+6][boardsize/2+6-7-1]='>';
    }
    ppq();
    homepage();
}
void homedraw(){
    h=0;
    memset(homed, ' ', sizeof(homed));
    for(int i=1; i<=boardsize; i++)homed[1][i] = homed[boardsize][i] = homed[i][1] = homed[i][boardsize] = '▀';
    string sta = "Start New Game";    
    int i=boardsize/2-3, j=-2;
    for(auto it: sta)homed[i][i+j]=it, j++;j=-1;i+=3;
    sta = "Help";
    for(auto it: sta)homed[i][i+j]=it, j++;j=-4, i+=3;
    sta = "Exit";
    if(h==0)homed[boardsize/2-3][boardsize/2-3-2-1]='>';
    else if(h==3)homed[boardsize/2][boardsize/2-1-1]='>';
    else homed[boardsize/2+3][boardsize/2+3-4-1]='>';
    for(auto it: sta)homed[i][i+j]=it, j++;
    ppq();
    homepage();
}
void homemove(){
    if(h>6)h=0;
    else if(h<0)h=6;
    if(h==0){
        homed[boardsize/2-3][boardsize/2-3-2-1]='>';
        homed[boardsize/2][boardsize/2-1-1]=' ';
        homed[boardsize/2+3][boardsize/2+3-4-1]=' ';
    }
    else if(h==3){
        homed[boardsize/2-3][boardsize/2-3-2-1]=' ';
        homed[boardsize/2][boardsize/2-1-1]='>';
        homed[boardsize/2+3][boardsize/2+3-4-1]=' ';
    }
    else{
        homed[boardsize/2-3][boardsize/2-3-2-1]=' ';
        homed[boardsize/2][boardsize/2-1-1]=' ';
        homed[boardsize/2+3][boardsize/2+3-4-1]='>';
    }
    ppq();
    homepage();
}
void homepage(){
    char kk = _getch();
    if(kk == 'w'){
        h-=3;
        if(cont)continuemove();
        else homemove();
    }
    else if(kk == 's'){
        h+=3;
        if(cont)continuemove(); 
        else homemove();
    }
    else if(kk == 'x'){
        if(h == 6)return;
        if(h == -3){
            c = ch;
        }
        else if(h == 0)newgame();
        else if(h == 3){
            csc();
            cout<<R"(
._______________________________________.
|                                       |
|               H E L P                 |
|           ________________            |
|                                       |
|                                       |
|     'w' -> Navigate DOWN              |
|     's' -> Navigate UP                |
|     'a' -> Navigate LEFT              |
|     'd' -> Navigate RIGHT             |
|     'x' -> Back to main menu          |
|                                       |
|    The snake is hunting for the       |
|    food which looks like '#' and      |
|    each time it eats the food, it     |
|    becomes larger and a new food      |
|    grows somewhere else.              |
|    But if the snake hit the wall      |
|    or its body, then it dies.         |
|                                       |
|_______________________________________|)";
            getch();
            if(cont)continuemove();
            else homemove();
        }
    }
}
int main()
{
    homedraw();
    system("cls");
    cout<<R"(
._______________________________________.
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|             Press x again             |
|                to Exit                |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|_______________________________________|)";
}