//
// Created by Steve_Hsu on 2023/3/21.
//
#include <stdio.h>
#include <strings.h>
#include "datastore.h"

unit* find(char* name, unit* head) {
    unit* mid = head;
    if (mid->next != NULL && strcmp(mid->col.name, name) == 0) {
        return mid;
    }
    while (mid->next != NULL) {
        if (strcmp(mid->next->col.name, name) == 0) {
            return mid->next;
        }
        mid = mid->next;
    }
    return NULL;

}