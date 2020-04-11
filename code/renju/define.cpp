#include "define.h"

int chessBoard[GRID_NUM][GRID_NUM];//定义棋盘

//只用检测一半的出发点
int directions[4][2] = {
	1, 0,
	0, 1,
	1, 1,
	-1, 1
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