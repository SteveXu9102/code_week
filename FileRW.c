//
// Created by Steve_Hsu on 2023/3/20.
// �ļ���д����
//

#include <stdio.h>
#include <stdlib.h>
#include "list_func.h"

int fileRead(unit *head) {     // ��ȡ�浵�����ؽ�����
    unit *single = (unit *) malloc(sizeof(unit));  // ������ת��������
    FILE *fp = fopen("stock_info.bin", "rb+");

    if (fp == NULL) fp = fopen("stock_info.bin", "wb+");    // �ж���дȨ���Ƿ�����
    if (fp == NULL) {
        printf("ERROR: CANNOT CREATE OR READ FILE. THE PROGRAM WILL EXIT.\n");
        exit(-1);
    }

    getc(fp);  // ���feof���Զ�����Ĳ��������ļ�ָ�����1B�Ա�׼ȷʶ���ļ�β
    if (feof(fp) != 0) {
        printf("ERROR: NO RECORD.\n");   // ���浵���Ƿ��м�¼
        return -1;
    } else rewind(fp);  // �����ϳ�ʼ���ļ�ָ��

    while (!feof(fp)) {  // ���ָ���Ƿ����ļ�β
        fscanf(fp, "%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", single->col.name, &single->col.type.main_type,
               &single->col.type.mid_type, &single->col.type.subtype, &single->col.type.isotc, &single->col.man_date,
               &single->col.stock,
               &single->col.sale_vol);
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

    FILE *fp, *fp2;

    if ((fp = fopen("stock_info.bin", "rb")) != NULL) {  // ���浵�ļ��Ƿ���ڣ���������б���
        fclose(fp);
        if ((fp2 = fopen("stock_info.bin.bak", "rb")) != NULL) { // ���ɱ����ļ��Ƿ���ڣ�������ɾ��
            fclose(fp2);
            remove("stock_info.bin.bak");  // ɾ���ɱ����ļ�
        }
        rename("stock_info.bin", "stock_info.bin.bak");  // ���ϴδ洢�����ݽ��б���
    }

    fp = fopen("stock_info.bin", "wb+");  // �����´浵�ļ�

    do {  // д����������
        fprintf(fp, "%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", pointer->col.name, pointer->col.type.main_type,
                pointer->col.type.mid_type, pointer->col.type.subtype, pointer->col.type.isotc, pointer->col.man_date,
                pointer->col.stock,
                pointer->col.sale_vol);
        pointer = pointer->next;
    } while (pointer->next != NULL); // ��ѭ������©β�����ݣ���ѭ�������½���һ��д��
    fprintf(fp, "%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", pointer->col.name, pointer->col.type.main_type,
            pointer->col.type.mid_type, pointer->col.type.subtype, pointer->col.type.isotc, pointer->col.man_date,
            pointer->col.stock,
            pointer->col.sale_vol);
    fclose(fp);
}

int csvTableGenerate(unit* head) {
    unit* pointer = head;
    FILE *fp = fopen("list.csv", "w+");
    if (fp == NULL) return -1;
    fprintf(fp,"Ʒ��,����,�Ƿ�ΪOTCҩ��,��������,Ŀǰ����״̬,�����,������\n");
    do {  // д����������
        fprintf(fp, "%s,%d_%02d_%d,%s,%ld,%s,%ld,%ld\n", pointer->col.name, pointer->col.type.main_type,
                pointer->col.type.mid_type, pointer->col.type.subtype, (pointer->col.type.isotc == 1 ? "��" : "��"), pointer->col.man_date,
                (pointer->col.qa == 1 ? "����" : (pointer->col.qa == -1 ? "����" : "����")), pointer->col.stock, pointer->col.sale_vol);
        pointer = pointer->next;
    } while (pointer->next != NULL); // ��ѭ������©β�����ݣ���ѭ�������½���һ��д��
    fprintf(fp, "%s,%d_%02d_%d,%s,%ld,%s,%ld,%ld\n", pointer->col.name, pointer->col.type.main_type,
            pointer->col.type.mid_type, pointer->col.type.subtype, (pointer->col.type.isotc == 1 ? "��" : "��"), pointer->col.man_date,
            (pointer->col.qa == 1 ? "����" : (pointer->col.qa == -1 ? "����" : "����")), pointer->col.stock, pointer->col.sale_vol);
    fclose(fp);
    return 0;
}