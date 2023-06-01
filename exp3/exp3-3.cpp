#define MAX_VERTEX_NUM  20//��󶥵���

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

