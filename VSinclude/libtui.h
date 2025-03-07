#ifndef LIBTUI_H
#define LIBTUI_H


extern "C" 
{
    extern void PrintLogo();
    extern int GetMenuChoice();
    extern void TypeText(char* text);
    extern void PressEnter();
}

#endif // LIBTUI_H