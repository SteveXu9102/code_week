#include <stdlib.h>
#include <string.h>
#include"list_func.h"

// 数据操作函数
// 增删改查 - 康宇宸

void replace(unit *dest, unit *new) {      // 对应数据替换
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

unit *findByName(char name[256], unit *head) {     // 链表查找函数，参数为需要查找的条目名称字符串和链表首部指针
    unit *mid = head;  // 避免直接修改头指针
    char nm[256];
    strcpy(nm, name);
    if (strcmp(mid->col.name, nm) == 0) {  //对首部节点的查找比较
        return mid;    // 查找到后返回地址
    }
    while (mid->next != NULL) {    // 对后续节点的查找比较
        if (strcmp(mid->next->col.name, nm) == 0) {  // 比较名称
            return mid->next;   // 查找到后返回地址
        }
        mid = mid->next;
    }
    return NULL;  // 无结果返回空指针

}

unit *add(unit *L, unit *head) {  // 添加节点，参数为待添加的节点数据和链表首部指针
    unit *mid = head, *p = (unit *) malloc(sizeof(unit));
    // mid: 避免直接修改head指向，p: 利用malloc随机获取地址，成为链表新尾端
    p->next = NULL;  // 确保尾端next指针为空
    replace(p, L);  // 将数据传递给p

    unit *result = findByName(p->col.name, head);  // 检查是否有同名称项

    if (result != NULL) {   // 出现同名称项
        free(p);   // 释放p的内存
        return result;      // 返回同名称项的地址
    } else {
        while (mid->next != NULL) {
            mid = mid->next;         // 无同名称项，将mid指向旧尾端
        }
        mid->next = p;  // 链接新旧尾端
    }
    return NULL;  // 返回空指针
}


unit *del(char *name, unit *L) {  // 删除节点，参数为待删除的节点名字符串和链表首部指针，返回值表示操作是否成功
    unit *head = L, *m; // m: 存储地址的中间量
    m = findByName(name, L);  // 搜索待删除节点
    if (m == L) {   // 待删除节点恰为首部
        if (m->next != NULL) {
            L = m->next;
            free(m);  // 释放原首部的内存
        } else {
            free(m);
            L = (unit *) malloc(sizeof(unit));
            strcpy(L->col.name, "NULL");
            L->next = NULL;
        }
        return L;
    } else if (m != NULL) {
        unit *n = m->next;  // 获取待删除节点的next指针对应地址
        while (L->next != NULL) {
            if (L->next == m) break;  // 使f指向待删除节点的前一节点
            L = L->next;
        }
        free(m);  // 释放节点内存
        L->next = n;  // 链接该节点前后的节点
        return head;  // 操作成功
    } else return NULL;
}