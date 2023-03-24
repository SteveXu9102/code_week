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

unit *findByName(char name[256], unit *head) {     // ������Һ���������Ϊ��Ҫ���ҵ���Ŀ�����ַ����������ײ�ָ��
    unit *mid = head;  // ����ֱ���޸�ͷָ��
    char nm[256];
    strcpy(nm, name);
    if (strcmp(mid->col.name, nm) == 0) {  //���ײ��ڵ�Ĳ��ұȽ�
        return mid;    // ���ҵ��󷵻ص�ַ
    }
    while (mid->next != NULL) {    // �Ժ����ڵ�Ĳ��ұȽ�
        if (strcmp(mid->next->col.name, nm) == 0) {  // �Ƚ�����
            return mid->next;   // ���ҵ��󷵻ص�ַ
        }
        mid = mid->next;
    }
    return NULL;  // �޽�����ؿ�ָ��

}

unit *add(unit *L, unit *head) {  // ��ӽڵ㣬����Ϊ����ӵĽڵ����ݺ������ײ�ָ��
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


unit *del(char *name, unit *L) {  // ɾ���ڵ㣬����Ϊ��ɾ���Ľڵ����ַ����������ײ�ָ�룬����ֵ��ʾ�����Ƿ�ɹ�
    unit *head = L, *m; // m: �洢��ַ���м���
    m = findByName(name, L);  // ������ɾ���ڵ�
    if (m == L) {   // ��ɾ���ڵ�ǡΪ�ײ�
        if (m->next != NULL) {
            L = m->next;
            free(m);  // �ͷ�ԭ�ײ����ڴ�
        } else {
            free(m);
            L = (unit *) malloc(sizeof(unit));
            strcpy(L->col.name, "NULL");
            L->next = NULL;
        }
        return L;
    } else if (m != NULL) {
        unit *n = m->next;  // ��ȡ��ɾ���ڵ��nextָ���Ӧ��ַ
        while (L->next != NULL) {
            if (L->next == m) break;  // ʹfָ���ɾ���ڵ��ǰһ�ڵ�
            L = L->next;
        }
        free(m);  // �ͷŽڵ��ڴ�
        L->next = n;  // ���Ӹýڵ�ǰ��Ľڵ�
        return head;  // �����ɹ�
    } else return NULL;
}