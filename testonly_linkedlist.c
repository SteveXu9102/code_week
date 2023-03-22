//
// Created by Steve_Hsu on 2023/3/21.
// ���ļ��ں�������Ϊ���������������Ƚ��в���֮��
//

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "datastore.h"

void makeLinkedList(unit* head) {       // ���ڶ�д���Ե�С������
    strcpy(head->col.name, "ͷ��");
    head->col.type.main_type = 1;
    head->col.type.mid_type = 1;
    head->col.type.subtype = 1;
    head->col.type.isotc = 1;
    head->col.man_date = 20220203;
    head->col.stock = 20;
    head->col.sale_vol = 13;
    head->next = malloc(sizeof(unit));
    head = head->next;
    strcpy(head->col.name, "��Ī����");
    head->col.type.main_type = 1;
    head->col.type.mid_type = 2;
    head->col.type.subtype = 1;
    head->col.type.isotc = 1;
    head->col.man_date = 20160930;
    head->col.stock = 10;
    head->col.sale_vol = 6;
    head->next = malloc(sizeof(unit));
    head = head->next;
    strcpy(head->col.name, "������");
    head->col.type.main_type = 1;
    head->col.type.mid_type = 1;
    head->col.type.subtype = 3;
    head->col.type.isotc = 1;
    head->col.man_date = 20230301;
    head->col.stock = 3;
    head->col.sale_vol = 37;
    head->next = malloc(sizeof(unit));
    head = head->next;
    strcpy(head->col.name, "���˸�");
    head->col.type.main_type = 2;
    head->col.type.mid_type = 4;
    head->col.type.subtype = 1;
    head->col.type.isotc = 0;
    head->col.man_date = 20200529;
    head->col.stock = 45;
    head->col.sale_vol = 7;
    head->next = NULL;
}

void listAll(unit* h0) {  // �������������Բ��Եĺ�������������������
    do {
        printf("%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", h0->col.name, h0->col.type.main_type, h0->col.type.mid_type, h0->col.type.subtype, h0->col.type.isotc, h0->col.man_date, h0->col.stock, h0->col.sale_vol);
        h0 = h0->next;
    } while (h0->next != NULL);
    printf("%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", h0->col.name, h0->col.type.main_type, h0->col.type.mid_type, h0->col.type.subtype, h0->col.type.isotc, h0->col.man_date, h0->col.stock, h0->col.sale_vol);
}