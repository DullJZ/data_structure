#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE    100

typedef int ElemType;  //����ElemType������


typedef int Status;  //��������������

typedef struct LNode {  //������Ͷ��� 
	
	ElemType data;
	struct LNode* next;
	
}LNode, * LinkList;


Status InitList(LinkList& L) {
	//����һ���յ����Ա�L�� 
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;

}

Status ClearList(LinkList& L) {
	//��յ�������L���������ݽ��ռ��ͷš�ֻʣ��һ��ͷ��㣬�ͳ�ʼ��������Ľ��һ���� 

}

int Listlength(LinkList L) {
	//������ĳ��ȣ�������L�����ݽ�������

}