#include "searchmove.h"


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

int last_x = -1;
int last_y = -1;
int last_color;
int minMaxSearch(int now_play, int depth, int alpha, int beta, GameLoop& gl)
{
	if (difftime(time(NULL), start_time) > g_time_limit)
	{
		int e = Evaluate(now_play, getOppo(now_play));
		return e;
	}

	if (depth <= 0 || gl.isGameOver(last_x, last_y, last_color))
	{
		int e = Evaluate(now_play, getOppo(now_play));
		return e;
	}

	auto choices = createMoves(now_play);

	for (auto& p : choices)
	{
		chessBoard[p.first][p.second] = now_play;
		last_x = p.first;
		last_y = p.second;
		last_color = now_play;

		int val = -minMaxSearch(getOppo(now_play), depth - 1, -beta, -alpha, gl);

		chessBoard[p.first][p.second] = blank;

		if (val > alpha)
		{
			alpha = val;
			if (depth == DEPTH && alpha > g_alpha)
			{
				next_x = p.first;
				next_y = p.second;

				g_alpha = alpha;
			}
		}
		if (val >= beta) return beta;

	}
	return alpha;
}

int deepSearch(int now_play, int depth, int alpha, int beta, GameLoop& gl, double time_limit)
{
	need_time_limit = true;
	g_time_limit = time_limit;
	start_time = time(NULL);

	for (int i = 2; difftime(time(NULL), start_time) < g_time_limit; i += 2)
	{
		DEPTH = i;
		g_alpha = alpha;
		minMaxSearch(now_play, DEPTH, alpha, beta, gl);
	}
#ifdef _DEBUG_
	cout << "search_depth" <<  DEPTH << endl;
	system("pause");
#endif
	need_time_limit = false;

	return 0;
}