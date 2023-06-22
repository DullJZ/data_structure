#include <stdlib.h>
#include <stdio.h>
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2


typedef int Status;

typedef int KeyType;        //�ؼ��ֵ���������

//����Ԫ�أ���¼�������Ͷ���
typedef struct {
    KeyType  key;            //ѧ��(�ؼ���)
    const char* name;     //����
    const char* sex;         //�Ա� 
    int  age;                     //���� 
} RecordType;

//��̬���ұ�����Ͷ���
typedef struct {
    RecordType* Record;      //����Ԫ�ش洢�ռ�Ļ�ַ(һά������)
    int    length;             //��ĳ��ȣ�Ԫ�ظ�����
}SSTable;

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

int SearchSSTable_Seq(SSTable ST, KeyType key, int& c) {
	/*����keyΪҪ���ҵĹؼ��֣�����c������ҹ����йؼ��ֱȽϵĴ�����
	�����ҳɹ����������ظùؼ���Ԫ�����ڵ��±꣬���򣬲��Ҳ��ɹ�������0���С��ڱ�������-1���ޡ��ڱ�������*/
	ST.Record[0].key = key;
	int i;
	for (i = ST.length; ST.Record[i].key != key; i--) {
		c++;
	}
	return i;
}

Status SortSSTable(SSTable& ST) {
	//����̬���ұ���������Ԫ�ذ��ؼ��ִ�С���������������
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
	//����keyΪҪ���ҵĹؼ��֣�����c������ҹ����йؼ��ֱȽϵĴ�����
	//�����ҳɹ����������ظùؼ���Ԫ�����ڵ��±꣬���򣬲��Ҳ��ɹ�������-1��
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
	//������̬���ұ�ST1 
	CreateSSTable(ST1, n);
	printf("\nѧ������ľ�̬���ұ�\n");
	TraversSSTable(ST1);
	printf("---˳�����---\n");
	printf("\n������Ҫ���ҵ�ѧ�ţ�");
	scanf_s("%d", &key);

	while (key != -1) {
		i = SearchSSTable_Seq(ST1, key, c);
		if (i == 0)
			printf("��ǰҪ���ҵļ�¼�����ڣ�\n");
		else
			printf("ѧ�ţ�%2d\t������%s\t�Ա�%s\t���䣺%d\n", ST1.Record[i].key, ST1.Record[i].name, ST1.Record[i].sex, ST1.Record[i].age);
		printf("����ʱ�ȽϵĴ���=%d\n", c);
		c = 0;
		printf("\n������Ҫ���ҵ�ѧ�ţ�"); //��һ�β��� 
		scanf_s("%d", &key);
	}
	printf("\n˳����Ҹ��ؼ��ֵıȽϴ�����\n");

	total = 0;

	for (i = 1; i <= ST1.length; i++) {
		SearchSSTable_Seq(ST1, ST1.Record[i].key, c);
		total = total + c;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n", ST1.Record[i].key, c);
		c = 0;
	}

	printf("\n\n���ҳɹ���ƽ�����ҳ���ASL=%f\n", (float)total / ST1.length);
	printf("\n���Ҳ��ɹ���ƽ�����ҳ���ASL=%f\n", (float)ST1.length + 1);

	//���ұ����� 
	SortSSTable(ST1);
	printf("\nѧ������ľ�̬���ұ�\n");
	TraversSSTable(ST1);

	printf("---�۰����(�ǵݹ�)---\n");
	printf("\n������Ҫ���ҵ�ѧ�ţ�");
	scanf_s("%d",&key);
	while (key!=-1){
		i=SearchSSTable_Bin(ST1,key,c);
		if(i==-1)
			printf("��ǰҪ���ҵļ�¼�����ڣ�\n");
		else
			printf("ѧ�ţ�%2d\t������%s\t�Ա�%s\t���䣺%d\n", ST1.Record[i].key, ST1.Record[i].name, ST1.Record[i].sex, ST1.Record[i].age);
		printf("����ʱ�ȽϵĴ���=%d\n",c);
		printf("\n������Ҫ���ҵ�ѧ�ţ�"); //��һ�β���
		scanf_s("%d",&key);
	}
	printf("\n�۰���Ҹ��ؼ��ֵıȽϴ�����\n");
	total=0;
	for(i=1;i<=ST1.length;i++){
		c = 0;
		SearchSSTable_Bin(ST1,ST1.Record[i].key,c);
		total=total+c;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n",ST1.Record[i].key,c);
	}

	printf("\n\n���ҳɹ���ƽ�����ҳ���ASL=%f\n",(float)total/ST1.length);
	printf("\n�۰���Ҹ��ؼ��ֵıȽϴ�����\n");

	total=0;

	for(i=0;i<=ST1.length;i++){
		c = 0;
		if(i==0) SearchSSTable_Bin(ST1,4,c);
		else SearchSSTable_Bin(ST1,ST1.Record[i].key+1,c);
		total=total+c;
		printf("�ؼ���=%2d  �Ƚϴ���=%d\n",(i==0)?4:ST1.Record[i].key+1,c);
	}
	printf("\n���Ҳ��ɹ���ƽ�����ҳ���ASL=%f\n",(float)total/(ST1.length+1));

	return 0;
}