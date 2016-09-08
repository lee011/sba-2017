/*
header:    types.h
date:      25-08-2015
name:      Lee Ka Lok
class:     5A
class no.: 29
*/

#include <time.h>
#define TRUE 1
#define FALSE 0

typedef struct {
    char number[5];
    int  status;
    char customerName[99];
} Room;

typedef struct {
    int    id;
    char   customerName[99];
    char   phone[20];
    time_t bookingDate;
} Booking;
