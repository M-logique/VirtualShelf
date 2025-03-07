#include <iostream>
#include <libtui.h>

using namespace std;

int main() {

    PrintLogo();
    int choice = GetMenuChoice();

    cout << "User's choice: " << choice << endl;
    return 0;
}