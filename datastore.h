//
// Created by Steve_Hsu on 2023/3/20.
// ��Ŀ�����ݽṹ
// CODING: GBK
//

#ifndef CODE_WEEK_DATASTORE_H
#define CODE_WEEK_DATASTORE_H
typedef struct types {
    int main_type;              // ����
    int mid_type;               // ����
    int subtype;                // С��
    int isotc;                  // ����ҩ��־��ʵ���а�����ֵ����
} types;

// ҩƷ��������� https://www.docin.com/p-1168914112.html ���зֶ�

typedef struct medication {
    char name[256];             // ����
    types type;                 // ����
    long man_date;              // ��������
    long stock;                 // �����
    long sale_vol;              // �ۼ�������
    short qa;                   // ������״̬��� - ����/����/���� -> 1/0/-1
} med;

typedef struct sing_unit {      // ���������λ
    med col;
    struct sing_unit *next;
} unit;

#endif //CODE_WEEK_DATASTORE_H
