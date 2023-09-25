/*
    ������Ʈ ����: �̻��� �������� �����ϴ� ���� ��(Cournot model)�� �������� ��� Ǯ�� ����� ����: ť(Queue)�� ü�̴�(Chaining)�� �߽�����
    ���ϸ�: CCW.c
    �ۼ���: �뱸���а���б� 32�� 2�г� �輮��
    �ۼ��Ϸ���: 2020.7.6.
    �ۼ�����: �̻��� ������ ������ �����͵�� ���� ��(Cournot model)�� �ع��� �ڷᱸ���� �̿��Ͽ� �����ϰ��� �߱� ����
*/

#include "Mixed.h"
#include <stdio.h>

// CCW �˰���: ����(cross product) ���� ��ȣ�� ��ġ���� �Ǻ�
int CCW(Pos A, Pos B, Pos C)
{
    Pos AB = { B.x_pos - A.x_pos, B.y_pos - A.y_pos };
    Pos AC = { C.x_pos - A.x_pos, C.y_pos - A.y_pos };
    double Zdirection = (AB.x_pos) * (AC.y_pos) - (AB.y_pos) * (AC.x_pos); // ����(cross product)

    if (Zdirection > 0)
        return counterclockwise;
    else if (Zdirection < 0)
        return clockwise;
    else
        return parralel;
}

// CCW �˰����� �̿��Ͽ� ������ ���� ���� �Ǵ�
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