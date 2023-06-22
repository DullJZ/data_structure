#include <stdlib.h>
#include <stdio.h>
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
int count = 0;
typedef int KeyType;        //�ؼ��ֵ���������

//����Ԫ�أ���¼�������Ͷ���
typedef struct {
    KeyType  key;            //ѧ��(�ؼ���)
    const char* name;     //����
    const char* sex;         //�Ա� 
    int  age;                     //���� 
} RecordType;

//��̬���ұ�BST�����Ͷ���
typedef  struct BSTNode {
    RecordType  data;
    struct BSTNode* lchild, * rchild; //ָ�����Һ��ӽ���ָ��
}BSTNode, * BSTree;

//��̬���ұ�����Ͷ���
typedef struct {
	RecordType* Record;      //����Ԫ�ش洢�ռ�Ļ�ַ(һά������)
	int    length;             //��ĳ��ȣ�Ԫ�ظ�����
}SSTable;

BSTree SearchDSTable_BST(BSTree DT, KeyType key);

Status CreateSSTable(SSTable& ST, int n) {
	n = 11;
	/*��дһ��������̬���ұ�ĺ���CreateSSTable(SSTable &ST, int n)������nΪԪ�ظ�����
	�����ľ�̬���ұ���±�1��ʼ�������(0Ԫ�ؿ����������ڱ���)��

	ע��Ϊ��߳�������ٶȣ��ú�������ֱ���ø�ֵ��佫������Ԫ�ص�ֵ�ԡ���������ʽ������̬���ұ�ĸ�������Ԫ�ء�*/
	ST.Record = (RecordType*)malloc((n + 1) * sizeof(RecordType));
	if (!ST.Record) {
		return ERROR;
	}
	ST.length = n;
	//¼������
	RecordType example_data[11] = {
		{56,"Zhang","F",19},
		{19,"Wang","F",20},
		{80,"Zhou" ,"F",19},
		{5,"Huang", "M",20},
		{21, "Zheng","M",  20},
		{64, "Li", 	"M",19},
		{88, "Liu", "F",18},
		{13,  "Qian","F",19},
		{37,  "Sun", "M",20},
		{75,  "Zhao", "M",20},
		{92,  "Chen" ,"M",20 }
	};
	for (int i = 1; i <= n; i++)
	{
		ST.Record[i] = example_data[i - 1];
	}
	return OK;
}

Status TraversSSTable(SSTable ST) {
	//�����̬���ұ�ST����������Ԫ�ء�
	for (int i = 1; i <= ST.length; i++) {
		printf("ѧ�ţ�%2d\t������%s\t�Ա�%s\t���䣺%d\n", ST.Record[i].key, ST.Record[i].name, ST.Record[i].sex, ST.Record[i].age);
	}
	return OK;
}

/*����BST�����ʽ�����Ԫ��e���뵽��̬���ұ�DT�С�
��Ԫ��e��DT���Ѵ��ڣ������ʧ�ܣ�����FALSE��*/
bool InsertDSTable_BST(BSTree& DT, KeyType e) {
    if (!DT) {
        BSTNode* S = (BSTNode*)malloc(sizeof(BSTNode));
		if (!S) return ERROR;
        S->data.key = e;
		S->lchild = NULL;
		S->rchild = NULL;
        DT = S;
    }
	else if (e < DT->data.key) {
		InsertDSTable_BST(DT->lchild, e);
	}
	else if (e > DT->data.key) {
		InsertDSTable_BST(DT->rchild, e);
	}
	else {
		return false;
	}
    return true;
}

//��дһ��������̬���ұ�ĺ���CreateDSTable_BST(BSTree &DT, SSTable &ST)������STΪʵ��4-1�������ľ�̬���ұ��ú���Ҫ����InsertDSTable_BST()������
Status CreateDSTable_BST(BSTree& DT, SSTable& ST) {
	RecordType* tmp;
	tmp = ST.Record;
	tmp++;
	for (int i = 1; i <= ST.length; i++) {
		InsertDSTable_BST(DT, tmp->key);
		tmp++;
	}
	return OK;
}

//��дһ�������������TraversDSTable_InOrder(BSTree DT)�������̬���ұ�DT����������Ԫ�ء�
Status TraversDSTable_InOrder(BSTree DT) {
	if (DT) {
		TraversDSTable_InOrder(DT->lchild);
		printf("%d ", DT->data.key);
		TraversDSTable_InOrder(DT->rchild);
	}
	return OK;
}

/*��дһ�����Һ��� BSTree SearchDSTable_BST(BSTree DT, KeyType key)��
���в���keyΪҪ����Ԫ�صĹؼ��֡������ҳɹ����������ظùؼ���Ԫ�ؽ��ĵ�ַ��ָ�룩��
���򣬲��Ҳ��ɹ�������NULL���ú��������õݹ��ǵݹ鷽ʽʵ�֣�
ͬʱҪ�������ҹ����йؼ��ֱȽϵĴ������ݹ麯��������ȫ�ֱ���ʵ�֣���*/
BSTree SearchDSTable_BST(BSTree DT, KeyType key) {
	count++;
	if (!DT|| key == DT->data.key) {
		return DT;
	}
	else if (key < DT->data.key) {
		return SearchDSTable_BST(DT->lchild, key);
	}
	else {
		return SearchDSTable_BST(DT->rchild, key);
	}
}

/*��дһ��ɾ������ DeleteDSTable_BST(BSTree &DT, KeyType key)��
���в���keyΪҪɾ��Ԫ�صĹؼ��֣����ùؼ��ֵ�Ԫ����DT�в����ڣ������ʧ�ܣ�����FALSE��*/
bool DeleteDSTable_BST(BSTree& DT, KeyType key) {
	BSTree f, p, q, s;
	f = NULL;
	q = NULL;
	p = DT;
	while (p) {
		if (p->data.key == key) {
			break;
		}
		f = p;
		if (key < p->data.key) {
			p = p->lchild;
		}
		else {
			p = p->rchild;
		}
	}
	if (!p) {
		return false;
	}
	if ((p->lchild) && (p->rchild)) {
		q = p;
		s = p->lchild;
		while (s->rchild) {
			q = s;
			s = s->rchild;
		}
		p->data = s->data;
		if (q != p) {
			q->rchild = s->lchild;
		}
		else {
			q->lchild = s->lchild;
		}
		free(s);
		return true;
	}
	else if (!p->rchild) {
		q = p;
		p = p->lchild;
	}
	else if (!p->lchild) {
		q = p;
		p = p->rchild;
	}
	if (!f) DT = p;
	else if (q == f->lchild) {
		f->lchild = p;
	}
	else {
		f->rchild = p;
	}
	free(q);
}


int main() {
	int i, key;
	int n = 11;
	SSTable ST1;
	BSTree DT1 = NULL, p;

	//������̬���ұ�ST1 
	CreateSSTable(ST1, n);
	printf("\n��̬���ұ�\n");
	TraversSSTable(ST1);
	
	//������̬���ұ�DT1 
	CreateDSTable_BST(DT1, ST1);
	printf("\n��̬���ұ�(�������)\n");
	printf("ѧ�� ���� �Ա� ����\n");
	TraversDSTable_InOrder(DT1);

	//���Ҷ�̬���ұ�Ԫ�� 
	printf("\n---Ԫ�ز���---\n");

	printf("\n������Ҫ���Ҽ�¼��ѧ��(����-1����)��");

	scanf_s("%d", &key);

	while (key != -1) {

		p = SearchDSTable_BST(DT1, key);

		if (!p)
			printf("��ǰҪ���ҵļ�¼�����ڣ�\n");
		else
			TraversDSTable_InOrder(p);	//����ҵ��ļ�¼ 

		printf("����ʱ�ȽϵĴ���=%d\n", count);
		count = 0;
		printf("\n������Ҫ���ҵ�ѧ�ţ�"); //��һ�β��� 

		scanf_s("%d", &key);

	}



	int total = 0;

	for (i = 1; i <= ST1.length; i++) {
		count = 0;
		SearchDSTable_BST(DT1, ST1.Record[i].key);
		total = total + count;
	}

	printf("\n\n���ҳɹ���ƽ�����ҳ���ASL=%f\n", (float)total / ST1.length);



	total = 0;

	for (i = 0; i <= ST1.length; i++) {
		count = 0;
		if (i == 0) SearchDSTable_BST(DT1, 4);
		else SearchDSTable_BST(DT1, ST1.Record[i].key + 1);
		total = total + count;
	}

	printf("\n���Ҳ��ɹ���ƽ�����ҳ���ASL=%f\n", (float)total / (ST1.length + 1));

	//���춯̬���ұ�������Ԫ�� �� 
	printf("\n---Ԫ�ز���---\n");
	RecordType* e = (RecordType*)malloc(sizeof(RecordType));
	
	printf("\n������Ҫ������¼�¼(����-1����)\nѧ�� ���� �Ա� ����\n");
	
	scanf_s("%d %s %s %d", &e->key, e->name, e->sex, &e->age);

	while (e->key != -1) {

		if (InsertDSTable_BST(DT1, e->key)) {

			printf("\n����Ԫ�غ�Ķ�̬���ұ�(�������)\n");

			printf("ѧ�� ���� �Ա� ����\n");

			TraversDSTable_InOrder(DT1);

		}

		else printf("��ǰҪ����ļ�¼�Ѵ��ڣ���ֹ���룡\n");

		printf("\n������Ҫ������¼�¼(����-1����)\nѧ�� ���� �Ա� ����\n");
		
		scanf_s("%d %s %s %d", &e->key, e->name, e->sex, &e->age);

	}



	//ɾ����̬���ұ�Ԫ�� 

	printf("\n---Ԫ��ɾ��---\n");

	printf("\n������Ҫɾ����¼��ѧ��(����-1����)��");

	scanf_s("%d", &key);

	while (key != -1) {

		if (DeleteDSTable_BST(DT1, key)) {

			printf("\nɾ��Ԫ�غ�Ķ�̬���ұ�(�������)\n");

			printf("ѧ�� ���� �Ա� ����\n");

			TraversDSTable_InOrder(DT1);

		}

		else printf("��ǰҪɾ���ļ�¼�����ڣ�\n");

		printf("\n������Ҫɾ����¼��ѧ��(����-1����)��"); //��һ��ɾ�� 

		scanf_s("%d", &key);

	}





	return 1;

}