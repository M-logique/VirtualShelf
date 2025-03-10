#ifndef LIBTUI_H
#define LIBTUI_H


extern "C" 
{
    extern void GoPrintLogo();
    extern int  GoGetMenuChoice();
    extern void GoTypeText(char* text);
    extern void GoPressEnter();
    extern void GoBetterPrint(char* text);
}

#endif // LIBTUI_H