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
};

