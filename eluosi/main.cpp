#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
//定义全局变量
int x1, x2, x3, x4, y1, y2, y3, y4;
//定义游戏分数
int score = 0;

//定义游戏区
char ground[21][16] = { 0 };
//画出方块图形
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
//将画出的方块涂成与背景颜色相同的颜色，达到消除的目的
void cube_2(int x, int y, int color) {
	setcolor(color);
	for (int i = 0; i <= 29; i++) {
		line(x, y + i, x + 29, y + i);
	}
}
//判断是否有一行铺满方块，如果铺满则消除这一行方块
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
//改变方块形状样式
void change(int x, int y, int z, int n) {
	//凸字形方块
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
	//单个方块
	if (n == 2) {
		x1 = x2 = x3 = x4 = x;
		y1 = y2 = y3 = y4 = y;
	}
	//田字方块
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
//画出对应形状的方块
void drawcube(int x, int y, int z, int n) {
	change(x, y, z, n);
	cube_1(x1, y1, RED);
	cube_1(x2, y2, RED);
	cube_1(x3, y3, RED);
	cube_1(x4, y4, RED);
}
//将对应形状的方块隐藏
void transparent(int x, int y, int z, int n) {
	change(x, y, z, n);
	cube_2(x1, y1, WHITE);
	cube_2(x2, y2, WHITE);
	cube_2(x3, y3, WHITE);
	cube_2(x4, y4, WHITE);
}
//向左移动判断
int left(int x, int y, int z, int n) {
	change(x, y, z, n);
	if (ground[(y1 + 30) / 30 + 1][x1 / 30 - 1] == 0)
		if (ground[(y2 + 30) / 30 + 1][x2 / 30 - 1] == 0)
			if (ground[(y3 + 30) / 30 + 1][x3 / 30 - 1] == 0)
				if (ground[(y4 + 30) / 30 + 1][x4 / 30 - 1] == 0)
					return 1;
	return 0;
}
//向右移动判断
int right(int x, int y, int z, int n) {
	change(x, y, z, n);
	if (ground[(y1 + 30) / 30 + 1][x1 / 30 + 1] == 0)
		if (ground[(y2 + 30) / 30 + 1][x2 / 30 + 1] == 0)
			if (ground[(y3 + 30) / 30 + 1][x3 / 30 + 1] == 0)
				if (ground[(y4 + 30) / 30 + 1][x4 / 30 + 1] == 0)
					return 1;
	return 0;
}
//向下移动判断
int down(int x, int y, int z, int n) {
	change(x, y, z, n);
	if (ground[(y1 + 30) / 30 + 1][x1 / 30 ] == 0)
		if (ground[(y2 + 30) / 30 + 1][x2 / 30 ] == 0)
			if (ground[(y3 + 30) / 30 + 1][x3 / 30 ] == 0)
				if (ground[(y4 + 30) / 30 + 1][x4 / 30 ] == 0)
					return 1;
	return 0;
}
//方块实体化（将方块作为边界）
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
	outtextxy(460, 100, "您的得分是：");
	sprintf_s(str, 32, "%d", score);
	outtextxy(550, 100, str);
	outtextxy(500, 150, "操作说明");
	outtextxy(500, 200, "W:旋转");
	outtextxy(500, 250, "A:左移");
	outtextxy(500, 300, "D:右移");
}
void gameover() {
	setcolor(BLACK);
	setfont(45, 0, "隶体");
	outtextxy(130, 300, "Game Over！");
	system("pause");
	closegraph();
	exit(0);

}
int main() {
	initgraph(640, 600);//设置游戏窗口大小
	SetWindowText(GetHWnd(), "俄罗斯方块");//设置窗口句柄
	setbkcolor(WHITE);//设置背景颜色为白色
	cleardevice();
	setcolor(GREEN);//设置游戏框线为绿色
	rectangle(29, 0, 450, 570);//设置游戏框线
	srand((unsigned)time(NULL));//设置随机数种子
	for (int i = 1; i < 15; i++) {
		ground[20][i] = 1;
	}//设置方块移动边界
	for (int i = 1; i < 21; i++) {
		ground[i][0] = 1;
		ground[i][15] = 1;
	}//设置方块移动边界
	while (1) {
		int x = 270;
		int z = 1;
		int y = 1;
		int n = rand() % 4 + 1;//随机方块类型
		if (ground[2][9] == 1) {
			gameover();
		}
		while (down(x, y, z, n)) {
			y += 30;
			//方块左移控制
			if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
				if (left(x, y, z, n)) {
					x -= 30;
				}
			}
			//方块右移控制
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
			//方块变换形状控制
			if (GetAsyncKeyState(VK_UP) && right(x, y, z + 1, n) && left(x, y, z + 1, n)) {
				if (z == 4)
					z = 1;
				else
					z++;
			}
			drawcube(x, y, z, n);//画方块
			Sleep(150);//设置150毫秒延迟
			//如果向下移动未触碰到边界，隐藏自己，否则将方块实体化
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