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
	//初始化单链表L。利用malloc函数申请一个头结点，构造一个空的单链表L，此时L指向头结点。 
	L = (LinkList)malloc(sizeof(LNode));
	if (L) {
		L->next = NULL;
		return OK;
	}
	else {
		return OVERFLOW;
	}
}

Status ClearList(LinkList& L) {
	//清空单链表。将L中所有数据结点空间释放。只剩下一个头结点，和初始化操作后的结果一样。 
	LNode* p;
	p = L->next;
	while (p) {
		LNode* q = p;
		free(p);
		p = (LNode*)malloc(sizeof(LNode));
		p = q->next;
	}
	L->next = NULL;
	return OK;
}

int Listlength(LinkList L) {
	//求单链表的长度，即返回L中数据结点个数。
	LNode* p = L->next;
	int n = 0;
	while (p) {
		n++;
		p = p->next;
	}
	return n;
}

Status GetElem(LinkList L, int i, ElemType& e) {
	//用e返回L中第i个数据结点的值，其中1≤i≤Listlength(L)。 
	LNode* p = L->next;
	int  n = 1;
	while (n<i){
		n++;
		p = p->next;
	}
	e = p->data;
	return OK;
}

LNode* LocateList(LinkList L, ElemType e) {
	//返回L中第1个与e相等的数据结点的地址（指针），若e不存在，则返回NULL。
	LNode* p = L->next;
	while (p->data != e) {
		p = p->next;
		if (!p) {
			return NULL;
		}
	}
	return p;
}

int LocateList2(LinkList L, ElemType e) {
	//返回L中第1个与e相等的数据结点的位置，若e不存在，则返回NULL。
	LNode* p = L->next;
	int i = 1;
	while (p->data != e) {
		p = p->next;
		if (!p) {
			return NULL;
		}
		i++;
	}
	return i;
}

Status ListInsert(LinkList& L, int i, ElemType e) {
	//在L中的第i个数据结点之前插入新的数据结点e，1≤i≤Listlength(L)+1。
	LNode* p = L->next;
	int j = 1;
	while (j < i-1) {
		p = p->next;
		j++;
	}
	LNode* q = (LNode*)malloc(sizeof(LNode));
	if (!q) {
		return OVERFLOW;
	}
	else {
		q->next = p->next;
		p->next = q;
		q->data = e;
		return OK;
	}
}

Status ListDelete(LinkList& L, int i, ElemType& e) {
	//删除L中的第i个数据j结点，用e返回删除结点的值，1≤i≤Listlength(L)。
	LNode* p = L;
	int j = 1;
	while (j < i) {
		p = p->next;
		j++;
	}
	LNode* q = p->next;
	e = q->data; 
	p->next = q->next;
	free(q);
	return OK;
}

Status ListTraverse(LinkList L) {
	//利用printf函数依次输出L的每个数据结点的值。
	LNode* p = L->next;
	//LNode* p = (LNode*)malloc(sizeof(LNode));
	while (p) {
		printf("%d→", p->data);
		if (p->next == NULL) {
			printf("∧\n");
		}
		p = p->next;
	}
	return OK;
}

//线性表元素的集合运算
Status Union(LinkList& La, LinkList Lb) {
	//并运算 La=La U Lb
	LNode* q = Lb->next, *p = La->next;
	ElemType t = 0;
	while (q) {
		t = q->data;
		if (!LocateList(La, t)) {
			ListInsert(La, Listlength(La) + 1, t);
		}
		q = q->next;
	}
	return OK;
}

Status Intersection(LinkList& La, LinkList Lb) {
	//交运算 La=La ∩ Lb
	LNode* pa = La->next;
	while (pa) {
		if (!LocateList(Lb, pa->data)) {
			ElemType t;
			ListDelete(La, LocateList2(La,pa->data), t);
		}
		pa = pa->next;
	}
	return OK;
}

Status Difference(LinkList& La, LinkList Lb) {
	//差运算 La=La - Lb
	LNode* p = La->next;
	LNode* q = Lb->next;
	int i = 1;
	while (p) {
		while (q) {
			if (p->data != q->data) {
				q = q->next;
			}
			else {
				ListDelete(La, i, p->data);
				i = 1;
				break;
			}
			i++;
		}
	}
	return OK;
}


//两个有序表的合并
Status MergeList(LinkList La, LinkList Lb, LinkList& Lc) {
	//设La和Lb中的元素是非递减有序的，编写一个有序表合并，即Lc=La+Lb的函数源码
	LNode* pa = La->next;
	LNode* pb = Lb->next;
	LNode* pc = Lc->next;
	int i = 1;
	while (pa && pb) {
		if (pa->data < pb->data) {
			pc = pa;
			pc = pc->next;
			pa = pa->next;
		}
		else {
			if (pa->data > pb->data) {
				pc = pb;
				pc = pc->next;
				pb = pb->next;
			}
			else {
				pc = pa;
				pc = pc->next;
				pa = pa->next;
				pb = pb->next;
			}
		}
	}
	if (pa) {
		pc = pa;
	}
	if (pb) {
		pc = pb;
	}
	return OK;
}

//去掉线性表中的重复多余的元素
Status Purge(LinkList& Lc) {
	LNode* p = Lc->next;
	LNode* q = p->next;
	while (q) {
		if (p->data == q->data) {
			p->next = q->next;
			free(q);
			q = p->next;
		}
		else {
			p = q;
			q = q->next;
		}
	}
	return OK;
}

//检验函数正确性
int InitTestLaLb(LinkList& La, LinkList& Lb) {
	//LA = 2→8→27→39→66→77→89→∧
	//LB = 6→18→27→59→65→77→89→120→140→∧
	LNode* pa = La;
	LNode* pb = Lb;
	int a[7] = { 2,8,27,39,66,77,89 };
	int b[9] = { 6,18,27,59,65,77,89,120,140 };
	for (int i = 0; i < 7; i++) {
		LNode* r = (LNode*)malloc(sizeof(LNode));
		if (!r) {
			return OVERFLOW;
		}
		r->data = a[i];
		pa->next = r;
		pa = pa->next;
	}
	pa->next = NULL;
	for (int i = 0; i < 9; i++) {
		LNode* r = (LNode*)malloc(sizeof(LNode));
		r->data = b[i];
		pb->next = r;
		pb = pb->next;
	}
	pb->next = NULL;
	return 0;
}

int main() {
	LinkList La = (LinkList)malloc(sizeof(LNode));
	LinkList Lb = (LinkList)malloc(sizeof(LNode));
	if (La == NULL || Lb == NULL) {
		return OVERFLOW;
	}
	La->next = NULL;
	Lb->next = NULL;
	InitTestLaLb(La, Lb);
	LinkList Lc = (LinkList)malloc(sizeof(LNode));
	printf("La = ");
	ListTraverse(La);
	printf("Lb = ");
	ListTraverse(Lb);
	//并集
	printf("La=La U Lb = ");
	Union(La, Lb);
	ListTraverse(La);
	//交集
	InitTestLaLb(La, Lb);
	printf("La=La ∩ Lb = ");
	Intersection(La, Lb);
	ListTraverse(La);
	//差集
	InitTestLaLb(La, Lb);
	printf("La=La - Lb = ");
	Difference(La, Lb);
	ListTraverse(La);
	//合并
	InitTestLaLb(La, Lb);
	printf("有序表合并后 Lc = ");
	MergeList(La, Lb, Lc);
	ListTraverse(Lc);
	//去重
	InitTestLaLb(La, Lb);
	printf("去掉重复多余的元素 Lc = ");
	Purge(Lc);
	ListTraverse(Lc);
	
	return 0;
}