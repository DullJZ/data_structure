#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE    100
typedef int Status;            //声明函数类型名 
typedef  char TElemType;  //声明结点元素值得类型

typedef  struct BiTNode {  //定义二叉链表结点类型 
    TElemType  data;
    struct BiTNode* lchild, * rchild; //指向左右孩子结点的指针
} BiTNode, * BiTree;

//根据先序遍历的字符序列，创建一棵按二叉链表结构存储的二叉树，
//指针变量T指向二叉树的根结点。
Status CreateBiTree(BiTree& T) {
	TElemType c= getchar();
	if (c == '\n') {
		return OK;
	}
	if (c=='^') {
		T = NULL;
	}
	else {
		T = (BiTree)malloc(sizeof(BiTNode)); //生成根结点
		if (!T) {
			return OVERFLOW;
		}
		T->data = c;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

//递归先序遍历二叉树T，输出访问的结点字符序列;
Status PreOrderTraverse(BiTree T) {

	if (T) {
		printf_s("%c", T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
	return OK;
}

//递归中序遍历二叉树T，输出访问的结点字符序列;
Status InOrderTraverse(BiTree T) {
	if (T) {
		InOrderTraverse(T->lchild);
		printf_s("%c", T->data);
		InOrderTraverse(T->rchild);
	}
	return OK;
}

//递归后序序遍历二叉树T，输出访问的结点字符序列;
Status PostOrderTraverse(BiTree T) {
	if (T) {
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf_s("%c", T->data);
	}
	return OK;
}

//非递归先序遍历二叉树T，要求在遍历过程中输出访问的结点字符的同时，
//输出结点进栈/出栈的过程和栈中指针所指的结点字符;
Status NRPreOrderTraverse(BiTree T) {
	stack<BiTNode>S;
	BiTNode* p = T;
	while (p || !S.empty()) {
		if (p) {
			printf("%c", p->data);
			S.push(*p);
			p = p->lchild;
		}
		else {
			p = &S.top();
			S.pop();
			p = p->rchild;
		}
	}
	return OK;
}

//非递归中序遍历二叉树T，要求在遍历过程中输出访问的结点字符的同时，
//输出结点进栈 / 出栈的过程和栈中指针所指的结点字符;
Status NRInOrderTraverse(BiTree T){
	stack <BiTNode>S;
	BiTNode* p = T;
	while (p || !S.empty()) {
		if (p) {
			S.push(*p);
			p = p->lchild;
		}
		else {
			p = &S.top();
			printf("%c", p->data);
			S.pop();
			p = p->rchild;
		}
	}
	return OK; 
}

//非递归后序遍历二叉树T，要求在遍历过程中输出访问的结点字符的同时，
//输出结点进栈/出栈的过程和栈中指针所指的结点字符;
Status NRPostOrderTraverse(BiTree T) {
	stack<BiTNode*>S;
	BiTNode* p = T;
	BiTNode* pre = NULL;
	while (p != NULL || S.size() != 0) {
		while (p) {
			S.push(p);
			p = p->lchild;
		}
		p = S.top();
		if (p->rchild == NULL) {
			pre = p;
			printf("%c", p->data);
			p = p->rchild;
		}
		else if (p->rchild == pre) {
			pre = p;
			printf("%c", p->data);
			p = NULL;
		}
		else {
			S.push(p);
			p = p->rchild;
		}
	}
	return OK;
}
	
//返回二叉树T度分别为0,1,2的结点数，其中d为结点度数，如TNodes(T,0)返回度为0（即叶子结点）的结点数;
int TNodes(BiTree T, int d) {
	int num = 0;
	if (T) {
		int i = 0;
		if (T->lchild) i++;
		if (T->rchild) i++;
		if (i == d) {
			num = 1 + TNodes(T->lchild, d) + TNodes(T->rchild, d);
		}
		else {
			num = TNodes(T->lchild, d) + TNodes(T->rchild, d);
		}
	}
	return num;
}

//求二叉树T的高度
int High(BiTree T) {
	BiTNode* p = T;
	BiTree r = NULL;
	int max = 0;   //树高 
	stack<BiTree> s;
	while (p || !s.empty()){
		if (p != NULL){
			s.push(p);
			p = p->lchild;
		}
		else {
			p = s.top();
			if (p->rchild != NULL && p->rchild != r)
				p = p->rchild;
			else {
				if (s.size() > max) {
					max = s.size();
				}
				r = p;
				s.pop();
				p = NULL;
			}
		}
	}
	return max;
}

BiTNode* RecursionInsert(BiTNode* node, char data) {
	if (node == NULL) {
		node = (BiTNode*)malloc(sizeof(BiTNode));
		if (!node) {
			return NULL;
		}
		node->data = data;
		node->lchild = NULL;
		node->rchild = NULL;
		return node;
	}

	if (data < node->data){
		node->lchild = RecursionInsert(node->lchild, data);
	}
	else if (data > node->data){
		node->rchild = RecursionInsert(node->rchild, data);
	}

	return node;
}

//要求根据给定的字符序列（字符不重复），生成一棵二叉树。在二叉树中，左子树所有结点的字符小于根结点的字符，右子树所有结点的字符大于根结点。左右子树也满足这个条件。
Status CreateBST(BiTree& T, const char* chars) {
	int i = 0;
	while (chars[i] != '\0') {
		T = RecursionInsert(T, chars[i]);
		i++;
	}
	return OK;
}

int main() {
	//调用CreateBiTree(T)函数生成一棵二叉树T
	BiTree T ;
	CreateBiTree(T);
	//分别调用先序遍历、中序遍历和后序遍历的递归函数输出相应的遍历结果；
	printf_s("先序遍历的结果为：");
	PreOrderTraverse(T);
	printf_s("\n");
	printf_s("中序遍历的结果为：");
	InOrderTraverse(T);
	printf_s("\n");
	printf_s("后序遍历的结果为：");
	PostOrderTraverse(T);
	printf_s("\n");
	//分别调用先序遍历、中序遍历和后序遍历的非递归函数输出相应的遍历结果
	printf_s("非递归先序遍历的结果为：");
	NRPreOrderTraverse(T);
	printf_s("\n");
	printf_s("非递归中序遍历的结果为：");
	NRInOrderTraverse(T);
	printf_s("\n");
	printf_s("非递归后序遍历的结果为：");
	PostOrderTraverse(T);
	printf_s("\n");
	printf_s("二叉树T度为0的有%d个\n", TNodes(T, 0));
	printf_s("二叉树T度为1的有%d个\n", TNodes(T, 1));
	printf_s("二叉树T度为2的有%d个\n", TNodes(T, 2));
	BiTree T1 = NULL;
	BiTree T2 = NULL;
	CreateBST(T1, "DBFCAEG");
	CreateBST(T2, "ABCDEFG");
	InOrderTraverse(T1);
	printf_s("\n");
	InOrderTraverse(T2);
	printf_s("\n");
	printf_s("二叉树T1的高度为%d\n", High(T1));
	printf_s("二叉树T2的高度为%d\n", High(T2));
	
	return 0;
}