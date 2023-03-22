//
// Created by Steve_Hsu on 2023/3/20.
// ������
//

#include <stdio.h>
#include <stdlib.h>
#include "list_func.h"

//#define DEBUG
// ������Ա��
#define RDY
// ������ɱ��

#ifdef DEBUG

extern void makeLinkedList(unit *);  // ���ɲ���������

// ���������ú�����������
//extern int del(char*, unit*);
#endif

#ifndef RDY

extern void listAll(unit *);  // ����ʱ�г��������нڵ�
#endif

extern void menu(unit *);  // �˵�

int main() {
    unit *head = malloc(sizeof(unit));  // �����׸��ڵ�
    unit *ff;  // �����ڴ��ͷ�

    //system("chcp 65001");

    printf("��ȡ������...\n");

#ifndef DEBUG
    fileRead(head);        // ����������Ŀ�������������������ײ���ַд��head
    system("cls");
#endif

#ifdef DEBUG
    makeLinkedList(head);  // ���ɲ���������
#endif

#ifndef RDY
    listAll(head);  // ����ʱ�г��������нڵ�
#endif

#ifdef DEBUG
    // ������������
    // del(gets((char*)malloc(256*sizeof(char))), head);
    // listAll(head);
#endif

    menu(head);  // ���ز˵���ʵ�ֹ���

    while (head != NULL) {   // �����ڴ��ͷ�
        ff = head;
        head = head->next;
        free(ff);
    }
    return 0;
}