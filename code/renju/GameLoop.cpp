#include "GameLoop.h"
GameLoop::GameLoop(bool user_is_black)
{
	score_map["01100"]  = 50;
	score_map["00110"]  = 50;
	score_map["11010"]  = 200;
	score_map["00111"]  = 500;
	score_map["11100"]  = 500;
	score_map["01110"]  = 5000;
	score_map["010110"] = 5000;
	score_map["011010"] = 5000;
	score_map["11101"]  = 5000;
	score_map["11011"]  = 5000;
	score_map["10111"]  = 5000;
	score_map["11110"]  = 5000;
	score_map["01111"]  = 5000;
	score_map["011110"] = 50000;
	score_map["11111"]  = 99999999;
	if (user_is_black)
	{
		user_color = black;
		ai_color = white;
		cur_turn = AI;
	}
	else
	{
		user_color = white;
		ai_color = black;
		cur_turn = USER;
	}

	for (int i = 0; i < GRID_NUM; i++)
	{
		for (int j = 0; j < GRID_NUM; j++)
		{
			chessBoard[i][j] = blank;
		}
	}
}

void GameLoop::printMenu()
{
	cout << "*************五子棋人机对弈AI*************" << endl;
	if (user_color == black)
		cout << "*************电脑先手*********************" << endl;
	else
		cout << "*************电脑后手*********************" << endl;
	cout << "输入: end		 结束游戏" << endl;
	cout << "输入: move x y  表示落子点" << endl;
}

void GameLoop::printLog()
{
	cout << log;
}

void GameLoop::userLoop()
{
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string s, subs;
	int x = -1, y = -1;
	getline(cin, s ,'\n');
	if(s.empty())
		throw 1;
	istringstream ss(s);
	ss >> subs >> x >> y;
	ss.str("");
	if (inboard(y, x) && subs.compare("move") == 0 && chessBoard[y][x] == 0)
		chessBoard[y][x] = user_color;
	else
		throw 1;
}

void GameLoop::aiLoop()
{
	minMaxSearch(ai_color, DEPTH, -inf, +inf, *this);
	chessBoard[next_x][next_y] = ai_color;
	//random search bug: will endless loop if table  is full
	//int rx, ry;
	//do
	//{
	//	rx = rand() % GRID_NUM;
	//	ry = rand() % GRID_NUM;
	//} while (chessBoard[rx][ry] != blank);
	//chessBoard[rx][ry] = ai_color;
}

void GameLoop::run()
{
	while (true)
	{
		system("cls");
		printMenu();
		print();//输出棋盘
		//cout << "score: " << evaluate(ai_color, user_color) << endl;

		//printValueBoard(); //输出估值
		if (isWin())
		{
			cout << "you win" << endl;
			system("pause");
			return;
		}

		if (isLose())
		{
			cout << "you lose" << endl;
			system("pause");
			return;
		}

		switch (cur_turn)
		{
		case USER:
			try
			{
				userLoop();
			}
			catch (int i)
			{
				cur_turn = USER;
				break;
			}
			cur_turn = AI;
			break;
		case AI:
			aiLoop();
			cur_turn = USER;
			break;
		default:
			assert(1);
			break;
		}

		printLog();
	}

}

bool GameLoop::isWin()
{
	for (int i = 0; i < GRID_NUM; i++)
	{
		for (int j = 0; j < GRID_NUM; j++)
		{
			if (gameover(make_pair(i, j), user_color))
				return true;
		}
	}
	return false;
}

bool GameLoop::isLose()
{
	for (int i = 0; i < GRID_NUM; i++)
	{
		for (int j = 0; j < GRID_NUM; j++)
		{
			if (gameover(make_pair(i, j), ai_color))
				return true;
		}
	}
	return false;
}

GameLoop::~GameLoop()
{
}
