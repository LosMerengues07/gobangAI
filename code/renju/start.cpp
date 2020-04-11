#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "GameLoop.h"
#include <conio.h>

void printMenu()
{
	cout << "*************五子棋人机对弈AI*************" << endl;
	cout << "输入: newblack  电脑先手" << endl;
	cout << "输入: newwhite  电脑后手" << endl;
	cout << "输入: end		 结束游戏" << endl;
	cout << "输入: move x y  表示落子点" << endl;
}
int main()
{

	srand(time(NULL));

	while (true)
	{
		system("cls");
		printMenu();
		string s;
		cin >> s;
		if (s.compare("newblack") == 0)
		{
			GameLoop game = GameLoop(true);
			game.run();
		}
		else if (s.compare("newwhite") == 0)
		{
			GameLoop game = GameLoop(false);
			game.run();
		}
		else if (s.compare("end") == 0)
		{
			return 0;
		}
		else
		{
			cout << "您输入的参数无效,请重新输入,按任意键确认";
			system("pause");
		}
	}

	return 0;

}
