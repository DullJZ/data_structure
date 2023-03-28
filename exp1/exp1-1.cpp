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
	ElemType *elem;  //顺序表数据存储空间基址 
	int length;
}SqList;

Status InitList(SqList &L){
	// 利用new函数申请存储空间，构造一个空的顺序表表L，L的初始大小为MAXSIZE。	
	if (!(L.elem = new ElemType [MAXSIZE])){
		return OVERFLOW;
	}
	else{
		L.length=0;
		return OK;
	}
}

Status ClearList(SqList &L){
	//将顺序表的数据清空。只需将L.length清零，即L.length=0即可。 
	L.length=0;
	return OK;
}

int Listlength(SqList L){
	//返回L中数据元素个数。直接返回L.length的值即可。
	return L.length;
}

Status GetElem(SqList L, int i, ElemType &e){
	//用e返回L中第i个数据元素的值，1≤i≤L.Length。请注意函数参数i与数组下标之间的关系（以下同）。 
	e = L.elem[i-1];
	return OK;
}

int LocateList(SqList L, ElemType e){
	//返回L中第1个与e相等的数据元素位序，若e不存在，则返回0。
	for (int i =0;i<L.length;i++){
		if (L.elem[i]==e){
			return i+1;
		}
	}
	return 0;

Status ListInsert(SqList &L, int i, ElemType e){
	// 在L中的第i个位置之前插入新的数据元素e，1≤i≤L.length+1。
	for (int i0=L.length;i0>i-1;i0--){
		L.elem[i0]=L.elem[i0-1];
	}
	L.elem[i-1]=e;
	return OK;
}

