//
// Created by Steve_Hsu on 2023/3/21.
// 此文件内函数仅作为对链表数据完整度进行测试之用
//

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "datastore.h"

void makeLinkedList(unit* head) {       // 用于读写测试的小型链表
    strcpy(head->col.name, "头孢");
    head->col.type.main_type = 1;
    head->col.type.mid_type = 1;
    head->col.type.subtype = 1;
    head->col.type.isotc = 1;
    head->col.man_date = 20220203;
    head->col.stock = 20;
    head->col.sale_vol = 13;
    head->next = malloc(sizeof(unit));
    head = head->next;
    strcpy(head->col.name, "阿莫西林");
    head->col.type.main_type = 1;
    head->col.type.mid_type = 2;
    head->col.type.subtype = 1;
    head->col.type.isotc = 1;
    head->col.man_date = 20160930;
    head->col.stock = 10;
    head->col.sale_vol = 6;
    head->next = malloc(sizeof(unit));
    head = head->next;
    strcpy(head->col.name, "咳特灵");
    head->col.type.main_type = 1;
    head->col.type.mid_type = 1;
    head->col.type.subtype = 3;
    head->col.type.isotc = 1;
    head->col.man_date = 20230301;
    head->col.stock = 3;
    head->col.sale_vol = 37;
    head->next = malloc(sizeof(unit));
    head = head->next;
    strcpy(head->col.name, "枇杷膏");
    head->col.type.main_type = 2;
    head->col.type.mid_type = 4;
    head->col.type.subtype = 1;
    head->col.type.isotc = 0;
    head->col.man_date = 20200529;
    head->col.stock = 45;
    head->col.sale_vol = 7;
    head->next = NULL;
}

void listAll(unit* h0) {  // 用于数据完整性测试的函数，输出所有链表的项
    do {
        printf("%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", h0->col.name, h0->col.type.main_type, h0->col.type.mid_type, h0->col.type.subtype, h0->col.type.isotc, h0->col.man_date, h0->col.stock, h0->col.sale_vol);
        h0 = h0->next;
    } while (h0->next != NULL);
    printf("%s\t%d\t%d\t%d\t%d\t%ld\t%ld\t%ld\n", h0->col.name, h0->col.type.main_type, h0->col.type.mid_type, h0->col.type.subtype, h0->col.type.isotc, h0->col.man_date, h0->col.stock, h0->col.sale_vol);
}