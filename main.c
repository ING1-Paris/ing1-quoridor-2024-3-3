#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "Menu.h"

int main() {
    bool execution = 1;
    while(execution){
        execution = menu();
        system("cls");
    }
    return 0;
}