/*
	������Ʈ ����: �̻��� �������� �����ϴ� ���� ��(Cournot model)�� �������� ��� Ǯ�� ����� ����: ť(Queue)�� ü�̴�(Chaining)�� �߽�����
	���ϸ�: Cournot.c
	�ۼ���: �뱸���а���б� 32�� 2�г� �輮��
	�ۼ��Ϸ���: 2020.7.6.
	�ۼ�����: �̻��� ������ ������ �����͵�� ���� ��(Cournot model)�� �ع��� �ڷᱸ���� �̿��Ͽ� �����ϰ��� �߱� ����
*/

#include <stdio.h>
#include "Mixed.h"

// ü�̴� ����Ʈ ��� ������� �Ҵ�
chainingList_h* createPayoff(void) {
	chainingList_h* payoff = createChainingList_h();
	return payoff;
}

// ���ο� ������ ����
void insertNewStrategy(chainingList_h* L, double product_other, double product_mine, double profit_mine) {
	int success;
	success = insertSlotNode(L, product_other, product_mine, profit_mine);
	if (success) {
		printf("\n");
		printf("���忡 �����Ͽ����ϴ�.\n");
	}
	else {
		printf("\n");
		printf("���忡 �����Ͽ����ϴ�. �̹� ���� ������ �����Ͱ� ����Ǿ� �ֽ��ϴ�.\n");
	}
}

// ������ ����
void deleteStrategy(chainingList_h* L, double product_other, double product_mine) {
	int success;
	success = deleteSlotNode(L, product_other, product_mine);
	if (success) {
		printf("\n");
		printf("������ �����Ͽ����ϴ�.\n");
	}
	else {
		printf("\n");
		printf("������ �����Ͽ����ϴ�. ���� ����� �����Ͱ� �ƴմϴ�.\n");
	}
}

// ü�̴� ����Ʈ�� product�� ũ������ listNode�� ����
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

// player2�� ���������� ���귮 �������� ���(QNode)�� ���� ť(Queue) ����
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

// player1�� ���������� ���귮 �������� ���(QNode)�� ���� ť(Queue) ����
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

// CCW �˰������� ������ ���缺�� �ľ��ϰ� ������ ��� �̸� ����ϴ� �Լ�
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

// �� player�� ������Ŀ� �����ϴ� ��� ���� �� ���
void ShowPayoff(chainingList_h* L) {
	listNode* tempNode;
	slotNode* tempSlot;

	tempNode = L->head;
	while (tempNode != NULL) {
		printf("��밡 %.2f��ŭ �������� ��:\n", tempNode->product);
		tempSlot = tempNode->head;
		while (tempSlot != NULL) {
			printf("  %.2f��ŭ ����� %.2f�� ���� �߻�\n", tempSlot->product, tempSlot->profit);
			tempSlot = tempSlot->link;
		}
		tempNode = tempNode->link;
	}
}