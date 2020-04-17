#include "define.h"

vector<pair<int, int>> createMoves(int player) //����ȫ���Ϸ��߷���
{
	//Ϊ�˽�Լʱ��,��������Χ�������ӵ�
	vector<pair<int, int>> choices;
	for (int i = 0; i < GRID_NUM; i++) {
		for (int j = 0; j < GRID_NUM; j++) {
			if (chessBoard[i][j] == blank &&
				hasNeighbor(make_pair(i, j)))
				choices.push_back(make_pair(i, j));
		}
	}

	if (choices.size() == 0) {
		int x = GRID_NUM / 2 + rand() % 3 - 1;
		int y = GRID_NUM / 2 + rand() % 3 - 1;
		choices.push_back(make_pair(x,  y));
	}
	return choices;
}
//�������кϷ����ӵ㡣������������˵�������ϵĿհ׵��Ϊ�����߷���