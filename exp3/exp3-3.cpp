#define MAX_VERTEX_NUM  20//最大顶点数

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

