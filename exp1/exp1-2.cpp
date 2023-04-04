#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE    100

typedef int ElemType;  //声明ElemType的类型


typedef int Status;  //声明函数类型名

typedef struct LNode {  //结点类型定义 
	
	ElemType data;
	struct LNode* next;
	
}LNode, * LinkList;


Status InitList(LinkList& L) {
	//构造一个空的线性表L。 
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;

}

Status ClearList(LinkList& L) {
	//清空单链表。将L中所有数据结点空间释放。只剩下一个头结点，和初始化操作后的结果一样。 

}

int Listlength(LinkList L) {
	//求单链表的长度，即返回L中数据结点个数。

}