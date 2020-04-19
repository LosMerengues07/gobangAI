
#ifndef _DEFINE_
#define _DEFINE_
//全局变量定义

#include <stdio.h>
#include <sstream>
#include <string.h>
#include <string>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <assert.h>
#include <map>
using namespace std;

#define out -1		//棋盘外
#define blank 0		//空白点
#define black 1		//黑方
#define white 2		//白方

#define USER 11
#define AI 12
#define inf 1000000000
#define inboard(a,b) (a>0 && a<=15 && b>0 && b<=15)		//用于检验招法是否在棋盘上
#define _DEBUG_
#define GRID_NUM 16	//棋盘规模	
extern int chessBoard[GRID_NUM][GRID_NUM]; //棋盘
extern int valueBoard[GRID_NUM][GRID_NUM]; //棋盘
extern map<string, int> score_map;
extern vector<pair<int, int>> ai_steps;
extern vector<pair<int, int>> user_steps;
extern int turns;

struct ScoreWithP {
	int score;
	int x;
	int y;

	ScoreWithP(int s, int x, int y) :score(s), x(x), y(y){}
};
//extern int BASE_DEPTH;
bool gameover(pair<int, int> & node, int player, int dir); //判断是否游戏结束
bool gameover(pair<int, int> & node, int player); //判断是否游戏结束
void printValueBoard();
bool hasNeighbor(pair<int, int> & point);
bool hasLNeighbor(pair<int, int> & point);
//获取对手颜色
inline int getOppo(int player) {
	return 3 - player;
}
#endif


