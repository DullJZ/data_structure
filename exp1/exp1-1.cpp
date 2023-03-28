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



typedef struct SqList {
	ElemType* elem;  //顺序表数据存储空间基址 
	int length;
}SqList;

Status InitList(SqList& L) {
	// 利用new函数申请存储空间，构造一个空的顺序表表L，L的初始大小为MAXSIZE。	
	if (!(L.elem = new ElemType[MAXSIZE])) {
		return OVERFLOW;
	}
	else {
		L.length = 0;
		return OK;
	}
}

Status ClearList(SqList& L) {
	//将顺序表的数据清空。只需将L.length清零，即L.length=0即可。 
	L.length = 0;
	return OK;
}

int Listlength(SqList L) {
	//返回L中数据元素个数。直接返回L.length的值即可。
	return L.length;
}

Status GetElem(SqList L, int i, ElemType& e) {
	//用e返回L中第i个数据元素的值，1≤i≤L.Length。请注意函数参数i与数组下标之间的关系（以下同）。 
	e = L.elem[i - 1];
	return OK;
}

int LocateList(SqList L, ElemType e) {
	//返回L中第1个与e相等的数据元素位序，若e不存在，则返回0。
	for (int i = 0; i < L.length; i++) {
		if (L.elem[i] == e) {
			return i + 1;
		}
	}
	return 0;
}

Status ListInsert(SqList& L, int i, ElemType e) {
	// 在L中的第i个位置之前插入新的数据元素e，1≤i≤L.length+1。
	for (int i0 = L.length; i0 > i - 1; i0--) {
		L.elem[i0] = L.elem[i0 - 1];
	}
	L.elem[i - 1] = e;
	L.length++;
	return OK;
}

Status ListDelete(SqList& L, int i, ElemType& e) {
	//删除L中的第i个数据元素，用e返回其值，1≤i≤L.length。
	e = L.elem[i - 1];
	for (int i0 = i - 1; i0 < L.length - 1; i0++) {
		L.elem[i0] = L.elem[i0 + 1];
	}
	L.length--;
	return OK;
}

Status ListTraverse(SqList L) {
	//利用printf函数依次输出L的每个数据元素的值。
	for (int i = 0; i < L.length; i++) {
		printf("%d ", L.elem[i]);
	}
	printf("\n");
	return OK;
}

//线性表元素的集合运算
Status Union(SqList& La, SqList Lb) {
	//并运算 La=La U Lb
	for (int i = 0; i < Lb.length; i++) {
		if (!LocateList(La, Lb.elem[i])) {
			La.length++;
			La.elem[La.length - 1] = Lb.elem[i];
		}
	}
	return OK;
}

Status Intersection(SqList& La, SqList Lb) {
	//交运算 La=La ∩ Lb
	for (int i = 0; i < La.length; i++) {
		ElemType tmp = LocateList(Lb, La.elem[i]);
		if (!tmp) {  //在Lb中找到了
			ListDelete(La, i+1, tmp);
			i--;
		}
	}
	return OK;
}

Status Difference(SqList& La, SqList Lb) {
	//差运算 La=La - Lb
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

//两个有序表的合并
Status MergeList(SqList La, SqList Lb, SqList& Lc) {
	//已知顺序表La和Lb的元素按值非递减排列
	//归并La和Lb得到新的顺序表Lc，Lc的元素也按值非递减排列
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

//去掉线性表中的重复多余的元素
Status Purge(SqList& Lc) {
	//设Lc是一个有重复元素的顺序表，编写一个去掉顺序表中重复多余元素的函数
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

//检验上述应用函数是否正确
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
	// La=La ∩ Lb
	Intersection(La, Lb);
	printf("La =  La ∩ Lb = ");
	ListTraverse(La);
	// La=La - Lb
	InitTestLaLb(La, Lb);
	Difference(La, Lb);
	printf("La =  La - Lb = ");
	ListTraverse(La);
	//有序表合并
	InitTestLaLb(La, Lb);
	SqList Lc;
	InitList(Lc);
	MergeList(La, Lb, Lc);
	printf("有序表合并后 Lc = ");
	ListTraverse(Lc);
	//去掉重复元素
	Purge(Lc);
	printf("去掉重复元素后 Lc = ");
	ListTraverse(Lc);
}