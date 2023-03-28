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
	ElemType *elem;  //˳������ݴ洢�ռ��ַ 
	int length;
}SqList;

Status InitList(SqList &L){
	// ����new��������洢�ռ䣬����һ���յ�˳����L��L�ĳ�ʼ��СΪMAXSIZE��	
	if (!(L.elem = new ElemType [MAXSIZE])){
		return OVERFLOW;
	}
	else{
		L.length=0;
		return OK;
	}
}

Status ClearList(SqList &L){
	//��˳����������ա�ֻ�轫L.length���㣬��L.length=0���ɡ� 
	L.length=0;
	return OK;
}

int Listlength(SqList L){
	//����L������Ԫ�ظ�����ֱ�ӷ���L.length��ֵ���ɡ�
	return L.length;
}

Status GetElem(SqList L, int i, ElemType &e){
	//��e����L�е�i������Ԫ�ص�ֵ��1��i��L.Length����ע�⺯������i�������±�֮��Ĺ�ϵ������ͬ���� 
	e = L.elem[i-1];
	return OK;
}

int LocateList(SqList L, ElemType e){
	//����L�е�1����e��ȵ�����Ԫ��λ����e�����ڣ��򷵻�0��
	for (int i =0;i<L.length;i++){
		if (L.elem[i]==e){
			return i+1;
		}
	}
	return 0;
}

Status ListInsert(SqList &L, int i, ElemType e){
	// ��L�еĵ�i��λ��֮ǰ�����µ�����Ԫ��e��1��i��L.length+1��
	for (int i0=L.length;i0>i-1;i0--){
		L.elem[i0]=L.elem[i0-1];
	}
	L.elem[i-1]=e;
	L.length++;
	return OK;
}

Status ListDelete(SqList &L, int i, ElemType &e ){
	//ɾ��L�еĵ�i������Ԫ�أ���e������ֵ��1��i��L.length��
	e=L.elem[i-1];
	for (int i0=i-1;i0<L.length-1;i0++){
		L.elem[i0]=L.elem[i0+1];
	}
	L.length--;
	return OK;
}

Status ListTraverse(SqList L){
	//����printf�����������L��ÿ������Ԫ�ص�ֵ��
	for (int i=0;i<L.length;i++){
		printf("%d ",L.elem[i]);
	}
	printf("\n");
	return OK;
}



//���ڲ��Ժ���
int main(){
	SqList L;
	InitList(L);
	L.elem[0]=3;
	L.elem[1]=9;
	L.elem[2]=1;
	L.length=3;
	;
	ListTraverse(L);
	int e=0;
	ListDelete(L,2,e);
	ListTraverse(L);
}