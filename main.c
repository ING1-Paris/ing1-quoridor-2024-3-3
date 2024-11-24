#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "Menu.h"

int main() {
    //Initialise execution pour faire fonctionner le logiciel
    bool execution = 1;
    while (execution) {
        execution = menu();
        system("cls");
    }
    return 0;
}