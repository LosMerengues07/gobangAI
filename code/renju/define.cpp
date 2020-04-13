#include "define.h"

int chessBoard[GRID_NUM][GRID_NUM];//��������
int valueBoard[GRID_NUM][GRID_NUM];//���̹�ֵ


//ֻ�ü��һ��ĳ�����
int directions[4][2] = {
	1, 0,
	0, 1,
	1, 1,
	-1, 1
};
//�жϴ�node����,�Ƿ�������5��
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