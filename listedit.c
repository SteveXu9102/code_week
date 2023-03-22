#include <stdlib.h>
#include <string.h>
#include"list_func.h"

// ���ݲ�������
// ��ɾ�Ĳ� - �����

void replace(unit *dest, unit *new) {      // ��Ӧ�����滻
    dest->col.stock = new->col.stock;
    dest->col.sale_vol = new->col.sale_vol;
    strcpy(dest->col.name, new->col.name);
    dest->col.type.isotc = new->col.type.isotc;
    dest->col.type.subtype = new->col.type.subtype;
    dest->col.type.mid_type = new->col.type.mid_type;
    dest->col.type.main_type = new->col.type.main_type;
    dest->col.stock = new->col.stock;
    dest->col.man_date = new->col.man_date;
}

unit *findByName(char *name, unit *head) {     // �������Һ���������Ϊ��Ҫ���ҵ���Ŀ�����ַ����������ײ�ָ��
    unit *mid = head;  // ����ֱ���޸�ͷָ��
    if (mid->next != NULL && strcmp(mid->col.name, name) == 0) {  //���ײ��ڵ�Ĳ��ұȽ�
        return mid;    // ���ҵ��󷵻ص�ַ
    }
    while (mid->next != NULL) {    // �Ժ����ڵ�Ĳ��ұȽ�
        if (strcmp(mid->next->col.name, name) == 0) {  // �Ƚ�����
            return mid->next;   // ���ҵ��󷵻ص�ַ
        }
        mid = mid->next;
    }
    return NULL;  // �޽�����ؿ�ָ��

}

unit *add(unit *L, unit *head) {  // ���ӽڵ㣬����Ϊ�����ӵĽڵ����ݺ������ײ�ָ��
    unit *mid = head, *p = (unit *) malloc(sizeof(unit));
    // mid: ����ֱ���޸�headָ��p: ����malloc�����ȡ��ַ����Ϊ������β��
    p->next = NULL;  // ȷ��β��nextָ��Ϊ��
    replace(p, L);  // �����ݴ��ݸ�p

    unit *result = findByName(p->col.name, head);  // ����Ƿ���ͬ������

    if (result != NULL) {   // ����ͬ������
        free(p);   // �ͷ�p���ڴ�
        return result;      // ����ͬ������ĵ�ַ
    } else {
        while (mid->next != NULL) {
            mid = mid->next;         // ��ͬ�������midָ���β��
        }
        mid->next = p;  // �����¾�β��
    }
    return NULL;  // ���ؿ�ָ��
}


int del(char *name, unit *L) {  // ɾ���ڵ㣬����Ϊ��ɾ���Ľڵ����ַ����������ײ�ָ�룬����ֵ��ʾ�����Ƿ�ɹ�
    unit *f = L, *m; // f: ����ֱ���޸�Lָ��m: �洢��ַ���м���
    m = findByName(name, f);  // ������ɾ���ڵ�
    if (m == L) {   // ��ɾ���ڵ�ǡΪ�ײ�
        L = m->next;  // �޸��ײ�ָ��
        free(m);  // �ͷ�ԭ�ײ����ڴ�
        return 0;
    } else if (m != NULL) {
        unit *n = m->next;  // ��ȡ��ɾ���ڵ��nextָ���Ӧ��ַ
        while (f->next != NULL) {
            if (f->next == m) break;  // ʹfָ���ɾ���ڵ��ǰһ�ڵ�
            f = f->next;
        }
        free(m);  // �ͷŽڵ��ڴ�
        f->next = n;  // ���Ӹýڵ�ǰ��Ľڵ�
        return 0;  // �����ɹ�
    } else return -1;  // ����ʧ��
}