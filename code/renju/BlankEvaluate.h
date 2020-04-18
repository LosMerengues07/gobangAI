#pragma once
#include "define.h"
//������heuristic create moves
//�ο�https://www.cnblogs.com/maxuewei2/p/4825520.html#daima
class BlankEvaluate
{
public:
	static int valueBoard[GRID_NUM][GRID_NUM]; //����
	static int evaluate(pair<int, int> node, int ai_color, int user_color, bool defend);
	static void evaluate_all(int ai_color, int user_color);
	static int getLine(pair<int, int> node, int i, int j);

	BlankEvaluate();
	~BlankEvaluate();
};
