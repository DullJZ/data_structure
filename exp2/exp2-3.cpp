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
		HT[s1].parent = i+1;
		HT[s2].parent = i+1;
		HT[i + 1].lchild = s1;
		HT[i + 1].rchild = s2;
		HT[i + 1].weight = HT[s1].weight + HT[s2].weight;
	}
	return OK;
}

Status HTCoding(HTree HT, HTCode& HC, int n) {
	/*生成赫夫曼编码HC，其中n是叶子结点数。
	要求根据生成的赫夫曼树HT，生成n个叶子结点的赫夫曼编码并输出。*/
	HC = (HTCode)malloc(sizeof(char) * (n + 1));
	char* cd = (char*)malloc(sizeof(char) * n);
	if (!cd) {
		return ERROR;
	}
	cd[n - 1] = '\0';
	int i, start, c, f;
	
	for (i = 0; i < n; i++) {
		start = n - 1;
		c = i;
		f = HT[i].parent;
		
	}
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
}