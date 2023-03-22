//
// Created by Steve_Hsu on 2023/3/21.
//

#include <stdio.h>
#include <time.h>
#include "datastore.h"

extern struct tm *outDateTime();

extern void stdprn(unit *);

void chkSingDate(unit *cur) {
    unit *ptr = cur;
    int yr, mon, day, daytotal;

    struct tm *datetime;
    datetime = outDateTime();

    yr = ptr->col.man_date / 10000;
    mon = (ptr->col.man_date % 10000) / 100;
    day = ptr->col.man_date % 100;

    daytotal = (datetime->tm_year + 1900) * 365 + datetime->tm_yday - (yr * 365 + mon * 30 + day);

    if (670 < daytotal && 730 >= daytotal) {
        ptr->col.qa = 0;
    } else if (daytotal > 730) ptr->col.qa = -1;
    else ptr->col.qa = 1;
}

void chkAllDate(unit *head) {
    unit *ptr = head;

    while (ptr->next != NULL) {
        chkSingDate(ptr);
        ptr = ptr->next;
    }
    chkSingDate(ptr);
}

int showQaCond(unit *head, int prn) {
    unit *ptr = head;

    chkAllDate(ptr);
    ptr = head;

    if (prn == 0) {
        while (ptr->next != NULL) {
            if (ptr->col.qa != 1) return -1;
            ptr = ptr->next;
        }
        chkSingDate(ptr);
        if (ptr->col.qa != 1) return -1;
    } else {
        while (ptr->next != NULL) {
            if (ptr->col.qa != 1) {
                stdprn(ptr);
                printf("状态：%s\n\n", (ptr->col.qa == 0 ? "临期" : "过期"));
            }
            ptr = ptr->next;
        }
        chkSingDate(ptr);
        if (ptr->col.qa != 1) {
            stdprn(ptr);
            printf("状态：%s\n\n", (ptr->col.qa == 0 ? "临期" : "过期"));
        }
    }
    return 0;
}