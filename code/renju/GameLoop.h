#pragma once
#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "evaluate.h"
class GameLoop
{
	int user_color;
	int ai_color;
	int cur_turn;
	string log = "";
	void printMenu();
	void printLog();

	void userLoop();



public:
	GameLoop(bool ai_is_black);
	inline void clearBoard() {
		for (int i = 0; i < GRID_NUM; i++)
			for (int j = 0; j < GRID_NUM; j++)
				chessBoard[i][j] = blank;
	}
	void aiLoop();
	bool isWin();
	bool isLose();
	bool isGameOver(int last_x, int last_y, int last_color);
	void run();
	~GameLoop();

	map<pair<long long, long long>, int> zobrist_map;
	long long cur_zobrist[2] = { 0,0 };
	long long zobrist[GRID_NUM][GRID_NUM];

	void cal_zobrist(){
		cur_zobrist[0] = cur_zobrist[1] = 0;
		for (int i = 0; i < GRID_NUM; i++)
			for (int j = 0; j < GRID_NUM; j++) {
				if (chessBoard[i][j] == white) {
					cur_zobrist[0] ^= zobrist[i][j];
				}
				if (chessBoard[i][j] == black) {
					cur_zobrist[1] ^= zobrist[i][j];
				}
			}
	}

	void update_zobrist(int x, int y, int color) {
		if (color == white)
			cur_zobrist[0] ^= zobrist[x][y];
		if(color == black)
			cur_zobrist[1] ^= zobrist[x][y];
	}
};

