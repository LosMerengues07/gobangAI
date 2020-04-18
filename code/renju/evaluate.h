#ifndef _EVALUATE_
#define _EVALUATE_
//¹ÀÖµÉú³ÉÆ÷
#include "define.h"

int getLine(pair<int, int> node, int direction, int offset);
void getPoints(int x, int y, int offset, int direction, pair<int, int>* nodes);
int cal_score(pair<int, int> node, int direction, int my_player, int ai_color, int user_color, vector<map<string, int>>* score_all_arr);
int evaluate(int ai_color, int user_color);
#endif