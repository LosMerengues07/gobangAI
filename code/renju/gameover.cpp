#include "define.h"
//ֻ�ü��һ��ĳ�����
int directions[4][2] = {
	1, 0,
	0, 1,
	1, 1,
	-1, 1
};

bool gameover(pair<int, int> & node, int player, int dir) {//�ж��Ƿ���Ϸ����{
	int x = node.first;
	int y = node.second;
	for (int j = 0; j < 5; j++)
	{
		int nx = x + directions[dir][0] * j;
		int ny = y + directions[dir][1] * j;
		if (!inboard(nx, ny) || chessBoard[nx][ny] != player)
		{
			return false;
		}
	}
	return true;
}

//�жϴ�node����,�Ƿ�������5�ӣ������жϵ�����Ϸ�Ƿ����ʱ��ֻ�ü���������ӣ����Ӷ�ΪO1�����GameLoop
bool gameover(pair<int, int>& node, int player)
{
	int x = node.first;
	int y = node.second;

	for (int i = 0; i < 4; i++)
	{
		if (gameover(node, player, i))
			return true;
	}

	return false;
}
