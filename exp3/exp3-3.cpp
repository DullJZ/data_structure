#define MAX_VERTEX_NUM  20//最大顶点数
#define MVNum 20
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//队列
//引入队列，这里是顺序队列 
typedef struct
{
    int data[MVNum];//分配给队列一个数组空间 
    int front;//队列头 
    int rear;//队列尾 
}SqQueue;

void InitQueue(SqQueue& Q)//初始化队列 
{
    Q.front = Q.rear = 0;//使队列头和队列尾都为0 
}

void EnQueue(SqQueue& Q, int e)//入队 ，由于是循环队列，故少用一个元素空间，该函数在有MAXSIZE-1个元素时便已判断为满 
{
    if ((Q.rear + 1) % MVNum == Q.front)//判断队列是否为满 ，这里是循环队列队列满的条件是 (Q.rear+1)%MAXSIZE == Q.front
    {
        printf("队列已满！\n");
    }
    else
    {
        if (Q.rear == MVNum)//如果队尾超出最大值但队列又不满，便使其对最大值求余运算 
            Q.rear = Q.rear % MVNum;
        Q.data[Q.rear] = e;//使变量e的值入队 
        Q.rear++;//并使队尾加一 
    }
}

bool QueueEmpty(SqQueue Q)//队列判空操作 
{
    if (Q.front == Q.rear)//如果队列为空，返回true，否则返回false 
        return true;
    else
        return false;
}

int DeQueue(SqQueue& Q)//出队 
{
    int a = 0;
    if (QueueEmpty(Q))//首先判断队列是否为空，队列为空的条件是 Q.front == Q.rear
        printf("队列为空！\n");
    else
    {
        a = Q.data[Q.front];//导出队头元素数据 
        Q.front++;//使队头加一 
        if (!QueueEmpty(Q))//在队列非空的情况下，如果队头等于最大值，也对最大值做求余运算 
            Q.front = Q.front % MVNum;
    }
    return a;
}

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
    AdjList vertices;                   //图的顶点数组 
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
        ArcNode* p1 = G.vertices[i].firstarc;
        while (p1) {
            printf("%d ", p1->adjvex);
            if (G.kind == DN || G.kind == UDN) {
                printf("(%d) ", p1->weight);
            }
            p1 = p1->nextarc;
        }
        printf("\n");
    }
    return OK;
}

bool visited[MAX_VERTEX_NUM] = { false };

Status DFSTraverse(ALGraph G, int v) {
	//图的深度优先遍历
    visited[v] = true;
	ArcNode* p1 = G.vertices[v].firstarc;
	printf("%c ", G.vertices[v].data);
	while (p1){
		if (!visited[p1->adjvex]){
            DFSTraverse(G, p1->adjvex);
		}
		
		p1 = p1->nextarc;
	}
    return OK;
}

ArcNode* p;//创建一个全局变量，以便于进行查找 
int FirstAdjVex(ALGraph G, int u)//表示u的第一个邻接点 
{
    p = G.vertices[u].firstarc;//全局变量的赋值 
    if (p == NULL)//如果头结点的下一个结点为空，返回负数，否则返回p结点的值 
        return -1;
    else
        return p->adjvex;
}

int NextAdjVex(ALGraph G)//下一个邻接点 
{
    p = p->nextarc;//由于p为全局变量，这里直接指向下一个便是 
    if (p == NULL)//如果头结点的下一个结点为空，返回负数，否则返回p结点的值  
        return -1;
    else
        return p->adjvex;
}

Status BFSTraverse(ALGraph G, int v){
    //图的广度优先遍历
    int u;
    printf("%c ", G.vertices[v].data);
    visited[v] = true;//访问第v个顶点，并置访问标志数组相应分量值为true 
    SqQueue Q;
    InitQueue(Q);//引入队列，初始化 
    EnQueue(Q, v);//入队 
    while (!QueueEmpty(Q))//队列非空 
    {
        u = DeQueue(Q);//出队，别赋值给变量u 
        for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G))//依次检查u的所有邻接点w,w>=0表示存邻接点
            //函数FirstAdjVex(G,u)表示u的第一个邻接点，函数NextAdjVex(G)表示相对于w的下一个邻接点 
            if (!visited[w])//w为u的尚未访问的邻接点 
            {
                printf("%c ", G.vertices[w].data);
                visited[w] = true;//访问第w个顶点，并置访问标志数组相应分量值为true 
                EnQueue(Q, w);//w入队 
            }
    }
	return OK;
}

int main() {
    char vex[6] = { '0','1','2','3','4','5'};
    int arc[7][3] = { {'0','1',0},{'0','2',0},{'1','3',0},{'1','4',0},{'3','4',0},{'2','5',0},{'4','5',0} };
    ALGraph* G = (ALGraph*)malloc(sizeof(ALGraph));
    if (!G) {
        return OVERFLOW;
    }
    CreateALGraph(UDG, *G, 6, 7, vex, arc);
    OutALGraph(*G);
    printf("\nDFS:\n");
    DFSTraverse(*G, 0);
	//清空visited
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		visited[i] = false;
	}
	
	printf("\nBFS:\n");
	BFSTraverse(*G, 0);
    return 0;
}