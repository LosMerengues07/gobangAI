#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "GameLoop.h"
#include <conio.h>
#include "test.h"

void printMenu()
{
	cout << "*************�������˻�����AI*************" << endl;
	cout << "����: newai     ����ִ������" << endl;
	cout << "����: newuser   ����ִ�׺���" << endl;
	cout << "����: end       ������Ϸ" << endl;
	cout << "����: move x y  ��ʾ���ӵ�" << endl;
	cout << "����: regret    ��ʾ����" << endl;
}



int main()
{
#ifdef _TEST_
	test();
	return 0;
#endif // _TEST_

	srand(time(NULL));

	while (true)
	{
		system("cls");
		printMenu();
		cout << "ָ���Ⱥ���: ";
		string s;
		cin >> s;
		if (s.compare("newai") == 0)
		{
			GameLoop game = GameLoop(true);
			game.run();
		}
		else if (s.compare("newuser") == 0)
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
