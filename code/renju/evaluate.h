#ifndef _EVALUATE_
#define _EVALUATE_
//��ֵ������
#include "define.h"

//������㣬ƫ�ƺͷ������Ŀ���
int getPointStatus(pair<int, int> node, int direction, int offset);

//����ĳ���ĳ���򣬼�����offsetΪ������������
void getPoints(int x, int y, int offset, int direction, pair<int, int>* nodes);

//����ĳ��ĳ��������Ӧ��״����
int calScore(pair<int, int> node, int direction, int my_player, int ai_color, int user_color, vector<map<string, int>>* score_all_arr);

//��ֵ������������ǰmap������ǰ���Ʒ���
int Evaluate(int ai_color, int user_color, int gamma = 1);  //gamma�����������ص�Ȩ�� gamm��ƫ�����
#endif