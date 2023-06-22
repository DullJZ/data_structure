#include <stdlib.h>
#include <stdio.h>
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2


typedef int Status;

typedef int KeyType;        //关键字的数据类型

//数据元素（记录）的类型定义
typedef struct {
    KeyType  key;            //学号(关键字)
    const char* name;     //姓名
    const char* sex;         //性别 
    int  age;                     //年龄 
} RecordType;

//静态查找表的类型定义
typedef struct {
    RecordType* Record;      //数据元素存储空间的基址(一维数组名)
    int    length;             //表的长度（元素个数）
}SSTable;

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

int SearchSSTable_Seq(SSTable ST, KeyType key, int& c) {
	/*参数key为要查找的关键字，参数c保存查找过程中关键字比较的次数。
	若查找成功，函数返回该关键字元素所在的下标，否则，查找不成功，返回0（有“哨兵”）或-1（无“哨兵”）。*/
	ST.Record[0].key = key;
	int i;
	for (i = ST.length; ST.Record[i].key != key; i--) {
		c++;
	}
	return i;
}

Status SortSSTable(SSTable& ST) {
	//将静态查找表所有数据元素按关键字大小递增排序（有序表）。
	RecordType temp;
	for (int i = 1; i < ST.length; i++)
	{
		for (int j = i + 1; j <= ST.length; j++)
		{
			if (ST.Record[i].key > ST.Record[j].key)
			{
				temp = ST.Record[i];
				ST.Record[i] = ST.Record[j];
				ST.Record[j] = temp;
			}
		}
	}
	return OK;
}

int SearchSSTable_Bin(SSTable ST, KeyType key, int& c) {
	//参数key为要查找的关键字，参数c保存查找过程中关键字比较的次数。
	//若查找成功，函数返回该关键字元素所在的下标，否则，查找不成功，返回-1。
	int low = 1, high = ST.length, mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		c++;
		if (ST.Record[mid].key == key)
			return mid;
		else if (ST.Record[mid].key > key)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

int main() {
	int i, key;
	int n = 11;
	int c = 0, total = 0;
	SSTable ST1;
	//创建静态查找表ST1 
	CreateSSTable(ST1, n);
	printf("\n学号无序的静态查找表\n");
	TraversSSTable(ST1);
	printf("---顺序查找---\n");
	printf("\n请输入要查找的学号：");
	scanf_s("%d", &key);

	while (key != -1) {
		i = SearchSSTable_Seq(ST1, key, c);
		if (i == 0)
			printf("当前要查找的记录不存在！\n");
		else
			printf("学号：%2d\t姓名：%s\t性别：%s\t年龄：%d\n", ST1.Record[i].key, ST1.Record[i].name, ST1.Record[i].sex, ST1.Record[i].age);
		printf("查找时比较的次数=%d\n", c);
		c = 0;
		printf("\n请输入要查找的学号："); //下一次查找 
		scanf_s("%d", &key);
	}
	printf("\n顺序查找各关键字的比较次数：\n");

	total = 0;

	for (i = 1; i <= ST1.length; i++) {
		SearchSSTable_Seq(ST1, ST1.Record[i].key, c);
		total = total + c;
		printf("关键字=%2d  比较次数=%d\n", ST1.Record[i].key, c);
		c = 0;
	}

	printf("\n\n查找成功的平均查找长度ASL=%f\n", (float)total / ST1.length);
	printf("\n查找不成功的平均查找长度ASL=%f\n", (float)ST1.length + 1);

	//查找表排序 
	SortSSTable(ST1);
	printf("\n学号有序的静态查找表\n");
	TraversSSTable(ST1);

	printf("---折半查找(非递归)---\n");
	printf("\n请输入要查找的学号：");
	scanf_s("%d",&key);
	while (key!=-1){
		i=SearchSSTable_Bin(ST1,key,c);
		if(i==-1)
			printf("当前要查找的记录不存在！\n");
		else
			printf("学号：%2d\t姓名：%s\t性别：%s\t年龄：%d\n", ST1.Record[i].key, ST1.Record[i].name, ST1.Record[i].sex, ST1.Record[i].age);
		printf("查找时比较的次数=%d\n",c);
		printf("\n请输入要查找的学号："); //下一次查找
		scanf_s("%d",&key);
	}
	printf("\n折半查找各关键字的比较次数：\n");
	total=0;
	for(i=1;i<=ST1.length;i++){
		c = 0;
		SearchSSTable_Bin(ST1,ST1.Record[i].key,c);
		total=total+c;
		printf("关键字=%2d  比较次数=%d\n",ST1.Record[i].key,c);
	}

	printf("\n\n查找成功的平均查找长度ASL=%f\n",(float)total/ST1.length);
	printf("\n折半查找各关键字的比较次数：\n");

	total=0;

	for(i=0;i<=ST1.length;i++){
		c = 0;
		if(i==0) SearchSSTable_Bin(ST1,4,c);
		else SearchSSTable_Bin(ST1,ST1.Record[i].key+1,c);
		total=total+c;
		printf("关键字=%2d  比较次数=%d\n",(i==0)?4:ST1.Record[i].key+1,c);
	}
	printf("\n查找不成功的平均查找长度ASL=%f\n",(float)total/(ST1.length+1));

	return 0;
}