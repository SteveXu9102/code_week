//
// Created by Steve_Hsu on 2023/3/20.
// ������
//

#include "list_func.h"

extern unit *menu(unit *);  // �˵�

int main() {
    unit *head = malloc(sizeof(unit));  // �����׸��ڵ�
    unit *ff;  // �����ڴ��ͷ�

    printf("��ȡ������...\n");

    fileRead(head);        // ����������Ŀ�����������������ײ���ַд��head
    system("cls");

    head = menu(head);  // ���ز˵���ʵ�ֹ���

    dataSave(head);     // ��������

    while (head != NULL) {   // �����ڴ��ͷ�
        ff = head;
        head = head->next;
        free(ff);
    }
    system("pause");
    return 0;
}