/*
	프로젝트 주제: 이산적 선택지가 존재하는 쿠르노 모델(Cournot model)의 최적대응 기반 풀이 기법의 개발: 큐(Queue)와 체이닝(Chaining)을 중심으로
	파일명: Main.c
	작성자: 대구과학고등학교 32기 2학년 김석준
	작성완료일: 2020.7.6.
	작성이유: 이산적 변수로 구성된 데이터들로 쿠르노 모델(Cournot model)의 해법을 자료구조를 이용하여 제시하고자 했기 때문
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Mixed.h"
#include <windows.h>

// 콘솔 창 설정
void consol(void) {
	system("2203김석준 자료구조 프로젝트");
	system("mode con: cols=70 lines=40");
}

// 메뉴창 설정
int menu(void) {
	int num;
	printf("\n");
	printf("==========================자료구조 프로젝트===========================\n");
	printf("=========이산적 변수를 가진 쿠르노 모델(Cournot model)의 해법=========\n");
	printf("\n");
	printf("1. 새로운 전략(Strategy) 입력\n");
	printf("2. 전략(Strategy) 삭제\n");
	printf("3. 모든 전략(Strategy) 출력\n");
	printf("4. 내쉬균형지점(Nash Equilibrium) 출력\n");
	printf("5. 종료\n");
	while (1) {
		printf("\n");
		printf("시행 입력: ");
		scanf("%d", &num);
		if (num >= 1 && num <= 5) {
			printf("\n");
			printf("----------------------------------------------------------------------\n");
			return num;
		}
		else
			printf("다시 입력해주세요.\n");
	}	
}

int main(void) {
	consol();
	chainingList_h* L1;	// 보수(payoff)행렬 리스트의 체이닝(chaining) 기반 구현
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
		// case 1: 새로운 전략(Strategy) 입력
		case 1: 
			printf("\n");
			printf("1. player2에 대한 player1의 전략 입력\n");
			printf("2. player1에 대한 player2의 전략 입력\n");
			while (1) {
				printf("\n");
				printf("시행 입력: ");
				scanf("%d", &n);
				if (n >= 1 && n <= 2)
					break;
				else
					printf("다시 입력해주세요.\n");
			}
			if (n == 1) {
				printf("\n");
				printf("player2의 생산량 입력: ");
				scanf("%lf", &product2);
				printf("그에 따른 player1의 생산량 입력: ");
				scanf("%lf", &product1);
				printf("그에 따른 player1의 이윤 입력: ");
				scanf("%lf", &profit1);
				insertNewStrategy(L1, product2, product1, profit1);
				printf("엔터를 입력하면 메뉴로 돌아갑니다.\n");
				getchar();
				getchar();
			}
			else {
				printf("\n");
				printf("player1의 생산량 입력: ");
				scanf("%lf", &product1);
				printf("그에 따른 player2의 생산량 입력: ");
				scanf("%lf", &product2);
				printf("그에 따른 player2의 이윤 입력: ");
				scanf("%lf", &profit2);
				insertNewStrategy(L2, product1, product2, profit2);
				printf("엔터를 입력하면 메뉴로 돌아갑니다.\n");
				getchar();
				getchar();
			}
			break;

		// case 2: 전략(Strategy) 삭제
		case 2:
			printf("\n");
			printf("1. player2에 대한 player1의 전략 삭제\n");
			printf("2. player1에 대한 player2의 전략 삭제\n");
			while (1) {
				printf("\n");
				printf("시행 입력: ");
				scanf("%d", &n);
				if (n >= 1 && n <= 2)
					break;
				else
					printf("다시 입력해주세요.\n");
			}
			if (n == 1) {
				printf("\n");
				printf("player2의 생산량 입력: ");
				scanf("%lf", &product2);
				printf("그에 따른 player1의 생산량 입력: ");
				scanf("%lf", &product1);
				deleteStrategy(L1, product2, product1);
				printf("엔터를 입력하면 메뉴로 돌아갑니다.\n");
				getchar();
				getchar();
			}
			else {
				printf("\n");
				printf("player1의 생산량 입력: ");
				scanf("%lf", &product1);
				printf("그에 따른 player2의 생산량 입력: ");
				scanf("%lf", &product2);
				deleteStrategy(L2, product1, product2);
				printf("엔터를 입력하면 메뉴로 돌아갑니다.\n");
				getchar();
				getchar();
			}
			break;

		// case 3: 모든 전략(Strategy) 출력
		case 3:
			printf("\n");
			printf("[player1 기준]\n");
			ShowPayoff(L1);
			printf("\n");
			printf("[player2 기준]\n");
			ShowPayoff(L2);
			printf("\n");
			printf("엔터를 입력하면 메뉴로 돌아갑니다.\n");
			getchar();
			getchar();
			break;

		// case 4: 내쉬균형지점(Nash Equilibrium) 출력
		case 4:
			printf("\n");
			ShowCross(L1, L2);
			printf("\n");
			printf("본 범위에서 생산할시 내쉬균형(Nash Equilibrium)을 이룹니다.\n");
			printf("엔터를 입력하면 메뉴로 돌아갑니다.\n");
			getchar();
			getchar();
			break;

		// case 5: 종료
		case 5:
			printf("\n");
			printf("프로그램을 종료합니다.\n");
			printf("\n");
			return 0;
		}
		system("cls");
	}
}
