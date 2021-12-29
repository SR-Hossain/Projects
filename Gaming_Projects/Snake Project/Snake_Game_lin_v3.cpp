#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
int winrow, wincol, tc=42, tr=22;
int snakekey=1, frogkey=2, eaglekey=3, boardkey=4;
char cs, ch;
int totalboard[100][100];
void new_console_size(){
    int precol=wincol, prerow=winrow;
    wincol=WEXITSTATUS(std::system("exit `tput cols`"));
    winrow = WEXITSTATUS(std::system("exit `tput lines`"));
    // if(precol-wincol or prerow-winrow){
    //     if(tw)draw_afresh();
    //     else system("clear");
    // }

}

void cursor(int row, int col){
    printf("\033[%d;%dH", row+winrow/2-10, col+wincol/2-20);
}
char retch(){
    cursor(tr+1, tc/2);
    char kkkk = getch();
    cursor(tr+1, tc/2);
    return kkkk;
}
struct node{
    int row, col;
    node *next, *prev;
    node(){
        next = prev = NULL;
    }
};
struct figure{
    int len, key;
    node *head, *tail;
    figure(){
        head = tail = NULL;
        len = 0;
    }
    void initiate();
    void insert(int, int);
    void draw();
    void erase();
    void move();
    void destruct();
};
void figure::initiate(){
    if(key == snakekey){
        for(int i=0; i<7; i++){
            insert(tr/2, (tc/2-((tc/2)&1)-4+i*2));
            len++;
        }
    }
    else if(key == frogkey){
        node* tmp = new node();
        head = tmp;
        move();
    }
    else if(key == eaglekey){
        for(int i=0; i<3; i++){
            int op = rand()%(tr-2)+1;
            if(totalboard[op][tc]==0)insert(op, tc);
            else i--;
        }
    }
    else if(key == boardkey){

    }
}
void figure::insert(int r, int c){
    node* tmp = new node();
    tmp->row = r;
    tmp->col = c;
    if(head == NULL)head=tail=tmp;
    else{
        tail->next = tmp; tmp->prev = tail;
        tail = tmp;
    }
    len++;
}
void figure::draw(){
    node* tmp = head;
    bool f=0;
    while(tmp!=NULL){
        cursor(tmp->row, tmp->col);
            // cout<<tmp->row<<" "<<tmp->col;
        if(key == snakekey){ if(tmp == head)cout<<"O"; else if(f)cout<<"ợ"; else cout<<"ờ"; }
        if(key == frogkey){ cout<<"🐸"; }
        if(key == eaglekey){ cout<<"🦅"; }
        if(key == boardkey){ cout<<"🧱"; }

        tmp = tmp->next;
    }
}
void figure::erase(){
    node* tmp = head;
    while(tmp!=NULL){
        cursor(tmp->row, tmp->col); cout<<"  ";

        tmp = tmp->next;
    }
}
void figure::destruct(){
    node* tmp = head;
    node* tmpp;
    while(tmp!=NULL){
        tmpp = tmp;
        tmp = tmp->next;
        delete tmpp;
    }
}
void figure::move(){
    if(key == snakekey){
            node* tmpp = new node();
            tmpp->row = head->row;
            tmpp->col = head->col;
            tmpp->next = head;
            head->prev = tmpp;
            head = tmpp;
            if(_kbhit()) cs = retch();


            if(!(cs=='a' or cs=='s' or cs=='d' or cs=='w' or cs=='j'))cs = ch;
            else if(cs+ch==234 or cs+ch==197)cs=ch;
            else if(cs == 'j'){
                // system("clear");
                // control();
                // if(exit_the_game == 1)return 0;
                // draw_afresh();

                // retch();
                cs = ch;
            }
            ch = cs;


            if(cs=='w')head->row--;
            else if(cs=='s')head->row++;
            else if(cs=='a')head->col-=2;
            else if(cs=='d')head->col+=2;

            
            return;

        }
    node* tmp = head;
    while(tmp!=NULL){
        if(key == eaglekey){
            tmp->col--;
            if(tmp->col==1)tmp->col=tc;
        }
        else if(key == frogkey){
            tmp->col = rand()%((tc-3)/2)*2+2;
            tmp->row = 1+((rand()%(tr-2))/2)*2;
        }

        tmp = tmp->next;
    }
}
void game(){
    figure snake, frog, eagle, board;
    snake.key=snakekey;
    eagle.key=eaglekey;
    frog.key=frogkey;
    board.key=boardkey;

    snake.initiate();
    frog.initiate();
    eagle.initiate();


    eagle.draw();
    frog.draw();
    snake.draw();
    ch = cs = 'a';

    int lives = 1;
    while(lives){
        snake.move();
        if(totalboard[snake.head->row][snake.head->col] == frogkey){
            frog.move();
        }
        else{
            cursor(snake.tail->row, snake.tail->col);cout<<" ";
            node* tmp = snake.tail;
            snake.tail = snake.tail->prev;
            delete tmp;
            snake.tail->next = NULL;
        }
        eagle.draw();
        frog.draw();
        snake.draw();

        usleep(200000);

        // snake.erase();
    }
}
int main(){
    new_console_size();
    game();
}