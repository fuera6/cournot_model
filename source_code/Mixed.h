/*
	������Ʈ ����: �̻��� �������� �����ϴ� ���� ��(Cournot model)�� �������� ��� Ǯ�� ����� ����: ť(Queue)�� ü�̴�(Chaining)�� �߽�����
	���ϸ�: Mixed.h
	�ۼ���: �뱸���а���б� 32�� 2�г� �輮��
	�ۼ��Ϸ���: 2020.7.6.
	�ۼ�����: �̻��� ������ ������ �����͵�� ���� ��(Cournot model)�� �ع��� �ڷᱸ���� �̿��Ͽ� �����ϰ��� �߱� ����
*/

#ifndef __MIXED_H__
#define __MIXED_H__

#define TRUE	1
#define FALSE	0

// CCW.c���� ���Ǵ� ���
#define counterclockwise	1
#define clockwise	-1
#define parralel	0

#define MAX(a,b)	(((a)>(b)) ? (a) : (b))
#define MIN(a,b)	(((a)<(b)) ? (a) : (b))


// ChainingBasedLinkedList.c ����ü
typedef struct _slotNode {
	double product;
	double profit;
	struct _slotNode* link;
} slotNode;

typedef struct _listNode {
	double product;
	struct _listNode* link;
	slotNode* head;
	slotNode* tail;
	int slotNodeNum;
} listNode;

typedef struct _chainingList_h {
	listNode* head;
	listNode* tail;
	int listNodeNum;
} chainingList_h;

// Queue.c ����ü
typedef struct _product {
	double product1;
	double product2;
} Product;

typedef struct _qnode
{
	Product data;
	struct _node* link;
} QNode;

typedef struct _queue
{
	QNode* front;
	QNode* rear;
} Queue;

// CCW.c ����ü
typedef struct _pos {
	double x_pos;
	double y_pos;
} Pos;


// ChainingBasedLinkedList.c �Լ�
chainingList_h* createChainingList_h(void);
int insertSlotNode(chainingList_h* L, double product_other, double product_mine, double profit_mine);
int deleteSlotNode(chainingList_h* L, double product_other, double product_mine);

// Queue.c �Լ�
Queue* QueueInit(void);
int isEmpty(Queue* Q);
void deleteQueue(Queue* Q);
void Enqueue(Queue* Q, Product data);
Product Dequeue(Queue* Q);
Product Peek(Queue* Q);

// Cournot.c �Լ�
chainingList_h* createPayoff(void);
void insertNewStrategy(chainingList_h* L, double product_other, double product_mine, double profit_mine);
void deleteStrategy(chainingList_h* L, double product_other, double product_mine);
Queue* makeBR2Queue(chainingList_h* L2);
Queue* makeBR1Queue(chainingList_h* L1);
void ShowCross(chainingList_h* L1, chainingList_h* L2);
void ShowPayoff(chainingList_h* L);

// CCW.c �Լ�
int CCWbaseCross(Pos A, Pos B, Pos C, Pos D);

#endif