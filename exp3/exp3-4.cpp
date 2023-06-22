#define INFINITY 32767                   //��ʾ���ֵ��
#define MAX_VERTEX_NUM  20      //��󶥵���
#define MAX_EDGE_NUM  20         //������
#include <stdlib.h>
#include <stdio.h>
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef enum { DG, DN, UDG, UDN } GraphKind;  //ͼ��ö������
typedef int VRType;
typedef char InfoType;

typedef struct ArcCell {
    VRType  adj;          //����Ȩͼ��1��0��ʾ���Դ�Ȩͼ����ΪȨֵ���͡�
    InfoType* info;       //�ñ߻������Ϣ��ָ�루�ַ����� 
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef char VertexType;

typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];   //�������飬��Ŷ�����Ϣ
    AdjMatrix   arcs;                  //�ڽӾ���
    int vexnum, arcnum;           //ͼ�ж��������뻡��
    GraphKind  kind;                 //ͼ�������־
} MGraph;

struct {
	VertexType adjvex;
	int lowcost;
}closedge[MAX_VERTEX_NUM];

struct {
	VertexType Head;
	VertexType Tail;
	int lowcost;
}Edge[MAX_EDGE_NUM],temp;

int LocateVex(MGraph G, char u) {
	/* ��ʼ����: ͼG����,u��G�ж�������ͬ����*/
	/* �������: ��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 */
	for (int i = 0; i < G.vexnum; ++i) {
		if (u == G.vexs[i]) {
			return i;
		}
	}
	return -1;
}

Status CreateMGraph(GraphKind GKind, MGraph& G, int vexnum, int arcnum, char* vexs, int arcs[][3]) {
	//��дһ���ܹ�����4�ֲ�ͬ����ͼ���ڽӾ���洢��ͨ�ú���
	//char *vexs: �������飬���ͼ�Ķ��� 
	//int *arcs:  ��(��)���飬ÿ���ߣ�����������Ԫ����ʽ���(i, j, w)���ֱ��ʾ�ߵ��ڽӶ����Ȩֵ�򻡵Ļ�β����ͷ��Ȩֵ��
	//            ������Ȩֵ��ͼ��Ȩֵ=1���ò�����ʵ���ö�ά����洢���β���һά�������ʽ���ʡ�
	G.kind = GKind;
	G.vexnum = vexnum;
	G.arcnum = arcnum;
	for (int i = 0; i < vexnum; i++) {
		G.vexs[i] = vexs[i];
	}
	switch (GKind) {
	case DG: { //����ͼ
		//��ʼ�����ڽӾ�����Ϊ0
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				G.arcs[i][j] = { 0,nullptr };
			}
		}
		//�����ڽӾ���
		for (int k = 0; k < arcnum; k++) {
			int i = LocateVex(G, arcs[k][0]);
			int j = LocateVex(G, arcs[k][1]);
			G.arcs[i][j].adj = 1;
		}
		break;
	}
	case DN: { //������
		//��ʼ�����ڽӾ�����Ϊ�����
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				G.arcs[i][j] = { INFINITY,nullptr };
			}
		}
		//�����ڽӾ���
		for (int k = 0; k < arcnum; k++) {
			int i = LocateVex(G, arcs[k][0]);
			int j = LocateVex(G, arcs[k][1]);
			int w = arcs[k][2];
			G.arcs[i][j].adj = w;
		}
		break;
	}
	case UDG: { //����ͼ
		//��ʼ�����ڽӾ�����Ϊ0
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				G.arcs[i][j] = { 0,nullptr };
			}
		}
		//�����ڽӾ���
		for (int k = 0; k < arcnum; k++) {
			int i = LocateVex(G, arcs[k][0]);
			int j = LocateVex(G, arcs[k][1]);
			G.arcs[i][j].adj = 1;
			G.arcs[j][i].adj = 1;
		}
		break;
	}
	case UDN: { //������
		//��ʼ�����ڽӾ�����Ϊ�����
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				G.arcs[i][j] = { INFINITY,nullptr };
			}
		}
		//�����ڽӾ���
		for (int k = 0; k < arcnum; k++) {
			int i = LocateVex(G, arcs[k][0]);
			int j = LocateVex(G, arcs[k][1]);
			int w = arcs[k][2];
			G.arcs[i][j].adj = w;
			G.arcs[j][i].adj = w;
		}
		break;
	}		
	}
	return OK;
}

Status OutMGraph(MGraph G) {
	//����ڽӾ���G
	switch (G.kind) {
	case DG: { //����ͼ
		printf("����ͼ\n");
		printf("�������飺");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%c ", G.vexs[i]);
		}
		printf("\n");
		printf("�ڽӾ���\n");
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				printf("%d ", G.arcs[i][j].adj);
			}
			printf("\n");
		}
		break;
	}
	case DN: { //������
		printf("������\n");
		printf("�������飺");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%c ", G.vexs[i]);
		}
		printf("\n");
		printf("�ڽӾ���\n");
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				printf("%-5d ", G.arcs[i][j].adj);
			}
			printf("\n");
		}
		break;
		return OK;
	}
	case UDG: {
		printf("����ͼ\n");
		printf("�������飺");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%c ", G.vexs[i]);
		}
		printf("\n");
		printf("�ڽӾ���\n");
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				printf("%d ", G.arcs[i][j].adj);
			}
			printf("\n");
		}
		break;
	}
	case UDN: {
		printf("������\n");
		printf("�������飺");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%c ", G.vexs[i]);
		}
		printf("\n");
		printf("�ڽӾ���\n");
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				printf("%-5d ", G.arcs[i][j].adj);
			}
			printf("\n");
		}
		break;
	}
	}
	return OK;
}

int Min(MGraph G)
{
	int i, j;
	int min, loc=0;

	min = INFINITY;
	for (i = 1; i < G.vexnum; i++)
	{
		if (min > closedge[i].lowcost && closedge[i].lowcost != 0)
		{
			min = closedge[i].lowcost;
			loc = i;
		}
	}
	return loc;
}

Status MiniSpanTree_Prim(MGraph G, VertexType u) {
	//ʵ��Prim�㷨
	//����u��ͼ����һ������Ԫ�ء�Ҫ�����ÿһ����С���ɱߺ͸�������closedge[]�ı仯���̡�
	int i, j, k;

	//������ʼ��u
	k = LocateVex(G, u);
	for (j = 0; j < G.vexnum; j++){
		if (j != k) {
			closedge[j] = { u,G.arcs[k][j].adj };
		}
	}
	closedge[k].lowcost = 0; //��ʼ 

	for (i = 1; i < G.vexnum; i++) {
		k = Min(G);//�����·���Ķ��� 

		printf("%c->%c,%d\n", closedge[k].adjvex, G.vexs[k], closedge[k].lowcost);//����ҵ������·��������·��Ȩֵ 
		closedge[k].lowcost = 0;//���ҵ������·��������뼯��U�� 

		for (j = 0; j < G.vexnum; j++){ //U�м������½ڵ㣬���ܳ����µ����·�����ʸ���closedge���� 
			if (G.arcs[k][j].adj < closedge[j].lowcost)//�и���·������ʱ�������滻��closedge���� 
			{
				closedge[j].lowcost = G.arcs[k][j].adj;
				closedge[j].adjvex = G.vexs[k];
			}
		}
	}
	return OK;
}

int cnvx[MAX_EDGE_NUM];

Status MiniSpanTree_Kruskal(MGraph G) {
	//ʵ��Kruskal�㷨
	//Ҫ�����������edge���飬Ȼ�����ÿһ����С���ɱߺ���ͨ��������cnvx[]�ı仯���̡�
	//��ʼ��edge����
	
	int index = 0;
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = i + 1; j < G.vexnum; j++) {
			if (G.arcs[i][j].adj != INFINITY) {
				Edge[index].Head = G.vexs[i];
				Edge[index].Tail = G.vexs[j];
				Edge[index].lowcost = G.arcs[i][j].adj;
				index++;
			}

		}
	}
	//����Edge����
	for (int i = 0; i < G.arcnum - 1; i++) {
		for (int j = 0; j < G.arcnum - 1; j++) {
			if (Edge[j].lowcost > Edge[j + 1].lowcost) {
				temp = Edge[j];
				Edge[j] = Edge[j + 1];
				Edge[j + 1] = temp;
			}
		}
	}
	//��ʼ����ָ���Լ�
	for (int i = 0; i < G.vexnum; i++) {
		cnvx[i] = i;
	}
	int v1, v2, vs1, vs2;
	for (int i = 0; i < G.arcnum; i++) {
		//��ӡcnvx����
		printf("\ncnvx���飺");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%d ", cnvx[i]);
		}
		
		v1 = LocateVex(G, Edge[i].Head); //Head�±�
		v2 = LocateVex(G, Edge[i].Tail); //Tail�±�
		vs1 = cnvx[v1];
		vs2 = cnvx[v2];
		if (vs1 != vs2) {
			printf("%c->%c,%d\n", Edge[i].Head, Edge[i].Tail, Edge[i].lowcost);
			for (int j = 0; j < G.vexnum; j++) {
				if (cnvx[j] == vs2) {
					cnvx[j] = vs1;
				}
			}
		}
	}
	return OK;
}

int main() {
	MGraph* G1 = (MGraph*)malloc(sizeof(MGraph));
	if (!G1) {
		return ERROR;
	}
	char vex[6] = { 'A','B','C','D','E','F' };
	int arc[10][3] = { {'A','B',10},{'A','E',15},{'A','C',12},{'B','C',7},{'B','D',5},{'B','F',6},{'C','E',12},{'C','F',8},{'D','F',6},{'E','F',10} };
	CreateMGraph(UDN, *G1, 6, 10, vex, arc);
	OutMGraph(*G1);
	printf("\nPrim�㷨\n");
	MiniSpanTree_Prim(*G1,'A');
	printf("\nKruskal�㷨\n");
	MiniSpanTree_Kruskal(*G1);
}