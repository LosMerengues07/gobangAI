#ifndef _EVALUATE_
#define _EVALUATE_
//��ֵ������

int getLine(pair<int, int> node, int i, int j);
int evaluate(pair<int, int> node, int target_player, int ai_color, int user_color);
void evaluate_all(int ai_color, int user_color);
int evaluate(int now_color);
#endif