#include "define.h"

int chessBoard[GRID_NUM][GRID_NUM];//定义棋盘
int valueBoard[GRID_NUM][GRID_NUM];//棋盘估值


//只用检测一半的出发点
int directions[4][2] = {
	1, 0,
	0, 1,
	1, 1,
	-1, 1
};

int neighbor[8][2] = {
	-1, -1,
	-1, 0,
	-1, 1,
	0, -1,
	0, 1,
	1, -1,
	1, 0,
	1, 1
};

//判断从node出发,是否能连出5子
bool gameover(pair<int, int> node, int player)
{
	int x = node.first;
	int y = node.second;

	for (int i = 0; i < 4; i++)
	{
		int flag = true;
		for (int j = 0; j < 5; j++)
		{
			int nx = x + directions[i][0] * j;
			int ny = y + directions[i][1] * j;
			if (!inboard(nx, ny) || chessBoard[nx][ny] != player)
			{
				flag = false;
				break;
			}
		}
		if (flag)
			return true;
	}

	return false;
}

void printValueBoard()
{
	for (int i = 1; i < GRID_NUM; i++)
	{
		for (int j = 1; j < GRID_NUM; j++)
		{
			cout << valueBoard[i][j] << " ";
		}
		cout << endl;
	}
}

bool hasNeighbor(pair<int, int> point) {
	for (int i = 0; i < 8; i++) {
		int dx = neighbor[i][0];
		int dy = neighbor[i][1];
		if (inboard(point.first + dx, point.second + dy)
			&& chessBoard[point.first + dx][point.second + dy] != blank)
			return true;
	}

	return false;
}