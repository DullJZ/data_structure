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
	//��ʼ��������L������malloc��������һ��ͷ��㣬����һ���յĵ�����L����ʱLָ��ͷ��㡣 
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
	//��յ�������L���������ݽ��ռ��ͷš�ֻʣ��һ��ͷ��㣬�ͳ�ʼ��������Ľ��һ���� 
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
	//������ĳ��ȣ�������L�����ݽ�������
	LNode* p = L->next;
	int n = 0;
	while (p) {
		n++;
		p = p->next;
	}
	return n;
}

Status GetElem(LinkList L, int i, ElemType& e) {
	//��e����L�е�i�����ݽ���ֵ������1��i��Listlength(L)�� 
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
	//����L�е�1����e��ȵ����ݽ��ĵ�ַ��ָ�룩����e�����ڣ��򷵻�NULL��
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
	//����L�е�1����e��ȵ����ݽ���λ�ã���e�����ڣ��򷵻�NULL��
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
	//��L�еĵ�i�����ݽ��֮ǰ�����µ����ݽ��e��1��i��Listlength(L)+1��
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
	//ɾ��L�еĵ�i������j��㣬��e����ɾ������ֵ��1��i��Listlength(L)��
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
	//����printf�����������L��ÿ�����ݽ���ֵ��
	LNode* p = L->next;
	//LNode* p = (LNode*)malloc(sizeof(LNode));
	while (p) {
		printf("%d��", p->data);
		if (p->next == NULL) {
			printf("��\n");
		}
		p = p->next;
	}
	return OK;
}

//���Ա�Ԫ�صļ�������
Status Union(LinkList& La, LinkList Lb) {
	//������ La=La U Lb
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
	//������ La=La �� Lb
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
	//������ La=La - Lb
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


//���������ĺϲ�
Status MergeList(LinkList La, LinkList Lb, LinkList& Lc) {
	//��La��Lb�е�Ԫ���Ƿǵݼ�����ģ���дһ�������ϲ�����Lc=La+Lb�ĺ���Դ��
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

//ȥ�����Ա��е��ظ������Ԫ��
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

//���麯����ȷ��
int InitTestLaLb(LinkList& La, LinkList& Lb) {
	//LA = 2��8��27��39��66��77��89����
	//LB = 6��18��27��59��65��77��89��120��140����
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
	//����
	printf("La=La U Lb = ");
	Union(La, Lb);
	ListTraverse(La);
	//����
	InitTestLaLb(La, Lb);
	printf("La=La �� Lb = ");
	Intersection(La, Lb);
	ListTraverse(La);
	//�
	InitTestLaLb(La, Lb);
	printf("La=La - Lb = ");
	Difference(La, Lb);
	ListTraverse(La);
	//�ϲ�
	InitTestLaLb(La, Lb);
	printf("�����ϲ��� Lc = ");
	MergeList(La, Lb, Lc);
	ListTraverse(Lc);
	//ȥ��
	InitTestLaLb(La, Lb);
	printf("ȥ���ظ������Ԫ�� Lc = ");
	Purge(Lc);
	ListTraverse(Lc);
	
	return 0;
}