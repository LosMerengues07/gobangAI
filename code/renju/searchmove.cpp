#include "searchmove.h"

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
time_t start_time;
double g_time_limit;
bool need_time_limit = false;
int g_alpha;

int minMaxSearch(int now_play, int depth, int alpha, int beta, GameLoop & gl) {
	if (difftime(time(NULL), start_time) > g_time_limit) {
		int e = evaluate(now_play, getOppo(now_play));
		return e;
	}

	if (depth <= 0 || gl.isLose() || gl.isWin()) {
		int e = evaluate(now_play, getOppo(now_play));
		return e;
	}

	auto choices = createMoves(now_play);

	for (auto & p : choices) {
		chessBoard[p.first][p.second] = now_play;

		int val = -minMaxSearch(getOppo(now_play), depth - 1, -beta, -alpha, gl);

		chessBoard[p.first][p.second] = blank;

		if (val > alpha) {
			alpha = val;
			if (depth == DEPTH && alpha > g_alpha) {
				next_x = p.first;
				next_y = p.second;

				g_alpha = alpha;
			}
		}
		if (val >= beta) return beta;

	}
	return alpha;
}

int deepSearch(int now_play, int depth, int alpha, int beta, GameLoop & gl, double time_limit) {
	need_time_limit = true;
	g_time_limit = time_limit;
	start_time = time(NULL);

	for (int i = 2; difftime(time(NULL), start_time) < g_time_limit ; i+= 2) {
		DEPTH = i;
		g_alpha = alpha;
		minMaxSearch(now_play, DEPTH, alpha, beta, gl);
	}

	need_time_limit = false;
	return 0;
}