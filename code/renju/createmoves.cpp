#include "createmoves.h"
//�˴���createmoves���ݿհ�����ļ�ֵ������
//

bool compS(ScoreWithP & p1, ScoreWithP & p2) {
	return p1.score > p2.score;
}
vector<pair<int, int>> createMoves(int player) //����ȫ���Ϸ��߷���
{
	//Ϊ�˽�Լʱ��,��������Χ�������ӵ�
	vector<pair<int, int>> choices;
	vector<ScoreWithP> choicesWithS;
	for (int i = 0; i < GRID_NUM; i++) {
		for (int j = 0; j < GRID_NUM; j++) {
			if (chessBoard[i][j] == blank &&	//TODO:֮�󽫿���������߶ε�����2��
				hasNeighbor(make_pair(i, j))) {
				int score = BlankEvaluate::evaluate(make_pair(i, j), player, getOppo(player), false) + BlankEvaluate::evaluate(make_pair(i, j), getOppo(player), player, true);
				ScoreWithP sp(score, i, j);
				choicesWithS.push_back(sp);
			}
		}
	}

	sort(choicesWithS.begin(), choicesWithS.end(), compS);

	for (auto s : choicesWithS) {
		choices.push_back(make_pair(s.x, s.y));
	}
	if (choices.size() == 0) {
		int x = GRID_NUM / 2 + rand() % 3 - 1;
		int y = GRID_NUM / 2 + rand() % 3 - 1;
		choices.push_back(make_pair(x,  y));
	}
	return choices;
}
//�������кϷ����ӵ㡣������������˵�������ϵĿհ׵��Ϊ�����߷���