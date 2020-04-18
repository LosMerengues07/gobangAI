#include "define.h"
#include "createmoves.h"
#include "makemove.h"
#include "evaluate.h"
#include "printchessboard.h"

int BASE_DEPTH = 5;
int searchMove() //ËÑË÷º¯ÊýÖ÷Ìå
{

	return 0;
}

//
//int killSearch(int now_player, int depth, int alpha, int beta) {
//	int score, num_of_ava;
//
//	int flag = kill_value(now_player);
//	if (flag)
//		return flag;
//
//
//	return 0;
//}
int DEPTH = 4;
int next_x, next_y;

int minMaxSearch(int now_play, int depth, int alpha, int beta) {
	if (depth <= 0) {
		int e = evaluate(now_play);
		return e;
	}

	auto choices = createMoves(now_play);

	for (auto & p : choices) {
		chessBoard[p.first][p.second] = now_play;

		int val = -minMaxSearch(3 - now_play, depth - 1, -beta, -alpha);

		chessBoard[p.first][p.second] = blank;

		if (val >= alpha) {
			alpha = val;
			if (depth == DEPTH) {
				next_x = p.first;
				next_y = p.second;
			}
		}
		if (val >= beta) return beta;

	}
	return alpha;
}