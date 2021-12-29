#include "../Basic_console_feature.h"
#include<sys/ioctl.h>
#include<conio.h>
#include<string.h>
// int main()
// {
//     char ch;
//     gotoxy(6,8);
//     cout<<wherex();
//     gotoxy(6,8);
//     cscanf("%c",ch);
//     cout<<ch;
//     return 0;
//     int br, bc;
//     cout<<"kikoro";
//     get_terminal_size(br, bc);
//     int t; cin>>t; int n = t;
//     for(int i=0, k; t-- and cin>>k; ){
//         cursor(br/2+n-i*2, bc/2);cout<<k;
//         cursor(++i+2, 0);
//     }
//     cursor(br-1,0);
    
// }

int main(void)
 {
    char buffer[83];
    char *p;
    buffer[0] = 81;
    printf("Enter some characters:");
    fflush(stdin);
    p = cgets(buffer);
    printf("\n Entered characters: \"%s\"\n",p);
    return 0;
 }