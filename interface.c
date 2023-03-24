//
// Created by Steve_Hsu on 2023/3/21.
// ���׽�������
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "list_func.h"

void stdprn(unit *ptr) {
    printf("Ʒ����%s\t���ࣺ%d-%d-%d\tOTC��%s\n�������ڣ�%ld\t�������%ld\t��������%ld\n",
           ptr->col.name, ptr->col.type.main_type, ptr->col.type.mid_type, ptr->col.type.subtype,
           (ptr->col.type.isotc == 1 ? "��" : "��"), ptr->col.man_date, ptr->col.stock, ptr->col.sale_vol);
}

unit *menu(unit *head) {  // �˵�������ʵ�֣�����Ϊ�����׵�ַ
    int arg;  // ��ȡ���������
    int qacond; // ����Ƿ���ҩƷ��Ҫ���ڵı�ʶ
    char name[256]; // ��ȡ��������Ŀ������

    unit *result, *mid = (unit *) malloc(sizeof(unit));  // ��ʱ�洢����������

    init:      // �˱�ǩ���ڷ������˵�
    strnset(name, '\0', 256);
    mid = NULL;
    mid = (unit *) malloc(sizeof(unit));
    mid->next = NULL;
    result = NULL;
    printf("��ǰ���ڣ�");
    timePrn();  // �������

    if ((!strcmp(head->col.name, "NULL")) && head->next == NULL) {
        printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n���棺����Ŀ��¼��ѡ�������\n\n");
        printf("1.����ҩƷ��Ŀ\n2.�������۱���\n3.ȡ�����沢�˳�\n");
        printf("\n������Ӧ��Ų����»س�����[ ]\b\b");
        scanf("%d", &arg);
        switch (arg) {
            case 1:
                printf("������ҩƷ����");
                scanf("%s", mid->col.name);
                printf("����������ţ��ÿո�ָ������֣�");
                scanf("%d %d %d", &mid->col.type.main_type, &mid->col.type.mid_type, &mid->col.type.subtype);
                printf("��ҩƷ�Ƿ�ΪOTCҩƷ����������1����������0��");
                scanf("%d", &mid->col.type.isotc);
                printf("������ҩƷ�������ڣ��԰�λ���ֱ�ʾ����");
                scanf("%ld", &mid->col.man_date);
                chkSingDate(mid);
                printf("������ҩƷ�������");
                scanf("%ld", &mid->col.stock);
                mid->col.sale_vol = 0;
                if ((arg == saleStats(mid, 0, 0)) != 0) {
                    printf("\n�����޷����Ķ�д�����ۼ�¼�ļ���\n");
                }
                replace(head, mid);
                printf("\n��ӳɹ���\n\n");
                free(mid);
                system("pause");  // �������˵�ǰ�ȴ�����
                system("cls");  // ����
                break;
            case 2:
                arg = 6;
                goto submenu;
            case 3:
                arg = 8;
                goto submenu;
            default:
                printf("������Ч����š�\n\n");
                goto init;
        }

    }
    printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ӭ����ѡ�����²����е�һ����\n\n");
    printf("1.����ҩƷ��Ŀ\n2.��ѯҩƷ��Ŀ\n3.�޸�ҩƷ��Ŀ\n4.ɾ��ҩƷ��Ŀ\n5.��ʾ����ҩƷ\n6.�������۱���\n7.����ҩƷ\n8.���沢�˳�\n9.ȡ�����沢�˳�\n");
    if ((qacond = showQaCond(head, 0)) == -1)
        printf("\n[ע��] �����п��ҩ�Ｔ�����Ѿ����ڡ�\n[ע��] ѡ�����5�Բ鿴���顣\n");
    printf("\n������Ӧ��Ų����»س�����[ ]\b\b");
    scanf("%d", &arg); // ��ȡ�������

    //�Ӳ˵�
    submenu:
    switch (arg) {
        case 1:
            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�1.����ҩƷ��Ŀ\n\n");
            printf("������ҩƷ����");
            scanf("%s", mid->col.name);
            printf("����������ţ��ÿո�ָ������֣�[        ]\b\b\b\b\b\b\b\b\b");
            scanf("%d %d %d", &mid->col.type.main_type, &mid->col.type.mid_type, &mid->col.type.subtype);
            printf("��ҩƷ�Ƿ�ΪOTCҩƷ����������1����������0��[ ]\b\b");
            scanf("%d", &mid->col.type.isotc);
            printf("������ҩƷ�������ڣ��԰�λ���ֱ�ʾ����[        ]\b\b\b\b\b\b\b\b");
            scanf("%ld", &mid->col.man_date);
            chkSingDate(mid);
            printf("������ҩƷ�������");
            scanf("%ld", &mid->col.stock);
            mid->col.sale_vol = 0;
            if ((arg == saleStats(mid, 0, 0)) != 0) {
                printf("\n�����޷����Ķ�д�����ۼ�¼�ļ���\n");
            }
            system("cls");
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�1.����ҩƷ��Ŀ\n\n");
            result = add(mid, head);  // ������ӽڵ�
            if (result != NULL) {  // ʧ��
                printf("���󣺸���Ŀ�Ѵ��ڡ���ϸ��ϢΪ��\n");
                stdprn(result);
            } else {  // �ɹ�
                printf("\n��ӳɹ���\n\n");
            }
            free(mid);
            system("pause");  // �������˵�ǰ�ȴ�����
            system("cls");  // ����
            goto init;  // �������˵�

        case 2:
            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�2.��ѯҩƷ��Ŀ\n\n");
            printf("��������Ҫ������ҩƷ����");
            getchar();
            gets(name);
            system("cls");
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�2.��ѯҩƷ��Ŀ\n\n");
            if ((result = findByName(name, head)) != NULL) {  // ���Բ���
                printf("���ҵ���Ŀ��\n");
                chkSingDate(result);
                stdprn(result);
            } else {  // ����ʧ��
                printf("����δ�ҵ���Ŀ��\n��ȷ�������Ƿ���ȷ��\n");
            }
            system("pause");
            system("cls");
            goto init;

        case 3:
            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�3.�޸�ҩƷ��Ŀ\n\n");
            printf("������Ҫ�޸���Ŀ��ҩƷ����");
            scanf("%s", name);
            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�3.�޸�ҩƷ��Ŀ\n\n");
            if ((result = findByName(name, head)) != NULL) {  // ���ҵ����޸���Ŀ�������޸�
                chkSingDate(result);
                printf("\n��ǰ��Ŀ��Ϣ��\n");
                stdprn(result);
                printf("��������ҩƷ��Ϣ��\n\n");
                printf("ҩƷ���ƣ�");
                scanf("%s", mid->col.name);
                if ((arg = strcmp(mid->col.name, result->col.name)) != 0) {
                    result->col.stock = 0;
                    if ((arg == saleStats(result, 0, 0)) != 0) {
                        printf("\n�����޷����Ķ�д�����ۼ�¼�ļ���\n");
                    }
                }
                printf("����������ţ��ÿո�ָ������֣�[        ]\b\b\b\b\b\b\b\b\b");
                scanf("%d %d %d", &mid->col.type.main_type, &mid->col.type.mid_type, &mid->col.type.subtype);
                printf("��ҩƷ�Ƿ�ΪOTCҩƷ����������1����������0��[ ]\b\b");
                scanf("%d", &mid->col.type.isotc);
                printf("������ҩƷ�������ڣ��԰�λ���ֱ�ʾ����[        ]\b\b\b\b\b\b\b\b\b");
                scanf("%ld", &mid->col.man_date);
                chkSingDate(mid);
                printf("������ҩƷ�������");
                scanf("%ld", &mid->col.stock);
                replace(result, mid);
                if ((arg == saleStats(mid, 0, 0)) != 0) {
                    printf("\n�����޷����Ķ�д�����ۼ�¼�ļ���\n");
                }
            } else printf("����δ�ҵ���Ŀ��\n");   // δ���ҵ����޸���Ŀ
            free(mid);
            system("pause");
            system("cls");
            goto init;

        case 4:
            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�4.ɾ��ҩƷ��Ŀ\n\n");
            printf("��������Ҫɾ������Ŀ��ҩƷ������");
            scanf("%s", name);
            system("cls");
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�4.ɾ��ҩƷ��Ŀ\n\n");
            if ((result = findByName(name, head)) != NULL) {  // ���ҵ����޸���Ŀ�������޸�
                chkSingDate(result);
                printf("\n��ǰ��Ŀ��Ϣ��\n");
                stdprn(result);
                result->col.stock = 0;
                if ((arg == saleStats(result, 0, 0)) != 0) {
                    printf("\n�����޷����Ķ�д�����ۼ�¼�ļ���\n");
                }
                free(mid);
                if ((mid = del(name, head)) != NULL) {  // ����ɾ����Ŀ
                    head = mid;
                    printf("ɾ�������ɹ���ɡ�\n");
                }
            } else {  // ɾ��ʧ��
                printf("����δ�ҵ���Ŀ��\n");
            }
            system("pause");
            system("cls");
            goto init;

        case 5:
            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�5.��ʾ��/����ҩƷ\n");
            printf("\n������Ԥ�����ڣ�������С��60�죩����ڵ�ҩƷ�б�\n");
            printf("������������/����ҩƷ��\n");
            showQaCond(head, 1);  // ���Ҳ������������/������Ŀ
            system("pause");
            system("cls");
            goto init;
        case 6:
            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�6.�������۱���\n");


            printf("\nѡ��һ���������:\n1.���ɵ�Ʒ�����ۼ�¼\n2.���ɿ��ͳ��\n\n");
            printf("\n������Ӧ��Ų����»س�����[ ]\b\b");
            scanf("%d", &arg);

            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�6.�������۱���\n");

            switch (arg) {
                case 1:
                    printf("\n��������Ҫ���ɱ���ҩƷ����");
                    scanf("%s", name);
                    if ((arg = csvSingGen(name)) == 0) {
                        printf("\n��ɡ������ִ洢������ͬ��Ŀ¼�£��ļ���Ϊ��stats_%s.csv\n", name);
                    } else printf("\n�����޴���Ŀ��\n");
                    break;
                case 2:
                    printf("\n����������...\n");
                    if ((arg = csvAllGen(head)) == 0) {  // ���ɱ���ж������Ƿ�ɹ�
                        printf("\n��ɡ������ִ洢������ͬ��Ŀ¼�£��ļ���Ϊ��stock.csv\n");
                    } else printf("\n�����������Ȩ�޺ʹ���ʣ��ռ䡣\n");
                    break;
                default:
                    printf("\n���������󣬷������˵���\n");
                    break;
            }

            system("pause");
            system("cls");
            goto init;
        case 7:
            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�7.����ҩƷ\n\n");
            printf("��������Ҫ���۵�ҩƷ����");
            scanf("%s", name);
            system("cls");
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�7.����ҩƷ\n\n");
            if ((result = findByName(name, head)) != NULL) {  // ���Բ���
                printf("���ҵ���Ŀ��\n");
                numin:
                chkSingDate(result);  // ˢ���������
                stdprn(result);
                switch (result->col.qa) {  // �ж�ҩƷ�Ƿ����ڻ����
                    case -1:
                        printf("\n[����] ��ҩƷ���ڡ���ֹ������\n");
                        goto ret_prev;
                    case 0:
                        printf("\n[ע��] ��ҩƷ���ڡ�\n");
                        break;
                    default:
                        break;
                }
                if (result->col.stock == 0) {
                    printf("\n[����] ��ҩƷ�޿�档�������˵���\n");
                    goto ret_prev;
                }
                int num; // ����
                double unit_price;  // ����
                printf("\n������ҩƷ������");
                scanf("%d", &num);
                if (num > result->col.stock || num <= 0) {  // ����������Ƿ����
                    system("cls");
                    printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�7.����ҩƷ\n\n");
                    printf("���󣺿������������������������ѡ�������\n1.������������\n2.�������˵�\nѡ��һ�");
                    scanf("%d", &arg);
                    if (arg == 1) {
                        system("cls");
                        printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�7.����ҩƷ\n");
                        goto numin;
                    } else if (arg == 2) goto ret_prev;
                    else {  // ��ֹ���������
                        printf("\n���������󡣷������˵���\n");
                        goto ret_prev;
                    }
                } else {
                    printf("\n�����뵥�ۣ�Ԫ����");
                    scanf("%lf", &unit_price);
                    printf("\n�ܼۣ�%.2lf Ԫ��֧���Ƿ�ɹ���(�ǣ�1����0) [ ]\b\b", 1.0 * num * unit_price);  // ����۸�
                    scanf("%d", &arg);
                    if (arg == 1) {  //�շѳɹ���۳����������������
                        if ((arg == saleStats(result, num, unit_price)) == 0) {
                            printf("\n���״̬���¡�\n");
                        } else printf("\n�����޷����Ķ�д���ļ���\n");
                    } else printf("\n���״̬�޸��¡�\n");
                    goto ret_prev;
                }
            } else {  // ����ʧ��
                printf("����δ�ҵ���Ŀ��\n��ȷ�������Ƿ���ȷ��\n");
            }

        ret_prev:
            system("pause");
            system("cls");
            goto init;

        case 8:
            printf("���沢�˳���...\n");
            dataSave(head);     // �������ݲ����ϴ����ݽ��б���
            break;

        case 9:
            printf("�Ķ�δ���档�˳���...\n");
            break;

        default:  // ��ֹ���������
            system("cls");
            printf("\n\n�����쳣����š�\n\n�����������档\n\n");
            system("pause");
            system("cls");
            goto init;
    }
    free(mid);
    return head;
}
