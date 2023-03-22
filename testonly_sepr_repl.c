//
// Created by Steve_Hsu on 2023/3/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "datastore.h"

void change(med* new, unit *dest) {
    if (&new->stock != NULL) dest->col.stock = new->stock;
    if (&new->sale_vol != NULL) dest->col.sale_vol = new->sale_vol;
    if (&new->name != NULL) strcpy(dest->col.name, new->name);
    if (&new->type.isotc != NULL) dest->col.type.isotc = new->type.isotc;
    if (&new->type.subtype != NULL) dest->col.type.subtype = new->type.subtype;
    if (&new->type.mid_type != NULL) dest->col.type.mid_type = new->type.mid_type;
    if (&new->type.main_type != NULL) dest->col.stock = new->stock;
    if (&new->man_date != NULL) dest->col.man_date = new->man_date;
}