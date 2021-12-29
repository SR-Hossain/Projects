#include<bits/stdc++.h>
using namespace std;
#include "Basic_console_feature.h"

int main() {
    int width=0, height=0;
    
    get_terminal_size(width, height);
    cout << "width=" << width << ", height=" << height << endl;
    return 0;
    cout << "\x1B[2J\x1B[H";
}