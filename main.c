//
// Created by Steve_Hsu on 2023/3/20.
// 主函数
//

#include <stdio.h>
#include <stdlib.h>
#include "list_func.h"

//#define DEBUG
// 程序调试标记
#define RDY
// 程序完成标记

#ifdef DEBUG

extern void makeLinkedList(unit *);  // 生成测试用链表

// 单个测试用函数导入区域
//extern int del(char*, unit*);
#endif

#ifndef RDY

extern void listAll(unit *);  // 测试时列出链表所有节点
#endif

extern void menu(unit *);  // 菜单

int main() {
    unit *head = malloc(sizeof(unit));  // 生成首个节点
    unit *ff;  // 用于内存释放

    //system("chcp 65001");

    printf("读取数据中...\n");

#ifndef DEBUG
    fileRead(head);        // 加载所有条目并生成链表，把链表首部地址写入head
    system("cls");
#endif

#ifdef DEBUG
    makeLinkedList(head);  // 生成测试用链表
#endif

#ifndef RDY
    listAll(head);  // 测试时列出链表所有节点
#endif

#ifdef DEBUG
    // 函数测试区域
    // del(gets((char*)malloc(256*sizeof(char))), head);
    // listAll(head);
#endif

    menu(head);  // 加载菜单并实现功能

    while (head != NULL) {   // 链表内存释放
        ff = head;
        head = head->next;
        free(ff);
    }
    return 0;
}