#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using  namespace std;
#define ppr cout<<(char)219

int bs = 21, snakepos[1000][2], snakelen=9, totalboard[500][500], point, fruitposx, fruitposy, h=1, levelh = 1, stageunlocked[4], stagenumber=1;
char border = 219, c, ch;
bool gameover, f, exit_the_game;
int highscore = 0, stagepoint[6]={100,50,250,200,200,150} ;



HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


void gotoXY(int,int);



void prepare();
void Draw_snake();
void Erase_snake();
void Draw_border();


void homepage(bool whilegame);
void Erase_homepage();
void control_homepage(bool whilegame);
void Start_new_game();
void Continue();
void Level();
void Help();
void Draw();
void Erase_everything();

void key_press();
void move_snake(int x, int y);
void snake_has_eaten_the_fruit(int x, int y);
void new_fruit_pos();

void pointcheck();
void Draw_stage();
void Erase_stage();
void Move_stage();
void stage_normal();
void stage_tunnel();
void stage_campaign();
void stage_apartment();
void stage_maze();
void whichstage();






void Erase_everything(){
    for(int i=0; i<bs+3; i++)gotoXY(i,0),cout<<"                                                                                             ";


    for(int i=0; i<=2*bs; i++)
        for(int j=0; j<=bs-1;  j++)
            totalboard[j][i]=0;
}


void stage_normal(){
    for(int i=0; i<bs; i++)gotoXY(i, 0),cout<<'|',totalboard[i][0]=3;
    for(int i=0; i<bs; i++)gotoXY(i, 2*bs),cout<<'|',totalboard[i][2*bs]=3;
    for(int i=0; i<=2*bs; i++)gotoXY(0,i),cout<<'|',totalboard[0][i]=3;
    for(int i=0; i<=2*bs; i++)gotoXY(bs-1,i),cout<<'|',totalboard[bs-1][i]=3;    
}

void stage_campaign(){
    Draw_border();
}

void stage_tunnel(){
    for(int i=4; i<bs-4; i++)gotoXY(i, 0),cout<<'|',totalboard[i][0]=3;
    for(int i=4; i<bs-4; i++)gotoXY(i, 2*bs),cout<<'|',totalboard[i][2*bs]=3;
    for(int i=9; i<=2*bs-9; i++)gotoXY(0,i),cout<<'|',totalboard[0][i]=3;
    for(int i=9; i<=2*bs-9; i++)gotoXY(bs-1,i),cout<<'|',totalboard[bs-1][i]=3;

    for(int i=11; i<=bs+bs-11; i++)gotoXY(6, i), cout<<(char)border, totalboard[6][i] = 1;
    for(int i=11; i<=bs+bs-11; i++)gotoXY(bs-6, i), cout<<(char)border, totalboard[bs-6][i] = 1;
}

void stage_apartment(){
    for(int i=0; i<bs; i++)gotoXY(i, 0),cout<<'|',totalboard[i][0]=3;
    for(int i=0; i<bs; i++)gotoXY(i, 2*bs),cout<<'|',totalboard[i][2*bs]=3;
    for(int i=0; i<=2*bs; i++)gotoXY(0,i),cout<<'|',totalboard[0][i]=3;
    for(int i=0; i<=2*bs; i++)gotoXY(bs-1,i),cout<<'|',totalboard[bs-1][i]=3;    

    for(int i=0; i<=2*bs; i++)gotoXY(6, i), cout<<(char)border, totalboard[6][i]=1;
    for(int i=1; i<=6; i++)gotoXY(i, 10), ppr, totalboard[i][10] = 1;
    for(int i=1; i<=6; i++)gotoXY(i, 11), ppr, totalboard[i][11] = 1;
    for(int i=0; i<=2*bs; i++)
    if(i<13 or i>19)
    gotoXY(bs-6, i), cout<<(char)border, totalboard[bs-6][i]=1;
    
}

void stage_maze(){
    for(int i=0; i<bs; i++)gotoXY(i, 0),cout<<'|',totalboard[i][0]=3;
    for(int i=0; i<bs; i++)gotoXY(i, 2*bs),cout<<'|',totalboard[i][2*bs]=3;
    for(int i=0; i<=2*bs; i++)gotoXY(0,i),cout<<'|',totalboard[0][i]=3;
    for(int i=0; i<=2*bs; i++)gotoXY(bs-1,i),cout<<'|',totalboard[bs-1][i]=3;    

    for(int i=0; i<=2*bs; i++)gotoXY(6, i), cout<<(char)border, totalboard[6][i]=1;
    for(int i=1; i<=6; i++)gotoXY(i, 16), ppr, totalboard[i][16] = 1;
    for(int i=1; i<=6; i++)gotoXY(i, 17), ppr, totalboard[i][17] = 1;
    for(int i=0; i<=2*bs; i++)
    if(i<13 or i>19)
    gotoXY(bs-6, i), cout<<(char)border, totalboard[bs-6][i]=1;
    for(int i=bs-6; i<bs; i++)gotoXY(i, 20), ppr, totalboard[i][20]=1;
    for(int i=bs-6; i<bs; i++)gotoXY(i, 21), ppr, totalboard[i][21]=1;
    for(int i=14; i<30; i++)gotoXY(bs-1, i), ppr, totalboard[bs-1][i]=1, totalboard[0][i]=1;
    for(int i=bs-3; i<bs; i++)gotoXY(i, 2*bs), ppr, totalboard[i][2*bs]=1, totalboard[i][0]=1;
    for(int i=bs-3; i<bs; i++)gotoXY(i, 2*bs-1), ppr, totalboard[i][2*bs-1]=1;
    
}



void Erase_stage(){
gotoXY(3,1); cout<<"                      ";
gotoXY(4,1); cout<<"                           ";
gotoXY(8,1); cout<<"                    ";
gotoXY(10,1);cout<<"                       ";
gotoXY(12,1);cout<<"                         ";
gotoXY(14,1);cout<<"                                   ";
gotoXY(16,1);cout<<"                                   ";
}


void Draw_stage(){
gotoXY(3,1); cout<<"                Stages";
gotoXY(4,1); cout<<"            _______________";
gotoXY(8,1); cout<<"       Normal";
gotoXY(10,1);cout<<"          * Campaign";
gotoXY(12,1);cout<<"               * Tunnel";
gotoXY(14,1);cout<<"                     * Apartment";
gotoXY(16,1);cout<<"                          * Maze";


if(stageunlocked[levelh] >= 2)gotoXY(10,11),cout<<' ';
if(stageunlocked[levelh] >= 3)gotoXY(12,16),cout<<' ';
if(stageunlocked[levelh] >= 4)gotoXY(14,22),cout<<' ';
if(stageunlocked[levelh] >= 5)gotoXY(16,27),cout<<' ';

Move_stage();
}



void Move_stage(){
if(stagenumber < 1)stagenumber = stageunlocked[levelh];
if(stagenumber > stageunlocked[levelh])stagenumber=1;
if(stagenumber == 1)gotoXY(8,6),cout<<'>';
else if(stagenumber == 2)gotoXY(10,11),cout<<'>';
else if(stagenumber == 3)gotoXY(12,16),cout<<'>';
else if(stagenumber == 4)gotoXY(14,22),cout<<'>';
else if(stagenumber == 5)gotoXY(16,27),cout<<'>';
gotoXY(bs+1,0);
char q = getch();
    if(q - 'w' and q - 'a' and q - 's' and q - 'd' and q - 'j'){
    Move_stage();
    return;
    }
if(stagenumber == 1)gotoXY(8,6),cout<<' ';
else if(stagenumber == 2)gotoXY(10,11),cout<<' ';
else if(stagenumber == 3)gotoXY(12,16),cout<<' ';
else if(stagenumber == 4)gotoXY(14,22),cout<<' ';
else if(stagenumber == 5)gotoXY(16,27),cout<<' ';
    if(q == 'w' or q == 'a')stagenumber--;
    else if(q == 's' or q == 'd')stagenumber++;
    else if(q == 'j'){
        Erase_stage();
        whichstage();

        gotoXY(9,50);cout<<"Target : "<<stagepoint[stagenumber];
        gotoXY(10,50);
        cout<<"Point : 0";

        Draw_snake();
        new_fruit_pos();

        pointcheck();
        Sleep(300);
        Erase_everything();
        Draw_border();
        return;
    }
    
Move_stage();
}

void whichstage(){
    if(stagenumber == 1)stage_normal();
    else if(stagenumber == 2)stage_campaign();
    else if(stagenumber == 3)stage_tunnel();
    else if(stagenumber == 4)stage_apartment();
    else if(stagenumber == 5)stage_maze();
}



void Erase_homepage(){
    gotoXY(4,12),cout<<"                ";
    gotoXY(8,15),cout<<"               ";
    gotoXY(12,17),cout<<"               ";
    gotoXY(16,17),cout<<"               ";
}


void homepage(bool whilegame){
    if(exit_the_game)return;
    Erase_everything();
    Draw_border();
    gotoXY(8, 18); cout<<"Level";
    if(whilegame){
        h = 2;
        gotoXY(8, 17); cout<<"Continue";
    }
    gotoXY(4, 14); cout<<"Start New Game";
    gotoXY(12, 19); cout<<"Help";
    gotoXY(16, 19); cout<<"Exit";
    control_homepage(whilegame);
}


void control_homepage(bool whilegame){
    if(exit_the_game)return;
    if(h<1)h=4;
    else if(h>4) h=1;

    int tx, ty;

    if(h==1)tx=4, ty=12;
    else if(h==2)tx=8, ty=15;
    else if(h==3)tx=12, ty=17;
    else tx=16, ty=17;

    gotoXY(tx, ty);

    cout<<'>';
    gotoXY(bs+1, 0);


    char cli = getch();
    if(cli == 'w')h--;
    else if(cli == 's')h++;
    else if(cli == 'j'){
        Erase_homepage();
        if(h == 4){
            exit_the_game = 1;
        }
        else if(h == 1){
            Start_new_game();
            homepage(0);
        }
        else if(h == 2){
            if(whilegame){
                whichstage();
                Draw_snake();
                gotoXY(fruitposx, fruitposy);
                cout<<"#";
                totalboard[fruitposx][fruitposy] = 2;
                gotoXY(9,50);cout<<"Target : "<<stagepoint[stagenumber];
                gotoXY(10,50);
                cout<<"Point : 0";
            
            }
            else {
                Level();
                homepage(0);
            }
        }
        else if(h == 3){
            Help();
            homepage(whilegame);
        }
        return;
    }

    gotoXY(tx, ty);
    cout<<" ";
    control_homepage(whilegame);
}


void Level(){
    gotoXY(12, 50); cout<<"Click \'j\' to select...";
    gotoXY(9, 13);int aa=16;while(aa--)cout<<'.';
    gotoXY(10,13);cout<<"|";aa=5*levelh;while(aa--)ppr;
    gotoXY(10, 28); cout<<"|";
    gotoXY(11, 13);aa=16;while(aa--)cout<<'\'';
    gotoXY(bs+1,0);
    char levelcont = getch();
    if(levelcont == 'd'){
        if(levelh < 3){
            levelh++;
            gotoXY(10,14);
            for(aa=5*levelh; aa--; ppr);
        }
    }
    else if(levelcont == 'a'){
        if(levelh>1)levelh--;
        gotoXY(10,14+5*levelh);
        for(aa=5*(3-levelh); aa--; cout<<' ');
    }
    else if(levelcont == 'j'){
        gotoXY(9, 13);for(aa=18;aa--;cout<<' ');
        gotoXY(10, 13);for(aa=18;aa--;cout<<' ');
        gotoXY(11, 13);for(aa=18;aa--;cout<<' ');
        gotoXY(12, 50); for(aa=22; aa--; cout<<' ');
        return;
    }
    Level();

}


void pointcheck(){
    if(exit_the_game)return;
    gotoXY(10,58); cout<<point;
    gotoXY(bs+1,0);
    if(gameover == 0 and point != stagepoint[stagenumber]){        
        Sleep(100*(4-levelh));
        key_press();
        pointcheck();
        return;
    }
    h = 1;
}



void prepare(){
    stageunlocked[1] = 5;
    stageunlocked[2] = 5;
    stageunlocked[3] = 5;
    point=gameover=0;
    snakelen = 9;
    c=ch='d';
    for(int i=0,j=0; i<snakelen; i++, j+=2)snakepos[i][0]=bs/2,snakepos[i][1]=bs/2+j;

}

void Start_new_game(){
    if(exit_the_game)return;
    prepare();
    Level();
    Draw_stage(); //////////
    if(exit_the_game)return;


    gotoXY(10,15); 
    if(point == stagepoint[stagenumber]){
        gotoXY(10,13);
        cout<<"Stage complete !!!";
    }
    else cout<<"Point : "<<point;
    gotoXY(bs+1,0);
    cout<<"Press \'j\' to go to homepage... ";
    for(c=getch();c-'j';c=getch());
    gotoXY(bs+1,0);
    cout<<"                                   ";
    gotoXY(10,15);cout<<"                ";
}


void key_press(){
    int x=snakepos[snakelen-1][0];
    int y=snakepos[snakelen-1][1];
    if(_kbhit()){
        c=getch();
    }
    if(c == 'w' and ch == 's')c=ch;
    else if(c == 's' and ch == 'w')c=ch;
    else if(c == 'a' and ch == 'd')c=ch;
    else if(c == 'd' and ch == 'a')c=ch;
    else if(c == 'j'){
        homepage(1);
        if(exit_the_game)return;
        c=ch;
    }
    else ch = c;

    if(c=='w')x--;
    else if(c=='s')x++;
    else if(c=='a')y-=2;
    else if(c=='d')y+=2;


    if(totalboard[x][y] == 1){
        gotoXY(snakepos[snakelen-1][0], snakepos[snakelen-1][1]); cout<<"X";
        gameover=1;
    }
    else if(totalboard[x][y] == 2)snake_has_eaten_the_fruit(x,y);
    else if(totalboard[x][y] == 3){
        if(x == 0)x=bs-2;
        else if(x == bs-1)x=1;
        else if(y == 0)y=2*bs-2;
        else if(y == 2*bs)y=2;
        if(totalboard[x][y] == 2)snake_has_eaten_the_fruit(x,y);
        else move_snake(x,y);
    }
    else move_snake(x,y);
}


void move_snake(int x, int y){
    snakepos[snakelen][0] = x;
    snakepos[snakelen][1] = y;

    totalboard[snakepos[0][0]][snakepos[0][1]]=0;
    totalboard[x][y]=1;


    gotoXY(snakepos[0][0], snakepos[0][1]); cout<<" ";
    gotoXY(x, y); cout<<'O';
    gotoXY(snakepos[snakelen-1][0], snakepos[snakelen-1][1]); 
    if((snakelen-1+f)&1)cout<<(char)248;
    else cout<<'o';
    
    for(int i=0; i<snakelen; i++)snakepos[i][0]=snakepos[i+1][0], snakepos[i][1]=snakepos[i+1][1];

    f=!f;
}

void snake_has_eaten_the_fruit(int x, int y){
    point += 10;

    snakepos[snakelen][0] = x;
    snakepos[snakelen][1] = y;

    gotoXY(x, y);totalboard[x][y]=1; cout<<"O";
    gotoXY(snakepos[snakelen-1][0], snakepos[snakelen-1][1]); 
    if((snakelen-1+f)&1)cout<<(char)248;   // if eating fruit glich, delete f in this line....
    else cout<<"o";

    snakelen++;
    new_fruit_pos();
}


void Help(){
    int tr=7;
    gotoXY(2,tr);cout<<"        H E L P";
    gotoXY(3,tr);cout<<"     ______________";

    gotoXY(5,tr); cout<<"\'w\' -> Navigate UP";
    gotoXY(6,tr); cout<<"\'s\' -> Navigate DOWN";
    gotoXY(7,tr); cout<<"\'a\' -> Navigate LEFT";
    gotoXY(8,tr); cout<<"\'d\' -> Navigate RIGHT";
    gotoXY(9,tr); cout<<"\'j\' -> Go back to main menu";
    
    gotoXY(11,tr); cout<<"The snake is hunting for the";
    gotoXY(12,tr); cout<<"food which looks like \'#\' and";
    gotoXY(13,tr); cout<<"each time it eats the food, it";
    gotoXY(14,tr); cout<<"becomes larger and a new food";
    gotoXY(15,tr); cout<<"grows somewhere else.";              
    gotoXY(16,tr); cout<<"But if the snake hit the border\'"<<(char)border<<'\'';
    gotoXY(17,tr); cout<<"or its body, then it dies.";

    gotoXY(bs+1,0);

    getch();
    for(int i=2; i<18; i++)gotoXY(i,tr),cout<<"                                ";
}


void Draw_border(){
    for(int i=0; i<=2*bs; i++)gotoXY(0,i),cout<<border,totalboard[0][i]=1;
    for(int i=0; i<=2*bs; i++)gotoXY(bs-1,i),cout<<border,totalboard[bs-1][i]=1;
    for(int i=0; i<bs; i++)gotoXY(i, 0),cout<<border,totalboard[i][0]=1;
    for(int i=0; i<bs; i++)gotoXY(i, 2*bs),cout<<border,totalboard[i][2*bs]=1;
}


void Draw_snake(){
    for(int i=0; i<snakelen; i++){
        totalboard[snakepos[i][0]][snakepos[i][1]]=1;
        gotoXY(snakepos[i][0], snakepos[i][1]);
        if(i&1 and i!=snakelen-1)cout<<(char)248;
        else cout<<"oO"[i==snakelen-1];
    }
}

void Erase_snake(){
    for(int i=0; i<snakelen; i++){
        totalboard[snakepos[i][0]][snakepos[i][1]]=0;
        gotoXY(snakepos[i][0], snakepos[i][1]);
        cout<<' ';
    }
}


void new_fruit_pos(){
    if(gameover == 1){
        totalboard[fruitposx][fruitposy] = 0;
        gotoXY(fruitposx, fruitposy),cout<<' ';
        return;}
    fruitposy = rand()%(bs-1); fruitposy = 2*fruitposy+2;
    fruitposx = rand()%(bs-2); fruitposx++;
    int x = fruitposx;
    int y = fruitposy;
    if(totalboard[x][y])new_fruit_pos();
    else{
        gotoXY(x, y);
        totalboard[x][y] = 2;
        cout<<"#";
    }
}






int main()
{
    Draw_border();

    homepage(0);
    Erase_everything();
    gotoXY(0,0);
}

/*
▓ -> 178
█ -> 219 -> more preferable
° -> 248 -> Snake body
*/





void gotoXY(int y, int x) 
{ 
    CursorPosition.X = x; 
    CursorPosition.Y = y; 
    SetConsoleCursorPosition(console,CursorPosition); 
}
