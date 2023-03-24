//
// Created by Steve_Hsu on 2023/3/21.
//

#include <stdio.h>
#include <time.h>
#include "datastore.h"

extern struct tm *outDateTime();

extern void stdprn(unit *);

void chkSingDate(unit *cur) {  // 刷新单项临期情况
    unit *ptr = cur;
    int yr, mon, day, daytotal;

    struct tm *datetime;
    datetime = outDateTime(); // 获取时间

    yr = ptr->col.man_date / 10000;
    mon = (ptr->col.man_date % 10000) / 100;
    day = ptr->col.man_date % 100;
    // 年月日转换

    daytotal = (datetime->tm_year + 1900) * 365 + datetime->tm_yday - (yr * 365 + mon * 30 + day); // 估算自生产日期起过去的总时间

    if (670 < daytotal && 730 >= daytotal) {
        ptr->col.qa = 0;  // 临期
    } else if (daytotal > 730) ptr->col.qa = -1;  // 超期
    else ptr->col.qa = 1;  // 正常
}

void chkAllDate(unit *head) {  // 批量刷新临期情况
    unit *ptr = head;

    while (ptr->next != NULL) {
        chkSingDate(ptr);  // 检查整个链表
        ptr = ptr->next;
    }
    chkSingDate(ptr); // 处理链表尾端
}

int showQaCond(unit *head, int prn) {  // 检查链表内是否有临期药品或直接输出临期/过期药品
    unit *ptr = head;

    chkAllDate(ptr);  // 批量刷新
    ptr = head;

    if (prn == 0) { // 不需要输出时
        while (ptr->next != NULL) {
            if (ptr->col.qa != 1) return -1; // 除链表尾端的条目有临期药品则返回-1
            ptr = ptr->next;
        }
        chkSingDate(ptr);
        if (ptr->col.qa != 1) return -1; // 链表尾端的条目是临期药品则返回-1
    } else { // 需要输出时
        while (ptr->next != NULL) {
            if (ptr->col.qa != 1) {
                stdprn(ptr);  // 输出基本信息
                printf("状态：%s\n\n", (ptr->col.qa == 0 ? "临期" : "过期"));  // 输出临期信息
            }
            ptr = ptr->next;
        }
        chkSingDate(ptr);  // 检查链表尾部临期信息
        if (ptr->col.qa != 1) {
            stdprn(ptr);
            printf("状态：%s\n\n", (ptr->col.qa == 0 ? "临期" : "过期"));
        }
    }
    return 0;
}