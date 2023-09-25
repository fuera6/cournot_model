/*
	프로젝트 주제: 이산적 선택지가 존재하는 쿠르노 모델(Cournot model)의 최적대응 기반 풀이 기법의 개발: 큐(Queue)와 체이닝(Chaining)을 중심으로
	파일명: ChainingBasedLinkedList.c
	작성자: 대구과학고등학교 32기 2학년 김석준
	작성완료일: 2020.7.6.
	작성이유: 이산적 변수로 구성된 데이터들로 쿠르노 모델(Cournot model)의 해법을 자료구조를 이용하여 제시하고자 했기 때문
	출처: 윤성우의 열혈 자료구조(윤성우, 오렌지미디어), C로 배우는 쉬운 자료구조(이지영, 한빛아카데미)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Mixed.h"

// 체이닝 리스트를 가리키는 chainingList_h를 동적 할당
chainingList_h* createChainingList_h(void) {
	chainingList_h* L;
	L = (chainingList_h*)malloc(sizeof(chainingList_h));
	L->head = NULL;
	L->tail = NULL;
	L->listNodeNum = 0;
	return L;
}

// 체이닝 리스트의 뼈대 리스트를 구성하는 listNode를 할당
listNode* createListNode(chainingList_h* L, double product) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->product = product;
	newNode->head = NULL;
	newNode->tail = NULL;
	newNode->link = NULL;
	newNode->slotNodeNum = 0;
	L->listNodeNum += 1;

	if (L->head == NULL) {
		L->head = newNode;
		L->tail = newNode;
	}
	else {
		L->tail->link = newNode;
		L->tail = newNode;
	}
	return newNode;
}

// 체이닝 리스트에서 listNode 탐색
listNode* searchListNode(chainingList_h* L, double product) {
	listNode* temp;
	temp = L->head;
	while (temp != NULL) {
		if (temp->product == product)	return temp;
		temp = temp->link;
	}
	return temp;
}

// 체이닝 리스트에서 slotNode 탐색
slotNode* searchSlotNode(chainingList_h* L, double product_other, double product_mine) {
	listNode* tempNode = searchListNode(L, product_other);
	slotNode* tempSlot;
	if (tempNode == NULL) return NULL;
	else {
		tempSlot = tempNode->head;
		while (tempSlot != NULL) {
			if (tempSlot->product == product_mine) return tempSlot;
			tempSlot = tempSlot->link;
		}
		return tempSlot;
	}
}

// 삽입하고자 하는 데이터가 적절한지 판단하는 함수
int isPossible(chainingList_h* L, double product_other, double product_mine, double profit_mine) {
	listNode* tempNode;
	slotNode* tempSlot;
	tempNode = searchListNode(L, product_other);

	if (tempNode != NULL) {
		tempSlot = tempNode->head;
		while (tempSlot != NULL) {
			if (tempSlot->product == product_mine || tempSlot->profit == profit_mine) return FALSE;
			tempSlot = tempSlot->link;
		}
		return TRUE;
	}
	else return TRUE;
}

// 체이닝 리스트의 listNode의 체인을 구성하는 slotNode를 할당
int insertSlotNode(chainingList_h* L, double product_other, double product_mine, double profit_mine) {
	listNode* tempNode = searchListNode(L, product_other);
	slotNode* newSlot;
	if (!isPossible(L, product_other, product_mine, profit_mine)) return FALSE;

	if (tempNode == NULL)
		tempNode = createListNode(L, product_other);

	newSlot = (slotNode*)malloc(sizeof(slotNode));
	newSlot->link = NULL;
	newSlot->product = product_mine;
	newSlot->profit = profit_mine;
	tempNode->slotNodeNum += 1;
	if (tempNode->head == NULL) {
		tempNode->head = newSlot;
		tempNode->tail = newSlot;
	}
	else {
		tempNode->tail->link = newSlot;
		tempNode->tail = newSlot;
	}
	return TRUE;
}

// listNode 삭제
void deleteListNode(chainingList_h* L, double product) {
	listNode* tempNode, *deleteNode;
	slotNode* tempSlot, * parentSlot;
	tempNode = L->head;
	if (tempNode == NULL) return;
	else if (tempNode->product == product) {
		tempSlot = tempNode->head;
		while (tempSlot != NULL) {
			parentSlot = tempSlot;
			tempSlot = tempSlot->link;
			free(parentSlot);
		}
		L->head = tempNode->link;
		if (L->head == NULL) L->tail = NULL;
		L->listNodeNum -= 1;
		free(tempNode);
	}
	else {
		while (tempNode->link != NULL && tempNode->link->product != product) {
			tempNode = tempNode->link;
		}
		if (tempNode->link == NULL) return;
		else {
			deleteNode = tempNode->link;
			tempSlot = deleteNode->head;
			while (tempSlot != NULL) {
				parentSlot = tempSlot;
				tempSlot = tempSlot->link;
				free(parentSlot);
			}
			tempNode->link = deleteNode->link;
			if (deleteNode == L->tail) L->tail = tempNode;
			L->listNodeNum -= 1;
			free(deleteNode);
		}
	}
}

// slotNode 삭제
int deleteSlotNode(chainingList_h* L, double product_other, double product_mine) {
	listNode* tempNode = searchListNode(L, product_other);
	slotNode* tempSlot, *deleteSlot;
	if (tempNode == NULL) return FALSE;
	else {
		tempSlot = tempNode->head;
		if (tempSlot->product == product_mine) {
			tempNode->head = tempSlot->link;
			tempNode->slotNodeNum -= 1;
			free(tempSlot);
			if (tempNode->head == NULL)
				deleteListNode(L, product_other);
		}
		else {
			while (tempSlot->link != NULL && tempSlot->link->product != product_mine) {
				tempSlot = tempSlot->link;
			}
			if (tempSlot->link == NULL) return FALSE;
			else {
				deleteSlot = tempSlot->link;
				tempSlot->link = deleteSlot->link;
				tempNode->slotNodeNum -= 1;
				if (deleteSlot == tempNode->tail) tempNode->tail = tempSlot;
				free(deleteSlot);
			}
		}
	}
	return TRUE;
}