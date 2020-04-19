
#ifndef _DEFINE_
#define _DEFINE_
//ȫ�ֱ�������

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

#define out -1		//������
#define blank 0		//�հ׵�
#define black 1		//�ڷ�
#define white 2		//�׷�

#define USER 11
#define AI 12
#define inf 1000000000
#define inboard(a,b) (a>0 && a<=15 && b>0 && b<=15)		//���ڼ����з��Ƿ���������
#define _DEBUG_
#define GRID_NUM 16	//���̹�ģ	
extern int chessBoard[GRID_NUM][GRID_NUM]; //����
extern int valueBoard[GRID_NUM][GRID_NUM]; //����
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
bool gameover(pair<int, int> & node, int player, int dir); //�ж��Ƿ���Ϸ����
bool gameover(pair<int, int> & node, int player); //�ж��Ƿ���Ϸ����
void printValueBoard();
bool hasNeighbor(pair<int, int> & point);
bool hasLNeighbor(pair<int, int> & point);
//��ȡ������ɫ
inline int getOppo(int player) {
	return 3 - player;
}
#endif


