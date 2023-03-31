//
// Created by Steve_Hsu on 2023/3/21.
// ���׽�������
//

#include "list_func.h"

void stdprn(unit *ptr) {  // ����Ŀ������Ϣ��ӡ
    printf("Ʒ����%s\t���ࣺ%d-%d-%d\tOTC��%s\n�������ڣ�%ld\t�������%ld\t��������%ld\n",
           ptr->col.name, ptr->col.type.main_type, ptr->col.type.mid_type, ptr->col.type.subtype,
           (ptr->col.type.isotc == 1 ? "��" : "��"), ptr->col.man_date, ptr->col.stock, ptr->col.sale_vol);
}

unit *menu(unit *head) {  // �˵���������ʵ�֣�����Ϊ���׵�ַ
    int arg;  // ��ȡ������š��洢������
    char name[256]; // ��ȡ��������Ŀ������

    unit *result, *mid;  // ��ʱ�洢���������� - resultΪ��ѯ����ĵ�ַ��midΪ����������ת������

    init:      // �˱�ǩ���ڷ������˵�
    strnset(name, '\0', 256);  // ����ֹ���Ÿ��������ֽڽ��г�ʼ��
    mid = NULL;  // ������еĵ�ַ��Ϣ
    mid = (unit *) malloc(sizeof(unit));  // �����µ�ַ
    mid->next = NULL;  // �������һ�ڵ㡱��Ϣ
    result = NULL;  //���֮ǰ��ѯ����ĵ�ַ��Ϣ
    arg = 0;  // ��ղ�����Ϣ
    printf("��ǰ���ڣ�");
    timePrn();  // �������

    if ((!strcmp(head->col.name, "NULL")) && head->next == NULL) {  // ����Ŀʱǿ�����ƹ���
        printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n���棺����Ŀ��¼��ѡ�������\n\n");
        printf("1.����ҩƷ��Ŀ\n2.�������۱���\n3.���沢�˳�\n");
        printf("\n������Ӧ��Ų����»س�����");
        scanf("%d", &arg);
        switch (arg) {
            case 1:
                printf("������ҩƷ����");
                scanf("%s", mid->col.name);
                printf("���������η����ţ�1-5��1-25��1-8�����ÿո�ָ����Σ�");
                scanf("%d %d %d", &mid->col.type.main_type, &mid->col.type.mid_type, &mid->col.type.subtype);
                if (chkType(mid->col.type.main_type, mid->col.type.mid_type, mid->col.type.subtype)) goto inerr;
                printf("��ҩƷ�Ƿ�ΪOTCҩƷ����������1����������0��");
                scanf("%d", &mid->col.type.isotc);
                if (mid->col.type.isotc != 1 && mid->col.type.isotc != 0) goto inerr;
                printf("������ҩƷ�������ڣ��԰�λ���ֱ�ʾ����");
                scanf("%ld", &mid->col.man_date);
                if (!chkDate((mid->col.man_date))) goto inerr;
                chkSingDate(mid);  // ����Ƿ���ڲ���¼
                printf("������ҩƷ�������");
                scanf("%ld", &mid->col.stock);
                if (mid->col.stock < 0) {
                    inerr:  // ���ݲ����Ϲ淶�������Դ���ʱ��ת
                    printf("\n���������������롣\n���������˵���\n");
                    goto ret_prev;  // ׼���������˵�
                }
                mid->col.sale_vol = 0;  // ���۶��ֵΪ0
                if ((arg = saleStats(mid, 0, 0)) != 0) {  // �ж����ۼ�¼д���Ƿ�ɹ�
                    printf("\n�����޷����Ķ�д�����ۼ�¼�ļ���\n");
                }
                replace(head, mid);  // ������д������
                printf("\n��ӳɹ���\n\n");
                free(mid);  // �ͷ��м�ṹ����ڴ�
                dataSave(head);
                printf("\n���浽�ļ�...\n");
                system("pause");  // �������˵�ǰ�ȴ�����
                system("cls");  // ����
                break;
            case 2:
                arg = 6;
                goto submenu;  // ֱ����ת��Ӧ����
            case 3:
                arg = 8;
                goto submenu;
            default:
                printf("������Ч����š�\n\n");  // ���������
                goto init;
        }

    }
    printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ӭ����ѡ�����²����е�һ����\n\n");
    printf("1.����ҩƷ��Ŀ\n2.��ѯҩƷ��Ŀ\n3.�޸�ҩƷ��Ŀ\n4.ɾ��ҩƷ��Ŀ\n5.��ʾ����ҩƷ\n6.�������۱���\n7.����ҩƷ\n8.���沢�˳�\n");
    if ((arg = showQaCond(head, 0)) == -1)  // ����Ƿ��������ҩƷ
        printf("\n[ע��] �����п��ҩ�Ｔ�����Ѿ����ڡ�\n[ע��] ѡ�����5�Բ鿴���顣\n");
    printf("\n������Ӧ��Ų����»س�����");
    scanf("%d", &arg); // ��ȡ�������

    //�Ӳ˵�
    submenu:
    switch (arg) {
        case 1:
            arg = 0;
            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�1.����ҩƷ��Ŀ\n\n");
            printf("������ҩƷ����");
            scanf("%s", mid->col.name);


            printf("���������η����ţ�1-5��1-25��1-8�����ÿո�ָ����Σ�");
            scanf("%d %d %d", &mid->col.type.main_type, &mid->col.type.mid_type, &mid->col.type.subtype);
            if (chkType(mid->col.type.main_type, mid->col.type.mid_type, mid->col.type.subtype)) goto inerr;
            printf("��ҩƷ�Ƿ�ΪOTCҩƷ����������1����������0��");
            scanf("%d", &mid->col.type.isotc);
            if (mid->col.type.isotc != 1 && mid->col.type.isotc != 0) goto inerr;
            printf("������ҩƷ�������ڣ��԰�λ���ֱ�ʾ����");
            scanf("%ld", &mid->col.man_date);
            if (!chkDate(mid->col.man_date)) goto inerr;
            chkSingDate(mid);
            printf("������ҩƷ�������");
            scanf("%ld", &mid->col.stock);
            if (mid->col.stock < 0) goto inerr;
            mid->col.sale_vol = 0;

            system("cls");
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�1.����ҩƷ��Ŀ\n\n");
            result = add(mid, head);  // ������ӽڵ�
            if (result != NULL) {  // ʧ�ܣ�ͬ����Ŀ����
                printf("���󣺸���Ŀ�Ѵ��ڡ���ϸ��ϢΪ��\n");
                stdprn(result);
            } else {  // �ɹ�
                printf("\n��ӳɹ���\n\n");
                dataSave(head);
                if ((arg = saleStats(mid, 0, 0)) != 0) {
                    printf("\n�����޷����Ķ�д�����ۼ�¼�ļ���\n");
                }
                printf("\n���浽�ļ�...\n");
            }
            free(mid);
            system("pause");  // �������˵�ǰ�ȴ�����
            system("cls");  // ����
            goto init;  // �������˵�

        case 2:
            arg = 0;
            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�2.��ѯҩƷ��Ŀ\n\n");
            printf("��������Ҫ������ҩƷ����");
            getchar(); // �˴���ȡ����Ļس�������gets���ȡ��ֱ����ת��һ��
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
            arg = 0;
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
                chkSingDate(result);  // ����Ƿ�����
                printf("\n��ǰ��Ŀ��Ϣ��\n");
                stdprn(result);
                printf("��������ҩƷ��Ϣ��\n\n");
                printf("ҩƷ���ƣ�");
                scanf("%s", mid->col.name);
                printf("���������η����ţ�1-5��1-25��1-8�����ÿո�ָ����Σ�");
                scanf("%d %d %d", &mid->col.type.main_type, &mid->col.type.mid_type, &mid->col.type.subtype);
                if (chkType(mid->col.type.main_type, mid->col.type.mid_type, mid->col.type.subtype)) goto inerr;
                printf("��ҩƷ�Ƿ�ΪOTCҩƷ����������1����������0��");
                scanf("%d", &mid->col.type.isotc);
                if (mid->col.type.isotc != 1 && mid->col.type.isotc != 0) goto inerr;
                printf("������ҩƷ�������ڣ��԰�λ���ֱ�ʾ����");
                scanf("%ld", &mid->col.man_date);
                if (!chkDate(mid->col.man_date)) goto inerr;
                chkSingDate(mid);
                printf("������ҩƷ�������");
                scanf("%ld", &mid->col.stock);
                if (mid->col.stock < 0) goto inerr;

                if ((arg = strcmp(mid->col.name, result->col.name)) != 0) {  // ������������Ʋ�ͬ
                    result->col.stock = 0;  // ��վɿ��
                    if ((arg = saleStats(mid, 0, 0)) != 0) {  // ��¼���仯
                        printf("\n�����޷����Ķ�д�����ۼ�¼�ļ���\n");
                    }
                } else mid->col.sale_vol = result->col.sale_vol;
                replace(result, mid);  // ������д����Ϣ
                dataSave(head);
                printf("\n���浽�ļ�...\n");
                if ((arg = saleStats(result, 0, 0)) != 0) {  // д������Ϣ
                    printf("\n�����޷����Ķ�д�����ۼ�¼�ļ���\n");
                }
            } else printf("����δ�ҵ���Ŀ��\n");   // δ���ҵ����޸���Ŀ
            free(mid);
            system("pause");
            system("cls");
            goto init;

        case 4:
            arg = 0;
            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�4.ɾ��ҩƷ��Ŀ\n\n");
            printf("��������Ҫɾ������Ŀ��ҩƷ������");
            scanf("%s", name);
            system("cls");
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�4.ɾ��ҩƷ��Ŀ\n\n");
            if ((result = findByName(name, head)) != NULL) {  // ���Ҵ�ɾ����Ŀ
                chkSingDate(result);
                printf("\n��ǰ��Ŀ��Ϣ��\n");
                stdprn(result);
                choose:
                printf("\n�Ƿ�ɾ�������ǣ�1  ��0��[ ]\b\b");
                scanf("%d", &arg);
                switch (arg) {
                    case 0:
                        printf("\nȡ����\n");
                        goto ret_prev;
                    case 1:
                        printf("ɾ����...");
                        goto delete;
                    default:
                        printf("������Ч����š�\n\n");  // ���������
                        goto choose;
                }
                delete:
                result->col.stock = 0;
                if ((arg = saleStats(result, 0, 0)) != 0) { // ��¼���䶯
                    printf("\n�����޷����Ķ�д�����ۼ�¼�ļ���\n");
                }
                free(mid);
                if ((mid = del(name, head)) != NULL) {  // ����ɾ����Ŀ
                    head = mid; // ��¼������ͷ��ַ
                    dataSave(head);
                    printf("\n���浽�ļ�...\n");
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
            arg = 0;
            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�6.�������۱���\n");


            printf("\nѡ��һ���������:\n1.���ɵ�Ʒ�����ۼ�¼\n2.���ɿ��ͳ��\n\n");
            printf("\n������Ӧ��Ų����»س�����");
            scanf("%d", &arg);

            system("cls");
            printf("��ǰ���ڣ�");
            timePrn();
            printf("********** ҩ������ϵͳ Ver.1.0 **********\n\n��ǰѡ�6.�������۱���\n");

            switch (arg) {
                case 1:
                    printf("\n��������Ҫ���ɱ���ҩƷ����");
                    scanf("%s", name);
                    if ((arg = csvSingGen(name)) == 0) {  // ���ɱ���
                        printf("\n��ɡ������ִ洢������ͬ��Ŀ¼�£��ļ���Ϊ��stats_%s.csv\n", name);
                    } else printf("\n�����޴���Ŀ��\n");
                    break;
                case 2:
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
            arg = 0;
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
                numin:  // �������������
                chkSingDate(result);  // ˢ���������
                stdprn(result);
                switch (result->col.qa) {  // �ж�ҩƷ�Ƿ����ڻ�����Ա������ʾ
                    case -1:
                        printf("\n[����] ��ҩƷ���ڡ���ֹ������\n");
                        goto ret_prev;  // ׼�������ϼ��˵�
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
                        if ((arg = saleStats(result, num, unit_price)) == 0) { // ��¼�������
                            dataSave(head);
                            printf("\n���浽�ļ�...\n");
                            printf("\n���״̬���¡�\n");
                        } else printf("\n�����޷����Ķ�д���ļ���\n");
                    } else printf("\n���״̬�޸��¡�\n");
                    goto ret_prev;
                }
            } else {  // ����ʧ��
                printf("����δ�ҵ���Ŀ��\n��ȷ�������Ƿ���ȷ��\n");
            }

        ret_prev:
            free(mid);
            system("pause");
            system("cls");
            goto init;

        case 8:
            printf("���沢�˳���...\n");
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
