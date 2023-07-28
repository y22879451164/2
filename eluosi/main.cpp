#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
//����ȫ�ֱ���
int x1, x2, x3, x4, y1, y2, y3, y4;
//������Ϸ����
int score = 0;

//������Ϸ��
char ground[21][16] = { 0 };
//��������ͼ��
void cube_1(int x, int y, int color) {
	setcolor(color);
	for (int i = 0; i <= 29; i++) {
		line(x, y + i, x + 29, y + i);
	}
	setcolor(BLACK);
	line(x, y, x + 29, y);
	line(x, y, x, y + 29);
	line(x + 29, y, x + 29, y + 29);
	line(x, y + 29, x + 29, y + 29);
}
//�������ķ���Ϳ���뱳����ɫ��ͬ����ɫ���ﵽ������Ŀ��
void cube_2(int x, int y, int color) {
	setcolor(color);
	for (int i = 0; i <= 29; i++) {
		line(x, y + i, x + 29, y + i);
	}
}
//�ж��Ƿ���һ���������飬���������������һ�з���
void  destroy() {
	for (int a = 19; a > 0; a--) {
		for (int i = 1, j = 1; i < 15; i++, j++) {
			if (ground[a][i] == 0)
				break;
			else if (j == 14) {
				score = score + 100;
				for (int i = 1; i < 15; i++) {
					ground[a][i] = 0;
					cube_2(30 * i, 30 * a - 30, WHITE);
				}
				for (int m = 19; m > 0; m--) {
					for (int j = 1; j < 15; j++) {
						if (ground[m][j] == 1) {
							while (ground[m + 1][j] != 1) {
								ground[m + 1][j] = 1;
								ground[m][j] = 0;
								cube_2(30 * j, 30 * m - 30, WHITE);
								cube_1(30 * j, 30 * (m + 1) - 30, RED);
								m = m + 1;
							}
						}
					}
				}
			}
		}
	}
}
//�ı䷽����״��ʽ
void change(int x, int y, int z, int n) {
	//͹���η���
	if (n == 1) {
		if (z == 1) {
			x1 = x3 = x;
			x2 = x - 30;
			x4 = x + 30;
			y1 = y;
			y2 = y3 = y4 = y + 30;
		}
		if (z == 2) {
			x1 = x2 = x3 = x;
			x4 = x + 30;
			y1 = y;
			y2 = y + 30;
			y3 = y + 60;
			y4 = y + 30;
		}
		if (z == 3) {
			x1 = x;
			x2 = x4 = x + 30;
			x3 = x + 60;
			y1 = y2 = y3 = y;
			y4 = y + 30;
		}
		if (z == 4) {
			x1 = x2 = x3 = x;
			x4 = x - 30;
			y1 = y;
			y2 = y4 = y + 30;
			y3 = y + 60;
		}
	}
	//��������
	if (n == 2) {
		x1 = x2 = x3 = x4 = x;
		y1 = y2 = y3 = y4 = y;
	}
	//���ַ���
	if (n == 3) {
		x1 = x3 = x;
		x2 = x4 = x + 30;
		y1 = y2 = y;
		y3 = y4 = y + 30;
	}
	if (n == 4) {
		if (z == 1 || z == 3) {
			x1 = x;
			x2 = x3 = x + 30;
			x4 = x + 60;
			y1 = y2 = y;
			y3 = y4 = y + 30;
		}
		if (z == 2 || z == 4) {
			x1 = x2 = x;
			x3 = x4 = x - 30;
			y2 = y3 = y + 30;
			y1 = y;
			y4 = y + 60;
		}
	}
}
//������Ӧ��״�ķ���
void drawcube(int x, int y, int z, int n) {
	change(x, y, z, n);
	cube_1(x1, y1, RED);
	cube_1(x2, y2, RED);
	cube_1(x3, y3, RED);
	cube_1(x4, y4, RED);
}
//����Ӧ��״�ķ�������
void transparent(int x, int y, int z, int n) {
	change(x, y, z, n);
	cube_2(x1, y1, WHITE);
	cube_2(x2, y2, WHITE);
	cube_2(x3, y3, WHITE);
	cube_2(x4, y4, WHITE);
}
//�����ƶ��ж�
int left(int x, int y, int z, int n) {
	change(x, y, z, n);
	if (ground[(y1 + 30) / 30 + 1][x1 / 30 - 1] == 0)
		if (ground[(y2 + 30) / 30 + 1][x2 / 30 - 1] == 0)
			if (ground[(y3 + 30) / 30 + 1][x3 / 30 - 1] == 0)
				if (ground[(y4 + 30) / 30 + 1][x4 / 30 - 1] == 0)
					return 1;
	return 0;
}
//�����ƶ��ж�
int right(int x, int y, int z, int n) {
	change(x, y, z, n);
	if (ground[(y1 + 30) / 30 + 1][x1 / 30 + 1] == 0)
		if (ground[(y2 + 30) / 30 + 1][x2 / 30 + 1] == 0)
			if (ground[(y3 + 30) / 30 + 1][x3 / 30 + 1] == 0)
				if (ground[(y4 + 30) / 30 + 1][x4 / 30 + 1] == 0)
					return 1;
	return 0;
}
//�����ƶ��ж�
int down(int x, int y, int z, int n) {
	change(x, y, z, n);
	if (ground[(y1 + 30) / 30 + 1][x1 / 30 ] == 0)
		if (ground[(y2 + 30) / 30 + 1][x2 / 30 ] == 0)
			if (ground[(y3 + 30) / 30 + 1][x3 / 30 ] == 0)
				if (ground[(y4 + 30) / 30 + 1][x4 / 30 ] == 0)
					return 1;
	return 0;
}
//����ʵ�廯����������Ϊ�߽磩
void hide(int x, int y, int z, int n) {
	change(x, y, z, n);
	ground[(y1 + 30) / 30][x1 / 30] = 1;
	ground[(y2 + 30) / 30][x2 / 30] = 1;
	ground[(y3 + 30) / 30][x3 / 30] = 1;
	ground[(y4 + 30) / 30][x4 / 30] = 1;
}
void gametip() {
	char str[32];
	setcolor(GREEN);
	outtextxy(460, 100, "���ĵ÷��ǣ�");
	sprintf_s(str, 32, "%d", score);
	outtextxy(550, 100, str);
	outtextxy(500, 150, "����˵��");
	outtextxy(500, 200, "W:��ת");
	outtextxy(500, 250, "A:����");
	outtextxy(500, 300, "D:����");
}
void gameover() {
	setcolor(BLACK);
	setfont(45, 0, "����");
	outtextxy(130, 300, "Game Over��");
	system("pause");
	closegraph();
	exit(0);

}
int main() {
	initgraph(640, 600);//������Ϸ���ڴ�С
	SetWindowText(GetHWnd(), "����˹����");//���ô��ھ��
	setbkcolor(WHITE);//���ñ�����ɫΪ��ɫ
	cleardevice();
	setcolor(GREEN);//������Ϸ����Ϊ��ɫ
	rectangle(29, 0, 450, 570);//������Ϸ����
	srand((unsigned)time(NULL));//�������������
	for (int i = 1; i < 15; i++) {
		ground[20][i] = 1;
	}//���÷����ƶ��߽�
	for (int i = 1; i < 21; i++) {
		ground[i][0] = 1;
		ground[i][15] = 1;
	}//���÷����ƶ��߽�
	while (1) {
		int x = 270;
		int z = 1;
		int y = 1;
		int n = rand() % 4 + 1;//�����������
		if (ground[2][9] == 1) {
			gameover();
		}
		while (down(x, y, z, n)) {
			y += 30;
			//�������ƿ���
			if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
				if (left(x, y, z, n)) {
					x -= 30;
				}
			}
			//�������ƿ���
			if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
				if (right(x, y, z, n)) {
					x += 30;
				}
			}
			if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
				if (y < 450) {
					y += 60;
				}
			}
			//����任��״����
			if (GetAsyncKeyState(VK_UP) && right(x, y, z + 1, n) && left(x, y, z + 1, n)) {
				if (z == 4)
					z = 1;
				else
					z++;
			}
			drawcube(x, y, z, n);//������
			Sleep(150);//����150�����ӳ�
			//��������ƶ�δ�������߽磬�����Լ������򽫷���ʵ�廯
			if (down(x, y, z, n)) {
				transparent(x, y, z, n);
			} else {
				hide(x, y, z, n);
			}
			destroy();
			gametip();
		}
	}
	_getch();
	return 0;
}