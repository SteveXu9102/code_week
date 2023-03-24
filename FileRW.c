//
// Created by Steve_Hsu on 2023/3/20.
// 文件读写函数
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "list_func.h"

int fileRead(unit *head) {     // 读取存档并加载进链表，返回值表示读取状态
    unit *single = (unit *) malloc(sizeof(unit));  // 用于中转单项数据
    FILE *fp = fopen("stock_info.sav", "r+");

    if (fp == NULL) fp = fopen("stock_info.sav", "w+");    // 判定读写权限是否正常
    if (fp == NULL) {
        printf("ERROR: CANNOT CREATE OR READ FILE. THE PROGRAM WILL EXIT.\n");  // 无法正常读写则退出
        exit(-1);
    }

    getc(fp);  // 针对feof特性而必需的操作，将文件指针后移1Byte以便准确识别文件尾
    if (feof(fp) != 0) {  // 判断指针是否到达文件尾部
        printf("ERROR: NO RECORD.\n");   // 检查存档内是否有记录
        system("pause");
        fclose(fp);
        strcpy(head->col.name, "NULL");  // 无数据，用字符串"NULL"标记空链表头
        head->next = NULL;
        return -1;  // 错误返回1
    } else rewind(fp);  // 检查完毕初始化文件指针

    while (!feof(fp)) {  // 检查指针是否在文件尾
        fscanf(fp, "%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", single->col.name, &single->col.type.main_type,
               &single->col.type.mid_type, &single->col.type.subtype, &single->col.type.isotc, &single->col.man_date,
               &single->col.stock, &single->col.sale_vol); // 读取一段数据
        replace(head, single);  // 复制数据
        if (feof(fp)) continue;  // 再次检查指针是否在文件尾，避免不必要的内存开销
        head->next = malloc(sizeof(unit));  // 分配内存，延伸链表
        head = head->next;
    }
    fclose(fp);  // 关闭文件指针
    head->next = NULL;  // 使链表尾指针为空
    return 0;   // 完成返回0
}

void dataSave(unit *pointer) {  // 数据保存

    FILE *fp = fopen("stock_info.sav", "w+");  // 生成新存档文件

    if (fp == NULL) {  // 判断读写是否正常
        printf("\n错误：无法保存，文件操作失败。\n");
        exit(-1);  // 无法存档则直接退出程序
    }

    while (pointer->next != NULL) {  // 写入所有数据
        fprintf(fp, "%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", pointer->col.name, pointer->col.type.main_type,
                pointer->col.type.mid_type, pointer->col.type.subtype, pointer->col.type.isotc, pointer->col.man_date,
                pointer->col.stock, pointer->col.sale_vol);
        pointer = pointer->next;
    }  // 此循环会遗漏尾端数据，故循环外重新进行一次写入
    fprintf(fp, "%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", pointer->col.name, pointer->col.type.main_type,
            pointer->col.type.mid_type, pointer->col.type.subtype, pointer->col.type.isotc, pointer->col.man_date,
            pointer->col.stock, pointer->col.sale_vol);
    fclose(fp); // 关闭文件指针
}

int saleStats(unit *target, int num, double unit_price) {  // 销售记录创建
    FILE *fp = fopen("stats.sav", "r+");  // 总销售记录文件
    struct tm *t_current = outDateTime();  // 时间获取
    if (fp == NULL) {   // 判定读写权限是否正常
        fclose(fp);
        fp = fopen("stats.sav", "w+");  // 尝试强制覆盖
        if (fp == NULL) {
            fclose(fp);
            return -1;  // 失败
        }
    }
    fclose(fp);
    fp = fopen("stats.sav", "a+"); // 权限正常则重新打开，直接在文件尾添加条目

    fprintf(fp, "%s\t%d\t%.2lf\t%.2lf\t%ld\t%ld\t%4d-%02d-%02d %02d:%02d:%02d\n", target->col.name, num, unit_price,
            1.0 * num * unit_price, (target->col.sale_vol += num), (target->col.stock -= num),
            1900 + t_current->tm_year, 1 + t_current->tm_mon, t_current->tm_mday,
            t_current->tm_hour, t_current->tm_min, t_current->tm_sec);  // 写入条目
    fclose(fp);
    return 0;  // 写入成功
}

int csvAllGen(unit *head) {  // 生成当前库存信息
    unit *pointer = head;
    FILE *fp = fopen("stock.csv", "w+");  // 覆盖式生成
    if (fp == NULL) return -1; // 无法读写返回-1
    fprintf(fp, "品名,种类,是否为OTC药物,生产日期,目前质量状态,库存量,销售量\n");
    while (pointer->next != NULL) {  // 写入所有数据
        fprintf(fp, "%s,%d_%02d_%d,%s,%ld,%s,%ld,%ld\n", pointer->col.name, pointer->col.type.main_type,
                pointer->col.type.mid_type, pointer->col.type.subtype, (pointer->col.type.isotc == 1 ? "是" : "否"),
                pointer->col.man_date, (pointer->col.qa == 1 ? "正常" : (pointer->col.qa == -1 ? "过期" : "临期")),
                pointer->col.stock, pointer->col.sale_vol);
        pointer = pointer->next;
    }  // 此循环会遗漏尾端数据，故循环外重新进行一次写入
    fprintf(fp, "%s,%d_%02d_%d,%s,%ld,%s,%ld,%ld\n", pointer->col.name, pointer->col.type.main_type,
            pointer->col.type.mid_type, pointer->col.type.subtype, (pointer->col.type.isotc == 1 ? "是" : "否"),
            pointer->col.man_date, (pointer->col.qa == 1 ? "正常" : (pointer->col.qa == -1 ? "过期" : "临期")),
            pointer->col.stock, pointer->col.sale_vol);
    fclose(fp);
    return 0;  //成功
}

int csvSingGen(char *n0) {  // 创建单项报表

    typedef struct temp {
        char name[256];
        int num;
        double unit_price;
        double total;
        long sales_vol;
        long stock;
        char ymd[20];
        char hms[20];
    } temp;  // 对需要的数据建立临时结构体

    int arg = 0;  // 记录字符串比较状态
    char name[256];
    temp *cur = (temp *) malloc(sizeof(temp)); // 暂存单项数据
    char *filename = (char *) malloc(270 * sizeof(char));  // 存储生成的文件名

    strcpy(name, n0);  // 避免直接使用形参导致的数据丢失
    strcpy(filename, "stats_");  // 准备文件名

    FILE *fp = fopen("stats.sav", "r+"), *fp2;  // 打开存档

    while (!feof(fp)) {
        fscanf(fp, "%s\t%d\t%lf\t%lf\t%ld\t%ld\t%s %s\n", cur->name, &cur->num, &cur->unit_price, &cur->total,
               &cur->sales_vol, &cur->stock, cur->ymd, cur->hms);  // 读取一行
        if ((arg = strcmp(cur->name, name) == 0)) {  // 判定是否存在需要的记录（名字相同）
            strcat(filename, name);  // 是则合成报表文件名
            strcat(filename, ".csv");
            fclose(fp); // 关闭存档文件
            fp2 = fopen(filename, "w+"); // 建立报表
            fp = fopen("stats.sav", "r+"); // 重新打开存档文件
            while (!feof(fp)) { // 按（时间）先后顺序读取所有项
                fscanf(fp, "%s\t%d\t%lf\t%lf\t%ld\t%ld\t%s %s\n", cur->name, &cur->num, &cur->unit_price, &cur->total,
                       &cur->sales_vol, &cur->stock, cur->ymd, cur->hms);  // 单条读取
                if ((arg = strcmp(cur->name, name) == 0))  // 检查名字是否相同
                    fprintf(fp2, "%s,%d,%.2lf,%.2lf,%ld,%ld,%s %s\n", cur->name, cur->num, cur->unit_price, cur->total,
                            cur->sales_vol, cur->stock, cur->ymd, cur->hms);  // 是，写入到报表
            }
            free(cur);  // 释放内存
            free(filename);
            fclose(fp);  // 关闭文件
            fclose(fp2);
            return 0;  // 正常退出
        }
    }

    free(cur);
    free(filename);
    fclose(fp);
    return -1;  // 未读取到内容
}