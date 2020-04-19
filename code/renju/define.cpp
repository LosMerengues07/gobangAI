#include "define.h"

int chessBoard[GRID_NUM][GRID_NUM];//��������
int valueBoard[GRID_NUM][GRID_NUM];//���̹�ֵ
vector<pair<int, int>> ai_steps; //��¼ai
vector<pair<int, int>> user_steps; //��¼�û�
map<string, int> score_map;
int turns = 0;
//ֻ�ü��һ��ĳ�����
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

int lNeighbor[24][2] = {
	-2, -2,
	-2, -1,
	-2, 0,
	-2, 1,
	-2, 2,
	-1, -2,
	-1, -1,
	-1, 0,
	-1, 1,
	-1, 2,
	0, -2,
	0, -1,
	0, 1,
	0, 2,
	1, -2,
	1, -1,
	1, 0,
	1, 1,
	1, 2,
	2, -2,
	2, -1,
	2, 0,
	2, 1, 
	2, 2
};

bool gameover(pair<int, int> & node, int player, int dir){//�ж��Ƿ���Ϸ����{
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

//�жϴ�node����,�Ƿ�������5��
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

bool hasNeighbor(pair<int, int>& point) {
	for (int i = 0; i < 8; i++) {
		int dx = neighbor[i][0];
		int dy = neighbor[i][1];
		if (inboard(point.first + dx, point.second + dy)
			&& chessBoard[point.first + dx][point.second + dy] != blank)
			return true;
	}

	return false;
}

bool hasLNeighbor(pair<int, int>& point) {
	for (int i = 0; i < 24; i++) {
		int dx = lNeighbor[i][0];
		int dy = lNeighbor[i][1];
		if (inboard(point.first + dx, point.second + dy)
			&& chessBoard[point.first + dx][point.second + dy] != blank)
			return true;
	}

	return false;
}