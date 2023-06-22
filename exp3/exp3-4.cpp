#define INFINITY 32767                   //表示最大值∞
#define MAX_VERTEX_NUM  20      //最大顶点数
#define MAX_EDGE_NUM  20         //最大边数
#include <stdlib.h>
#include <stdio.h>
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef enum { DG, DN, UDG, UDN } GraphKind;  //图的枚举类型
typedef int VRType;
typedef char InfoType;

typedef struct ArcCell {
    VRType  adj;          //对无权图用1或0表示；对带权图，则为权值类型。
    InfoType* info;       //该边或弧相关信息的指针（字符串） 
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef char VertexType;

typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];   //顶点数组，存放顶点信息
    AdjMatrix   arcs;                  //邻接矩阵
    int vexnum, arcnum;           //图中顶点总数与弧数
    GraphKind  kind;                 //图的种类标志
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
	//实现Prim算法
	//参数u是图中任一个顶点元素。要求输出每一条最小生成边和辅助数组closedge[]的变化过程。
	int i, j, k;

	//处理起始点u
	k = LocateVex(G, u);
	for (j = 0; j < G.vexnum; j++){
		if (j != k) {
			closedge[j] = { u,G.arcs[k][j].adj };
		}
	}
	closedge[k].lowcost = 0; //初始 

	for (i = 1; i < G.vexnum; i++) {
		k = Min(G);//找最短路径的顶点 

		printf("%c->%c,%d\n", closedge[k].adjvex, G.vexs[k], closedge[k].lowcost);//输出找到的最短路径顶，及路径权值 
		closedge[k].lowcost = 0;//将找到的最短路径顶点加入集合U中 

		for (j = 0; j < G.vexnum; j++){ //U中加入了新节点，可能出现新的最短路径，故更新closedge数组 
			if (G.arcs[k][j].adj < closedge[j].lowcost)//有更短路径出现时，将其替换进closedge数组 
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
	//实现Kruskal算法
	//要求输出排序后的edge数组，然后输出每一条最小生成边和连通分量数组cnvx[]的变化过程。
	//初始化edge数组
	
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
	//排序Edge数组
	for (int i = 0; i < G.arcnum - 1; i++) {
		for (int j = 0; j < G.arcnum - 1; j++) {
			if (Edge[j].lowcost > Edge[j + 1].lowcost) {
				temp = Edge[j];
				Edge[j] = Edge[j + 1];
				Edge[j + 1] = temp;
			}
		}
	}
	//初始化，指向自己
	for (int i = 0; i < G.vexnum; i++) {
		cnvx[i] = i;
	}
	int v1, v2, vs1, vs2;
	for (int i = 0; i < G.arcnum; i++) {
		//打印cnvx数组
		printf("\ncnvx数组：");
		for (int i = 0; i < G.vexnum; i++) {
			printf("%d ", cnvx[i]);
		}
		
		v1 = LocateVex(G, Edge[i].Head); //Head下标
		v2 = LocateVex(G, Edge[i].Tail); //Tail下标
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
	printf("\nPrim算法\n");
	MiniSpanTree_Prim(*G1,'A');
	printf("\nKruskal算法\n");
	MiniSpanTree_Kruskal(*G1);
}