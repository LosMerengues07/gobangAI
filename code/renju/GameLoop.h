#pragma once
#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
class GameLoop
{
	int user_color;
	int ai_color;
	int cur_turn;
	string log = "";
	void printMenu();
	void printLog();
	bool isWin();
	bool isLose();
	void userLoop();

	void aiLoop();

public:
	GameLoop(bool user_is_black);

	void run();
	~GameLoop();
};

