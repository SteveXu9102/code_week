//
// Created by Steve_Hsu on 2023/3/21.
// 时间获取，可精确到秒
//

#include <stdio.h>
#include <time.h>

struct tm *outDateTime() {
    time_t now = time(NULL);  // 获取time_t格式的当前时间
    return localtime(&now);   // 将当前时间转换为struct tm*格式返回
}

void timePrn() {
    struct tm *datetime;
    datetime = outDateTime();  // 用于获取时间
    char *weekday;  // 用于用户友好输出
    switch (datetime->tm_wday) {
        case 1:
            weekday = "周一";
            break;
        case 2:
            weekday = "周二";
            break;
        case 3:
            weekday = "周三";
            break;
        case 4:
            weekday = "周四";
            break;
        case 5:
            weekday = "周五";
            break;
        case 6:
            weekday = "周六";
            break;
        case 0:
            weekday = "周日";
            break;
    }
    printf("%d年%d月%d日 %s\n", 1900 + datetime->tm_year, 1 + datetime->tm_mon, datetime->tm_mday, weekday);  // 输出日期
}