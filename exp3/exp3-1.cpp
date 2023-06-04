#include<stdio.h>
#include<stdlib.h>
#define INFINITY 32767                   //��ʾ���ֵ��
#define MAX_VERTEX_NUM  20       //��󶥵���

#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE    100
typedef int Status;
typedef enum { DG, DN, UDG, UDN } GraphKind;  //ͼ��ö������ {����ͼ��������������ͼ��������}
typedef int VRType;
typedef char InfoType;
typedef struct ArcCell {
    VRType adj;          //����Ȩͼ��1��0��ʾ���Դ�Ȩͼ����ΪȨֵ���͡�
    InfoType* info;       //�ñ߻������Ϣ��ָ�루�ַ����� 
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef char VertexType;

typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];   //�������飬��Ŷ�����Ϣ
    AdjMatrix   arcs;                  //�ڽӾ���
    int vexnum, arcnum;           //ͼ�ж��������뻡��
    GraphKind  kind;                 //ͼ�������־
} MGraph;

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

Status VerDegree(MGraph G) {
	switch (G.kind){
	case DG:
	case DN: {
		//�������ͼG�и��������Ⱥͳ���
		int indegree[MAX_VERTEX_NUM] = { 0 };
		int outdegree[MAX_VERTEX_NUM] = { 0 };
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				if (G.arcs[i][j].adj != 0 && G.arcs[i][j].adj != INFINITY) {
					indegree[j]++;
					outdegree[i]++;
				}
			}
		}
		printf("������飺");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%d ", indegree[i]);
		}
		printf("\n");
		printf("�������飺");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%d ", outdegree[i]);
		}
		printf("\n");
		break;
	}
	case UDN:
	case UDG: {
		//�������ͼG�и�����Ķ�
		int degree[MAX_VERTEX_NUM] = { 0 };
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				if (G.arcs[i][j].adj != 0 && G.arcs[i][j].adj != INFINITY) {
					degree[i]++;
				}
			}
		}
		printf("�����飺");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%d ", degree[i]);
		}
		printf("\n");
		break;
	}
	}
	return OK;
}

int main() {
	MGraph* G1 = (MGraph*)malloc(sizeof(MGraph));
	MGraph* G2 = (MGraph*)malloc(sizeof(MGraph));
	MGraph* G3 = (MGraph*)malloc(sizeof(MGraph));
	MGraph* G4 = (MGraph*)malloc(sizeof(MGraph));
	if (!G1 || !G2 || !G3 || !G4) {
		printf("�ڴ����ʧ�ܣ�\n");
		exit(0);
	}
	char vex[4] = { '0','1','2','3' };
	//����ͼ
	int arc1[5][3] = { {'0','1',0},{'0','2',0},{'0','3',0},{'1','2',0},{'2','3',0} };
	CreateMGraph(UDG, *G1, 4, 5, vex, arc1);
	OutMGraph(*G1);
	VerDegree(*G1);
	printf("\n");
	//����ͼ
	int arc2[6][3] = { {'0','1',0},{'1','0',0},{'1','2',0},{'2','1',0},{'2','0',0},{'3','1',0} };
	CreateMGraph(DG, *G2, 4, 6, vex, arc2);
	OutMGraph(*G2);
	VerDegree(*G2);
	printf("\n");
	//������
	int arc3[4][3] = { {'0','1',56},{'0','2',34},{'0','3',78},{'2','3',25} };
	CreateMGraph(UDN, *G3, 4, 4, vex, arc3);
	OutMGraph(*G3);
	VerDegree(*G3);
	printf("\n");
	//������
	int arc4[3][3] = { {'0','2',50},{'2','0',64},{'1','2',45} };
	CreateMGraph(DN, *G4, 3, 3, vex, arc4);
	OutMGraph(*G4);
	VerDegree(*G4);
	return 0;
}