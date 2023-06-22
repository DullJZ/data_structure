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
#define SUCCESS        1        //查找成功     
#define UNSUCCESS   0        //查找不成功
typedef int Status;
typedef int KeyType;             //关键字的数据类型
//“线性探测再散列”哈希表的类型定义
typedef struct {
    KeyType* key;        //哈希表的基址（一维数组，数据元素只用一个关键字）
    int count;               //元素个数
    int size;                   //哈希表的长度
} HashTable;
//“链地址法”中同义词结点的类型定义
typedef struct KeyNode {
    KeyType key;                //数据元素的关键字
    struct KeyNode* next;  //指向下一个同义词结点的指针
}KeyNode, * KeyLink;
//“链地址法”哈希表的类型定义 
typedef struct {
    KeyLink* head;   //哈希表的基址（一维指针数组，每个元素是同义词单链表的头指针）
    int count;            //元素个数
    int size;                //哈希表的长度（哈希函数“除留余数法”的除数）
}HashLink;
//哈希函数
int Hash(KeyType key) {
    return key % 13;  //除留余数法
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
    printf("线性探测再散列哈希表:\n");
    do
    {
        printf("请输入线性探测再散列哈希表的长度\n", MAXSIZE);
        ref = scanf("%d", &HT_Length);
        ch = getchar();
        rewind(stdin);
        if (ref != 1 || ch != '\n')
        {
            printf("数据输入异常!\n");
        }
    } while (ref != 1 || ch != '\n');
    do
    {
        printf("请读入元素个数(范围[0..%d]):\n", MAXSIZE);
        ref = scanf("%d", &n1);
        ch = getchar();
        rewind(stdin);
        if (ref != 1 || ch != '\n' || n1< 0 || n1>MAXSIZE)
        {
            printf("数据输入异常!\n");
        }
    } while (ref != 1 || ch != '\n' || n1< 0 || n1>MAXSIZE);
    for (i = 1; i <= n1; i++)
    {
        do
        {
            printf("请读入第%d个元素:\n", i);
            ref = scanf("%d", &keys1[i]);
            ch = getchar();
            rewind(stdin);
            if (ref != 1 || ch != '\n')
            {
                printf("数据输入异常!\n");
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
        printf("查找关键字=%2d\n", keys1[i]);
        SearchHashTable(HT, keys1[i], j, k);
        cnt += k;
        printf("所在哈希表下标=%2d\n", j);
        printf("关键字比较次数=%2d\n", k);
        printf("\n");
    }
    printf("查找成功ASL=%f\n", (float)cnt / n1);
    for (i = 0; i < n2; i++)
    {
        printf("\n查找关键字=%2d", keys2[i]);
        SearchHashTable(HT, keys2[i], j, k);
        cnt += k;
        printf("所在哈希表下标=%2d\n", j);
        printf("关键字比较次数=%2d\n", k);

    }
    printf("查找不成功ASL=%f\n", (float)cnt / n2);
    printf("\n链地址法哈希表:\n");
    CreateHashLink(HL, 13, keys1, n1);
    OutHashLink(HL);
    cnt = 0;
    for (i = 1; i <= n1; i++)
    {
        printf("查找关键字=%2d", keys1[i]);
        SearchHashLink(HL, keys1[i], p, k);
        cnt += k;
        printf("所在哈希表下标=%2d\n", (keys1[i]) % 13);
        printf("关键字比较次数=%2d\n", k);
    }
    printf("查找成功ASL=%f\n", (float)cnt / n1);
    cnt = 0;
    for (i = 0; i < n2; i++) {
        printf("\n查找关键字=%2d", keys2[i]);
        SearchHashLink(HL, keys2[i], p, k);
        cnt = cnt + k;
        printf("所在哈希表下标=%2d\n", (keys2[i]) % 13);
        printf("关键字比较次数=%2d\n", k);
    }
    printf("查找不成功ASL=%f\n", (float)cnt / n1);
}
