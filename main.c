//
// Created by Steve_Hsu on 2023/3/20.
// 主函数
//

#include "list_func.h"

extern unit *menu(unit *);  // 菜单

int main() {
    unit *head = malloc(sizeof(unit));  // 生成首个节点
    unit *ff;  // 用于内存释放

    printf("读取数据中...\n");

    fileRead(head);        // 加载所有条目并生成链表，把链表首部地址写入head
    system("cls");

    head = menu(head);  // 加载菜单并实现功能

    dataSave(head);     // 保存数据

    while (head != NULL) {   // 链表内存释放
        ff = head;
        head = head->next;
        free(ff);
    }
    system("pause");
    return 0;
}