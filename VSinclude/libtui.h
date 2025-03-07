#ifndef LIBTUI
#define LIBTUI


extern "C" 
{
    extern void PrintLogo();
    extern int GetMenuChoice();
    extern void TypeText(char* text);
}

#endif // LIBTUI