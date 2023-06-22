#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define OK         1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE  20
#define SUCCESS        1        //���ҳɹ�     
#define UNSUCCESS   0        //���Ҳ��ɹ�
typedef int Status;
typedef int KeyType;             //�ؼ��ֵ���������
//������̽����ɢ�С���ϣ������Ͷ���
typedef struct {
    KeyType* key;        //��ϣ��Ļ�ַ��һά���飬����Ԫ��ֻ��һ���ؼ��֣�
    int count;               //Ԫ�ظ���
    int size;                   //��ϣ��ĳ���
} HashTable;
//������ַ������ͬ��ʽ������Ͷ���
typedef struct KeyNode {
    KeyType key;                //����Ԫ�صĹؼ���
    struct KeyNode* next;  //ָ����һ��ͬ��ʽ���ָ��
}KeyNode, * KeyLink;
//������ַ������ϣ������Ͷ��� 
typedef struct {
    KeyLink* head;   //��ϣ��Ļ�ַ��һάָ�����飬ÿ��Ԫ����ͬ��ʵ������ͷָ�룩
    int count;            //Ԫ�ظ���
    int size;                //��ϣ��ĳ��ȣ���ϣ�������������������ĳ�����
}HashLink;
//��ϣ����
int Hash(KeyType key) {
    return key % 13;  //����������
}
Status CreateHashTable(HashTable& HT, int HT_Length, KeyType key[], int KeyNum)
{
    int i, j;
    HT.key = (KeyType*)malloc(HT_Length * sizeof(KeyType));
    HT.count = KeyNum;
    HT.size = HT_Length;
    for (i = 0; i < HT.size; i++)
    {
        HT.key[i] = -1;
    }
    for (i = 1; i <= HT.count; i++)
    {
        int k = Hash(key[i]);
        if (HT.key[k] == -1)
        {
            HT.key[k] = key[i];
        }
        else
        {
            j = (k + 1) % HT_Length;
            while (j != k && HT.key[j] != -1)
            {
                j = (j + 1) % HT_Length;
            }
            if (HT.key[j] == -1)
            {
                HT.key[j] = key[i];
            }
            else
            {
                return ERROR;
            }
        }
    }
    return OK;
}
Status SearchHashTable(HashTable HT, KeyType key, int& p, int& c)
{
    p = Hash(key);
    c = 0;
    while (HT.key[p] != -1 && ((p + 1) % HT.size) != Hash(key) && HT.key[p] != key)
    {
        c++;
        p = (p + 1) % HT.size;
    }
    if (HT.key[p] == key)
    {
        c++;
        return SUCCESS;
    }
    else
    {
        if (HT.key[p] == -1)
        {
            c++;
        }
        p = -1;
        return UNSUCCESS;
    }
}
Status CreateHashLink(HashLink& HL, int HL_Length, KeyType key[], int KeyNum)
{
    int i, k;
    KeyLink s;
    HL.head = (KeyLink*)malloc(HL_Length * sizeof(KeyLink));
    HL.count = KeyNum;
    HL.size = HL_Length;
    for (i = 0; i < HL.size; i++)
    {
        HL.head[i] = NULL;
    }
    for (i = 1; i <= HL.count; i++)
    {
        s = (KeyLink)malloc(sizeof(KeyNode));
        s->key = key[i];
        k = Hash(key[i]);
        s->next = HL.head[k];
        HL.head[k] = s;
    }
    return OK;
}
Status OutHashLink(HashLink HL)
{
    int i;
    KeyLink p;
    for (i = 0; i < HL.size; i++)
    {
        if (HL.head[i] != NULL)
        {
            printf("%d %d", i, HL.head[i]->key);
            p = HL.head[i]->next;
            while (p != NULL)
            {
                printf("->%d", p->key);
                p = p->next;
            }
            printf("\n");
        }
    }
    return OK;
}
Status  SearchHashLink(HashLink HL, KeyType key, KeyLink& p, int& c)
{
    p = HL.head[Hash(key)];
    c = 0;
    while (p && p->key != key)
    {
        c++;
        p = p->next;
    }
    c++;
    if (p)
    {
        return SUCCESS;
    }
    else
    {
        return UNSUCCESS;
    }
}
void main()
{
    char ch;
    int ref, data;
    int i, j, k, cnt = 0;
    int n1, n2 = 13;
    int HT_Length;
    int keys1[MAXSIZE] = { 0 };
    int keys2[13] = { 26,40,15,29,30,18,32,46,60,74,36,24,38 };
    HashTable HT;
    HashLink HL;
    KeyLink p;
    printf("����̽����ɢ�й�ϣ��:\n");
    do
    {
        printf("����������̽����ɢ�й�ϣ��ĳ���\n", MAXSIZE);
        ref = scanf("%d", &HT_Length);
        ch = getchar();
        rewind(stdin);
        if (ref != 1 || ch != '\n')
        {
            printf("���������쳣!\n");
        }
    } while (ref != 1 || ch != '\n');
    do
    {
        printf("�����Ԫ�ظ���(��Χ[0..%d]):\n", MAXSIZE);
        ref = scanf("%d", &n1);
        ch = getchar();
        rewind(stdin);
        if (ref != 1 || ch != '\n' || n1< 0 || n1>MAXSIZE)
        {
            printf("���������쳣!\n");
        }
    } while (ref != 1 || ch != '\n' || n1< 0 || n1>MAXSIZE);
    for (i = 1; i <= n1; i++)
    {
        do
        {
            printf("������%d��Ԫ��:\n", i);
            ref = scanf("%d", &keys1[i]);
            ch = getchar();
            rewind(stdin);
            if (ref != 1 || ch != '\n')
            {
                printf("���������쳣!\n");
            }
        } while (ref != 1 || ch != '\n');
    }
    CreateHashTable(HT, HT_Length, keys1, n1);

    for (i = 0; i < HT_Length; i++)
    {
        printf("%d %d\n", i, HT.key[i]);
    }
    for (i = 1; i <= n1; i++)
    {
        printf("���ҹؼ���=%2d\n", keys1[i]);
        SearchHashTable(HT, keys1[i], j, k);
        cnt += k;
        printf("���ڹ�ϣ���±�=%2d\n", j);
        printf("�ؼ��ֱȽϴ���=%2d\n", k);
        printf("\n");
    }
    printf("���ҳɹ�ASL=%f\n", (float)cnt / n1);
    for (i = 0; i < n2; i++)
    {
        printf("\n���ҹؼ���=%2d", keys2[i]);
        SearchHashTable(HT, keys2[i], j, k);
        cnt += k;
        printf("���ڹ�ϣ���±�=%2d\n", j);
        printf("�ؼ��ֱȽϴ���=%2d\n", k);

    }
    printf("���Ҳ��ɹ�ASL=%f\n", (float)cnt / n2);
    printf("\n����ַ����ϣ��:\n");
    CreateHashLink(HL, 13, keys1, n1);
    OutHashLink(HL);
    cnt = 0;
    for (i = 1; i <= n1; i++)
    {
        printf("���ҹؼ���=%2d", keys1[i]);
        SearchHashLink(HL, keys1[i], p, k);
        cnt += k;
        printf("���ڹ�ϣ���±�=%2d\n", (keys1[i]) % 13);
        printf("�ؼ��ֱȽϴ���=%2d\n", k);
    }
    printf("���ҳɹ�ASL=%f\n", (float)cnt / n1);
    cnt = 0;
    for (i = 0; i < n2; i++) {
        printf("\n���ҹؼ���=%2d", keys2[i]);
        SearchHashLink(HL, keys2[i], p, k);
        cnt = cnt + k;
        printf("���ڹ�ϣ���±�=%2d\n", (keys2[i]) % 13);
        printf("�ؼ��ֱȽϴ���=%2d\n", k);
    }
    printf("���Ҳ��ɹ�ASL=%f\n", (float)cnt / n1);
}
