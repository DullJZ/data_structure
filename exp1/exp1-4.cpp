#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE    100

typedef int ElemType;  //����ElemType������
typedef int Status;  //��������������

typedef struct {
    char* ch;       //���Ƿǿմ����򰴴�������洢��������chΪNULL��
    int  length;   //������
} HString;           //�ѷ��䴮�����Ͷ���

Status StrAssign(HString& S, char* chars) {
	//���ַ�������chars����������S
	S.length = strlen(chars);
	S.ch = (char*)malloc(10 * sizeof(char));
	if (!S.ch) return(OVERFLOW);
	for (int i = 0; i < S.length; i++) {
		S.ch[i] = chars[i];
	}
	return OK;
}

int StrCompare(HString S, HString T) {
	//�Ƚϴ�S��T��ֵ ����S>T, �򷵻�1����S=T,�򷵻�0�����򷵻�-1��
	for (int i = 0; i < S.length; i++) {
		if (S.ch[i] < T.ch[i]) {
			return -1;
		}
		if (S.ch[i] > T.ch[i]){
			return 1;
		}
	}
	return 0;
}

int StrLength(HString S) {
	//���ش�S�ĳ���
	return S.length;
}

Status Concat(HString& S, HString T1, HString T2) {
	//����T1��T2������һ�𸳸�������S��
	S.length = T1.length + T2.length;
	if (S.ch == NULL) {
		S.ch = (char*)malloc(sizeof(char) * 10);
	}
	for (int i = 0; i < T1.length; i++) {
		S.ch[i] = T1.ch[i];
	}
	for (int i = 0; i < T2.length; i++) {
		S.ch[T1.length + i] = T2.ch[i];
	}
	return OK;
}

Status SubString(HString& sub, HString S, int pos, int len) {
	//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ���1�� pos ��StrLength(S)��1��len��StrLength(S)-pos+1
	sub.ch = (char*)malloc(10 * sizeof(char));
	if (!sub.ch) exit(OVERFLOW);
	if (len == 0) {
		sub.length = 0;
		return OK;
	}
	if (pos < 1 || pos > S.length || len > S.length - pos + 1) {
		return ERROR;
	}
	for (int i = 0; i < len; i++) {
		sub.ch[i] = S.ch[pos + i - 1];
	}
	sub.length = len;
	return OK;
}

Status StrTraverse(HString S) {
	//������������ַ���S�еĸ����ַ���
	for (int i = 0; i < S.length; i++) {
		printf("%c", S.ch[i]);
	}
	printf("\n");
	return OK;
}

Status StrCopy(HString& S, HString T) {
	//����T������S����ʹ�öѷ���洢�ṹ��������Concat()����ʵ�֡�
	//��ʹ�öѷ���洢�ṹ��������Դ洢�ṹ������
	HString* T1 = (HString*)malloc(sizeof(HString));
	if (!T1) {
		return OVERFLOW;
	}
	T1->ch = NULL;
	T1->length = 0;
	Concat(S, T, *T1);
	return OK;
}

int Index(HString S, HString T, int pos) {
	//���ش�T�ڴ�S�е�pos���ַ���ʼ���ֵ�λ�ã�����T���Ǵ�S���Ӵ����򷵻�0��
	//1�� pos ��StrLength(S)������SubString()��StrCompare()ʵ�֡�
	
	if (pos < 1 || pos > S.length) {
		return ERROR;
	}
	int i = pos;
	for (; i + T.length -1 <= S.length; i++) {
		HString* sub=(HString*)malloc(sizeof(HString));
		if (!sub){
			exit(OVERFLOW);
		}
		SubString(*sub, S, i, T.length);
		if (!StrCompare(*sub, T)) { //��ͬ
			return i;
		}
	}
	return 0;
}

Status Replace(HString& S, HString T1, HString T2) {
	//��S�������е��Ӵ�T1�ô�T2���档����SubString()��StrCompare()��Concat()ʵ�֡�
	int p = Index(S, T1, 1);
	while (p) {
		HString* sub1 = (HString*)malloc(sizeof(HString)); //ͷ��

		HString* sub3 = (HString*)malloc(sizeof(HString)); //β��
		if (!sub1 || !sub3) {
			return OVERFLOW;
		}
		int j = 0;
		sub3->ch = (char*)malloc(sizeof(char) * 10);
		for (int i = p + T1.length - 1; i < S.length; i++) {
			sub3->ch[j] = S.ch[i];
			j++;
		}
		sub3->length = j;
		SubString(*sub1, S, 1, p - 1);
		Concat(*sub1, *sub1, T2);
		Concat(S, *sub1, *sub3);
		
		p = Index(S, T1, 1);
	}
	return OK;
}

Status StrInsert(HString& S, int pos, HString T) {
	//�ڴ�S�ĵ�pos���ַ�֮ǰ���봮T��1�� pos ��StrLength(S)+1������SubString()��Concat()ʵ�֡�
	if (pos < 1 || pos > S.length + 1) {
		return ERROR;
	}
	HString* sub1 = (HString*)malloc(sizeof(HString)); //ͷ��
	HString* sub2 = (HString*)malloc(sizeof(HString)); //β��
	if (!sub1 || !sub2) {
		return OVERFLOW;
	}
	SubString(*sub1, S, 1, pos - 1);
	SubString(*sub2, S, pos, S.length - pos + 1);
	HString* tmp = (HString*)malloc(sizeof(HString));
	tmp->ch = NULL;
	if (!tmp) {
		return OVERFLOW;
	}
	Concat(*tmp, *sub1, T);
	Concat(S, *tmp, *sub2);
	return OK;
}

Status StrDelete(HString& S, int pos, int len) {
	//ɾ����S�дӵ�pos���ַ���ʼ������len���ַ���1�� pos ��StrLength(S)-len+1������SubString()��Concat()ʵ�֡�
	if (pos < 1 || pos > S.length - len + 1) {
		return ERROR;
	}
	HString* sub1 = (HString*)malloc(sizeof(HString)); //ͷ��
	HString* sub2 = (HString*)malloc(sizeof(HString)); //β��
	if (!sub1 || !sub2) {
		return OVERFLOW;
	}
	SubString(*sub1, S, 1, pos - 1);
	SubString(*sub2, S, pos + len, S.length - pos - len + 1);
	Concat(S, *sub1, *sub2);
	return OK;
}

int main(void) {
	//����StrAssign()���趨���ַ��������������趨������3���ַ�������T1,T2,T3��Ȼ������StrTraverse()����ַ����ַ���
	HString T1, T2, T3;
	StrAssign(T1, "abc");
	StrAssign(T2, "def");
	StrAssign(T3, "ghi");
	StrTraverse(T1);
	StrTraverse(T2);
	StrTraverse(T3);
	//����StrCopy()����T1������S�������S���ַ���
	HString S;
	S.ch = (char*)malloc(sizeof(char) * 10);
	StrCopy(S, T1);
	StrTraverse(S);
	//����StrInsert()����T2���뵽S��β���������S���ַ���
	StrInsert(S, S.length+1, T2);
	StrTraverse(S);
	//����StrReplace()����S�е�T1�滻��T3�������S���ַ���
	Replace(S, T1, T3);
	StrTraverse(S);
	//����Index()���Ҵ�T2��S�е�λ�ã������λ�ý����
	printf("%d\n",Index(S, T2, 1));
	//����StrDelete()ɾ��S���Ӵ�T2�������ɾ����S�Ľ����
	StrDelete(S, Index(S, T2, 1), T2.length);
	StrTraverse(S);
	return 0;
}