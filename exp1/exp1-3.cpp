#include <stdio.h>
#include <stdlib.h>

typedef int Status;         //声明函数类型名
#define STACK_INIT_SIZE    10
#define STACKINCREMENT  5
#define OK 1
#define ERROR   0
#define TRUE    1
#define FALSE    0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int SElemType;  //声明SElemType的类型

typedef struct {
    SElemType* base;  //顺序栈数据存储空间基址 
    SElemType* top;    //顺序栈栈顶指针 
    int stacksize;
}SqStack;  // SqStack为用户定义的顺序栈类型

#define MAXQSIZE 10    //队列的最大长度

typedef int QElemType;  //声明SElemType的类型

typedef struct {
    QElemType* base;    //初始化队列时动态分配存储空间的地址(数组名)
    int front;                 //头元素的下标变量
    int rear;                   //尾元素的下标变量
} SqQueue;   // SqQueue为用户定义的循环队列类型



//顺序栈基本操作函数的实现

Status InitStack(SqStack& S) {
    //利用malloc函数申请存储空间，构造一个空的顺序栈S，S的初始大小为STACK_INIT_SIZE。
    S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base) {
        return OVERFLOW;
    }
    S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status ClearStack(SqStack& S) {
    //将顺序栈数据清空。只需做S.top = S.base赋值操作即可。
	S.top = S.base;
    return OK;
}

int StackLength(SqStack S) {
	//返回L中数据元素个数。直接返回S.top-S.base的值即可。
    return S.top - S.base;
}

Status GetTop(SqStack S, SElemType& e) {
	//用e返回栈顶元素的值。 
    e = *(S.top-1);
    return OK;
}

Status Push(SqStack& S, SElemType e) {
	//将数据e进栈。
    if (StackLength(S) >= S.stacksize) { //栈满
        return ERROR;
    }
    *S.top = e;
    S.top++;
    return OK;
}

Status Pop(SqStack& S, SElemType& e) {
    //将栈顶元素出栈，用e返回其值。
    if (StackLength(S) == 0) { //栈空
        return ERROR;
    }
    e = *(S.top - 1);
    S.top--;
    return OK;
}

//循环队列基本操作函数的实现

Status InitQueue(SqQueue& Q) {
    //利用malloc函数申请存储空间，构造一个空的循环队列Q，Q的大小为MAXQSIZE。
    Q.base = (QElemType*)malloc(sizeof(QElemType) * MAXQSIZE);
    if (!Q.base) {
        return OVERFLOW;
    }
    Q.front = 0;
    Q.rear = 0;
    return OK;
}

Status ClearQueue(SqQueue& Q) {
    //将循环队列数据清空。 
    Q.base = 0;
    Q.rear = 0;
    return OK;
}

int QueueLength(SqQueue Q) {
    //返回Q中数据元素个数。
    return (Q.front - Q.rear + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(SqQueue& Q, QElemType e) {
    //数据e入队
    if ((Q.rear + 1) % MAXQSIZE == Q.front) {
        return ERROR;
    }
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue& Q, QElemType& e) {
    //数据出队，用e返回其值。
    if (Q.front == Q.rear) {
        return ERROR;
    }
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

int QueueEmpty(SqQueue Q) {
    //判队空
    if (Q.rear == Q.front) {
        return 1;
    }
    else {
        return 0;
    }
}

int QueueFull(SqQueue Q) {
    //判队满
    if (((Q.rear + 1) % MAXQSIZE) == Q.front) {
        return 1;
    }
    else {
        return 0;
    }
}

void Conversion(int m, int n) {
    //利用顺序栈的基本操作函数，编制一个将十进制整数m转换成n进制(n=2或8)整数的数制转换函数Conversion(m,n)
    //，并在函数中输出转换结果。
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
    //利用栈将将队列中的元素逆序重排，即队头元素变成队尾元素。
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
	//数制转换
    int m;
    printf("m = ");
    scanf("%d", &m);
    printf("二进制：");
    Conversion(m, 2);
    printf("八进制：");
    Conversion(m, 8);
	
	/*循环队列操作
    <1>连续入队9个整数后，显示队列Q的front和rear的值；
    <2>若再入队1个整数，显示此时队列的状态信息；
    <3>连续出队5个整数，再入队2个整数，显示此时的队列Q的长度与front和rear的值；
    <4>调用函数QueueReverse(Q)，将队列元素逆序重排，然后将队列元素出队并输出。*/
    SqQueue Q;
    InitQueue(Q);
    for (int i = 0; i < 9; i++) {
        EnQueue(Q, i);
    }
    printf("入队九个整数后，Q.front=%d，Q.rear=%d\n", Q.front, Q.rear);
    EnQueue(Q, 9);
    printf("再入队一个整数，Q.front=%d，Q.rear=%d\n", Q.front, Q.rear);
    for (int i = 0; i < 5; i++) {
        int t;
        DeQueue(Q, t);
    }
    EnQueue(Q, 22);
    EnQueue(Q, 33);
    printf("连续出队5个整数，再入队2个整数，Q.front=%d，Q.rear=%d\n", Q.front, Q.rear);
    QueueReverse(Q);
    printf("调用函数QueueReverse(Q)，将队列元素逆序重排\n");
    while (!QueueEmpty(Q)) {
        int t;
        DeQueue(Q, t);
        printf("%d ", t);
    }
}