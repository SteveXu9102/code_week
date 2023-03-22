//
// Created by Steve_Hsu on 2023/3/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "datastore.h"

extern unit *findByName(char *, unit *);

int sadd(unit *L, unit *head) {
    unit *mid = head, *p = (unit *) malloc(sizeof(unit));

    p->next = NULL;
    strcpy(p->col.name, L->col.name);
    p->col.type.main_type = L->col.type.main_type;
    p->col.type.mid_type = L->col.type.mid_type;
    p->col.type.subtype = L->col.type.subtype;
    p->col.sale_vol = L->col.sale_vol;
    p->col.type.isotc = L->col.type.isotc;
    p->col.man_date = L->col.man_date;
    p->col.stock = L->col.stock;

    unit *result = findByName(p->col.name, head);

    if (result != NULL) {
        free(p);
        return -1;
    } else {
        while (mid->next != NULL) {
            mid = mid->next;
        }
        mid->next = p;
    }
    return 0;
}