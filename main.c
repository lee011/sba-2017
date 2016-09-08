/*
program:   main.c
component: #1
date:      24-08-2015
name:      Lee Ka Lok
class:     5A
class no.: 29
*/
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

int main() {
    int i;
    do {
        system("cls");
        switch (i = mainMenu()) {
            case 1:
                roomManMenu(); // -> component #2
                break;
            case 2:
                bookingManMenu();
                break;
            case 0:
                break;
            default:
                puts("Error input. Please retry.");
                system("pause");
                break;
        }
    } while (i != 0);
    puts("Goodbye.");
    system("pause");
	return 0;
}

int mainMenu() {
    int i;
    puts(" Home");
    puts("=======================================================================");
    puts("*******************************************");
    puts("*                                         *");
    puts("*         Hotel Management System         *");
    puts("*                                         *");
    puts("*******************************************");
    puts("");
    puts("Please select:");
    puts("[1] Room Management");
    puts("[2] Booking Management");
    puts("============================");
    puts("[0] Exit");
    printf("Enter your choice: ");
    scanf("%d", &i);
    return i;
}

// code to clear input buffer to ensure gets() work properly
int clear_input_buffer() {
    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n')) /* void */;
    return ch;
}
