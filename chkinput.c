int chkType(int large, int middle, int small) {  // 检查种类码是否符合规范
    if (large >= 1 && large <= 5) {   // 大类
        if (middle >= 1 && middle <= 25) {  // 中类
            if (small >= 1 && small <= 8) {  // 小类
                return 0;
            } else return 1;
        } else return 1;
    } else return 1;
}  // 符合返回0，不符合返回1

int chkDate(long ymd) {
    int year, month, day;

    // 将年月日长码拆分
    year = ymd / 10000;
    month = (ymd % 10000) / 100;
    day = ymd % 100;

    if (month == 0 || month > 12) return 0;  // 月份大小范围判断
    else {
        if (day > 31) return 0;  // 基本对应日期判断
        else {
            if ((month == 2 || month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
                return 0;  // 大小月对应日期判断
            else {
                if (month == 2 && day == 30) return 0;  // 2月日期判断
                else {
                    if (month == 2 && day == 29) {  // 闰2月日期判断
                        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) return 1;  // 闰年判断，是闰年则2月29日存在
                        else return 0;
                    } else return 1;
                }

            }
        }
    }
}