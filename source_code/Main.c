/*
	������Ʈ ����: �̻��� �������� �����ϴ� ���� ��(Cournot model)�� �������� ��� Ǯ�� ����� ����: ť(Queue)�� ü�̴�(Chaining)�� �߽�����
	���ϸ�: Main.c
	�ۼ���: �뱸���а���б� 32�� 2�г� �輮��
	�ۼ��Ϸ���: 2020.7.6.
	�ۼ�����: �̻��� ������ ������ �����͵�� ���� ��(Cournot model)�� �ع��� �ڷᱸ���� �̿��Ͽ� �����ϰ��� �߱� ����
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Mixed.h"
#include <windows.h>

// �ܼ� â ����
void consol(void) {
	system("2203�輮�� �ڷᱸ�� ������Ʈ");
	system("mode con: cols=70 lines=40");
}

// �޴�â ����
int menu(void) {
	int num;
	printf("\n");
	printf("==========================�ڷᱸ�� ������Ʈ===========================\n");
	printf("=========�̻��� ������ ���� ���� ��(Cournot model)�� �ع�=========\n");
	printf("\n");
	printf("1. ���ο� ����(Strategy) �Է�\n");
	printf("2. ����(Strategy) ����\n");
	printf("3. ��� ����(Strategy) ���\n");
	printf("4. ������������(Nash Equilibrium) ���\n");
	printf("5. ����\n");
	while (1) {
		printf("\n");
		printf("���� �Է�: ");
		scanf("%d", &num);
		if (num >= 1 && num <= 5) {
			printf("\n");
			printf("----------------------------------------------------------------------\n");
			return num;
		}
		else
			printf("�ٽ� �Է����ּ���.\n");
	}	
}

int main(void) {
	consol();
	chainingList_h* L1;	// ����(payoff)��� ����Ʈ�� ü�̴�(chaining) ��� ����
	chainingList_h* L2;
	int n;
	double product1;
	double product2;
	double profit1;
	double profit2;
	
	L1 = createPayoff();
	L2 = createPayoff();

	while (1) {
		n = menu();
		switch (n) {
		// case 1: ���ο� ����(Strategy) �Է�
		case 1: 
			printf("\n");
			printf("1. player2�� ���� player1�� ���� �Է�\n");
			printf("2. player1�� ���� player2�� ���� �Է�\n");
			while (1) {
				printf("\n");
				printf("���� �Է�: ");
				scanf("%d", &n);
				if (n >= 1 && n <= 2)
					break;
				else
					printf("�ٽ� �Է����ּ���.\n");
			}
			if (n == 1) {
				printf("\n");
				printf("player2�� ���귮 �Է�: ");
				scanf("%lf", &product2);
				printf("�׿� ���� player1�� ���귮 �Է�: ");
				scanf("%lf", &product1);
				printf("�׿� ���� player1�� ���� �Է�: ");
				scanf("%lf", &profit1);
				insertNewStrategy(L1, product2, product1, profit1);
				printf("���͸� �Է��ϸ� �޴��� ���ư��ϴ�.\n");
				getchar();
				getchar();
			}
			else {
				printf("\n");
				printf("player1�� ���귮 �Է�: ");
				scanf("%lf", &product1);
				printf("�׿� ���� player2�� ���귮 �Է�: ");
				scanf("%lf", &product2);
				printf("�׿� ���� player2�� ���� �Է�: ");
				scanf("%lf", &profit2);
				insertNewStrategy(L2, product1, product2, profit2);
				printf("���͸� �Է��ϸ� �޴��� ���ư��ϴ�.\n");
				getchar();
				getchar();
			}
			break;

		// case 2: ����(Strategy) ����
		case 2:
			printf("\n");
			printf("1. player2�� ���� player1�� ���� ����\n");
			printf("2. player1�� ���� player2�� ���� ����\n");
			while (1) {
				printf("\n");
				printf("���� �Է�: ");
				scanf("%d", &n);
				if (n >= 1 && n <= 2)
					break;
				else
					printf("�ٽ� �Է����ּ���.\n");
			}
			if (n == 1) {
				printf("\n");
				printf("player2�� ���귮 �Է�: ");
				scanf("%lf", &product2);
				printf("�׿� ���� player1�� ���귮 �Է�: ");
				scanf("%lf", &product1);
				deleteStrategy(L1, product2, product1);
				printf("���͸� �Է��ϸ� �޴��� ���ư��ϴ�.\n");
				getchar();
				getchar();
			}
			else {
				printf("\n");
				printf("player1�� ���귮 �Է�: ");
				scanf("%lf", &product1);
				printf("�׿� ���� player2�� ���귮 �Է�: ");
				scanf("%lf", &product2);
				deleteStrategy(L2, product1, product2);
				printf("���͸� �Է��ϸ� �޴��� ���ư��ϴ�.\n");
				getchar();
				getchar();
			}
			break;

		// case 3: ��� ����(Strategy) ���
		case 3:
			printf("\n");
			printf("[player1 ����]\n");
			ShowPayoff(L1);
			printf("\n");
			printf("[player2 ����]\n");
			ShowPayoff(L2);
			printf("\n");
			printf("���͸� �Է��ϸ� �޴��� ���ư��ϴ�.\n");
			getchar();
			getchar();
			break;

		// case 4: ������������(Nash Equilibrium) ���
		case 4:
			printf("\n");
			ShowCross(L1, L2);
			printf("\n");
			printf("�� �������� �����ҽ� ��������(Nash Equilibrium)�� �̷�ϴ�.\n");
			printf("���͸� �Է��ϸ� �޴��� ���ư��ϴ�.\n");
			getchar();
			getchar();
			break;

		// case 5: ����
		case 5:
			printf("\n");
			printf("���α׷��� �����մϴ�.\n");
			printf("\n");
			return 0;
		}
		system("cls");
	}
}
