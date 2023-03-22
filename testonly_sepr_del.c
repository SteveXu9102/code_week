//
// Created by Steve_Hsu on 2023/3/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "datastore.h"

extern unit *findByName(char *, unit *);

int delete(char *name, unit *L) {
    unit *f = L, *m;
    m = findByName(name, f);
    if (m == L) {
        L = L->next;
        free(m);
    } else if (m != NULL) {
        unit *n = m->next;
        while (f->next != NULL) {
            if (f->next == m) break;
            f = f->next;
        }
        free(m);
        f->next = n;
        return 0;
    } else return -1;
}