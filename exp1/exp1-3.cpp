#include <stdio.h>
#include <stdlib.h>

typedef int Status;         //��������������
#define STACK_INIT_SIZE    10
#define STACKINCREMENT  5
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int SElemType;  //����SElemType������

typedef struct {
    SElemType* base;  //˳��ջ���ݴ洢�ռ��ַ 
    SElemType* top;    //˳��ջջ��ָ�� 
    int stacksize;
}SqStack;  // SqStackΪ�û������˳��ջ����

#define MAXQSIZE 10    //���е���󳤶�

typedef int QElemType;  //����SElemType������

typedef struct {
    QElemType* base;    //��ʼ������ʱ��̬����洢�ռ�ĵ�ַ(������)
    int front;                 //ͷԪ�ص��±����
    int rear;                   //βԪ�ص��±����
} SqQueue;   // SqQueueΪ�û������ѭ����������



//˳��ջ��������������ʵ��

Status InitStack(SqStack& S) {
    //����malloc��������洢�ռ䣬����һ���յ�˳��ջS��S�ĳ�ʼ��СΪSTACK_INIT_SIZE��
    S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base) {
        return OVERFLOW;
    }
    S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status ClearStack(SqStack& S) {
    //��˳��ջ������ա�ֻ����S.top = S.base��ֵ�������ɡ�
	S.top = S.base;
    return OK;
}

int StackLength(SqStack S) {
	//����L������Ԫ�ظ�����ֱ�ӷ���S.top-S.base��ֵ���ɡ�
    return S.top - S.base;
}

Status GetTop(SqStack S, SElemType& e) {
	//��e����ջ��Ԫ�ص�ֵ�� 
    e = *(S.top-1);
    return OK;
}

Status Push(SqStack& S, SElemType e) {
	//������e��ջ��
    if (StackLength(S) >= S.stacksize) { //ջ��
        return ERROR;
    }
    *S.top = e;
    S.top++;
    return OK;
}

Status Pop(SqStack& S, SElemType& e) {
    //��ջ��Ԫ�س�ջ����e������ֵ��
    if (StackLength(S) == 0) { //ջ��
        return ERROR;
    }
    e = *(S.top - 1);
    S.top--;
    return OK;
}

//ѭ�����л�������������ʵ��

Status InitQueue(SqQueue& Q) {
    //����malloc��������洢�ռ䣬����һ���յ�ѭ������Q��Q�Ĵ�СΪMAXQSIZE��
    Q.base = (QElemType*)malloc(sizeof(QElemType) * MAXQSIZE);
    if (!Q.base) {
        return OVERFLOW;
    }
    Q.front = 0;
    Q.rear = 0;
    return OK;
}

Status ClearQueue(SqQueue& Q) {
    //��ѭ������������ա� 
    Q.base = 0;
    Q.rear = 0;
    return OK;
}

int QueueLength(SqQueue Q) {
    //����Q������Ԫ�ظ�����
    return (Q.front - Q.rear + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(SqQueue& Q, QElemType e) {
    //����e���
    if ((Q.rear + 1) % MAXQSIZE == Q.front) {
        return ERROR;
    }
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue& Q, QElemType& e) {
    //���ݳ��ӣ���e������ֵ��
    if (Q.front == Q.rear) {
        return ERROR;
    }
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

int QueueEmpty(SqQueue Q) {
    //�жӿ�
    if (Q.rear == Q.front) {
        return 1;
    }
    else {
        return 0;
    }
}

int QueueFull(SqQueue Q) {
    //�ж���
    if (((Q.rear + 1) % MAXQSIZE) == Q.front) {
        return 1;
    }
    else {
        return 0;
    }
}

void Conversion(int m, int n) {
    //����˳��ջ�Ļ�����������������һ����ʮ��������mת����n����(n=2��8)����������ת������Conversion(m,n)
    //�����ں��������ת�������
    SqStack S;
	InitStack(S);
    while (m) {
        Push(S, m % n);
        m = m / n;
    }
    while (StackLength(S)) {
        SElemType t;
        Pop(S, t);
        printf("%d", t);
    }
    printf("\n");
	
}

void QueueReverse(SqQueue Q) {
    //����ջ���������е�Ԫ���������ţ�����ͷԪ�ر�ɶ�βԪ�ء�
    SqStack S;
    InitStack(S);
    while(!QueueEmpty(Q)){
        int t;
        DeQueue(Q, t);
        Push(S, t);
    }
    while (StackLength(S)) {
        int t;
        Pop(S, t);
        EnQueue(Q, t);
    }
}

int main(void) {
	//����ת��
    int m;
    printf("m = ");
    scanf("%d", &m);
    printf("�����ƣ�");
    Conversion(m, 2);
    printf("�˽��ƣ�");
    Conversion(m, 8);
	
	/*ѭ�����в���
    <1>�������9����������ʾ����Q��front��rear��ֵ��
    <2>�������1����������ʾ��ʱ���е�״̬��Ϣ��
    <3>��������5�������������2����������ʾ��ʱ�Ķ���Q�ĳ�����front��rear��ֵ��
    <4>���ú���QueueReverse(Q)��������Ԫ���������ţ�Ȼ�󽫶���Ԫ�س��Ӳ������*/
    SqQueue Q;
    InitQueue(Q);
    for (int i = 0; i < 9; i++) {
        EnQueue(Q, i);
    }
    printf("��ӾŸ�������Q.front=%d��Q.rear=%d\n", Q.front, Q.rear);
    EnQueue(Q, 9);
    printf("�����һ��������Q.front=%d��Q.rear=%d\n", Q.front, Q.rear);
    for (int i = 0; i < 5; i++) {
        int t;
        DeQueue(Q, t);
    }
    EnQueue(Q, 22);
    EnQueue(Q, 33);
    printf("��������5�������������2��������Q.front=%d��Q.rear=%d\n", Q.front, Q.rear);
    QueueReverse(Q);
    printf("���ú���QueueReverse(Q)��������Ԫ����������\n");
    while (!QueueEmpty(Q)) {
        int t;
        DeQueue(Q, t);
        printf("%d ", t);
    }
}