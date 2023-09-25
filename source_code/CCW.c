/*
    프로젝트 주제: 이산적 선택지가 존재하는 쿠르노 모델(Cournot model)의 최적대응 기반 풀이 기법의 개발: 큐(Queue)와 체이닝(Chaining)을 중심으로
    파일명: CCW.c
    작성자: 대구과학고등학교 32기 2학년 김석준
    작성완료일: 2020.7.6.
    작성이유: 이산적 변수로 구성된 데이터들로 쿠르노 모델(Cournot model)의 해법을 자료구조를 이용하여 제시하고자 했기 때문
*/

#include "Mixed.h"
#include <stdio.h>

// CCW 알고리즘: 외적(cross product) 값의 부호로 위치관계 판별
int CCW(Pos A, Pos B, Pos C)
{
    Pos AB = { B.x_pos - A.x_pos, B.y_pos - A.y_pos };
    Pos AC = { C.x_pos - A.x_pos, C.y_pos - A.y_pos };
    double Zdirection = (AB.x_pos) * (AC.y_pos) - (AB.y_pos) * (AC.x_pos); // 외적(cross product)

    if (Zdirection > 0)
        return counterclockwise;
    else if (Zdirection < 0)
        return clockwise;
    else
        return parralel;
}

// CCW 알고리즘을 이용하여 선분의 교차 여부 판단
int CCWbaseCross(Pos A, Pos B, Pos C, Pos D)
{
    int check1 = CCW(A, B, C) * CCW(A, B, D);
    int check2 = CCW(C, D, A) * CCW(C, D, B);
    if (check1 <= 0 && check2 <= 0)
    {
        if (check1 == 0 && check2 == 0)
        {
            if ((C.x_pos - A.x_pos) * (C.x_pos - B.x_pos) > 0)
                if ((D.x_pos - A.x_pos) * (D.x_pos - B.x_pos) > 0)
                    if ((A.x_pos - C.x_pos) * (A.x_pos - D.x_pos) > 0)
                        if ((B.x_pos - C.x_pos) * (B.x_pos - D.x_pos) > 0)
                            return TRUE;
            return FALSE;
        }
        else
            return TRUE;
    }
    else
        return FALSE;
}