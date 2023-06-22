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

typedef  struct {  //����������������� 
    unsigned int  weight;
    unsigned int parent, lchild, rchild;
} HTNode, * HTree;           //��̬��������洢�շ�����

typedef  char** HTCode;  //��̬�����ַ�������洢�շ��������

typedef int Status;

Status InitHTree(HTree& HT, int* w, int n) {
	/*��ʼ���շ�����������w��n�ֱ���Ȩ�������Ҷ�ӽ������
	Ҫ����ݶ���ĺշ������ṹ������һ����2n-1��Ԫ����ɵ�һά����HT��
	HT[0..n-1]���n��Ҷ�ӽ���Ȩ�غͽ����������Ԫ�غ��������ֵ���ó�-1��*/
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
	/*��HT[0..n-1]��ѡ��parentΪ0��weight��С��������㣬
	����ŷֱ�Ϊs1��s2����s1<s2��*/
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
	/*����շ�����HT������n��Ҷ�ӽ������
	Ҫ����ݺշ������Ĺ����������һ����2n-1�������ɵ�һ�úշ�������*/
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
	/*���ɺշ�������HC������n��Ҷ�ӽ������
	Ҫ��������ɵĺշ�����HT������n��Ҷ�ӽ��ĺշ������벢�����*/
	n = 8;
	HC = (HTCode)malloc(sizeof(HTCode) * n + 1);
	char* cd = (char*)malloc(sizeof(char) * n);							//����n��char��Сchar���͵���ʱ�ռ䣬�����ʱ�����¼ÿ�α��������ı���
	int start = 0, c = 0, f = 0;											//startΪcd�����¼�±꣬c��ʼΪҶ�ӽ���±꣬������Ǻ��ӽ����±꣬f��¼˫�׽����±�
	cd[n - 1] = '\0';													//������Ǹ�printf���ŵģ���Ϊprintf��������'\0'�������puts�Ͳ�����������
	for (int i = 1; i <= n; i++)										//ֻҪҶ�ӽ��ı���
	{
		start = n - 1;													//���Ҫ��ֵn�Ļ���start--Ҫд���жϺ�
		c = i;
		f = HT[c].parent;
		while (f != -1)													//���ڵ�û��˫��
		{
			start--;
			if (HT[f].lchild == c)											//�����Ӿ���0���Һ��Ӿ�Ϊ1
				cd[start] = '0';
			else
				cd[start] = '1';
			c = f; f = HT[c].parent;									//������ӽ�
		}
		HC[i] = (char*)malloc(sizeof(char) * (n - start));				//�����������������n - start��char��С��char*���͵���ʱ�ռ�
		strcpy(HC[i], &cd[start]);										//cd���¼�ı����HC�ĵ�i������
	}
	free(cd);															//�ͷ���ʱ�ռ�

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