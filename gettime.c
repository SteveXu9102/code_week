//
// Created by Steve_Hsu on 2023/3/21.
// ʱ���ȡ���ɾ�ȷ����
//

#include <stdio.h>
#include <time.h>

struct tm *outDateTime() {
    time_t now = time(NULL);  // ��ȡtime_t��ʽ�ĵ�ǰʱ��
    return localtime(&now);   // ����ǰʱ��ת��Ϊstruct tm*��ʽ����
}

void timePrn() {
    struct tm *datetime;
    datetime = outDateTime();  // ���ڻ�ȡʱ��
    char *weekday;  // �����û��Ѻ����
    switch (datetime->tm_wday) {
        case 1:
            weekday = "��һ";
            break;
        case 2:
            weekday = "�ܶ�";
            break;
        case 3:
            weekday = "����";
            break;
        case 4:
            weekday = "����";
            break;
        case 5:
            weekday = "����";
            break;
        case 6:
            weekday = "����";
            break;
        case 7:
            weekday = "����";
            break;
    }
    printf("%d��%d��%d�� %s\n", 1900 + datetime->tm_year, 1 + datetime->tm_mon, datetime->tm_mday, weekday);  // �������
}