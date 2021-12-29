#include<bits/stdc++.h>
#include<conio.h>
#include "Basic_console_feature.h"
using namespace std;
int main(){
    while(1){
    clock_t begin = clock();

/* here, do your time-consuming job */
    for(int j=0; j<1e3; j++){
    // for(int i=0; i<10; i++)cout<<"6\n";
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    int width = (int)(w.ws_col);
    int height = (int)(w.ws_row);
    }

clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;


    
    begin = clock();

/* here, do your time-consuming job */
    for(int j=0; j<1e3; j++){
    int wincol = WEXITSTATUS(std::system("exit `tput cols`"));
    int winrow = WEXITSTATUS(std::system("exit `tput lines`"));
    }

    end = clock();
    double time_spents = (double)(end - begin) / CLOCKS_PER_SEC;
    cout<<time_spent<<'\n'<<time_spents<<'\n';

    getch();}


}