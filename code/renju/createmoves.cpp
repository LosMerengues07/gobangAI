#include "define.h"

vector<pair<int, int>> createMoves(int player) //生成全部合法走法集
{
	//为了节约时间,仅产生周围已有落子的
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
//查找所有合法落子点。对于五子棋来说，棋盘上的空白点均为可行走法。