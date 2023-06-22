#define _CRT_SECURE_NO_WARNINGS
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

typedef  struct {  //定义二叉链表结点类型 
    unsigned int  weight;
    unsigned int parent, lchild, rchild;
} HTNode, * HTree;           //动态分配数组存储赫夫曼树

typedef  char** HTCode;  //动态分配字符串数组存储赫夫曼编码表

typedef int Status;

Status InitHTree(HTree& HT, int* w, int n) {
	/*初始化赫夫曼树，其中w和n分别是权重数组和叶子结点数。
	要求根据定义的赫夫曼树结构，申请一个由2n-1个元素组成的一维数组HT，
	HT[0..n-1]存放n个叶子结点的权重和结点数，其他元素和数据域的值度置成-1。*/
	if (n <= 1) return ERROR;
	int m = 2 * n - 1;
	HT = (HTNode*)malloc((m + 1) * sizeof(HTNode));
	if (!HT) return OVERFLOW;
	for (int i = 0; i < n; ++i) {
		HT[i].weight = w[i];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (int i = n; i < m ; ++i) {
		HT[i].weight = -1;
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
	}
	return OK;
	
}

Status Select(HTree HT, int n, int& s1, int& s2) {
	/*在HT[0..n-1]中选择parent为0且weight最小的两个结点，
	其序号分别为s1和s2，且s1<s2。*/
	int min1 = 0, min2 = 0;
	for (int i = 0; i < n; ++i) {
		if (HT[i].parent == 0) {
			if (min1 == 0) {
				min1 = i;
			}
			else if (min2 == 0) {
				min2 = i;
			}
			else if (HT[i].weight < HT[min1].weight) {
				min2 = min1;
				min1 = i;
			}
			else if (HT[i].weight < HT[min2].weight) {
				min2 = i;
			}
		}
	}
	s1 = min1;
	s2 = min2;
	return OK;
}

Status CreatHTree(HTree& HT, int n) {
	/*构造赫夫曼树HT，其中n是叶子结点数。
	要求根据赫夫曼树的构造规则，生成一个由2n-1个结点组成的一棵赫夫曼树。*/
	int m = 2 * n - 1;
	int s1, s2, i;
	for (i = n; i < m; i++) {
		Select(HT, i, s1, s2);
		HT[s1].parent = i + 1;
		HT[s2].parent = i + 1;
		HT[i + 1].lchild = s1;
		HT[i + 1].rchild = s2;
		HT[i + 1].weight = HT[s1].weight + HT[s2].weight;
	}
	return OK;
}

Status HTCoding(HTree HT, HTCode& HC, int n) {
	/*生成赫夫曼编码HC，其中n是叶子结点数。
	要求根据生成的赫夫曼树HT，生成n个叶子结点的赫夫曼编码并输出。*/
	n = 8;
	HC = (HTCode)malloc(sizeof(HTCode) * n + 1);
	char* cd = (char*)malloc(sizeof(char) * n);							//申请n个char大小char类型的临时空间，这个临时数组记录每次遍历出来的编码
	int start = 0, c = 0, f = 0;											//start为cd数组记录下标，c初始为叶子结点下标，而后就是孩子结点的下标，f记录双亲结点的下标
	cd[n - 1] = '\0';													//这个就是给printf留着的，因为printf不会生成'\0'，如果用puts就不用这句语句了
	for (int i = 1; i <= n; i++)										//只要叶子结点的编码
	{
		start = n - 1;													//这句要赋值n的话，start--要写在判断后方
		c = i;
		f = HT[c].parent;
		while (f != -1)													//根节点没有双亲
		{
			start--;
			if (HT[f].lchild == c)											//是左孩子就是0，右孩子就为1
				cd[start] = '0';
			else
				cd[start] = '1';
			c = f; f = HT[c].parent;									//向根结点接近
		}
		HC[i] = (char*)malloc(sizeof(char) * (n - start));				//给数组里的数组申请n - start个char大小的char*类型的临时空间
		strcpy(HC[i], &cd[start]);										//cd里记录的编码给HC的第i个数组
	}
	free(cd);															//释放临时空间

	return OK;
}

int main() {
	int w[8] = { 5,29,7,8,14,23,3,11 };
	HTree HT;
	int n = 8;
	InitHTree(HT, w, n);
	for (int i = 0; i < 2 * n - 1; i++) {
		printf("%d ", HT[i].weight);
	}
	printf("\n");
	CreatHTree(HT, n);
	for (int i = 0; i < 2 * n - 1; i++) {
		printf("%d ", HT[i].weight);
	}
	HTCode HTCode1;
	HTCoding(HT, HTCode1, n);
	for (int i = 1; i <= n; i++) {
		printf("%s\n", HTCode1[i]);
	}
}