#include "searchmove.h"

int DEPTH = 4;
int next_x, next_y;
clock_t start_time;//����������ʼʱ��
double g_time_limit = inf;//ʱ������
bool need_time_limit = false;//�Ƿ��ʱ����������
int g_alpha;//���������㷨�д洢����������alpha

int last_x = -1;//�洢�����㷨�����ֵ���ʱ��x,y�����ɫ��
int last_y = -1;
int last_color;
int minMaxHeauSearch(int now_play, int depth, int alpha, int beta, GameLoop& gl)
{
	if (need_time_limit && clock() - start_time > g_time_limit)
	{
		int e = Evaluate(now_play, getOppo(now_play));
		return e;
	}

	if (gl.isGameOver(last_x, last_y, last_color)) {
		int e = Evaluate(now_play, getOppo(now_play));
		return e;
	}

	if (depth <= 0  )
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

		int val = -minMaxHeauSearch(getOppo(now_play), depth - 1, -beta, -alpha, gl);

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

int minMaxAlphaSearch(int now_play, int depth, int alpha, int beta, GameLoop& gl)
{
	if (need_time_limit && clock() - start_time > g_time_limit)
	{
		int e = Evaluate(now_play, getOppo(now_play));
		return e;
	}

	if (gl.isGameOver(last_x, last_y, last_color)) {
		return -99999999;
	}

	if (depth <= 0)
	{
		int e = Evaluate(now_play, getOppo(now_play));
		return e;
	}

	auto choices = createSimpleMoves(now_play);

	for (auto& p : choices)
	{
		chessBoard[p.first][p.second] = now_play;
		last_x = p.first;
		last_y = p.second;
		last_color = now_play;

		int val = -minMaxAlphaSearch(getOppo(now_play), depth - 1, -beta, -alpha, gl);

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

//

int minMaxZobristSearch(int now_play, int depth, int alpha, int beta, GameLoop& gl)
{
	if (gl.isGameOver(last_x, last_y, last_color)) {
		return  -99999999;
	}

	if ((need_time_limit && clock() - start_time > g_time_limit) || depth <= 0 )
	{
		auto hist = gl.zobrist_map.find(make_pair(gl.cur_zobrist[0], gl.cur_zobrist[1]));
		if (hist != gl.zobrist_map.end()) {
			return hist->second;
		}
		else {
			int e = Evaluate(now_play, getOppo(now_play));
			gl.zobrist_map[make_pair(gl.cur_zobrist[0], gl.cur_zobrist[1])] = e;
			return e;
		}

	}

	auto choices = createSimpleMoves(now_play);

	for (auto& p : choices)
	{
		chessBoard[p.first][p.second] = now_play;
		gl.update_zobrist(p.first, p.second, now_play);

		last_x = p.first;
		last_y = p.second;
		last_color = now_play;

		int val = -minMaxZobristSearch(getOppo(now_play), depth - 1, -beta, -alpha, gl);

		chessBoard[p.first][p.second] = blank;
		gl.update_zobrist(p.first, p.second, now_play);

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


int minMaxHeauZobristSearch(int now_play, int depth, int alpha, int beta, GameLoop& gl)
{
	if (gl.isGameOver(last_x, last_y, last_color)) {
		return  -99999999;
	}

	if (depth <= 0 ||  (need_time_limit && clock() - start_time > g_time_limit))
	{
		auto hist = gl.zobrist_map.find(make_pair(gl.cur_zobrist[0], gl.cur_zobrist[1]));
		if (hist != gl.zobrist_map.end()) {
			return hist->second;
		}
		else {
			int e = Evaluate(now_play, getOppo(now_play));
			gl.zobrist_map[make_pair(gl.cur_zobrist[0], gl.cur_zobrist[1])] = e;
			return e;
		}

	}

	auto choices = createMoves(now_play);

	for (auto& p : choices)
	{
		chessBoard[p.first][p.second] = now_play;
		gl.update_zobrist(p.first, p.second, now_play);

		last_x = p.first;
		last_y = p.second;
		last_color = now_play;

		int val = -minMaxHeauZobristSearch(getOppo(now_play), depth - 1, -beta, -alpha, gl);

		chessBoard[p.first][p.second] = blank;
		gl.update_zobrist(p.first, p.second, now_play);

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
//��alpha,beta�Ż�
int  minMaxSearch(int now_play, int depth, GameLoop& gl) {
	int best = -inf;
	if (depth <= 0 || gl.isGameOver(last_x, last_y, last_color)) {
		int e = Evaluate(now_play, getOppo(now_play));
		return e;
	}
	auto choices = createSimpleMoves(now_play);
	for (auto & p : choices) {
		chessBoard[p.first][p.second] = now_play;
		last_x = p.first;
		last_y = p.second;
		last_color = now_play;

		int val = -minMaxSearch(getOppo(now_play), depth - 1, gl);

		chessBoard[p.first][p.second] = blank;

		if (val > best) {
			best = val;
			if (depth == DEPTH) {
				next_x = p.first;
				next_y = p.second;
			}
		}
	}
	return best;
}

int deepSearch(int now_play, int depth, int alpha, int beta, GameLoop& gl, double time_limit)
{
	need_time_limit = true;
	g_time_limit = time_limit * 1000;
	gl.cal_zobrist();
	start_time = clock();
	for (int i = 2; clock() - start_time < g_time_limit; i += 2)
	{
		DEPTH = i;
		g_alpha = alpha;
		//minMaxHeauZobristSearch(now_play, DEPTH, alpha, beta, gl);
		minMaxHeauSearch(now_play, DEPTH, alpha, beta, gl);
	}
#ifdef _DEBUG_
	cout << "search_depth" <<  DEPTH << endl;
	system("pause");
#endif
	need_time_limit = false;

	return 0;
}