//
// Created by Steve_Hsu on 2023/3/20.
// �ļ���д����
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "list_func.h"

int fileRead(unit *head) {     // ��ȡ�浵�����ؽ�����
    unit *single = (unit *) malloc(sizeof(unit));  // ������ת��������
    FILE *fp = fopen("stock_info.sav", "r+");

    if (fp == NULL) fp = fopen("stock_info.sav", "w+");    // �ж���дȨ���Ƿ�����
    if (fp == NULL) {
        printf("ERROR: CANNOT CREATE OR READ FILE. THE PROGRAM WILL EXIT.\n");
        exit(-1);
    }

    getc(fp);  // ���feof���Զ�����Ĳ��������ļ�ָ�����1B�Ա�׼ȷʶ���ļ�β
    if (feof(fp) != 0) {
        printf("ERROR: NO RECORD.\n");   // ���浵���Ƿ��м�¼
        system("pause");
        fclose(fp);
        strcpy(head->col.name, "NULL");
        head->next = NULL;
        return -1;
    } else rewind(fp);  // �����ϳ�ʼ���ļ�ָ��

    while (!feof(fp)) {  // ���ָ���Ƿ����ļ�β
        fscanf(fp, "%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", single->col.name, &single->col.type.main_type,
               &single->col.type.mid_type, &single->col.type.subtype, &single->col.type.isotc, &single->col.man_date,
               &single->col.stock, &single->col.sale_vol);
        replace(head, single);  // ��������
        if (feof(fp)) continue;  // �ٴμ��ָ���Ƿ����ļ�β�����ⲻ��Ҫ���ڴ濪��
        head->next = malloc(sizeof(unit));  // �����ڴ棬��������
        head = head->next;
    }
    fclose(fp);  // �ر��ļ�ָ��
    head->next = NULL;  // ʹ����βָ��Ϊ��
    return 0;
}

void dataSave(unit *pointer) {

    FILE *fp = fopen("stock_info.sav", "w+");  // �����´浵�ļ�

    if (fp == NULL) {
        printf("\n�����޷����棬�ļ�����ʧ�ܡ�\n");
        exit(-1);
    }

    while (pointer->next != NULL) {  // д����������
        fprintf(fp, "%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", pointer->col.name, pointer->col.type.main_type,
                pointer->col.type.mid_type, pointer->col.type.subtype, pointer->col.type.isotc, pointer->col.man_date,
                pointer->col.stock, pointer->col.sale_vol);
        pointer = pointer->next;
    }  // ��ѭ������©β�����ݣ���ѭ�������½���һ��д��
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
    fprintf(fp, "Ʒ��,����,�Ƿ�ΪOTCҩ��,��������,Ŀǰ����״̬,�����,������\n");
    while (pointer->next != NULL) {  // д����������
        fprintf(fp, "%s,%d_%02d_%d,%s,%ld,%s,%ld,%ld\n", pointer->col.name, pointer->col.type.main_type,
                pointer->col.type.mid_type, pointer->col.type.subtype, (pointer->col.type.isotc == 1 ? "��" : "��"),
                pointer->col.man_date, (pointer->col.qa == 1 ? "����" : (pointer->col.qa == -1 ? "����" : "����")),
                pointer->col.stock, pointer->col.sale_vol);
        pointer = pointer->next;
    }  // ��ѭ������©β�����ݣ���ѭ�������½���һ��д��
    fprintf(fp, "%s,%d_%02d_%d,%s,%ld,%s,%ld,%ld\n", pointer->col.name, pointer->col.type.main_type,
            pointer->col.type.mid_type, pointer->col.type.subtype, (pointer->col.type.isotc == 1 ? "��" : "��"),
            pointer->col.man_date, (pointer->col.qa == 1 ? "����" : (pointer->col.qa == -1 ? "����" : "����")),
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