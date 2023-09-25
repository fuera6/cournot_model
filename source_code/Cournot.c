/*
	프로젝트 주제: 이산적 선택지가 존재하는 쿠르노 모델(Cournot model)의 최적대응 기반 풀이 기법의 개발: 큐(Queue)와 체이닝(Chaining)을 중심으로
	파일명: Cournot.c
	작성자: 대구과학고등학교 32기 2학년 김석준
	작성완료일: 2020.7.6.
	작성이유: 이산적 변수로 구성된 데이터들로 쿠르노 모델(Cournot model)의 해법을 자료구조를 이용하여 제시하고자 했기 때문
*/

#include <stdio.h>
#include "Mixed.h"

// 체이닝 리스트 기반 보수행렬 할당
chainingList_h* createPayoff(void) {
	chainingList_h* payoff = createChainingList_h();
	return payoff;
}

// 새로운 전략쌍 삽입
void insertNewStrategy(chainingList_h* L, double product_other, double product_mine, double profit_mine) {
	int success;
	success = insertSlotNode(L, product_other, product_mine, profit_mine);
	if (success) {
		printf("\n");
		printf("저장에 성공하였습니다.\n");
	}
	else {
		printf("\n");
		printf("저장에 실패하였습니다. 이미 동일 조건의 데이터가 저장되어 있습니다.\n");
	}
}

// 전략쌍 삭제
void deleteStrategy(chainingList_h* L, double product_other, double product_mine) {
	int success;
	success = deleteSlotNode(L, product_other, product_mine);
	if (success) {
		printf("\n");
		printf("삭제에 성공하였습니다.\n");
	}
	else {
		printf("\n");
		printf("삭제에 실패하였습니다. 현재 저장된 데이터가 아닙니다.\n");
	}
}

// 체이닝 리스트의 product의 크기순대로 listNode를 정렬
void SortListNode(chainingList_h* L) {
	listNode *startNode, *tempNode;
	double tempProduct;
	int tempNum;
	slotNode* tempSlot;

	startNode = L->head;
	if (startNode == NULL)	return;
	else {
		while (startNode->link != NULL) {
			tempNode = startNode;
			while (tempNode->link != NULL) {
				if (tempNode->product > tempNode->link->product) {
					tempProduct = tempNode->product;
					tempNode->product = tempNode->link->product;
					tempNode->link->product = tempProduct;

				    tempNum = tempNode->slotNodeNum;
					tempNode->slotNodeNum = tempNode->link->slotNodeNum;
					tempNode->link->slotNodeNum = tempNum;

					tempSlot = tempNode->head;
					tempNode->head = tempNode->link->head;
					tempNode->link->head = tempSlot;
					tempSlot = tempNode->tail;
					tempNode->tail = tempNode->link->tail;
					tempNode->link->tail = tempSlot;
				}
				tempNode = tempNode->link;
			}
			startNode = startNode->link;
		}
	}
}

// player2의 최적대응시 생산량 순서쌍을 노드(QNode)로 갖는 큐(Queue) 생성
Queue* makeBR2Queue(chainingList_h* L2) {
	Queue* q2;
	listNode *tempNode;
	slotNode *tempSlot, *maxprofitSlot;
	Product new;

	q2 = QueueInit();
	SortListNode(L2);

	tempNode = L2->head;
	while (tempNode != NULL) {
		tempSlot = tempNode->head;
		maxprofitSlot = tempSlot;
		while (tempSlot != NULL) {
			if (tempSlot->profit > maxprofitSlot->profit) {
				maxprofitSlot = tempSlot;
			}
			tempSlot = tempSlot->link;
		}
		new.product1 = tempNode->product;
		new.product2 = maxprofitSlot->product;
		Enqueue(q2, new);
		tempNode = tempNode->link;
	}
	return q2;
}

// player1의 최적대응시 생산량 순서쌍을 노드(QNode)로 갖는 큐(Queue) 생성
Queue* makeBR1Queue(chainingList_h* L1) {
	Queue* q1;
	listNode* tempNode;
	slotNode* tempSlot, * maxprofitSlot;
	Product new;

	q1 = QueueInit();
	SortListNode(L1);

	tempNode = L1->head;
	while (tempNode != NULL) {
		tempSlot = tempNode->head;
		maxprofitSlot = tempSlot;
		while (tempSlot != NULL) {
			if (tempSlot->profit > maxprofitSlot->profit) {
				maxprofitSlot = tempSlot;
			}
			tempSlot = tempSlot->link;
		}
		new.product2 = tempNode->product;
		new.product1 = maxprofitSlot->product;
		Enqueue(q1, new);
		tempNode = tempNode->link;
	}
	return q1;
}

// CCW 알고리즘으로 교점의 존재성을 파악하고 존재할 경우 이를 출력하는 함수
void ShowCross(chainingList_h* L1, chainingList_h* L2) {
	int i, j;
	Queue* q1, * q2;
	Product p1_1, p1_2, p2_1, p2_2;
	Pos A, B, C, D;

	q1 = makeBR1Queue(L1);
	q2 = makeBR2Queue(L2);

	if (isEmpty(q1) || isEmpty(q2)) return;
	for (i = 0; i < L1->listNodeNum-1; i++) {
		p1_1 = Dequeue(q1);
		p1_2 = Peek(q1);
		for (j = 0; j < L2->listNodeNum - 1; j++) {
			p2_1 = Dequeue(q2);
			p2_2 = Peek(q2);

			A.x_pos = p1_1.product1; A.y_pos = p1_1.product2;
			B.x_pos = p1_2.product1; B.y_pos = p1_2.product2;
			C.x_pos = p2_1.product1; C.y_pos = p2_1.product2;
			D.x_pos = p2_2.product1; D.y_pos = p2_2.product2;

			if (CCWbaseCross(A, B, C, D))
				printf("player1: %.2f ~ %.2f, player2: %.2f ~ %.2f\n", MAX(MIN(p1_1.product1, p1_2.product1), MIN(p2_1.product1, p2_2.product1)), MIN(MAX(p1_1.product1, p1_2.product1), MAX(p2_1.product1, p2_2.product1)), MAX(MIN(p1_1.product2, p1_2.product2), MIN(p2_1.product2, p2_2.product2)), MIN(MAX(p1_1.product2, p1_2.product2), MAX(p2_1.product2, p2_2.product2)));
			Enqueue(q2, p2_1);
		}
		Enqueue(q2, Dequeue(q2));
		Enqueue(q1, p1_1);
	}
	Enqueue(q1, Dequeue(q1));

	deleteQueue(q1);
	deleteQueue(q2);
}

// 두 player의 보수행렬에 존재하는 모든 전략 명세 출력
void ShowPayoff(chainingList_h* L) {
	listNode* tempNode;
	slotNode* tempSlot;

	tempNode = L->head;
	while (tempNode != NULL) {
		printf("상대가 %.2f만큼 생산했을 때:\n", tempNode->product);
		tempSlot = tempNode->head;
		while (tempSlot != NULL) {
			printf("  %.2f만큼 생산시 %.2f의 이윤 발생\n", tempSlot->product, tempSlot->profit);
			tempSlot = tempSlot->link;
		}
		tempNode = tempNode->link;
	}
}