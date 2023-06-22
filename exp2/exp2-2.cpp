#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;
typedef int Status;              //��������������
typedef  char TElemType;    //�������Ԫ��ֵ������

#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE    100

typedef struct BiThrNode {  //����������������Ľ��ṹ������
    TElemType data;
    struct BiThrNode* lchild, * rchild;
    int  LTag, RTag;
}BiThrNode, * BiThrTree;

BiThrNode* pre = NULL;

//��������������������Ӧ�ú�����ʵ�� 
Status InitBiThrTree(BiThrTree& T) {
	//��������������ַ����У�����һ�ð�������������ṹ�洢����δ�������Ķ�������
    //�ڸö��������У�����������ӣ���lchild�ǿգ�������LTag=0������LTag=1��
    //���������Ľ�����Һ��ӣ���rchild�ǿգ�������RTag=0������RTag=1��ָ�����Tָ��������ĸ���㡣
	TElemType c = getchar();
	if (c == '\n') {
		return OK;
	}
	if (c == '^') {
		T = NULL;
	}
	else {
		T = (BiThrTree)malloc(sizeof(BiThrNode)); //���ɸ����
		if (!T) {
			return OVERFLOW;
		}
		T->data = c;
		InitBiThrTree(T->lchild);
		if (T->lchild == NULL) {
			T->LTag = 1;
		}
		else {
			T->LTag = 0;
		}
		InitBiThrTree(T->rchild);
		if (T->rchild == NULL) {
			T->RTag = 1;
		}
		else {
			T->RTag = 0;
		}
	}
	return OK;
}


Status InThreading(BiThrTree p) {
	if (p) {
		InThreading(p->lchild);
		if (!p->lchild) {
			p->LTag = 1;
			p->lchild = pre;
		}
		else {
			p->LTag = 0;
		}
		if (!pre->rchild) {
			pre->RTag = 1;
			pre->rchild = p;
		}
		else {
			pre->RTag = 0;
		}
		pre = p;
		InThreading(p->rchild);
	}
	return OK;
}

Status InOrderThreading(BiThrTree& Thrt, BiThrTree T) {
	//��InitBiThrTree(BiThrTree &T)���������Ķ�����T���������������������
	//���������������������������ͷ��㡱��ͷ����data�����ַ�'@'��
	//ָ��Thrtָ���ͷ��㣬ͷ������ָ��ָ��������ĸ���㣨LTag=0����
	//��ָ��ָ��ö�����������������һ����㣨RTag=1����
	//ͬʱ���ö��������������һ��������ָ��ָ��ͷ��㣨LTag=1����
	//����������һ��������ָ��Ҳָ��ͷ��㣨RTag=1����
	Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if (!Thrt) {
		return OVERFLOW;
	}
	Thrt->LTag = 0;
	Thrt->RTag = 1;
	Thrt->rchild = Thrt;
	Thrt->data = '@';
	if (!T) {
		Thrt->lchild = Thrt;
	}
	else {
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);
		pre->rchild = Thrt;
		pre->RTag = 1;
		Thrt->rchild = pre;
	}
	return OK;
}

Status InOrderTraverse(BiThrTree T) {
	//��������������������������ݹ飩�����ÿ����������
	if (T) {
		if (T->LTag == 0) InOrderTraverse(T->lchild);
		if (T->data == '@') return 0;
		// �������ֹδ������ǰ��NULL����
		if (T->lchild == NULL && T->rchild == NULL) {
			printf("|%d|^|%c|^|%d|\n", T->LTag, T->data, T->RTag);
		}
		else {
			if (T->lchild == NULL) {
				printf("|%d|^|%c|%c|%d|\n", T->LTag, T->data, T->rchild->data, T->RTag);
			}
			if (T->rchild == NULL) {
				printf("|%d|%c|%c|^|%d|\n", T->LTag, T->lchild->data, T->data, T->RTag);
			}
		}
		if (T->lchild && T->rchild) {
			printf("|%d|%c|%c|%c|%d|\n", T->LTag, T->lchild->data, T->data, T->rchild->data, T->RTag);
		}
		
		if (T->RTag == 0) InOrderTraverse(T->rchild);
	}
	return OK;
}

Status InOrderTraverse1(BiThrTree T) {
	//��������������������������ݹ飩�����ÿ����������
	if (T) {
		InOrderTraverse1(T->lchild);
		printf("|%d|%c|%c|%c|%d|\n", T->LTag, T->lchild->data, T->data, T->rchild->data, T->RTag);
		InOrderTraverse1(T->rchild);
	}
	return OK;
}

Status InOrderTraverse_Thr(BiThrTree T) {
	BiThrNode* p = T->lchild;
	while (p != T) {
		while (p->LTag == 0) {
			p = p->lchild;
		}
		printf("|%d|%c|%c|%c|%d|\n", p->LTag, p->lchild->data, p->data, p->rchild->data, p->RTag);
		while (p->RTag == 1 && p->rchild != T) {
			p = p->rchild;
			printf("|%d|%c|%c|%c|%d|\n", p->LTag, p->lchild->data, p->data, p->rchild->data, p->RTag);
		}
		p = p->rchild;
	}
	return OK;
}

int main() {
	BiThrTree T = NULL;
	InitBiThrTree(T);
	InOrderTraverse(T);
	printf("\n");
	BiThrTree Thrt = NULL;
	InOrderThreading(Thrt, T);
	InOrderTraverse(Thrt);
	printf("\n");
	InOrderTraverse_Thr(Thrt);
}