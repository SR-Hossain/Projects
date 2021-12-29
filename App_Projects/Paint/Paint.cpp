#include<bits/stdc++.h>
#if defined(_WIN32)
    #include<windows.h>
#endif
#include<conio.h>
using namespace std;
void work();
#if defined(_WIN32)
void work()
{
    cout<<"type tab to draw, select any character and drawing will pause and press tab again, backspace to erase the canvas";
    char c='d', ch='o';
    POINT prevpos = {0,0};
    while(1){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){0,0});
        if(_kbhit())
            c=_getch();

        if(c=='\t'){

            
        // if(f)continue;
        // console size
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE) ,&csbi);


        // get where the cursor is in the screen as pixel
        POINT pos;
        GetCursorPos(&pos);

        if(pos.x==prevpos.x and pos.y==prevpos.y)continue;
        prevpos.x = pos.x, prevpos.y = pos.y;


        // real console size as pixel
        HWND hwnd = GetConsoleWindow();
        RECT realconsole;
        GetClientRect(hwnd, &realconsole);
        ScreenToClient(hwnd, &pos);

        
        // set position of cursor not as pixel
        int posx = pos.x * csbi.srWindow.Right / realconsole.right;
        int posy = pos.y * csbi.srWindow.Bottom / realconsole.bottom;

        if(PtInRect(&realconsole, pos)){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){posx, posy});
        cout<<ch;}
        // Sleep(5);
        }
        else if (c=='\b'){
            system("cls");
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){0,0});
    cout<<"type tab to draw, select any character and drawing will pause and press tab again, backspace to erase the canvas";
            c=ch;
        }
        if(c==' ' or ('a'<=c and c<='z') or ('A'<=c and c<='Z') or ('0'<=c and c<='9'))
            ch=c;
    }
    


}

#else
void work(){
    
}

#endif
int main()
{
    work();
}