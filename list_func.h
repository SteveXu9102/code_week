//
// Created by Steve_Hsu on 2023/3/22.
//

#ifndef CODE_WEEK_LIST_FUNC_H
#define CODE_WEEK_LIST_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "datastore.h"
// ������ͨ�����ݽṹ

extern unit *findByName(char name[256], unit *);
// ���Һ���

extern unit *add(unit *, unit *);
// ��Ӻ���

extern unit *del(char *, unit *);
// ɾ������

extern void replace(unit *, unit *);
// �滻����

extern void dataSave(unit *);
// �浵����

extern int fileRead(unit *);
// �ļ���ȡ����

extern int saleStats(unit *, int, double);
// ��¼�����������/���䶯

extern int csvAllGen(unit *);
// ������ɺ���

extern int csvSingGen(char *);

extern void chkSingDate(unit *);
// ����Ŀ�����ж�

extern void chkAllDate(unit *);
// ������Ŀ�����ж�

extern int showQaCond(unit *, int);
// �ж�������Ƿ�����/����ҩ�� �� ��ʾ������/����ҩ��
// ʹ�õڶ��������л���������ģʽ

extern struct tm *outDateTime();
// ���һ���洢ʱ��Ľṹ��ָ��

extern void timePrn();
// ʱ����ʾ

extern int chkDate(long);
// ������������Ƿ���ȷ

extern int chkType(int, int, int);
// �������������Ƿ���ȷ

#endif //CODE_WEEK_LIST_FUNC_H
