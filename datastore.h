//
// Created by Steve_Hsu on 2023/3/20.
// 项目用数据结构
// CODING: GBK
//

#ifndef CODE_WEEK_DATASTORE_H
#define CODE_WEEK_DATASTORE_H
typedef struct types {
    int main_type;              // 大类
    int mid_type;               // 中类
    int subtype;                // 小类
    int isotc;                  // 处方药标志，实操中按布尔值处理
} types;

// 药品分类码参照 https://www.docin.com/p-1168914112.html 进行分段

typedef struct medication {
    char name[256];             // 名称
    types type;                 // 分类
    long man_date;              // 生产日期
    long stock;                 // 库存量
    long sale_vol;              // 累计销售量
    short qa;                   // 保质期状态标记 - 正常/临期/过期 -> 1/0/-1
} med;

typedef struct sing_unit {      // 链表基本单位
    med col;
    struct sing_unit *next;
} unit;

#endif //CODE_WEEK_DATASTORE_H
