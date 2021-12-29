// #include <iostream>
// #include <io.h>
// #include <fcntl.h>

// int main()
// {
//     _setmode(_fileno(stdout), _O_U16TEXT);
//     std::wcout << L"face: 👩\n";
//     return 0;
// }


#include <fcntl.h>  
#include <io.h>  
#include <stdio.h>  
  
int main(void) {  
    _setmode(_fileno(stdout), _O_U16TEXT);  
    wprintf(L"👩 \x043a\x043e\x0448\x043a\x0430 \x65e5\x672c\x56fd\n");  
    return 0;  
}