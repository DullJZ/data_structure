#include<stdio.h>
#include<stdlib.h>
#define INFINITY 32767                   //表示最大值∞
#define MAX_VERTEX_NUM  20       //最大顶点数

#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE    100
typedef int Status;
typedef enum { DG, DN, UDG, UDN } GraphKind;  //图的枚举类型 {有向图，有向网，无向图，无向网}
typedef int VRType;
typedef char InfoType;
typedef struct ArcCell {
    VRType adj;          //对无权图用1或0表示；对带权图，则为权值类型。
    InfoType* info;       //该边或弧相关信息的指针（字符串） 
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef char VertexType;

typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];   //顶点数组，存放顶点信息
    AdjMatrix   arcs;                  //邻接矩阵
    int vexnum, arcnum;           //图中顶点总数与弧数
    GraphKind  kind;                 //图的种类标志
} MGraph;

int LocateVex(MGraph G, char u) {
	/* 初始条件: 图G存在,u和G中顶点有相同特征*/
	/* 操作结果: 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
	for (int i = 0; i < G.vexnum; ++i) {
		if (u == G.vexs[i]) {
			return i;
		}
	}
	return -1;
}


Status CreateMGraph(GraphKind GKind, MGraph& G, int vexnum, int arcnum, char* vexs, int arcs[][3]) {
	//编写一个能够创建4种不同类型图的邻接矩阵存储的通用函数
	//char *vexs: 顶点数组，存放图的顶点 
	//int *arcs:  边(弧)数组，每条边（弧）采用三元组形式存放(i, j, w)，分别表示边的邻接顶点和权值或弧的弧尾、弧头和权值，
	//            对于无权值的图，权值=1。该参数的实参用二维数组存储，形参用一维数组的形式访问。
	G.kind = GKind;
	G.vexnum = vexnum;
	G.arcnum = arcnum;
	for (int i = 0; i < vexnum; i++) {
		G.vexs[i] = vexs[i];
	}
	switch (GKind) {
	case DG: { //有向图
		//初始化，邻接矩阵置为0
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				G.arcs[i][j] = { 0,nullptr };
			}
		}
		//构造邻接矩阵
		for (int k = 0; k < arcnum; k++) {
			int i = LocateVex(G, arcs[k][0]);
			int j = LocateVex(G, arcs[k][1]);
			G.arcs[i][j].adj = 1;
		}
		break;
	}
	case DN: { //有向网
		//初始化，邻接矩阵置为无穷大
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				G.arcs[i][j] = { INFINITY,nullptr };
			}
		}
		//构造邻接矩阵
		for (int k = 0; k < arcnum; k++) {
			int i = LocateVex(G, arcs[k][0]);
			int j = LocateVex(G, arcs[k][1]);
			int w = arcs[k][2];
			G.arcs[i][j].adj = w;
		}
		break;
	}
	case UDG: { //无向图
		//初始化，邻接矩阵置为0
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				G.arcs[i][j] = { 0,nullptr };
			}
		}
		//构造邻接矩阵
		for (int k = 0; k < arcnum; k++) {
			int i = LocateVex(G, arcs[k][0]);
			int j = LocateVex(G, arcs[k][1]);
			G.arcs[i][j].adj = 1;
			G.arcs[j][i].adj = 1;
		}
		break;
	}
	case UDN: { //无向网
		//初始化，邻接矩阵置为无穷大
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				G.arcs[i][j] = { INFINITY,nullptr };
			}
		}
		//构造邻接矩阵
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
	//输出邻接矩阵G
	switch (G.kind) {
	case DG: { //有向图
		printf("有向图\n");
		printf("顶点数组：");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%c ", G.vexs[i]);
		}
		printf("\n");
		printf("邻接矩阵：\n");
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				printf("%d ", G.arcs[i][j].adj);
			}
			printf("\n");
		}
		break;
	}
	case DN: { //有向网
		printf("有向网\n");
		printf("顶点数组：");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%c ", G.vexs[i]);
		}
		printf("\n");
		printf("邻接矩阵：\n");
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
		printf("无向图\n");
		printf("顶点数组：");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%c ", G.vexs[i]);
		}
		printf("\n");
		printf("邻接矩阵：\n");
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				printf("%d ", G.arcs[i][j].adj);
			}
			printf("\n");
		}
		break;
	}
	case UDN: {
		printf("无向网\n");
		printf("顶点数组：");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%c ", G.vexs[i]);
		}
		printf("\n");
		printf("邻接矩阵：\n");
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
		//输出有向图G中各顶点的入度和出度
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
			for (int j = 0; j < G.vexnum; j++) {
				if (G.arcs[i][j].adj != 0 && G.arcs[i][j].adj != INFINITY) {
					degree[i]++;
				}
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
	MGraph* G1 = (MGraph*)malloc(sizeof(MGraph));
	MGraph* G2 = (MGraph*)malloc(sizeof(MGraph));
	MGraph* G3 = (MGraph*)malloc(sizeof(MGraph));
	MGraph* G4 = (MGraph*)malloc(sizeof(MGraph));
	if (!G1 || !G2 || !G3 || !G4) {
		printf("内存分配失败！\n");
		exit(0);
	}
	char vex[4] = { '0','1','2','3' };
	//无向图
	int arc1[5][3] = { {'0','1',0},{'0','2',0},{'0','3',0},{'1','2',0},{'2','3',0} };
	CreateMGraph(UDG, *G1, 4, 5, vex, arc1);
	OutMGraph(*G1);
	VerDegree(*G1);
	printf("\n");
	//有向图
	int arc2[6][3] = { {'0','1',0},{'1','0',0},{'1','2',0},{'2','1',0},{'2','0',0},{'3','1',0} };
	CreateMGraph(DG, *G2, 4, 6, vex, arc2);
	OutMGraph(*G2);
	VerDegree(*G2);
	printf("\n");
	//无向网
	int arc3[4][3] = { {'0','1',56},{'0','2',34},{'0','3',78},{'2','3',25} };
	CreateMGraph(UDN, *G3, 4, 4, vex, arc3);
	OutMGraph(*G3);
	VerDegree(*G3);
	printf("\n");
	//有向网
	int arc4[3][3] = { {'0','2',50},{'2','0',64},{'1','2',45} };
	CreateMGraph(DN, *G4, 3, 3, vex, arc4);
	OutMGraph(*G4);
	VerDegree(*G4);
	return 0;
}