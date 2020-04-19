#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_
//��������
//���������㷨
#include "GameLoop.h"
#include "define.h"
#include "createmoves.h"
#include "makemove.h"
#include "evaluate.h"
#include "printchessboard.h"
class GameLoop;
//int searchMove();//��������
//����ʽalphabeta
int minMaxHeauSearch(int now_play, int depth, int alpha, int beta, GameLoop & gl);
//minimax
int minMaxSearch(int now_play, int depth, GameLoop& gl);
//alphabeta�㷨
int minMaxAlphaSearch(int now_play, int depth, int alpha, int beta, GameLoop& gl);
//zobristɢ��+alphabeta
int minMaxZobristSearch(int now_play, int depth, int alpha, int beta, GameLoop& gl);
//zobristɢ��+����ʽalphabeta
int minMaxHeauZobristSearch(int now_play, int depth, int alpha, int beta, GameLoop& gl);
//���������㷨
int deepSearch(int now_play, int depth, int alpha, int beta, GameLoop & gl, double time_limit);
//ÿ���������,next_x, next_y�������ŵ������.last_x,last_y
extern int next_x, next_y;
extern int DEPTH;//����������
#endif
