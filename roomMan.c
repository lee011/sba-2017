/*
program:   roomMan.c
component: #2
date:      24-08-2015
name:      Lee Ka Lok
class:     5A
class no.: 29
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

FILE *froom;
Room entries[200];
int roomCount;

void roomEntry(), roomManMenu(), checkRoom();
int findRoom(char *);

void roomManMenu() {
    int i;
    do {
        system("cls");
        puts(" Home > Room Management");
        puts("=======================================================================");
        puts("Please select:");
        puts("[1] Check Room Status");
        puts("[2] Room Entry Editor");
        puts("============================");
        puts("[0] Back to top");
        printf("Enter your choice: ");
        scanf("%d", &i);
        switch (i) {
            case 0:
                break;
            case 1:
                checkRoom();
                break;
            case 2:
                roomEntry();
                break;
            default:
                puts("Error input. Please retry.");
                system("pause");
                break;
        }
    } while (i != 0);
}

void checkRoom() {
    int i = 0, j;
    char r[5];
    clear_input_buffer();
    if (froom = fopen("roomdata.txt", "r")) {
        while (!feof(froom)) {
            fgets(entries[i + 1].number, 4, froom);
            for (j = 0; j < strlen(entries[i + 1].number); j++) {
                if (entries[i + 1].number[j] == '\n') {
                    entries[i + 1].number[j] = '\0';
                }
            }
            if (strcmp(entries[i + 1].number, "") != 0) {
                fscanf(froom, "%d\n", &entries[i + 1].status);
                fgets(entries[i + 1].customerName, 99, froom);
                for (j = 0; j < strlen(entries[i + 1].customerName); j++) {
                    if (entries[i + 1].customerName[j] == '\n') {
                        entries[i + 1].customerName[j] = '\0';
                    }
                }
                i++;
            }
        }
        roomCount = i + 1;
        fclose(froom);
        printf("Enter Room Number: ");
        gets(r);
        int j = findRoom(r);
        if (j == -1) {
            puts("Room not found.");
            system("pause");
        } else {
            puts("Status codes: -1 Not Available; 0 Free; 1 Occupied; 2 Reserved");
            printf("Status of room %s is %d.\n", entries[j].number, entries[j].status);
            system("pause");
        }
    } else {
        puts("No room entries saved. Please add entries first.");
        system("pause");
    }
}

void roomEntry() {
    int
        i = -1,
        j,
        k,
        readIn = 0;
    char r[5];
    if (froom = fopen("roomdata.txt", "r")) {
        while (!feof(froom)) {
            fgets(entries[i + 1].number, 4, froom);
            for (j = 0; j < strlen(entries[i + 1].number); j++) {
                if (entries[i + 1].number[j] == '\n') {
                    entries[i + 1].number[j] = '\0';
                }
            }
            if (strcmp(entries[i + 1].number, "") != 0) {
                fscanf(froom, "%d\n", &entries[i + 1].status);
                fgets(entries[i + 1].customerName, 99, froom);
                for (j = 0; j < strlen(entries[i + 1].customerName); j++) {
                    if (entries[i + 1].customerName[j] == '\n') {
                        entries[i + 1].customerName[j] = '\0';
                    }
                }
                i++;
            }
        }
        readIn = 1;
        roomCount = i + 1;
        fclose(froom);
    }
    do {
        system("cls");
        puts(" Home > Room Management > Room Entry Editor");
        puts("=======================================================================");
        if (readIn) {
            printf("Read in %d records successfully.\n", roomCount);
        }
        puts("Please select:");
        puts("[1] Add Entry");
        puts("[2] View and Edit Entry");
        puts("[3] Remove Entry");
        puts("============================");
        puts("[0] Save Records and Back");
        puts("[8] Discard Records and Back");
        printf("Enter your choice: ");
        scanf("%d", &j);
        switch (j) {
            case 0:
                if (roomCount != 0) {
                    froom = fopen("roomdata.txt", "w");
                    for (k = 0; k < roomCount - 1; k++) {
                        fprintf(froom, "%s\n%d\n%s\n", entries[k].number, entries[k].status, entries[k].customerName);
                    }
                    fprintf(froom, "%s\n%d\n%s", entries[roomCount - 1].number, entries[roomCount - 1].status, entries[roomCount - 1].customerName);
                    fclose(froom);
                }
                break;
            case -1:
                break;
            case 8: {
                char edit;
                do {
                    printf("All edited data will be lost! Continue? [y/n] ");
                    edit = getche();
                } while (edit != 'y' && edit != 'Y' && edit != 'n' && edit != 'N' && edit != 13);
                if (edit == 'n' || edit == 'N') j = -1;
                break;
            }
            case 1: {
                char contd, c;
                Room obj;
                do {
                    clear_input_buffer();
                    system("cls");
                    puts(" Home > Room Management > Room Entry Editor > Add Entry");
                    puts("=======================================================================");
                    do {
                        do {
                            printf("Enter room number: ");
                            gets(obj.number);
                        } while (strcmp(obj.number, "") == 0);
                        if (findRoom(obj.number) != -1) {
                            printf("Room number exists. Please enter an unique room number.\n");
                        }
                    } while (findRoom(obj.number) != -1);
                    puts("Status codes: -1 Not Available; 0 Free; 1 Occupied; 2 Reserved");
                    do {
                        printf("Enter status: ");
                        scanf("%d", &obj.status);
                        if (obj.status < -1 || obj.status > 2) {
                            puts("Invalid status code. Please retry.");
                            system("pause");
                        }
                    } while (obj.status < -1 || obj.status > 2);
                    scanf("%c", &c);
                    if (obj.status == 1 || obj.status == 2) {
                        printf("Enter customer name: ");
                        gets(obj.customerName);
                    } else {
                        strcpy(obj.customerName, "--");
                    }
                    entries[roomCount] = obj;
                    roomCount++;
                    puts("Entry added.");
                    do {
                        printf("Do you want to add more entries? [y/n] ");
                        contd = getche();
                    } while (contd != 'y' && contd != 'Y' && contd != 'n' && contd != 'N');
                } while (contd == 'y' || contd == 'Y');
                break;
            }
            case 2: {
                char edit;
                clear_input_buffer();
                if (roomCount == 0) {
                    puts("No room entries saved. Please add entries first.");
                    system("pause");
                } else {
                    system("cls");
                    puts(" Home > Room Management > Room Entry Editor > View and Edit Entry");
                    puts("=======================================================================");
                    printf("Enter Room Number: ");
                    gets(r);
                    int l = findRoom(r);
                    if (l == -1) {
                        puts("Room not found.");
                        system("pause");
                    } else {
                        printf("Found room info:\nNumber: %s\nStatus: %d\nCustomer Name: %s\n", entries[l].number, entries[l].status, entries[l].customerName);
                        do {
                            printf("Do you want to edit the entry? [y/n] ");
                            edit = getche();
                            printf("\n");
                        } while (edit != 'y' && edit != 'Y' && edit != 'n' && edit != 'N');
                        if (edit == 'y' || edit == 'Y') {
                            char num[4], name[100];
                            int s;
                            printf("Enter room number: ");
                            gets(num);
                            if (strcmp(num, "") != 0) {
                                strcpy(entries[l].number, num);
                            }
                            puts("Status codes: -1 Not Available; 0 Free; 1 Occupied; 2 Reserved; 3 Do not change");
                            do {
                                printf("Enter status: ");
                                scanf("%d", &s);
                                if (s != 3) {
                                    if (s < -1 || s > 2) {
                                        puts("Invalid status code. Please retry.");
                                        system("pause");
                                    }
                                    entries[l].status = s;
                                }
                            } while (entries[l].status < -1 || entries[l].status > 2);
                            if (entries[l].status == 1 || entries[l].status == 2) {
                                printf("Enter customer name: ");
                                gets(name);
                                if (strcmp(name, "") != 0) {
                                    strcpy(entries[l].customerName, name);
                                }
                            } else {
                                strcpy(entries[l].customerName, "--");
                            }
                            puts("Entry edited.\n");
                            system("pause");
                        }
                    }
                }
                break;
            }
            case 3: {
                char remove;
                int ii;
                clear_input_buffer();
                if (roomCount == 0) {
                    puts("No room entries saved. Please add entries first.");
                    system("pause");
                } else {
                    printf("Enter Room Number: ");
                    gets(r);
                    int l = findRoom(r);
                    if (l == -1) {
                        puts("Room not found.");
                        system("pause");
                    } else {
                        do {
                            printf("Found room info:\nNumber: %s\nStatus: %d\nCustomer Name: %s\nDo you want to remove the entry? [y/n] ", entries[l].number, entries[l].status, entries[l].customerName);
                            remove = getche();
                        } while (remove != 'y' && remove != 'Y' && remove != 'n' && remove != 'N');
                        if (remove == 'y' || remove == 'Y') {
                            for (ii = l; ii < roomCount; ii++) {
                                entries[ii] = entries[ii + 1];
                            }
                            roomCount -= 1;
                        }
                    }
                }
                break;
            }
            default:
                puts("Error input. Please retry.");
                system("pause");
                break;
        }
    } while (j != 0 && j != 8);
}

int findRoom(char *number) {
    int i;
    for (i = 0; i < roomCount; i++) {
        if (strcmp(number, entries[i].number) == 0) {
            return i;
        }
    }
    return -1;
}
