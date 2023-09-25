# cournot_model
이산적 선택지가 존재하는 쿠르노 모델(Cournot model)의 최적대응 기반 풀이 기법의 개발: 큐(Queue)와 체이닝(Chaining)을 중심으로

입력된 데이터를 바탕으로 최적대응을 적용한 선별된 데이터들로 각 점들에 대해 내쉬균형을 구해 쿠르노 모델의 균형점을 찾아주는 프로그램

## Usage
* 새로운 전략(Strategy) 입력: player2에 대한 player1의 전략 또는 player1에 대한 player2의 전략 입력
* 전략(Strategy) 삭제: player2에 대한 player1의 전략 또는 player1에 대한 player2의 전략 삭제
* 모든 전략(Strategy) 출력: 현재까지 저장된 모든 전략 출력
* 내쉬균형지점(Nash Equilibrium) 출력: 저장된 전략 데이터들을 바탕으로 내쉬균형지점 출력

## Time
* 2020

## Directories & Files
* document: 개발 관련 문서
* source_code: 프로그램 소스코드
  * Main.c: 메인 화면 구성
  * Cournot.c: 프로그램의 전반적 기능을 담당하는 함수
  * CCW.c: CCW 알고리즘 및 선분 교차 여부 판단 함수
  * ChainingBasedLinkedList.c: 체이닝(Chaining) 기반 연결리스트 관련 함수
  * Queue.c: 큐(Queue) 관련 함수
  * Mixed.h: 상수, 구조체, 함수 관련 헤더 파일
