#include "define.h"

int chessBoard[GRID_NUM][GRID_NUM];//��������
int valueBoard[GRID_NUM][GRID_NUM];//���̹�ֵ
vector<pair<int, int>> ai_steps; //��¼ai
vector<pair<int, int>> user_steps; //��¼�û�
map<string, int> score_map;  //��¼��ͬ��ֵĵ÷�
int turns = 0;

//�洢����1֮�ڵ��ڵ�ƫ����
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

//�洢����2֮�ڵ��ڵ�ƫ����
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

//�Ƿ��ھ���1���������ڵķǿյ�
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

//�Ƿ��ھ���2���������ڵķǿյ�
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