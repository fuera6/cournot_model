/*
	������Ʈ ����: �̻��� �������� �����ϴ� ���� ��(Cournot model)�� �������� ��� Ǯ�� ����� ����: ť(Queue)�� ü�̴�(Chaining)�� �߽�����
	���ϸ�: Queue.c
	�ۼ���: �뱸���а���б� 32�� 2�г� �輮��
	�ۼ��Ϸ���: 2020.7.6.
	�ۼ�����: �̻��� ������ ������ �����͵�� ���� ��(Cournot model)�� �ع��� �ڷᱸ���� �̿��Ͽ� �����ϰ��� �߱� ����
	��ó: �������� ���� �ڷᱸ��(������, �������̵��), C�� ���� ���� �ڷᱸ��(������, �Ѻ���ī����)
*/

#include <stdio.h>
#include <stdlib.h>
#include "Mixed.h"

// ť(Queue) �ʱ�ȭ
Queue* QueueInit(void) {
	Queue* Q;
	Q = (Queue*)malloc(sizeof(Queue));
	Q->front = NULL;
	Q->rear = NULL;
	return Q;
}

// ť(Queue) ���� ���� Ȯ��
int isEmpty(Queue* Q) {
	if (Q->front == NULL)
		return TRUE;
	else
		return FALSE;
}

// ť�� ���� ť ����
void deleteQueue(Queue* Q) {
	while (!isEmpty(Q)) {
		Dequeue(Q);
	}
	free(Q);
}

// ť(Queue)�� ���� ����
void Enqueue(Queue* Q, Product data) {
	QNode* newNode = (QNode*)malloc(sizeof(QNode));
	newNode->data = data;
	newNode->link = NULL;

	if (isEmpty(Q)) {
		Q->front = newNode;
		Q->rear = newNode;
	}
	else {
		Q->rear->link = newNode;
		Q->rear = newNode;
	}
}

// ť(Queue) ���� ���� �� ��ȯ
Product Dequeue(Queue* Q) {
	QNode* q;
	Product data;

	if (isEmpty(Q)) return;
	else {
		q = Q->front->link;
		data = Q->front->data;
		free(Q->front);
		Q->front = q;
		if (q == NULL) Q->rear = NULL;
		return data;
	}
}

// ť(Queue) ���� ����
Product Peek(Queue* Q) {
	if (isEmpty(Q)) return;
	else return Q->front->data;
}
