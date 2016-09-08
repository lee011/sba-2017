/*
program:   bookingMan.c
component: #3
date:      24-08-2015
name:      Lee Ka Lok
class:     5A
class no.: 29
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

FILE    *fbooking;
Booking bentries[9999];
int     bookingCount  = 0,
        readIn        = 0,
        autoIncrement = 0;
void    addEntry(), listEntries();

void bookingManMenu() {
    int i = 0,
        j,
        x;
    if (fbooking = fopen("bookingdata.txt", "r")) {
        char u;
        fscanf(fbooking, "autoIncrement=%d", &autoIncrement);
        fscanf(fbooking, "%c", &u);
        while (!feof(fbooking)) {
            char d0[30];
            char t[10];
            int d, m, y;
            struct tm d1;
            fgets(t, 10, fbooking);
            bentries[i].id = atoi(t);
            fgets(bentries[i].customerName, 99, fbooking);
            for (j = 0; j < strlen(bentries[i].customerName); j++) {
                if (bentries[i].customerName[j] == '\n') {
                    bentries[i].customerName[j] = '\0';
                }
            }
            fgets(bentries[i].phone, 20, fbooking);
            for (j = 0; j < strlen(bentries[i].phone); j++) {
                if (bentries[i].phone[j] == '\n') {
                    bentries[i].phone[j] = '\0';
                }
            }
            fscanf(fbooking, "%d-%d-%d", &y, &m, &d);
            fscanf(fbooking, "%c", &u);
            d1.tm_year = y - 1900;
            d1.tm_mon = m - 1;
            d1.tm_mday = d;
            d1.tm_min = 0;
            d1.tm_hour = 0;
            d1.tm_sec = 0;
            bentries[i].bookingDate = mktime(&d1);
            i++;
        }
        readIn = 1;
        bookingCount = i;
        fclose(fbooking);
    }
    do {
        system("cls");
        puts(" Home > Booking Management");
        puts("=======================================================================");
        puts("Please select:");
        puts("[1] Add Booking Entry");
        puts("[2] Edit Booking Entry");
        puts("[3] Remove Booking Entry");
        puts("[4] View Booking Entries");
        puts("============================");
        puts("[0] Save Records and Back");
        puts("[8] Discard Records and Back");
        printf("Enter your choice: ");
        scanf("%d", &x);
        switch (x) {
            case 0:
                if (fbooking = fopen("bookingdata.txt", "w")) {
                    fprintf(fbooking, "autoIncrement=%d\n", autoIncrement);
                    if (bookingCount != 0) {
                        int i;
                        for (i = 0; i < bookingCount - 1; i++) {
                            fprintf(fbooking, "%d\n", bentries[i].id);
                            fputs(bentries[i].customerName, fbooking);
                            fprintf(fbooking, "\n");
                            fputs(bentries[i].phone, fbooking);
                            fprintf(fbooking, "\n");
                            struct tm * date = gmtime(&bentries[i].bookingDate);
                            fprintf(fbooking, "%04d-%02d-%02d\n", date->tm_year + 1900, date->tm_mon + 1, date->tm_mday + 1);
                        }
                        fprintf(fbooking, "%d\n", bentries[bookingCount - 1].id);
                        fputs(bentries[bookingCount - 1].customerName, fbooking);
                        fprintf(fbooking, "\n");
                        fputs(bentries[bookingCount - 1].phone, fbooking);
                        fprintf(fbooking, "\n");
                        struct tm *date = gmtime(&bentries[bookingCount - 1].bookingDate);
                        fprintf(fbooking, "%04d-%02d-%02d", date->tm_year + 1900, date->tm_mon + 1, date->tm_mday + 1);
                    }
                    fclose(fbooking);
                }
                break;
            case 1:
                addEntry();
                break;
            case 2: {
                int id, i, d = -1;
                printf("Enter booking ID: ");
                scanf("%d", &id);
                for (i = 0; i < bookingCount; i++) {
                    if (bentries[i].id == id) {
                        d = i;
                        break;
                    }
                }
                if (d != -1) {
                    clear_input_buffer();
                    char n[99], p[20];
                    int j;
                    printf("Original Customer Name: %s\n", bentries[d].customerName);
                    printf("Enter Customer Name (press Enter directly if do not want to change): ");
                    gets(n);
                    for (j = 0; j < strlen(n); j++) {
                        if (n[j] == '\n') n[j] = '\0';
                    }
                    if (strcmp(n, "") != 0) strcpy(bentries[d].customerName, n);
                    printf("Original Phone Number: %s\n", bentries[d].phone);
                    printf("Enter Phone Number (press Enter directly if do not want to change): ");
                    gets(p);
                    for (j = 0; j < strlen(p); j++) {
                        if (p[j] == '\n') p[j] = '\0';
                    }
                    if (strcmp(p, "") != 0) strcpy(bentries[d].phone, p);
                    struct tm *date1 = gmtime(&bentries[d].bookingDate);
                    printf("Original Date: %04d-%02d-%02d\n", date1->tm_year + 1900, date1->tm_mon + 1, date1->tm_mday + 1);
                    printf("Enter the Date (in yyyy mm dd format, enter -1 for those value not intented to change): ");
                    struct tm date;
                    int d, m, y;
                    scanf("%d%d%d", &y, &m, &d);
                    if (y != -1) date.tm_year = y - 1900; else date.tm_year = date1->tm_year;
                    if (m != -1) date.tm_mon = m - 1; else date.tm_mon = date1->tm_mon;
                    if (d != -1) date.tm_mday = d; else date.tm_mday = date1->tm_mday + 1;
                    date.tm_min = 0;
                    date.tm_hour = 0;
                    date.tm_sec = 0;
                    bentries[i].bookingDate = mktime(&date);
                    printf("%s", asctime(&date));
                    clear_input_buffer();
                    printf("Item has been modified.\n");
                    system("pause");
                } else {
                    printf("No matching booking information found.\n");
                    system("pause");
                }
                break;
            }
            case 3: {
                int id, i, d = -1;
                char input;
                Booking b;
                printf("Enter booking ID: ");
                scanf("%d", &id);
                for (i = 0; i < bookingCount; i++) {
                    if (bentries[i].id == id) {
                        b = bentries[i];
                        d = i;
                        break;
                    }
                }
                if (d != -1) {
                    struct tm *date = gmtime(&b.bookingDate);
                    do {
                        printf("Do you want to delete this? [y/n]\nID: %04d\nName: %s\nPhone: %s\nDate: %04d-%02d-%02d\n", b.id, b.customerName, b.phone, date->tm_year + 1900, date->tm_mon + 1, date->tm_mday + 1);
                        input = getche();
                        if (input == 'Y' || input == 'y') {
                            int ii;
                            for (ii = d; ii < bookingCount; ii++) {
                                bentries[ii] = bentries[ii + 1];
                            }
                            bookingCount--;
                            printf("This item has been deleted.\n");
                            system("pause");
                        }
                    } while (!(input == 'Y' || input == 'y' || input == 'N' || input == 'n'));
                } else {
                    printf("No matching booking information found.\n");
                    system("pause");
                }
                break;
            }
            case 4:
                listEntries();
                break;
            case 8:
                break;
            default:
                puts("Error input. Please retry.");
                system("pause");
                break;
        }
    } while (x != 0 && x != 8);
}

void addEntry() {
    clear_input_buffer();
    Booking obj;
    system("cls");
    puts(" Home > Booking Management > Add Entry");
    puts("=======================================================================");
    printf("Enter Customer Name: ");
    gets(obj.customerName);
    printf("Enter Phone Number: ");
    gets(obj.phone);
    printf("Enter the Date (in yyyy mm dd format): ");
    struct tm date;
    int d, m, y;
    scanf("%d%d%d", &y, &m, &d);
    date.tm_year = y - 1900;
    date.tm_mon = m - 1;
    date.tm_mday = d;
    date.tm_min = 0;
    date.tm_hour = 0;
    date.tm_sec = 0;
    obj.bookingDate = mktime(&date);
    printf("%s", asctime(&date));
    system("pause");
    obj.id = autoIncrement;
    bentries[bookingCount] = obj;
    bookingCount++;
    autoIncrement++;
}

void listEntries() {
    int i = 0;
    system("cls");
    puts(" Home > Booking Management > List Entries");
    puts("=======================================================================");
    puts("Booking ID  Customer Name         Phone                 Date");
    puts("------------------------------------------------------------------");
    for (i = 0; i < bookingCount; i++) {
        struct tm * date;
        date = gmtime(&bentries[i].bookingDate);
        printf("      %04d  %-20s  %-20s  %04d/%02d/%02d\n", bentries[i].id, bentries[i].customerName, bentries[i].phone, date->tm_year + 1900, date->tm_mon + 1, date->tm_mday + 1);
    }
    system("pause");
}
