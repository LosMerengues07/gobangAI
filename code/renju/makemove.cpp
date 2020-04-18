#include "define.h"
#include "printchessboard.h"
bool makeMove(int i, int j, int player ,int color)
{
	chessBoard[i][j] = color;
	if (player == AI)
	{
		ai_steps.push_back(make_pair(i, j));
	}
	else if (player == USER)
	{
		user_steps.push_back(make_pair(i, j));
	}
	//执行落子操作（chessboard[i][j]=1 & chessboard[i][j]=2）
	return true;
}

void unMakeMove()
{
	pair<int, int> ai_node = ai_steps.back();
	pair<int, int> user_node = user_steps.back();
	ai_steps.pop_back();
	user_steps.pop_back();
	chessBoard[ai_node.first][ai_node.second] = blank;
	chessBoard[user_node.first][user_node.second] = blank;
	//撤销落子操作（chessboard[i][j]=0）
}
