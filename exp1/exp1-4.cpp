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

typedef int ElemType;  //声明ElemType的类型
typedef int Status;  //声明函数类型名

typedef struct {
    char* ch;       //若是非空串，则按串长分配存储区，否则ch为NULL。
    int  length;   //串长度
} HString;           //堆分配串的类型定义

Status StrAssign(HString& S, char* chars) {
	//将字符串常量chars赋给串变量S
	S.length = strlen(chars);
	S.ch = (char*)malloc(10 * sizeof(char));
	if (!S.ch) return(OVERFLOW);
	for (int i = 0; i < S.length; i++) {
		S.ch[i] = chars[i];
	}
	return OK;
}

int StrCompare(HString S, HString T) {
	//比较串S与T的值 ，若S>T, 则返回1；若S=T,则返回0；否则返回-1。
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
	//返回串S的长度
	return S.length;
}

Status Concat(HString& S, HString T1, HString T2) {
	//将串T1和T2连接在一起赋给串变量S。
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
	//用Sub返回串S的第pos个字符起长度为len的子串，1≤ pos ≤StrLength(S)，1≤len≤StrLength(S)-pos+1
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
	//遍历（输出）字符串S中的各个字符。
	for (int i = 0; i < S.length; i++) {
		printf("%c", S.ch[i]);
	}
	printf("\n");
	return OK;
}

Status StrCopy(HString& S, HString T) {
	//将串T赋给串S。若使用堆分配存储结构，可利用Concat()函数实现。
	//若使用堆分配存储结构，则需针对存储结构操作。
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
	//返回串T在串S中第pos个字符开始出现的位置，若串T不是串S的子串，则返回0。
	//1≤ pos ≤StrLength(S)。利用SubString()和StrCompare()实现。
	
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
		if (!StrCompare(*sub, T)) { //相同
			return i;
		}
	}
	return 0;
}

Status Replace(HString& S, HString T1, HString T2) {
	//将S串中所有的子串T1用串T2代替。利用SubString()、StrCompare()和Concat()实现。
	int p = Index(S, T1, 1);
	while (p) {
		HString* sub1 = (HString*)malloc(sizeof(HString)); //头部

		HString* sub3 = (HString*)malloc(sizeof(HString)); //尾部
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
	//在串S的第pos个字符之前插入串T。1≤ pos ≤StrLength(S)+1。利用SubString()和Concat()实现。
	if (pos < 1 || pos > S.length + 1) {
		return ERROR;
	}
	HString* sub1 = (HString*)malloc(sizeof(HString)); //头部
	HString* sub2 = (HString*)malloc(sizeof(HString)); //尾部
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
	//删除串S中从第pos个字符开始连续的len个字符。1≤ pos ≤StrLength(S)-len+1，利用SubString()和Concat()实现。
	if (pos < 1 || pos > S.length - len + 1) {
		return ERROR;
	}
	HString* sub1 = (HString*)malloc(sizeof(HString)); //头部
	HString* sub2 = (HString*)malloc(sizeof(HString)); //尾部
	if (!sub1 || !sub2) {
		return OVERFLOW;
	}
	SubString(*sub1, S, 1, pos - 1);
	SubString(*sub2, S, pos + len, S.length - pos - len + 1);
	Concat(S, *sub1, *sub2);
	return OK;
}

int main(void) {
	//利用StrAssign()将设定的字符串常量（自行设定）赋给3个字符串变量T1,T2,T3，然后利用StrTraverse()输出字符串字符。
	HString T1, T2, T3;
	StrAssign(T1, "abc");
	StrAssign(T2, "def");
	StrAssign(T3, "ghi");
	StrTraverse(T1);
	StrTraverse(T2);
	StrTraverse(T3);
	//利用StrCopy()将串T1赋给串S，并输出S的字符。
	HString S;
	S.ch = (char*)malloc(sizeof(char) * 10);
	StrCopy(S, T1);
	StrTraverse(S);
	//利用StrInsert()将串T2插入到S的尾部，并输出S的字符。
	StrInsert(S, S.length+1, T2);
	StrTraverse(S);
	//利用StrReplace()将串S中的T1替换成T3，并输出S的字符。
	Replace(S, T1, T3);
	StrTraverse(S);
	//利用Index()查找串T2在S中的位置，并输出位置结果。
	printf("%d\n",Index(S, T2, 1));
	//利用StrDelete()删除S中子串T2，并输出删除后S的结果。
	StrDelete(S, Index(S, T2, 1), T2.length);
	StrTraverse(S);
	return 0;
}