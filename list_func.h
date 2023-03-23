//
// Created by Steve_Hsu on 2023/3/22.
//

#ifndef CODE_WEEK_LIST_FUNC_H
#define CODE_WEEK_LIST_FUNC_H

#include "datastore.h"
// ������ͨ�����ݽṹ

extern unit *findByName(char name[256], unit *);

// ���Һ���
extern unit *add(unit *, unit *);
// ��Ӻ���
extern int del(char *, unit *);
// ɾ������
extern void replace(unit *, unit *);
// �滻����

extern void dataSave(unit *);
// �浵����
extern int fileRead(unit *);
// �ļ���ȡ����
extern int csvTableGenerate(unit*);
// ������ɺ���

extern void chkSingDate(unit *);
// ����Ŀ�����ж�
void chkAllDate(unit *);
// ������Ŀ�����ж�
extern int showQaCond(unit *, int);
// �ж�������Ƿ�����/����ҩ�� �� ��ʾ������/����ҩ��
// ʹ�õڶ��������л���������ģʽ

extern struct tm* outDateTime();
// ���һ���洢ʱ��Ľṹ��ָ��
extern void timePrn();
// ʱ����ʾ

#endif //CODE_WEEK_LIST_FUNC_H
