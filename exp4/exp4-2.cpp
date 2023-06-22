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
typedef int KeyType;        //关键字的数据类型

//数据元素（记录）的类型定义
typedef struct {
    KeyType  key;            //学号(关键字)
    const char* name;     //姓名
    const char* sex;         //性别 
    int  age;                     //年龄 
} RecordType;

//动态查找表BST的类型定义
typedef  struct BSTNode {
    RecordType  data;
    struct BSTNode* lchild, * rchild; //指向左右孩子结点的指针
}BSTNode, * BSTree;

//静态查找表的类型定义
typedef struct {
	RecordType* Record;      //数据元素存储空间的基址(一维数组名)
	int    length;             //表的长度（元素个数）
}SSTable;

BSTree SearchDSTable_BST(BSTree DT, KeyType key);

Status CreateSSTable(SSTable& ST, int n) {
	n = 11;
	/*编写一个创建静态查找表的函数CreateSSTable(SSTable &ST, int n)，其中n为元素个数。
	创建的静态查找表从下标1开始存放数据(0元素可以用作“哨兵”)。

	注：为提高程序调试速度，该函数允许直接用赋值语句将各数据元素的值以“常量”形式赋给静态查找表的各个数组元素。*/
	ST.Record = (RecordType*)malloc((n + 1) * sizeof(RecordType));
	if (!ST.Record) {
		return ERROR;
	}
	ST.length = n;
	//录入数据
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
	//输出静态查找表ST的所有数据元素。
	for (int i = 1; i <= ST.length; i++) {
		printf("学号：%2d\t姓名：%s\t性别：%s\t年龄：%d\n", ST.Record[i].key, ST.Record[i].name, ST.Record[i].sex, ST.Record[i].age);
	}
	return OK;
}

/*根据BST的性质将数据元素e插入到动态查找表DT中。
若元素e在DT中已存在，则操作失败，返回FALSE。*/
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

//编写一个创建动态查找表的函数CreateDSTable_BST(BSTree &DT, SSTable &ST)，其中ST为实验4-1所创建的静态查找表。该函数要调用InsertDSTable_BST()函数。
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

//编写一个中序遍历函数TraversDSTable_InOrder(BSTree DT)，输出动态查找表DT的所有数据元素。
Status TraversDSTable_InOrder(BSTree DT) {
	if (DT) {
		TraversDSTable_InOrder(DT->lchild);
		printf("%d ", DT->data.key);
		TraversDSTable_InOrder(DT->rchild);
	}
	return OK;
}

/*编写一个查找函数 BSTree SearchDSTable_BST(BSTree DT, KeyType key)，
其中参数key为要查找元素的关键字。若查找成功，函数返回该关键字元素结点的地址（指针），
否则，查找不成功，返回NULL。该函数可以用递归或非递归方式实现，
同时要计数查找过程中关键字比较的次数（递归函数可利用全局变量实现）。*/
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

/*编写一个删除函数 DeleteDSTable_BST(BSTree &DT, KeyType key)，
其中参数key为要删除元素的关键字，若该关键字的元素在DT中不存在，则操作失败，返回FALSE。*/
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

	//创建静态查找表ST1 
	CreateSSTable(ST1, n);
	printf("\n静态查找表\n");
	TraversSSTable(ST1);
	
	//创建动态查找表DT1 
	CreateDSTable_BST(DT1, ST1);
	printf("\n动态查找表(中序遍历)\n");
	printf("学号 姓名 性别 年龄\n");
	TraversDSTable_InOrder(DT1);

	//查找动态查找表元素 
	printf("\n---元素查找---\n");

	printf("\n请输入要查找记录的学号(输入-1结束)：");

	scanf_s("%d", &key);

	while (key != -1) {

		p = SearchDSTable_BST(DT1, key);

		if (!p)
			printf("当前要查找的记录不存在！\n");
		else
			TraversDSTable_InOrder(p);	//输出找到的记录 

		printf("查找时比较的次数=%d\n", count);
		count = 0;
		printf("\n请输入要查找的学号："); //下一次查找 

		scanf_s("%d", &key);

	}



	int total = 0;

	for (i = 1; i <= ST1.length; i++) {
		count = 0;
		SearchDSTable_BST(DT1, ST1.Record[i].key);
		total = total + count;
	}

	printf("\n\n查找成功的平均查找长度ASL=%f\n", (float)total / ST1.length);



	total = 0;

	for (i = 0; i <= ST1.length; i++) {
		count = 0;
		if (i == 0) SearchDSTable_BST(DT1, 4);
		else SearchDSTable_BST(DT1, ST1.Record[i].key + 1);
		total = total + count;
	}

	printf("\n查找不成功的平均查找长度ASL=%f\n", (float)total / (ST1.length + 1));

	//构造动态查找表（插入新元素 ） 
	printf("\n---元素插入---\n");
	RecordType* e = (RecordType*)malloc(sizeof(RecordType));
	
	printf("\n请输入要插入的新记录(输入-1结束)\n学号 姓名 性别 年龄\n");
	
	scanf_s("%d %s %s %d", &e->key, e->name, e->sex, &e->age);

	while (e->key != -1) {

		if (InsertDSTable_BST(DT1, e->key)) {

			printf("\n插入元素后的动态查找表(中序遍历)\n");

			printf("学号 姓名 性别 年龄\n");

			TraversDSTable_InOrder(DT1);

		}

		else printf("当前要插入的记录已存在，禁止插入！\n");

		printf("\n请输入要插入的新记录(输入-1结束)\n学号 姓名 性别 年龄\n");
		
		scanf_s("%d %s %s %d", &e->key, e->name, e->sex, &e->age);

	}



	//删除动态查找表元素 

	printf("\n---元素删除---\n");

	printf("\n请输入要删除记录的学号(输入-1结束)：");

	scanf_s("%d", &key);

	while (key != -1) {

		if (DeleteDSTable_BST(DT1, key)) {

			printf("\n删除元素后的动态查找表(中序遍历)\n");

			printf("学号 姓名 性别 年龄\n");

			TraversDSTable_InOrder(DT1);

		}

		else printf("当前要删除的记录不存在！\n");

		printf("\n请输入要删除记录的学号(输入-1结束)："); //下一次删除 

		scanf_s("%d", &key);

	}





	return 1;

}