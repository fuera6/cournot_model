/*
	프로젝트 주제: 이산적 선택지가 존재하는 쿠르노 모델(Cournot model)의 최적대응 기반 풀이 기법의 개발: 큐(Queue)와 체이닝(Chaining)을 중심으로
	파일명: Mixed.h
	작성자: 대구과학고등학교 32기 2학년 김석준
	작성완료일: 2020.7.6.
	작성이유: 이산적 변수로 구성된 데이터들로 쿠르노 모델(Cournot model)의 해법을 자료구조를 이용하여 제시하고자 했기 때문
*/

#ifndef __MIXED_H__
#define __MIXED_H__

#define TRUE	1
#define FALSE	0

// CCW.c에서 사용되는 상수
#define counterclockwise	1
#define clockwise	-1
#define parralel	0

#define MAX(a,b)	(((a)>(b)) ? (a) : (b))
#define MIN(a,b)	(((a)<(b)) ? (a) : (b))


// ChainingBasedLinkedList.c 구조체
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

// Queue.c 구조체
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

// CCW.c 구조체
typedef struct _pos {
	double x_pos;
	double y_pos;
} Pos;


// ChainingBasedLinkedList.c 함수
chainingList_h* createChainingList_h(void);
int insertSlotNode(chainingList_h* L, double product_other, double product_mine, double profit_mine);
int deleteSlotNode(chainingList_h* L, double product_other, double product_mine);

// Queue.c 함수
Queue* QueueInit(void);
int isEmpty(Queue* Q);
void deleteQueue(Queue* Q);
void Enqueue(Queue* Q, Product data);
Product Dequeue(Queue* Q);
Product Peek(Queue* Q);

// Cournot.c 함수
chainingList_h* createPayoff(void);
void insertNewStrategy(chainingList_h* L, double product_other, double product_mine, double profit_mine);
void deleteStrategy(chainingList_h* L, double product_other, double product_mine);
Queue* makeBR2Queue(chainingList_h* L2);
Queue* makeBR1Queue(chainingList_h* L1);
void ShowCross(chainingList_h* L1, chainingList_h* L2);
void ShowPayoff(chainingList_h* L);

// CCW.c 함수
int CCWbaseCross(Pos A, Pos B, Pos C, Pos D);

#endif