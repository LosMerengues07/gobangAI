#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "GameLoop.h"
#include <conio.h>

void printMenu()
{
	cout << "*************�������˻�����AI*************" << endl;
	cout << "����: newblack  ��������" << endl;
	cout << "����: newwhite  ���Ժ���" << endl;
	cout << "����: end		 ������Ϸ" << endl;
	cout << "����: move x y  ��ʾ���ӵ�" << endl;
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
			cout << "������Ĳ�����Ч,����������,�������ȷ��";
			system("pause");
		}
	}

	return 0;

}
