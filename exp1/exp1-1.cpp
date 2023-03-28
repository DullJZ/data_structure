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



typedef struct SqList {
	ElemType* elem;  //˳������ݴ洢�ռ��ַ 
	int length;
}SqList;

Status InitList(SqList& L) {
	// ����new��������洢�ռ䣬����һ���յ�˳����L��L�ĳ�ʼ��СΪMAXSIZE��	
	if (!(L.elem = new ElemType[MAXSIZE])) {
		return OVERFLOW;
	}
	else {
		L.length = 0;
		return OK;
	}
}

Status ClearList(SqList& L) {
	//��˳����������ա�ֻ�轫L.length���㣬��L.length=0���ɡ� 
	L.length = 0;
	return OK;
}

int Listlength(SqList L) {
	//����L������Ԫ�ظ�����ֱ�ӷ���L.length��ֵ���ɡ�
	return L.length;
}

Status GetElem(SqList L, int i, ElemType& e) {
	//��e����L�е�i������Ԫ�ص�ֵ��1��i��L.Length����ע�⺯������i�������±�֮��Ĺ�ϵ������ͬ���� 
	e = L.elem[i - 1];
	return OK;
}

int LocateList(SqList L, ElemType e) {
	//����L�е�1����e��ȵ�����Ԫ��λ����e�����ڣ��򷵻�0��
	for (int i = 0; i < L.length; i++) {
		if (L.elem[i] == e) {
			return i + 1;
		}
	}
	return 0;
}

Status ListInsert(SqList& L, int i, ElemType e) {
	// ��L�еĵ�i��λ��֮ǰ�����µ�����Ԫ��e��1��i��L.length+1��
	for (int i0 = L.length; i0 > i - 1; i0--) {
		L.elem[i0] = L.elem[i0 - 1];
	}
	L.elem[i - 1] = e;
	L.length++;
	return OK;
}

Status ListDelete(SqList& L, int i, ElemType& e) {
	//ɾ��L�еĵ�i������Ԫ�أ���e������ֵ��1��i��L.length��
	e = L.elem[i - 1];
	for (int i0 = i - 1; i0 < L.length - 1; i0++) {
		L.elem[i0] = L.elem[i0 + 1];
	}
	L.length--;
	return OK;
}

Status ListTraverse(SqList L) {
	//����printf�����������L��ÿ������Ԫ�ص�ֵ��
	for (int i = 0; i < L.length; i++) {
		printf("%d ", L.elem[i]);
	}
	printf("\n");
	return OK;
}

//���Ա�Ԫ�صļ�������
Status Union(SqList& La, SqList Lb) {
	//������ La=La U Lb
	for (int i = 0; i < Lb.length; i++) {
		if (!LocateList(La, Lb.elem[i])) {
			La.length++;
			La.elem[La.length - 1] = Lb.elem[i];
		}
	}
	return OK;
}

Status Intersection(SqList& La, SqList Lb) {
	//������ La=La �� Lb
	for (int i = 0; i < La.length; i++) {
		ElemType tmp = LocateList(Lb, La.elem[i]);
		if (!tmp) {  //��Lb���ҵ���
			ListDelete(La, i+1, tmp);
			i--;
		}
	}
	return OK;
}

Status Difference(SqList& La, SqList Lb) {
	//������ La=La - Lb
	for (int i = 0; i < La.length; i++) {
		for (int j = 0; j < Lb.length; j++) {
			if (La.elem[i] == Lb.elem[j]) {
				ElemType tmp;
				ListDelete(La, i + 1, tmp);
				i--;
				break;
			}
		}
	}
	return OK;
}

//���������ĺϲ�
Status MergeList(SqList La, SqList Lb, SqList& Lc) {
	//��֪˳���La��Lb��Ԫ�ذ�ֵ�ǵݼ�����
	//�鲢La��Lb�õ��µ�˳���Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
	int i = 0, j = 0, k = 0;
	while (i < La.length && j < Lb.length) {
		if (La.elem[i] <= Lb.elem[j]) {
			Lc.elem[k] = La.elem[i];
			i++;
			k++;
		}
		else {
			Lc.elem[k] = Lb.elem[j];
			j++;
			k++;
		}
	}
	while (i < La.length) {
		Lc.elem[k] = La.elem[i];
		i++;
		k++;
	}
	while (j < Lb.length) {
		Lc.elem[k] = Lb.elem[j];
		j++;
		k++;
	}
	Lc.length = k;
	return OK;
}

//ȥ�����Ա��е��ظ������Ԫ��
Status Purge(SqList& Lc) {
	//��Lc��һ�����ظ�Ԫ�ص�˳�����дһ��ȥ��˳������ظ�����Ԫ�صĺ���
	for (int i = 0; i < Lc.length; i++) {
		for (int j = i + 1; j < Lc.length; j++) {
			if (Lc.elem[i] == Lc.elem[j]) {
				ElemType tmp;
				ListDelete(Lc, j + 1, tmp);
				j--;
			}
		}
	}
	return OK;
}

//��������Ӧ�ú����Ƿ���ȷ
int InitTestLaLb(SqList& La, SqList& Lb) {
	InitList(La);
	InitList(Lb);
	La.length = 7;
	Lb.length = 9;
	La.elem[0] = 2;
	La.elem[1] = 8;
	La.elem[2] = 27;
	La.elem[3] = 39;
	La.elem[4] = 66;
	La.elem[5] = 77;
	La.elem[6] = 89;
	Lb.elem[0] = 6;
	Lb.elem[1] = 18;
	Lb.elem[2] = 27;
	Lb.elem[3] = 59;
	Lb.elem[4] = 65;
	Lb.elem[5] = 77;
	Lb.elem[6] = 89;
	Lb.elem[7] = 120;
	Lb.elem[8] = 140;
	return 0;
}

int main() {
	SqList La,Lb;
	InitTestLaLb(La, Lb);
	printf("La = ");
	ListTraverse(La);
	printf("Lb = ");
	ListTraverse(Lb);
	// La=La U Lb
	Union(La, Lb);
	printf("La =  La U Lb = ");
	ListTraverse(La);
	InitTestLaLb(La, Lb);
	// La=La �� Lb
	Intersection(La, Lb);
	printf("La =  La �� Lb = ");
	ListTraverse(La);
	// La=La - Lb
	InitTestLaLb(La, Lb);
	Difference(La, Lb);
	printf("La =  La - Lb = ");
	ListTraverse(La);
	//�����ϲ�
	InitTestLaLb(La, Lb);
	SqList Lc;
	InitList(Lc);
	MergeList(La, Lb, Lc);
	printf("�����ϲ��� Lc = ");
	ListTraverse(Lc);
	//ȥ���ظ�Ԫ��
	Purge(Lc);
	printf("ȥ���ظ�Ԫ�غ� Lc = ");
	ListTraverse(Lc);
}