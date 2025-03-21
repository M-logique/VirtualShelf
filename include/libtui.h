#ifndef LIBTUI_H
#define LIBTUI_H


extern "C" 
{
    extern void GoPrintLogo();
    extern int  GoGetMenuChoice();
    extern void GoTypeText(char* text);
    extern void GoPressEnter();
    extern void GoBetterPrint(char* text);
    extern void GoUpdateRGBState();
    extern int  GoDisplayBookSelector(int checkAv);
    extern int  GoDisplayStudentSelector();
    extern int  GoDisplayBorrowingSelector();
}

#endif // LIBTUI_H