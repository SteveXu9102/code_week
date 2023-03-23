//
// Created by Steve_Hsu on 2023/3/22.
//

#ifndef CODE_WEEK_LIST_FUNC_H
#define CODE_WEEK_LIST_FUNC_H

#include "datastore.h"
// 程序内通用数据结构

extern unit *findByName(char name[256], unit *);

// 查找函数
extern unit *add(unit *, unit *);
// 添加函数
extern int del(char *, unit *);
// 删除函数
extern void replace(unit *, unit *);
// 替换函数

extern void dataSave(unit *);
// 存档函数
extern int fileRead(unit *);
// 文件读取函数
extern int csvTableGenerate(unit*);
// 表格生成函数

extern void chkSingDate(unit *);
// 单条目临期判定
void chkAllDate(unit *);
// 所有条目临期判定
extern int showQaCond(unit *, int);
// 判定库存中是否有临/过期药物 或 显示所有临/过期药物
// 使用第二个参数切换上述工作模式

extern struct tm* outDateTime();
// 输出一个存储时间的结构体指针
extern void timePrn();
// 时间显示

#endif //CODE_WEEK_LIST_FUNC_H
