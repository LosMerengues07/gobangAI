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

	void aiLoop();

public:
	GameLoop(bool ai_is_black);
	bool isWin();
	bool isLose();
	bool isGameOver(int last_x, int last_y, int last_color);
	void run();
	~GameLoop();
};

