#define MAX_VERTEX_NUM  20//��󶥵���
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#include<stdio.h>
#include<stdlib.h>

typedef int Status;
typedef enum { DG, DN, UDG, UDN } GraphKind;  //ͼ������
typedef char VertexType; //�������ݵ�����(�ַ��� 

//��(��)����������� 
typedef struct ArcNode {
    int adjvex;       //�ñ�(��)������(ָ��)�Ķ����ڶ���������±�
    struct ArcNode* nextarc;       //ָ����һ����(��)��ָ��
    int weight;        //��(��)��Ȩֵ����Ȩͼ��ֵΪ0
}ArcNode;

//���������������� 
typedef struct VNode {
    VertexType  data;          //�������� 
    ArcNode* firstarc;         //ָ���һ�������ö���ı�(��)��ָ��
}VNode, AdjList[MAX_VERTEX_NUM];

//ͼ���ڽӱ��������� 
typedef  struct {
    AdjList   vertices;                   //ͼ�Ķ������� 
    int vexnum, arcnum;     //ͼ�Ķ������ͱ�(��)�� 
    GraphKind kind;                    //ͼ������ 
}ALGraph;

int LocateVex(ALGraph G, VertexType u) {
    /* ��ʼ����: ͼG����,u��G�ж�������ͬ����*/
    /* �������: ��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 */
    for (int i = 0; i < G.vexnum; ++i) {
        if (u == G.vertices[i].data) {
            return i;
        }
    }
    return -1;
}


Status CreateALGraph(GraphKind GKind, ALGraph& G, int vexnum, int arcnum, char* vexs, int arcs[][3]) {
    //��дһ���ܹ�����4�ֲ�ͬ����ͼ���ڽӱ�洢��ͨ�ú���
    G.kind = GKind;
    G.vexnum = vexnum;
    G.arcnum = arcnum;
    for (int i = 0; i < G.vexnum; i++) {
        G.vertices[i].data = vexs[i];
        G.vertices[i].firstarc = NULL;
    }
    switch (GKind) {
        case DG: { //����ͼ
            for (int k = 0; k < G.arcnum; k++) {
                int i = LocateVex(G, arcs[k][0]);
                int j = LocateVex(G, arcs[k][1]);
                ArcNode* p1 = (ArcNode*)malloc(sizeof(ArcNode));
                if (!p1) { return OVERFLOW; }
                p1->adjvex = j;
                p1->nextarc = G.vertices[i].firstarc;
                G.vertices[i].firstarc = p1;
            }
            break;
        }
        case DN: { //������
            for (int k = 0; k < G.arcnum; k++) {
                int i = LocateVex(G, arcs[k][0]);
                int j = LocateVex(G, arcs[k][1]);
                ArcNode* p1 = (ArcNode*)malloc(sizeof(ArcNode));
                if (!p1) { return OVERFLOW; }
                p1->adjvex = j;
                p1->nextarc = G.vertices[i].firstarc;
                G.vertices[i].firstarc = p1;
                p1->weight = arcs[k][2];
            }
            break;
        }
        case UDG: { //����ͼ
            for (int k = 0; k < G.arcnum; k++) {
                int i = LocateVex(G, arcs[k][0]);
                int j = LocateVex(G, arcs[k][1]);
                ArcNode* p1 = (ArcNode*)malloc(sizeof(ArcNode));
                if (!p1) { return OVERFLOW; }
                p1->adjvex = j;
                p1->nextarc = G.vertices[i].firstarc;
                G.vertices[i].firstarc = p1;
                ArcNode* p2 = (ArcNode*)malloc(sizeof(ArcNode));
                if (!p2) { return OVERFLOW; }
                p2->adjvex = i;
                p2->nextarc = G.vertices[j].firstarc;
                G.vertices[j].firstarc = p2;
            }
            break;
        }
        case UDN: { //������
            for (int k = 0; k < G.arcnum; k++) {
                int i = LocateVex(G, arcs[k][0]);
                int j = LocateVex(G, arcs[k][1]);
                ArcNode* p1 = (ArcNode*)malloc(sizeof(ArcNode));
                if (!p1) { return OVERFLOW; }
                p1->adjvex = j;
                p1->nextarc = G.vertices[i].firstarc;
                G.vertices[i].firstarc = p1;
                p1->weight = arcs[k][2];
                ArcNode* p2 = (ArcNode*)malloc(sizeof(ArcNode));
                if (!p2) { return OVERFLOW; }
                p2->adjvex = i;
                p2->nextarc = G.vertices[j].firstarc;
                G.vertices[j].firstarc = p2;
                p2->weight = arcs[k][2];
            }
            break;
        }
    }
    return OK;
}

Status OutALGraph(ALGraph G) {
    //���ͼG�Ķ�������Ԫ�غ��ڽӱ�ṹ���ݣ�������Ȩͼ��������Ȩֵ�����ű�ʾ��
    if (G.kind == DN) { printf("������\n"); }
	else if (G.kind == UDN) { printf("������\n"); }
	else if (G.kind == DG) { printf("����ͼ\n"); }
	else if (G.kind == UDG) { printf("����ͼ\n"); }
	
	for (int i = 0; i < G.vexnum; i++) {
		printf("%c ", G.vertices[i].data);
		ArcNode* p = G.vertices[i].firstarc;
		while (p) {
			printf("%d ", p->adjvex);
			if (G.kind == DN || G.kind == UDN) {
				printf("(%d) ", p->weight);
			}
			p = p->nextarc;
		}
		printf("\n");
	}
    return OK;
}

Status VerDegree(ALGraph G) {
	//���ͼG�и�����Ķȣ�����ͼ����Ⱥͳ��ȣ�
    switch (G.kind) {
    case DG:
    case DN: {
        //�������ͼG�и��������Ⱥͳ���
        int indegree[MAX_VERTEX_NUM] = { 0 };
        int outdegree[MAX_VERTEX_NUM] = { 0 };
		for (int i = 0; i < G.vexnum; i++) {
			ArcNode* p = G.vertices[i].firstarc;
			while (p) {
				outdegree[i]++;
				indegree[p->adjvex]++;
				p = p->nextarc;
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
			ArcNode* p = G.vertices[i].firstarc;
			while (p) {
				degree[i]++;
				p = p->nextarc;
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
    ALGraph* G1 = (ALGraph*)malloc(sizeof(ALGraph));
    ALGraph* G2 = (ALGraph*)malloc(sizeof(ALGraph));
    ALGraph* G3 = (ALGraph*)malloc(sizeof(ALGraph));
    ALGraph* G4 = (ALGraph*)malloc(sizeof(ALGraph));
    if (!G1 || !G2 || !G3 || !G4) {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(0);
    }
    char vex[4] = { '0','1','2','3' };
    //����ͼ
    int arc1[5][3] = { {'0','1',0},{'0','2',0},{'0','3',0},{'1','2',0},{'2','3',0} };
    CreateALGraph(UDG, *G1, 4, 5, vex, arc1);
    OutALGraph(*G1);
    VerDegree(*G1);
    printf("\n");
    //����ͼ
    int arc2[6][3] = { {'0','1',0},{'1','0',0},{'1','2',0},{'2','1',0},{'2','0',0},{'3','1',0} };
    CreateALGraph(DG, *G2, 4, 6, vex, arc2);
    OutALGraph(*G2);
    VerDegree(*G2);
    printf("\n");
    //������
    int arc3[4][3] = { {'0','1',56},{'0','2',34},{'0','3',78},{'2','3',25} };
    CreateALGraph(UDN, *G3, 4, 4, vex, arc3);
    OutALGraph(*G3);
    VerDegree(*G3);
    printf("\n");
    //������
    int arc4[3][3] = { {'0','2',50},{'2','0',64},{'1','2',45} };
    CreateALGraph(DN, *G4, 3, 3, vex, arc4);
    OutALGraph(*G4);
    VerDegree(*G4);
    return 0;
}