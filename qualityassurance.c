//
// Created by Steve_Hsu on 2023/3/21.
//

#include <stdio.h>
#include <time.h>
#include "datastore.h"

extern struct tm *outDateTime();

extern void stdprn(unit *);

void chkSingDate(unit *cur) {  // ˢ�µ����������
    unit *ptr = cur;
    int yr, mon, day, daytotal;

    struct tm *datetime;
    datetime = outDateTime(); // ��ȡʱ��

    yr = ptr->col.man_date / 10000;
    mon = (ptr->col.man_date % 10000) / 100;
    day = ptr->col.man_date % 100;
    // ������ת��

    daytotal = (datetime->tm_year + 1900) * 365 + datetime->tm_yday - (yr * 365 + mon * 30 + day); // �����������������ȥ����ʱ��

    if (670 < daytotal && 730 >= daytotal) {
        ptr->col.qa = 0;  // ����
    } else if (daytotal > 730) ptr->col.qa = -1;  // ����
    else ptr->col.qa = 1;  // ����
}

void chkAllDate(unit *head) {  // ����ˢ���������
    unit *ptr = head;

    while (ptr->next != NULL) {
        chkSingDate(ptr);  // �����������
        ptr = ptr->next;
    }
    chkSingDate(ptr); // ��������β��
}

int showQaCond(unit *head, int prn) {  // ����������Ƿ�������ҩƷ��ֱ���������/����ҩƷ
    unit *ptr = head;

    chkAllDate(ptr);  // ����ˢ��
    ptr = head;

    if (prn == 0) { // ����Ҫ���ʱ
        while (ptr->next != NULL) {
            if (ptr->col.qa != 1) return -1; // ������β�˵���Ŀ������ҩƷ�򷵻�-1
            ptr = ptr->next;
        }
        chkSingDate(ptr);
        if (ptr->col.qa != 1) return -1; // ����β�˵���Ŀ������ҩƷ�򷵻�-1
    } else { // ��Ҫ���ʱ
        while (ptr->next != NULL) {
            if (ptr->col.qa != 1) {
                stdprn(ptr);  // ���������Ϣ
                printf("״̬��%s\n\n", (ptr->col.qa == 0 ? "����" : "����"));  // ���������Ϣ
            }
            ptr = ptr->next;
        }
        chkSingDate(ptr);  // �������β��������Ϣ
        if (ptr->col.qa != 1) {
            stdprn(ptr);
            printf("״̬��%s\n\n", (ptr->col.qa == 0 ? "����" : "����"));
        }
    }
    return 0;
}