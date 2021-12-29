#include <bits/stdc++.h>
#include <conio.h>
#include <time.h>
using namespace std;
enum eDir
{
    STOP,
    LEFT,
    UPLEFT,
    DOWNLEFT,
    RIGHT,
    UPRIGHT,
    DOWNRIGHT
};
class pball
{
private:
    int x, y;
    int orix, oriy;
    eDir direction;

public:
    pball(int posx, int posy)
    {
        x = orix = posx;
        y = oriy = posy;
        direction = STOP;
    }
    void reset()
    {
        x = orix;
        y = oriy;
        direction = STOP;
    }
    void changedirection(eDir d)
    {
        direction = d;
    }
    void randomdirection()
    {
        direction = (eDir)((rand() % 6) + 1);
    }
    inline int getx() { return x; }
    inline int gety() { return y; }
    inline eDir getdir() { return direction; }
    void move()
    {
        switch (direction)
        {
        case STOP:
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UPLEFT:
            x--;
            y--;
            break;
        case UPRIGHT:
            x++;
            y--;
            break;
        case DOWNLEFT:
            x--;
            y++;
            break;
        case DOWNRIGHT:
            x++;
            y++;
            break;
        default:
            break;
        }
    }
    friend ostream &operator<<(ostream &o, pball c)
    {
        o << "Ball [" << c.x << ',' << c.y << "][" << c.direction << ']';
        return o;
    }
};
class paddle
{
private:
    int x, y;
    int orix, oriy;

public:
    paddle()
    {
        x = y = 0;
    }
    paddle(int posx, int posy) : paddle()
    {
        x = orix = posx;
        y = oriy = posy;
    }
    inline void reset()
    {
        x = orix;
        y = oriy;
    }
    inline int getx() { return x; }
    inline int gety() { return y; }
    inline void moveup() { y--; }
    inline void movedown() { y++; }
    friend ostream &operator<<(ostream &o, paddle c)
    {
        o << "Paddle [" << c.x << ',' << c.y << ']';
        return o;
    }
};
class gamemanager
{
private:
    int width, height;
    int score1, score2;
    char up1, up2, down1, down2;
    bool quit;
    pball *ball;
    paddle *player1;
    paddle *player2;

public:
    gamemanager(int w, int h)
    {
        srand(time(NULL));
        quit = 0;
        up1 = 'w';
        up2 = 'i';
        down1 = 's';
        down2 = 'k';
        score1 = score2 = 0;
        width = w;
        height = h;
        ball = new pball(w / 2, h / 2);
        player1 = new paddle(2, h / 2 - 3);
        player2 = new paddle(w - 3, h / 2 - 3);
    }
    ~gamemanager()
    {
        delete ball, player1, player2;
    }
    void scoreup(paddle *player)
    {
        if (player == player1)
            score1++;
        else
            score2++;
        ball->reset();
        player1->reset();
        player2->reset();
    }
    void draw()
    {
        system("cls");
        for (int i = 0; i < width; i++)
            cout << '\xB2';
        cout << '\n';
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int ballx = ball->getx();
                int bally = ball->gety();
                int player1x = player1->getx();
                int player1y = player1->gety();
                int player2y = player2->gety();
                int player2x = player2->getx();
                if (j == 0 or j == width - 1)
                    cout << '\xB2';
                else if (ballx == j and bally == i)
                    cout << 'O';
                else if (player1x == j and player1y == i)
                    cout << '\xB2';
                else if (player1x == j and player1y + 1 == i)
                    cout << '\xB2';
                else if (player1x == j and player1y + 2 == i)
                    cout << '\xB2';
                else if (player1x == j and player1y + 3 == i)
                    cout << '\xB2';
                else if (player2x == j and player2y == i)
                    cout << '\xB2';
                else if (player2x == j and player2y + 1 == i)
                    cout << '\xB2';
                else if (player2x == j and player2y + 2 == i)
                    cout << '\xB2';
                else if (player2x == j and player2y + 3 == i)
                    cout << '\xB2';
                else
                    cout << ' ';
            }
            cout << '\n';
        }
        for (int i = 0; i < width; i++)
            cout << '\xB2';
        cout << '\n';
        cout<<"Player 1 : "<<score1<<"     "<<"Player 2 : "<<score2<<'\n';
    }
    void input()
    {
        ball->move();
        int ballx = ball->getx();
        int bally = ball->gety();
        int player1x = player1->getx();
        int player1y = player1->gety();
        int player2y = player2->gety();
        int player2x = player2->getx();
        if (_kbhit)
        {
            char current = _getch();
            if (current == up1 and player1y > 0)
                player1->moveup();
            else if (current == up2 and player2y > 0)
                player2->moveup();
            else if (current == down1 and player1y + 4 < height)
                player1->movedown();
            else if (current == down2 and player2y + 4 < height)
                player2->movedown();
            else if (ball->getdir() == STOP)
                ball->randomdirection();
            else if (current == 'q')
                quit = 1;
        }
    }
    void logic()
    {
        int ballx = ball->getx();
        int bally = ball->gety();
        int player1x = player1->getx();
        int player1y = player1->gety();
        int player2y = player2->gety();
        int player2x = player2->getx();

        for (int i = 0; i < 4; i++)
            if (ballx == player1x + 1 and bally == player1y + 1)
                ball->changedirection((eDir)((rand() % 3) + 4));
        for (int i = 0; i < 4; i++)
            if (bally == player2x - 1 and bally == player2y + 1)
                ball->changedirection((eDir)((rand() % 3) + 1));
        if (bally == height - 1)
            ball->changedirection(ball->getdir() == DOWNRIGHT ?  UPRIGHT : UPLEFT);
        if (bally == 0)
            ball->changedirection(ball->getdir() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        if(ballx == width-1)scoreup(player1);
        if(ballx == 0)scoreup(player2);
    }
    void run(){
        while(!quit){
            draw();
            input();
            logic();
        }
        cout<<"Player 1 : "<<score1<<"     "<<"Player 2 : "<<score2<<'\n';
    }
};
int main()
{
    gamemanager g(40, 20);
    g.run();
    getch();
}