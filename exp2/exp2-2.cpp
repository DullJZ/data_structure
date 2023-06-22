#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;
typedef int Status;              //声明函数类型名
typedef  char TElemType;    //声明结点元素值得类型

#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE    100

typedef struct BiThrNode {  //定义线索二叉链表的结点结构和类型
    TElemType data;
    struct BiThrNode* lchild, * rchild;
    int  LTag, RTag;
}BiThrNode, * BiThrTree;

BiThrNode* pre = NULL;

//线索二叉树基本操作与应用函数的实现 
Status InitBiThrTree(BiThrTree& T) {
	//根据先序遍历的字符序列，创建一棵按线索二叉链表结构存储的尚未线索化的二叉树，
    //在该二叉链表中，若结点有左孩子（即lchild非空），则其LTag=0，否则LTag=1，
    //若二叉树的结点有右孩子（即rchild非空），则其RTag=0，否则RTag=1。指针变量T指向二叉树的根结点。
	TElemType c = getchar();
	if (c == '\n') {
		return OK;
	}
	if (c == '^') {
		T = NULL;
	}
	else {
		T = (BiThrTree)malloc(sizeof(BiThrNode)); //生成根结点
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
	//对InitBiThrTree(BiThrTree &T)函数创建的二叉树T按中序遍历进行线索化，
	//线索化后的中序线索二叉树带“头结点”，头结点的data域存放字符'@'，
	//指针Thrt指向该头结点，头结点的左指针指向二叉树的根结点（LTag=0），
	//右指针指向该二叉树中序遍历的最后一个结点（RTag=1）。
	//同时，该二叉树中序遍历第一个结点的左指针指向头结点（LTag=1），
	//中序遍历最后一个结点的右指针也指向头结点（RTag=1）。
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
	//按孩子中序遍历线索二叉树（递归），输出每个结点的数据
	if (T) {
		if (T->LTag == 0) InOrderTraverse(T->lchild);
		if (T->data == '@') return 0;
		// 输出，防止未线索化前报NULL错误
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
	//按孩子中序遍历线索二叉树（递归），输出每个结点的数据
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