/*
	프로젝트 주제: 이산적 선택지가 존재하는 쿠르노 모델(Cournot model)의 최적대응 기반 풀이 기법의 개발: 큐(Queue)와 체이닝(Chaining)을 중심으로
	파일명: Queue.c
	작성자: 대구과학고등학교 32기 2학년 김석준
	작성완료일: 2020.7.6.
	작성이유: 이산적 변수로 구성된 데이터들로 쿠르노 모델(Cournot model)의 해법을 자료구조를 이용하여 제시하고자 했기 때문
	출처: 윤성우의 열혈 자료구조(윤성우, 오렌지미디어), C로 배우는 쉬운 자료구조(이지영, 한빛아카데미)
*/

#include <stdio.h>
#include <stdlib.h>
#include "Mixed.h"

// 큐(Queue) 초기화
Queue* QueueInit(void) {
	Queue* Q;
	Q = (Queue*)malloc(sizeof(Queue));
	Q->front = NULL;
	Q->rear = NULL;
	return Q;
}

// 큐(Queue) 원소 존재 확인
int isEmpty(Queue* Q) {
	if (Q->front == NULL)
		return TRUE;
	else
		return FALSE;
}

// 큐의 노드와 큐 삭제
void deleteQueue(Queue* Q) {
	while (!isEmpty(Q)) {
		Dequeue(Q);
	}
	free(Q);
}

// 큐(Queue)에 원소 삽입
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

// 큐(Queue) 원소 삭제 및 반환
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

// 큐(Queue) 원소 참조
Product Peek(Queue* Q) {
	if (isEmpty(Q)) return;
	else return Q->front->data;
}
