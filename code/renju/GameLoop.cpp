#include "GameLoop.h"
GameLoop::GameLoop(bool ai_is_black)
{
	score_map["01100"] = 50;
	score_map["00110"] = 50;
	score_map["11010"] = 200;
	score_map["00111"] = 500;
	score_map["11100"] = 500;
	score_map["01110"] = 5000;
	score_map["010110"] = 5000;
	score_map["011010"] = 5000;
	score_map["11101"] = 5000;
	score_map["11011"] = 5000;
	score_map["10111"] = 5000;
	score_map["11110"] = 5000;
	score_map["01111"] = 5000;
	score_map["011110"] = 50000;
	score_map["11111"] = 99999999;
	if (ai_is_black)  //ai��������
	{
		user_color = white;
		ai_color = black;
		cur_turn = AI;
	}
	else  //�û���������
	{
		user_color = black;
		ai_color = white;
		cur_turn = USER;
	}

	for (int i = 0; i < GRID_NUM; i++)
	{
		for (int j = 0; j < GRID_NUM; j++)
		{
			chessBoard[i][j] = blank;
		}
	}

	//create_initialize();
}

void GameLoop::printMenu()
{
	cout << "*************�������˻�����AI*************" << endl;
	if (user_color == black)
		cout << "*************�û�ִ������*********************" << endl;
	else
		cout << "*************����ִ������*********************" << endl;
	cout << "����: end		 ������Ϸ" << endl;
	cout << "����: move x y  ��ʾ���ӵ�" << endl;
	cout << "����: regret    ��ʾ����" << endl;
	cout << "ai����:   " << ai_steps.size() << endl << "user����: " << user_steps.size() << endl;
	//cout << "�غ�: " << turns << endl;
}

void GameLoop::printLog()
{
	cout << log;
}

void GameLoop::userLoop()
{
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "user input: ";
	string cmd;
	int x = -1, y = -1;
	cin >> cmd;
	if (cmd.empty())
		throw - 1;
	if (cmd.compare("move") == 0)
	{
		cin >> x >> y;
		if (inboard(y, x) && chessBoard[y][x] == 0)
			makeMove(y, x, USER, user_color);
		else
			throw - 1;
	}
	else if (cmd.compare("regret") == 0)
	{
		if (ai_steps.empty() || user_steps.empty())
		{
			throw - 1;
		}
		else
		{
			unMakeMove();
			throw 1;
		}
	}
	else
	{
		throw - 1;
	}

}

void GameLoop::aiLoop()
{
	//minMaxSearch(ai_color, DEPTH, -inf, +inf, *this);
	//if (user_steps.size()) {
	//	auto & last_step = user_steps
	//}
	deepSearch(ai_color, DEPTH, -inf, +inf, *this, 1);
	makeMove(next_x, next_y, AI, ai_color);
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
		print();//�������
		//cout << "score: " << evaluate(ai_color, user_color) << endl;

		//printValueBoard(); //�����ֵ
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
				if (i == -1)
					cout << "invalid input!" << endl;
				else
					cout << "regret!" << endl;
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
			cout << "error!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			assert(1);
			break;
		}
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

bool GameLoop::isGameOver(int last_x, int last_y, int last_color)
{
	for (int offset = -5; offset <= 0; offset++)
	{
		if (gameover(make_pair(last_x + offset, last_y), last_color, 0) ||
			gameover(make_pair(last_x, last_y + offset), last_color, 1) ||
			gameover(make_pair(last_x + offset, last_y + offset), last_color, 2) ||
			gameover(make_pair(last_x - offset, last_y + offset), last_color, 3))
			return true;
	}
	return false;
}

GameLoop::~GameLoop()
{
}
