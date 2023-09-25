/*
	������Ʈ ����: �̻��� �������� �����ϴ� ���� ��(Cournot model)�� �������� ��� Ǯ�� ����� ����: ť(Queue)�� ü�̴�(Chaining)�� �߽�����
	���ϸ�: ChainingBasedLinkedList.c
	�ۼ���: �뱸���а���б� 32�� 2�г� �輮��
	�ۼ��Ϸ���: 2020.7.6.
	�ۼ�����: �̻��� ������ ������ �����͵�� ���� ��(Cournot model)�� �ع��� �ڷᱸ���� �̿��Ͽ� �����ϰ��� �߱� ����
	��ó: �������� ���� �ڷᱸ��(������, �������̵��), C�� ���� ���� �ڷᱸ��(������, �Ѻ���ī����)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Mixed.h"

// ü�̴� ����Ʈ�� ����Ű�� chainingList_h�� ���� �Ҵ�
chainingList_h* createChainingList_h(void) {
	chainingList_h* L;
	L = (chainingList_h*)malloc(sizeof(chainingList_h));
	L->head = NULL;
	L->tail = NULL;
	L->listNodeNum = 0;
	return L;
}

// ü�̴� ����Ʈ�� ���� ����Ʈ�� �����ϴ� listNode�� �Ҵ�
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

// ü�̴� ����Ʈ���� listNode Ž��
listNode* searchListNode(chainingList_h* L, double product) {
	listNode* temp;
	temp = L->head;
	while (temp != NULL) {
		if (temp->product == product)	return temp;
		temp = temp->link;
	}
	return temp;
}

// ü�̴� ����Ʈ���� slotNode Ž��
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

// �����ϰ��� �ϴ� �����Ͱ� �������� �Ǵ��ϴ� �Լ�
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

// ü�̴� ����Ʈ�� listNode�� ü���� �����ϴ� slotNode�� �Ҵ�
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

// listNode ����
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

// slotNode ����
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