#include "GameLoop.h"
GameLoop::GameLoop(bool user_is_black)
{
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
	cout << "*************�������˻�����AI*************" << endl;
	if (user_color == black)
		cout << "*************��������*********************" << endl;
	else
		cout << "*************���Ժ���*********************" << endl;
	cout << "����: end		 ������Ϸ" << endl;
	cout << "����: move x y  ��ʾ���ӵ�" << endl;
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
	//random search bug: will endless loop if table  is full
	evaluate_all(ai_color, user_color);
	int max = valueBoard[1][1];
	int max_x = 1, max_y = 1;
	for (int i = 1; i < GRID_NUM; i++)
	{
		for (int j = 1; j < GRID_NUM; j++)
		{
			if (valueBoard[i][j] > max)
			{
				max = valueBoard[i][j];
				max_x = i;
				max_y = j;
			}
		}
	} 
	if (max == 0)
	{ 
		do
		{
			max_x = rand() % GRID_NUM;
			max_y = rand() % GRID_NUM;
		} while (chessBoard[max_x][max_y] != blank);
	}
	chessBoard[max_x][max_y] = ai_color;
}

void GameLoop::run()
{
	while (true)
	{
		system("cls");
		printMenu();
		print();//�������
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
