//
// Created by Steve_Hsu on 2023/3/21.
// 简易交互界面
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "list_func.h"

void stdprn(unit *ptr) {  // 单条目所有信息打印
    printf("品名：%s\t分类：%d-%d-%d\tOTC：%s\n生产日期：%ld\t库存量：%ld\t总销量：%ld\n",
           ptr->col.name, ptr->col.type.main_type, ptr->col.type.mid_type, ptr->col.type.subtype,
           (ptr->col.type.isotc == 1 ? "是" : "否"), ptr->col.man_date, ptr->col.stock, ptr->col.sale_vol);
}

unit *menu(unit *head) {  // 菜单及功能实现，参数为链表首地址
    int arg;  // 获取操作序号、存储参数等
    char name[256]; // 获取待操作条目名称用

    unit *result, *mid;  // 临时存储待传入数据 - result为查询结果的地址，mid为从输入流中转的数据

    init:      // 此标签用于返回主菜单
    strnset(name, '\0', 256);  // 用终止符号覆盖所有字节进行初始化
    mid = NULL;  // 清除带有的地址信息
    mid = (unit *) malloc(sizeof(unit));  // 分配新地址
    mid->next = NULL;  // 清除“下一节点”信息
    result = NULL;  //清除之前查询结果的地址信息
    arg = 0;  // 清空参数信息
    printf("当前日期：");
    timePrn();  // 输出日期

    if ((!strcmp(head->col.name, "NULL")) && head->next == NULL) {  // 无条目时强制限制功能
        printf("********** 药房销售系统 Ver.1.0 **********\n\n警告：无条目记录。选择操作：\n\n");
        printf("1.新增药品条目\n2.生成销售报表\n3.取消保存并退出\n");
        printf("\n输入相应序号并按下回车键：");
        scanf("%d", &arg);
        switch (arg) {
            case 1:
                printf("请输入药品名：");
                scanf("%s", mid->col.name);
                printf("请输入三段分类编号（1-5，1-25，1-8），用空格分隔各段：");
                scanf("%d %d %d", &mid->col.type.main_type, &mid->col.type.mid_type, &mid->col.type.subtype);
                if (chkType(mid->col.type.main_type, mid->col.type.mid_type, mid->col.type.subtype)) goto inerr;
                printf("该药品是否为OTC药品？是请输入1，否则输入0：");
                scanf("%d", &mid->col.type.isotc);
                if (mid->col.type.isotc != 1 && mid->col.type.isotc != 0) goto inerr;
                printf("请输入药品生产日期（以八位数字表示）：");
                scanf("%ld", &mid->col.man_date);
                if (!chkDate((mid->col.man_date))) goto inerr;
                chkSingDate(mid);  // 检查是否过期并记录
                printf("请输入药品库存量：");
                scanf("%ld", &mid->col.stock);
                if (mid->col.stock < 0) {
                    inerr:  // 数据不符合规范或有明显错误时跳转
                    printf("\n错误：请检查数据输入。\n将返回主菜单。\n");
                    goto ret_prev;  // 准备加载主菜单
                }
                mid->col.sale_vol = 0;  // 销售额初值为0
                if ((arg = saleStats(mid, 0, 0)) != 0) {  // 判断销售记录写入是否成功
                    printf("\n错误：无法将改动写入销售记录文件。\n");
                }
                replace(head, mid);  // 向链表写入数据
                printf("\n添加成功！\n\n");
                free(mid);  // 释放中间结构体的内存
                system("pause");  // 返回主菜单前等待输入
                system("cls");  // 清屏
                break;
            case 2:
                arg = 6;
                goto submenu;  // 直接跳转对应功能
            case 3:
                arg = 8;
                goto submenu;
            default:
                printf("错误：无效的序号。\n\n");  // 误输入防范
                goto init;
        }

    }
    printf("********** 药房销售系统 Ver.1.0 **********\n\n欢迎！请选择以下操作中的一个：\n\n");
    printf("1.新增药品条目\n2.查询药品条目\n3.修改药品条目\n4.删除药品条目\n5.显示临期药品\n6.生成销售报表\n7.销售药品\n8.保存并退出\n9.取消保存并退出\n");
    if ((arg = showQaCond(head, 0)) == -1)  // 检查是否存在临期药品
        printf("\n[注意] 发现有库存药物即将或已经过期。\n[注意] 选择序号5以查看详情。\n");
    printf("\n输入相应序号并按下回车键：");
    scanf("%d", &arg); // 获取操作序号

    //子菜单
    submenu:
    switch (arg) {
        case 1:
            arg = 0;
            system("cls");
            printf("当前日期：");
            timePrn();
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：1.新增药品条目\n\n");
            printf("请输入药品名：");
            scanf("%s", mid->col.name);
            printf("请输入三段分类编号（1-5，1-25，1-8），用空格分隔各段：");
            scanf("%d %d %d", &mid->col.type.main_type, &mid->col.type.mid_type, &mid->col.type.subtype);
            if (chkType(mid->col.type.main_type, mid->col.type.mid_type, mid->col.type.subtype)) goto inerr;
            printf("该药品是否为OTC药品？是请输入1，否则输入0：");
            scanf("%d", &mid->col.type.isotc);
            if (mid->col.type.isotc != 1 && mid->col.type.isotc != 0) goto inerr;
            printf("请输入药品生产日期（以八位数字表示）：");
            scanf("%ld", &mid->col.man_date);
            if (!chkDate(mid->col.man_date)) goto inerr;
            chkSingDate(mid);
            printf("请输入药品库存量：");
            scanf("%ld", &mid->col.stock);
            if (mid->col.stock < 0) goto inerr;
            mid->col.sale_vol = 0;
            if ((arg = saleStats(mid, 0, 0)) != 0) {
                printf("\n错误：无法将改动写入销售记录文件。\n");
            }
            system("cls");
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：1.新增药品条目\n\n");
            result = add(mid, head);  // 尝试添加节点
            if (result != NULL) {  // 失败，同名条目存在
                printf("错误：该条目已存在。详细信息为：\n");
                stdprn(result);
            } else {  // 成功
                printf("\n添加成功！\n\n");
            }
            free(mid);
            system("pause");  // 返回主菜单前等待输入
            system("cls");  // 清屏
            goto init;  // 返回主菜单

        case 2:
            arg = 0;
            system("cls");
            printf("当前日期：");
            timePrn();
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：2.查询药品条目\n\n");
            printf("请输入需要搜索的药品名：");
            getchar(); // 此处读取输入的回车，避免gets误读取后直接跳转下一步
            gets(name);
            system("cls");
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：2.查询药品条目\n\n");
            if ((result = findByName(name, head)) != NULL) {  // 尝试查找
                printf("已找到条目。\n");
                chkSingDate(result);
                stdprn(result);
            } else {  // 查找失败
                printf("错误：未找到条目。\n请确认输入是否正确。\n");
            }
            system("pause");
            system("cls");
            goto init;

        case 3:
            arg = 0;
            system("cls");
            printf("当前日期：");
            timePrn();
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：3.修改药品条目\n\n");
            printf("请输入要修改条目的药品名：");
            scanf("%s", name);
            system("cls");
            printf("当前日期：");
            timePrn();
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：3.修改药品条目\n\n");
            if ((result = findByName(name, head)) != NULL) {  // 查找到待修改条目，进行修改
                chkSingDate(result);  // 检查是否临期
                printf("\n当前条目信息：\n");
                stdprn(result);
                printf("请输入新药品信息：\n\n");
                printf("药品名称：");
                scanf("%s", mid->col.name);
                if ((arg = strcmp(mid->col.name, result->col.name)) != 0) {  // 新名称与旧名称不同
                    result->col.stock = 0;  // 清空旧库存
                    if ((arg = saleStats(mid, 0, 0)) != 0) {  // 记录库存变化
                        printf("\n错误：无法将改动写入销售记录文件。\n");
                    }
                }
                printf("请输入三段分类编号（1-5，1-25，1-8），用空格分隔各段：");
                scanf("%d %d %d", &mid->col.type.main_type, &mid->col.type.mid_type, &mid->col.type.subtype);
                if (chkType(mid->col.type.main_type, mid->col.type.mid_type, mid->col.type.subtype)) goto inerr;
                printf("该药品是否为OTC药品？是请输入1，否则输入0：");
                scanf("%d", &mid->col.type.isotc);
                if (mid->col.type.isotc != 1 && mid->col.type.isotc != 0) goto inerr;
                printf("请输入药品生产日期（以八位数字表示）：");
                scanf("%ld", &mid->col.man_date);
                if (!chkDate(mid->col.man_date)) goto inerr;
                chkSingDate(mid);
                printf("请输入药品库存量：");
                scanf("%ld", &mid->col.stock);
                if (mid->col.stock < 0) goto inerr;
                replace(result, mid);  // 向链表写入信息
                if ((arg = saleStats(result, 0, 0)) != 0) {  // 写入库存信息
                    printf("\n错误：无法将改动写入销售记录文件。\n");
                }
            } else printf("错误：未找到条目。\n");   // 未查找到待修改条目
            free(mid);
            system("pause");
            system("cls");
            goto init;

        case 4:
            arg = 0;
            system("cls");
            printf("当前日期：");
            timePrn();
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：4.删除药品条目\n\n");
            printf("请输入需要删除的条目（药品名）：");
            scanf("%s", name);
            system("cls");
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：4.删除药品条目\n\n");
            if ((result = findByName(name, head)) != NULL) {  // 查找待删除条目
                chkSingDate(result);
                printf("\n当前条目信息：\n");
                stdprn(result);
                choose:
                printf("\n是否删除？（是：1  否：0）[ ]\b\b");
                scanf("%d", &arg);
                switch (arg) {
                    case 0:
                        printf("\n取消。\n");
                        goto ret_prev;
                    case 1:
                        printf("删除中...");
                        goto delete;
                    default:
                        printf("错误：无效的序号。\n\n");  // 误输入防范
                        goto choose;
                }
                delete:
                result->col.stock = 0;
                if ((arg = saleStats(result, 0, 0)) != 0) { // 记录库存变动
                    printf("\n错误：无法将改动写入销售记录文件。\n");
                }
                free(mid);
                if ((mid = del(name, head)) != NULL) {  // 尝试删除条目
                    head = mid; // 记录链表新头地址
                    printf("删除操作成功完成。\n");
                }
            } else {  // 删除失败
                printf("错误：未找到条目。\n");
            }
            system("pause");
            system("cls");
            goto init;

        case 5:
            system("cls");
            printf("当前日期：");
            timePrn();
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：5.显示临/过期药品\n");
            printf("\n以下是预估临期（保质期小于60天）或过期的药品列表：\n");
            printf("（若空则无临/过期药品）\n");
            showQaCond(head, 1);  // 查找并输出所有临期/过期条目
            system("pause");
            system("cls");
            goto init;
        case 6:
            arg = 0;
            system("cls");
            printf("当前日期：");
            timePrn();
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：6.生成销售报表\n");


            printf("\n选择一项进行生成:\n1.生成单品类销售记录\n2.生成库存统计\n\n");
            printf("\n输入相应序号并按下回车键：");
            scanf("%d", &arg);

            system("cls");
            printf("当前日期：");
            timePrn();
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：6.生成销售报表\n");

            switch (arg) {
                case 1:
                    printf("\n请输入需要生成表格的药品名：");
                    scanf("%s", name);
                    if ((arg = csvSingGen(name)) == 0) {  // 生成报表
                        printf("\n完成。报表现存储至程序同名目录下，文件名为：stats_%s.csv\n", name);
                    } else printf("\n错误：无此条目。\n");
                    break;
                case 2:
                    if ((arg = csvAllGen(head)) == 0) {  // 生成表格，判断生成是否成功
                        printf("\n完成。报表现存储至程序同名目录下，文件名为：stock.csv\n");
                    } else printf("\n错误：请检查程序权限和磁盘剩余空间。\n");
                    break;
                default:
                    printf("\n序号输入错误，返回主菜单。\n");
                    break;
            }

            system("pause");
            system("cls");
            goto init;
        case 7:
            arg = 0;
            system("cls");
            printf("当前日期：");
            timePrn();
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：7.销售药品\n\n");
            printf("请输入需要销售的药品名：");
            scanf("%s", name);
            system("cls");
            printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：7.销售药品\n\n");
            if ((result = findByName(name, head)) != NULL) {  // 尝试查找
                printf("已找到条目。\n");
                numin:  // 输入销售量标记
                chkSingDate(result);  // 刷新质量情况
                stdprn(result);
                switch (result->col.qa) {  // 判断药品是否临期或过期以便进行提示
                    case -1:
                        printf("\n[警告] 该药品过期。禁止售卖。\n");
                        goto ret_prev;  // 准备返回上级菜单
                    case 0:
                        printf("\n[注意] 该药品临期。\n");
                        break;
                    default:
                        break;
                }
                if (result->col.stock == 0) {
                    printf("\n[警告] 该药品无库存。返回主菜单。\n");
                    goto ret_prev;
                }
                int num; // 数量
                double unit_price;  // 单价
                printf("\n请输入药品数量：");
                scanf("%d", &num);
                if (num > result->col.stock || num <= 0) {  // 检查库存数量是否充足
                    system("cls");
                    printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：7.销售药品\n\n");
                    printf("错误：库存数量不足或数量输入错误。请选择操作：\n1.重新输入数量\n2.返回主菜单\n选择一项：");
                    scanf("%d", &arg);
                    if (arg == 1) {
                        system("cls");
                        printf("********** 药房销售系统 Ver.1.0 **********\n\n当前选项：7.销售药品\n");
                        goto numin;
                    } else if (arg == 2) goto ret_prev;
                    else {  // 防止序号误输入
                        printf("\n序号输入错误。返回主菜单。\n");
                        goto ret_prev;
                    }
                } else {
                    printf("\n请输入单价（元）：");
                    scanf("%lf", &unit_price);
                    printf("\n总价：%.2lf 元，支付是否成功？(是：1，否：0) [ ]\b\b", 1.0 * num * unit_price);  // 计算价格
                    scanf("%d", &arg);
                    if (arg == 1) {  //收费成功则扣除库存量增加销售量
                        if ((arg = saleStats(result, num, unit_price)) == 0) { // 记录销售情况
                            printf("\n库存状态更新。\n");
                        } else printf("\n错误：无法将改动写入文件。\n");
                    } else printf("\n库存状态无更新。\n");
                    goto ret_prev;
                }
            } else {  // 查找失败
                printf("错误：未找到条目。\n请确认输入是否正确。\n");
            }

        ret_prev:
            free(mid);
            system("pause");
            system("cls");
            goto init;

        case 8:
            printf("保存并退出中...\n");
            dataSave(head);     // 保存数据并对上次数据进行备份
            break;

        case 9:
            printf("改动未保存。退出中...\n");
            break;

        default:  // 防止误输入序号
            system("cls");
            printf("\n\n错误：异常的序号。\n\n将返回主界面。\n\n");
            system("pause");
            system("cls");
            goto init;
    }
    free(mid);
    return head;
}
