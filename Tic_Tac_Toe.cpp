#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
char drawing[10][10];
#define opt optio==1?'X':'O';
int optio=1;
bool visited[10], gameover = 0;
void draw()
{
    system("cls");
    cout<<"Turn for Player "<<optio<<'\n'<<"Use numkeys to play...\n\n";
    for(auto i=1; i<=5; i++, cout<<'\n')
    for(auto j=1; j<=5; j++){
        if(drawing[i][j]==0)cout<<"  ";
        else cout<<drawing[i][j]<<' ';
    }
}
void valuechange(){
    int k = _getch() - 48;
    int r = ceil(k/3.);
    int p = k%3?k%3:3;
    if(visited[k]==0){
        drawing[r*2-1][p*2-1]=opt;
        visited[k] = 1;
    }
    else{
        valuechange(); return;
    }
    optio = optio^3;
}
void score()
{
    if((drawing[1][1] and drawing[1][1]==drawing[1][3] and drawing[1][1]==drawing[1][5]) or
        (drawing[3][1] and drawing[3][1]==drawing[3][3] and drawing[3][1]==drawing[3][5]) or
        (drawing[5][1] and drawing[5][1]==drawing[5][3] and drawing[5][1]==drawing[5][5]) or

        (drawing[1][1] and drawing[1][1]==drawing[3][1] and drawing[3][1]==drawing[5][1]) or
        (drawing[1][3] and drawing[1][3]==drawing[3][3] and drawing[3][3]==drawing[5][3]) or
        (drawing[1][5] and drawing[1][5]==drawing[3][5] and drawing[3][5]==drawing[5][5]) or

        (drawing[1][1] and drawing[1][1]==drawing[3][3] and drawing[1][1]==drawing[5][5]) or
        (drawing[3][1] and drawing[3][1]==drawing[3][3] and drawing[3][1]==drawing[5][1])){
            gameover = 1; draw();
            cout<<'\n'<<'\n'<<"Player "<<(optio^3)<<" wins\n";
        }
}
int main()
{
    drawing[1][2] = drawing[1][4] = drawing[3][2] = drawing[3][4] = drawing[5][2] = drawing[5][4] ='|';
    drawing[2][1] = drawing[2][3] = drawing[2][5] = drawing[4][1] = drawing[4][3] = drawing[4][5] ='-';
    while(!gameover){
        draw();
        valuechange();
        score();
    }
    getch();
}