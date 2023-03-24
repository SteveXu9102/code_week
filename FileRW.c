//
// Created by Steve_Hsu on 2023/3/20.
// 文件读写函数
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "list_func.h"

int fileRead(unit *head) {     // 读取存档并加载进链表
    unit *single = (unit *) malloc(sizeof(unit));  // 用于中转单项数据
    FILE *fp = fopen("stock_info.sav", "r+");

    if (fp == NULL) fp = fopen("stock_info.sav", "w+");    // 判定读写权限是否正常
    if (fp == NULL) {
        printf("ERROR: CANNOT CREATE OR READ FILE. THE PROGRAM WILL EXIT.\n");
        exit(-1);
    }

    getc(fp);  // 针对feof特性而必需的操作，将文件指针后移1B以便准确识别文件尾
    if (feof(fp) != 0) {
        printf("ERROR: NO RECORD.\n");   // 检查存档内是否有记录
        system("pause");
        fclose(fp);
        strcpy(head->col.name, "NULL");
        head->next = NULL;
        return -1;
    } else rewind(fp);  // 检查完毕初始化文件指针

    while (!feof(fp)) {  // 检查指针是否在文件尾
        fscanf(fp, "%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", single->col.name, &single->col.type.main_type,
               &single->col.type.mid_type, &single->col.type.subtype, &single->col.type.isotc, &single->col.man_date,
               &single->col.stock, &single->col.sale_vol);
        replace(head, single);  // 复制数据
        if (feof(fp)) continue;  // 再次检查指针是否在文件尾，避免不必要的内存开销
        head->next = malloc(sizeof(unit));  // 分配内存，延伸链表
        head = head->next;
    }
    fclose(fp);  // 关闭文件指针
    head->next = NULL;  // 使链表尾指针为空
    return 0;
}

void dataSave(unit *pointer) {

    FILE *fp = fopen("stock_info.sav", "w+");  // 生成新存档文件

    if (fp == NULL) {
        printf("\n错误：无法保存，文件操作失败。\n");
        exit(-1);
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
    fclose(fp);
}

int saleStats(unit *target, int num, double unit_price) {
    FILE *fp = fopen("stats.sav", "r");
    struct tm *t_current = outDateTime();
    if (fp == NULL) {
        fp = fopen("stats.sav", "w+");
        if (fp == NULL) {
            fclose(fp);
            return -1;
        }
    }
    fclose(fp);
    fp = fopen("stats.sav", "a+");

    fprintf(fp, "%s\t%d\t%.2lf\t%.2lf\t%ld\t%ld\t%4d-%02d-%02d %02d:%02d:%02d\n", target->col.name, num, unit_price,
            1.0 * num * unit_price, (target->col.sale_vol += num), (target->col.stock -= num),
            1900 + t_current->tm_year, 1 + t_current->tm_mon, t_current->tm_mday,
            t_current->tm_hour, t_current->tm_min, t_current->tm_sec);
    fclose(fp);
    return 0;
}

int csvAllGen(unit *head) {
    unit *pointer = head;
    FILE *fp = fopen("stock.csv", "w+");
    if (fp == NULL) return -1;
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
    return 0;
}

int csvSingGen(char *n0) {

    typedef struct temp {
        char name[256];
        int num;
        double unit_price;
        double total;
        long sales_vol;
        long stock;
        char ymd[20];
        char hms[20];
    } temp;

    int arg = 0;
    char name[256];
    temp *cur = (temp *) malloc(sizeof(temp));
    char *filename = (char *) malloc(270 * sizeof(char));

    strcpy(name, n0);
    strcpy(filename, "stats_");

    FILE *fp = fopen("stats.sav", "r+"), *fp2;

    while (!feof(fp)) {
        fscanf(fp, "%s\t%d\t%lf\t%lf\t%ld\t%ld\t%s %s\n", cur->name, &cur->num, &cur->unit_price, &cur->total,
               &cur->sales_vol, &cur->stock, cur->ymd, cur->hms);
        if ((arg = strcmp(cur->name, name) == 0)) {
            strcat(filename, name);
            strcat(filename, ".csv");
            fclose(fp);
            fp2 = fopen(filename, "w+");
            fp = fopen("stats.sav", "r+");
            while (!feof(fp)) {
                fscanf(fp, "%s\t%d\t%lf\t%lf\t%ld\t%ld\t%s %s\n", cur->name, &cur->num, &cur->unit_price, &cur->total,
                       &cur->sales_vol, &cur->stock, cur->ymd, cur->hms);
                if ((arg = strcmp(cur->name, name) == 0))
                    fprintf(fp2, "%s,%d,%.2lf,%.2lf,%ld,%ld,%s %s\n", cur->name, cur->num, cur->unit_price, cur->total,
                            cur->sales_vol, cur->stock, cur->ymd, cur->hms);
            }
            free(cur);
            free(filename);
            fclose(fp);
            fclose(fp2);
            return 0;
        }
    }

    free(cur);
    free(filename);
    fclose(fp);
    return -1;
}