#include <stdio.h>
#include <Windows.h>
#include "Elf2D.h"


void Elf2DInitScreen()
{
    //Ŀ�� �����
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;  // Ŀ���� ����
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// ȭ�� �ʱ�ȭ �Լ�
void Elf2DClearScreen(char* Buffer, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Buffer[i * (width + 1) + j] = ' ';  // ȭ�� �ʱ�ȭ
        }
        Buffer[i * (width + 1) + width] = '\n';  // ���� ����
    }
    Buffer[(width + 1) * height - 1] = '\0';  // ���� ����

}

// ��ũ�����۸� �̿��Ͽ� ȭ���� �׸��� �Լ�
void Elf2DDrawBuffer(char* Buffer)
{
    //0,0���� �̵�
    COORD coord = { 0, 0 };  // ��ǥ (0, 0)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // ��ũ�� ���� ���
    printf("%s", Buffer);  // ȭ�� ���
}

// �� ���� �����ϴ� ������ �׸��� �Լ� (�극���� �˰�����)
void Elf2DDrawLine(int x1, int y1, int x2, int y2, char* Buffer, int width, int height)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
        {
            Buffer[y1 * (width + 1) + x1] = '*';  // ȭ�鿡 ���� ����
        }

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

#include <math.h>

void Elf2DDrawLine2(float x1, float y1, float x2, float y2, char* Buffer, int width, int height)
{
    float dx = fabs(x2 - x1); // ����
    float dy = fabs(y2 - y1); // ����
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    float err = dx - dy;

    while (1) {
        int ix1 = (int)roundf(x1); // float ��ǥ�� ������ ��ȯ (����)
        int iy1 = (int)roundf(y1); // float ��ǥ�� ������ ��ȯ (����)

        if (ix1 >= 0 && ix1 < width && iy1 >= 0 && iy1 < height)
        {
            Buffer[iy1 * (width + 1) + ix1] = '*';  // ȭ�鿡 ���� ����
        }

        if (fabs(x1 - x2) < 0.01 && fabs(y1 - y2) < 0.01) // �ε��Ҽ��� �� (���� ����)
            break;

        float e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}



void Elf2DSleep(int ms)
{
    Sleep(ms);
}