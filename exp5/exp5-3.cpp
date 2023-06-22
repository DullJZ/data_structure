#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define OK         1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE 20         //�ļ��м�¼���������ֵ
typedef int  KeyType;          //����ؼ�������Ϊ��������
typedef int Status;
typedef struct {
    KeyType  key;
    char name[50];
    char sex;
    int  age;
} RecordType;
typedef struct {
    RecordType  r[MAXSIZE + 1];      //r[0]���û��������ڱ�����Ԫ
    int length;                                  //��¼�ĸ���
}RecordTable;
int ccount, mcount;
Status CreateRecordTable(RecordTable& RT)
{
    int ref, i, j, data, cnt, flag;
    char ch;
    do
    {
        printf("������������¼��RT��Ԫ�ظ���:\n");
        ref = scanf("%d", &RT.length);
        ch = getchar();
        rewind(stdin);
        if (ref != 1 || ch != '\n' || RT.length < 0 || RT.length>MAXSIZE)
        {
            printf("���������쳣������������!\n");
        }
    } while (ref != 1 || ch != '\n' || RT.length < 0 || RT.length>MAXSIZE);
    for (i = 1; i <= RT.length; i++)
    {
        flag = 1;
        do
        {
            flag = 1;
            printf("������%d������(��ʽ:ѧ�� ���� �Ա� ����)��\n", i);
            ref = scanf("%d %s %c %d", &RT.r[i].key, &RT.r[i].name, &RT.r[i].sex, &RT.r[i].age);
            ch = getchar();
            rewind(stdin);
            if (ref != 4 || ch != '\n' || RT.r[i].key < 0 || RT.r[i].age < 0 || (RT.r[i].sex != 'F' && RT.r[i].sex != 'M'))
            {
                printf("���������쳣,����������!\n");
            }
            for (j = 1; j < i; j++)
            {
                if (RT.r[i].key == RT.r[j].key)
                {
                    printf("�ؼ����޷��ظ�����,����������!\n");
                    flag = 0;
                }
            }
        } while (ref != 4 || ch != '\n' || RT.r[i].key < 0 || RT.r[i].age < 0 || (RT.r[i].sex != 'F' && RT.r[i].sex != 'M') || (flag == 0));
    }
    return OK;
}
Status OutRecordTable(RecordTable RT)
{
    int i;
    printf("��� ѧ�� ���� �Ա� ����\n");
    for (i = 1; i <= RT.length; i++)
    {
        printf("%-5d%-3d %-6s %-3c %-4d\n", i, RT.r[i].key, RT.r[i].name, RT.r[i].sex, RT.r[i].age);
    }
    return OK;
}
Status SelectSort(RecordTable& RT)
{
    int i, j, k;
    for (i = 1; i <= RT.length - 1; i++)
    {
        k = i;
        for (j = i + 1; j <= RT.length; j++)
        {
            ccount++;
            if (RT.r[j].key < RT.r[k].key)
            {
                k = j;
            }
        }
        if (k != i)
        {
            RT.r[0] = RT.r[k];
            RT.r[k] = RT.r[i];
            RT.r[i] = RT.r[0];
            mcount++;
        }
    }
    return OK;
}
Status HeapAdjust(RecordTable& H, int i, int m)
{
    int j;
    H.r[0] = H.r[i];
    for (j = 2 * i; j <= m; j = j * 2)
    {
        ccount++;
        if (j < m && H.r[j].key < H.r[j + 1].key)
        {
            j++;
        }
        if (H.r[0].key >= H.r[j].key)
        {
            break;
        }
        H.r[i] = H.r[j];
        i = j;
    }
    if (H.r[i].key != H.r[0].key)
    {
        H.r[i] = H.r[0];
        mcount++;
    }
    return OK;
}
Status HeapSort(RecordTable& H)
{
    int i;
    for (i = H.length / 2; i > 0; i--)
    {
        HeapAdjust(H, i, H.length);
    }
    printf("��ʼ�����Ĵ󶥶�\n");
    OutRecordTable(H);
    printf("\n");
    for (i = H.length; i > 1; i--)
    {
        H.r[0] = H.r[1];
        H.r[1] = H.r[i];
        H.r[i] = H.r[0];
        mcount++;
        printf("�����Ѷ�Ԫ�غ�ļ�¼��\n");
        OutRecordTable(H);
        printf("\n");
        HeapAdjust(H, 1, i - 1);
    }
    return OK;
}
int main()
{
    RecordTable RT;
    CreateRecordTable(RT);
    RecordTable RT1 = RT;
    printf("�������¼��RT��Ԫ��:\n");
    OutRecordTable(RT1);
    ccount = 0;
    mcount = 0;
    printf("ѡ������\n");
    SelectSort(RT1);
    OutRecordTable(RT1);
    printf("�ؼ��ֵıȽϴ���:%d\n", ccount);
    printf("��¼���ƶ�����:%d\n", mcount);
    RT1 = RT;
    ccount = 0;
    mcount = 0;
    printf("������\n");
    HeapSort(RT1);
    OutRecordTable(RT1);
    printf("�ؼ��ֵıȽϴ���:%d\n", ccount);
    printf("��¼���ƶ�����:%d\n", mcount);
}