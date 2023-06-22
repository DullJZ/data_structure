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
typedef int Status;            //�������������� 
typedef  char TElemType;  //�������Ԫ��ֵ������

typedef  struct BiTNode {  //����������������� 
    TElemType  data;
    struct BiTNode* lchild, * rchild; //ָ�����Һ��ӽ���ָ��
} BiTNode, * BiTree;

//��������������ַ����У�����һ�ð���������ṹ�洢�Ķ�������
//ָ�����Tָ��������ĸ���㡣
Status CreateBiTree(BiTree& T) {
	TElemType c= getchar();
	if (c == '\n') {
		return OK;
	}
	if (c=='^') {
		T = NULL;
	}
	else {
		T = (BiTree)malloc(sizeof(BiTNode)); //���ɸ����
		if (!T) {
			return OVERFLOW;
		}
		T->data = c;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

//�ݹ��������������T��������ʵĽ���ַ�����;
Status PreOrderTraverse(BiTree T) {

	if (T) {
		printf_s("%c", T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
	return OK;
}

//�ݹ��������������T��������ʵĽ���ַ�����;
Status InOrderTraverse(BiTree T) {
	if (T) {
		InOrderTraverse(T->lchild);
		printf_s("%c", T->data);
		InOrderTraverse(T->rchild);
	}
	return OK;
}

//�ݹ���������������T��������ʵĽ���ַ�����;
Status PostOrderTraverse(BiTree T) {
	if (T) {
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf_s("%c", T->data);
	}
	return OK;
}

//�ǵݹ��������������T��Ҫ���ڱ���������������ʵĽ���ַ���ͬʱ��
//�������ջ/��ջ�Ĺ��̺�ջ��ָ����ָ�Ľ���ַ�;
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

//�ǵݹ��������������T��Ҫ���ڱ���������������ʵĽ���ַ���ͬʱ��
//�������ջ / ��ջ�Ĺ��̺�ջ��ָ����ָ�Ľ���ַ�;
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

//�ǵݹ�������������T��Ҫ���ڱ���������������ʵĽ���ַ���ͬʱ��
//�������ջ/��ջ�Ĺ��̺�ջ��ָ����ָ�Ľ���ַ�;
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
	
//���ض�����T�ȷֱ�Ϊ0,1,2�Ľ����������dΪ����������TNodes(T,0)���ض�Ϊ0����Ҷ�ӽ�㣩�Ľ����;
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

//�������T�ĸ߶�
int High(BiTree T) {
	BiTNode* p = T;
	BiTree r = NULL;
	int max = 0;   //���� 
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

//Ҫ����ݸ������ַ����У��ַ����ظ���������һ�ö��������ڶ������У����������н����ַ�С�ڸ������ַ������������н����ַ����ڸ���㡣��������Ҳ�������������
Status CreateBST(BiTree& T, const char* chars) {
	int i = 0;
	while (chars[i] != '\0') {
		T = RecursionInsert(T, chars[i]);
		i++;
	}
	return OK;
}

int main() {
	//����CreateBiTree(T)��������һ�ö�����T
	BiTree T ;
	CreateBiTree(T);
	//�ֱ���������������������ͺ�������ĵݹ麯�������Ӧ�ı��������
	printf_s("��������Ľ��Ϊ��");
	PreOrderTraverse(T);
	printf_s("\n");
	printf_s("��������Ľ��Ϊ��");
	InOrderTraverse(T);
	printf_s("\n");
	printf_s("��������Ľ��Ϊ��");
	PostOrderTraverse(T);
	printf_s("\n");
	//�ֱ���������������������ͺ�������ķǵݹ麯�������Ӧ�ı������
	printf_s("�ǵݹ���������Ľ��Ϊ��");
	NRPreOrderTraverse(T);
	printf_s("\n");
	printf_s("�ǵݹ���������Ľ��Ϊ��");
	NRInOrderTraverse(T);
	printf_s("\n");
	printf_s("�ǵݹ��������Ľ��Ϊ��");
	PostOrderTraverse(T);
	printf_s("\n");
	printf_s("������T��Ϊ0����%d��\n", TNodes(T, 0));
	printf_s("������T��Ϊ1����%d��\n", TNodes(T, 1));
	printf_s("������T��Ϊ2����%d��\n", TNodes(T, 2));
	BiTree T1 = NULL;
	BiTree T2 = NULL;
	CreateBST(T1, "DBFCAEG");
	CreateBST(T2, "ABCDEFG");
	InOrderTraverse(T1);
	printf_s("\n");
	InOrderTraverse(T2);
	printf_s("\n");
	printf_s("������T1�ĸ߶�Ϊ%d\n", High(T1));
	printf_s("������T2�ĸ߶�Ϊ%d\n", High(T2));
	
	return 0;
}