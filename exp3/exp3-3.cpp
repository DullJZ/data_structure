#define MAX_VERTEX_NUM  20//��󶥵���
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

//����
//������У�������˳����� 
typedef struct
{
    int data[MVNum];//���������һ������ռ� 
    int front;//����ͷ 
    int rear;//����β 
}SqQueue;

void InitQueue(SqQueue& Q)//��ʼ������ 
{
    Q.front = Q.rear = 0;//ʹ����ͷ�Ͷ���β��Ϊ0 
}

void EnQueue(SqQueue& Q, int e)//��� ��������ѭ�����У�������һ��Ԫ�ؿռ䣬�ú�������MAXSIZE-1��Ԫ��ʱ�����ж�Ϊ�� 
{
    if ((Q.rear + 1) % MVNum == Q.front)//�ж϶����Ƿ�Ϊ�� ��������ѭ�����ж������������� (Q.rear+1)%MAXSIZE == Q.front
    {
        printf("����������\n");
    }
    else
    {
        if (Q.rear == MVNum)//�����β�������ֵ�������ֲ�������ʹ������ֵ�������� 
            Q.rear = Q.rear % MVNum;
        Q.data[Q.rear] = e;//ʹ����e��ֵ��� 
        Q.rear++;//��ʹ��β��һ 
    }
}

bool QueueEmpty(SqQueue Q)//�����пղ��� 
{
    if (Q.front == Q.rear)//�������Ϊ�գ�����true�����򷵻�false 
        return true;
    else
        return false;
}

int DeQueue(SqQueue& Q)//���� 
{
    int a = 0;
    if (QueueEmpty(Q))//�����ж϶����Ƿ�Ϊ�գ�����Ϊ�յ������� Q.front == Q.rear
        printf("����Ϊ�գ�\n");
    else
    {
        a = Q.data[Q.front];//������ͷԪ������ 
        Q.front++;//ʹ��ͷ��һ 
        if (!QueueEmpty(Q))//�ڶ��зǿյ�����£������ͷ�������ֵ��Ҳ�����ֵ���������� 
            Q.front = Q.front % MVNum;
    }
    return a;
}

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
    AdjList vertices;                   //ͼ�Ķ������� 
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
	//ͼ��������ȱ���
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

ArcNode* p;//����һ��ȫ�ֱ������Ա��ڽ��в��� 
int FirstAdjVex(ALGraph G, int u)//��ʾu�ĵ�һ���ڽӵ� 
{
    p = G.vertices[u].firstarc;//ȫ�ֱ����ĸ�ֵ 
    if (p == NULL)//���ͷ������һ�����Ϊ�գ����ظ��������򷵻�p����ֵ 
        return -1;
    else
        return p->adjvex;
}

int NextAdjVex(ALGraph G)//��һ���ڽӵ� 
{
    p = p->nextarc;//����pΪȫ�ֱ���������ֱ��ָ����һ������ 
    if (p == NULL)//���ͷ������һ�����Ϊ�գ����ظ��������򷵻�p����ֵ  
        return -1;
    else
        return p->adjvex;
}

Status BFSTraverse(ALGraph G, int v){
    //ͼ�Ĺ�����ȱ���
    int u;
    printf("%c ", G.vertices[v].data);
    visited[v] = true;//���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue 
    SqQueue Q;
    InitQueue(Q);//������У���ʼ�� 
    EnQueue(Q, v);//��� 
    while (!QueueEmpty(Q))//���зǿ� 
    {
        u = DeQueue(Q);//���ӣ���ֵ������u 
        for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G))//���μ��u�������ڽӵ�w,w>=0��ʾ���ڽӵ�
            //����FirstAdjVex(G,u)��ʾu�ĵ�һ���ڽӵ㣬����NextAdjVex(G)��ʾ�����w����һ���ڽӵ� 
            if (!visited[w])//wΪu����δ���ʵ��ڽӵ� 
            {
                printf("%c ", G.vertices[w].data);
                visited[w] = true;//���ʵ�w�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue 
                EnQueue(Q, w);//w��� 
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
	//���visited
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		visited[i] = false;
	}
	
	printf("\nBFS:\n");
	BFSTraverse(*G, 0);
    return 0;
}