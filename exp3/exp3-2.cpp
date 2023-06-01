#define MAX_VERTEX_NUM  20//最大顶点数
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#include<stdio.h>
#include<stdlib.h>

typedef int Status;
typedef enum { DG, DN, UDG, UDN } GraphKind;  //图的类型
typedef char VertexType; //顶点数据的类型(字符） 

//边(弧)结点数据类型 
typedef struct ArcNode {
    int adjvex;       //该边(弧)所依附(指向)的顶点在顶点数组的下标
    struct ArcNode* nextarc;       //指向下一条边(弧)的指针
    int weight;        //边(弧)的权值，无权图其值为0
}ArcNode;

//顶点数组数据类型 
typedef struct VNode {
    VertexType  data;          //顶点数据 
    ArcNode* firstarc;         //指向第一条依附该顶点的边(弧)的指针
}VNode, AdjList[MAX_VERTEX_NUM];

//图的邻接表数据类型 
typedef  struct {
    AdjList   vertices;                   //图的顶点数组 
    int vexnum, arcnum;     //图的顶点数和边(弧)数 
    GraphKind kind;                    //图的类型 
}ALGraph;

int LocateVex(ALGraph G, VertexType u) {
    /* 初始条件: 图G存在,u和G中顶点有相同特征*/
    /* 操作结果: 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
    for (int i = 0; i < G.vexnum; ++i) {
        if (u == G.vertices[i].data) {
            return i;
        }
    }
    return -1;
}


Status CreateALGraph(GraphKind GKind, ALGraph& G, int vexnum, int arcnum, char* vexs, int arcs[][3]) {
    //编写一个能够创建4种不同类型图的邻接表存储的通用函数
    G.kind = GKind;
    G.vexnum = vexnum;
    G.arcnum = arcnum;
    for (int i = 0; i < G.vexnum; i++) {
        G.vertices[i].data = vexs[i];
        G.vertices[i].firstarc = NULL;
    }
    switch (GKind) {
        case DG: { //有向图
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
        case DN: { //有向网
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
        case UDG: { //无向图
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
        case UDN: { //无向网
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
    //输出图G的顶点数组元素和邻接表结构数据，对于有权图（网），权值加括号表示。
    if (G.kind == DN) { printf("有向网\n"); }
	else if (G.kind == UDN) { printf("无向网\n"); }
	else if (G.kind == DG) { printf("有向图\n"); }
	else if (G.kind == UDG) { printf("无向图\n"); }
	
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
	//输出图G中各顶点的度（有向图分入度和出度）
    switch (G.kind) {
    case DG:
    case DN: {
        //输出有向图G中各顶点的入度和出度
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
        printf("入度数组：");
        for (int i = 0; i < G.vexnum; i++) {
            printf("%d ", indegree[i]);
        }
        printf("\n");
        printf("出度数组：");
        for (int i = 0; i < G.vexnum; i++) {
            printf("%d ", outdegree[i]);
        }
        printf("\n");
        break;
    }
    case UDN:
    case UDG: {
        //输出无向图G中各顶点的度
        int degree[MAX_VERTEX_NUM] = { 0 };
		for (int i = 0; i < G.vexnum; i++) {
			ArcNode* p = G.vertices[i].firstarc;
			while (p) {
				degree[i]++;
				p = p->nextarc;
			}
		}
        printf("度数组：");
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
        printf("内存分配失败！\n");
        exit(0);
    }
    char vex[4] = { '0','1','2','3' };
    //无向图
    int arc1[5][3] = { {'0','1',0},{'0','2',0},{'0','3',0},{'1','2',0},{'2','3',0} };
    CreateALGraph(UDG, *G1, 4, 5, vex, arc1);
    OutALGraph(*G1);
    VerDegree(*G1);
    printf("\n");
    //有向图
    int arc2[6][3] = { {'0','1',0},{'1','0',0},{'1','2',0},{'2','1',0},{'2','0',0},{'3','1',0} };
    CreateALGraph(DG, *G2, 4, 6, vex, arc2);
    OutALGraph(*G2);
    VerDegree(*G2);
    printf("\n");
    //无向网
    int arc3[4][3] = { {'0','1',56},{'0','2',34},{'0','3',78},{'2','3',25} };
    CreateALGraph(UDN, *G3, 4, 4, vex, arc3);
    OutALGraph(*G3);
    VerDegree(*G3);
    printf("\n");
    //有向网
    int arc4[3][3] = { {'0','2',50},{'2','0',64},{'1','2',45} };
    CreateALGraph(DN, *G4, 3, 3, vex, arc4);
    OutALGraph(*G4);
    VerDegree(*G4);
    return 0;
}