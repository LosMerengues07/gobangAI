#include "BlankEvaluate.h"
//int getLine(pair<int, int> node, int i, int j)
//{ // node����ǰ��  i������  j���������ֵ 
//	int x = node.first;
//	int y = node.second;
//	switch (i)
//	{
//	case 0:
//		break;
//	case 1:
//		x = x + j;
//		break;
//	case 2:
//		x = x + j;
//		y = y + j;
//		break;
//	case 3:
//		y = y + j;
//		break;
//	case 4:
//		x = x - j;
//		y = y + j;
//		break;
//	case 5:
//		x = x - j;
//		break;
//	case 6:
//		x = x - j;
//		y = y - j;
//		break;
//	case 7:
//		y = y - j;
//		break;
//	case 8:
//		x = x + j;
//		y = y - j;
//	}
//	if (!inboard(x, y))
//	{ // Խ�紦��
//		return out;
//	}
//	return chessBoard[x][y];
//}

int BlankEvaluate::evaluate(pair<int, int> node, int cur_color, int oppo_color, bool defend = false)
{ //  target_player:��ǰ�����player�Ĵ���
	//defend Ϊ1ʱ,˵���ǴӶԷ��Ƕȿ���,����Ҫ���з���
	if (getLine(node, 0, 0) != blank) //�жϴ�λ���Ƿ��Ѿ�����
	{
		return -1000;
	}
	int value = 0;
	int numoftwo = 0;
	int target_color = cur_color;
	int other_color = oppo_color;

	for (int i = 1; i <= 8; i++)
	{ // 8������
// ���� 01111* *����ǰ��λ��  0 ����������λ��    ��ͬ 
		if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
			&& getLine(node, i, -3) == target_color && getLine(node, i, -4) == target_color
			&& getLine(node, i, -5) == blank)
		{
			value += 300000;
			if (defend) { value -= 500; }
			continue;
		}
		// ����A 21111*
		if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
			&& getLine(node, i, -3) == target_color && getLine(node, i, -4) == target_color
			&& (getLine(node, i, -5) == other_color || getLine(node, i, -5) == out))
		{
			value += 250000;
			if (defend) { value -= 500; }
			continue;
		}
		// ����B 111*1
		if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
			&& getLine(node, i, -3) == target_color && getLine(node, i, 1) == target_color)
		{
			value += 240000;
			if (defend) { value -= 500; }
			continue;
		}
		// ����C 11*11
		if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
			&& getLine(node, i, 1) == target_color && getLine(node, i, 2) == target_color)
		{
			value += 230000;
			if (defend) { value -= 500; }
			continue;
		}
		// ���� ��3λ�� 111*0
		if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
			&& getLine(node, i, -3) == target_color)
		{
			if (getLine(node, i, 1) == blank)
			{
				value += 750;
				if (getLine(node, i, -4) == blank)
				{
					value += 3150;
					if (defend) { value -= 300; }
				}
			}
			else
			{
				if (getLine(node, i, -4) == blank)
				{
					value += 500;
				}
			}
			continue;
		}
		// ���� Զ3λ�� 1110*
		if (getLine(node, i, -1) == blank && getLine(node, i, -2) == target_color
			&& getLine(node, i, -3) == target_color && getLine(node, i, -4) == target_color)
		{
			value += 350;
			continue;
		}
		// ���� 11*1
		if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
			&& getLine(node, i, 1) == target_color)
		{
			value += 600;
			if (getLine(node, i, -3) == blank && getLine(node, i, 2) == blank)
			{
				value += 3150;
				continue;
			}
			if ((getLine(node, i, -3) == other_color || getLine(node, i, -3) == out) && (getLine(node, i, 2) == other_color || getLine(node, i, 2) == out))
			{
				continue;
			}
			else
			{
				value += 700;
				continue;
			}
		}
		//����ĸ���   
		if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
			&& getLine(node, i, -3) != other_color && getLine(node, i, 1) != other_color)
		{
			numoftwo++;
		}
		//����ɢ��
		int numOfplyer = 0; // ��Ϊ����������Σ�
		for (int k = -4; k <= 0; k++)
		{ // ++++* +++*+ ++*++ +*+++ *++++
			int temp = 0;
			for (int l = 0; l <= 4; l++)
			{
				if (getLine(node, i, k + l) == target_color)
				{
					temp++;
				}
				else
					if (getLine(node, i, k + l) == other_color
						|| getLine(node, i, k + l) == out)
					{
						temp = 0;
						break;
					}
			}
			numOfplyer += temp;
		}
		value += numOfplyer * 15;
		if (numOfplyer != 0)
		{
		}
	}
	if (numoftwo >= 2)
	{
		value += 3000;
		if (defend)
		{
			value -= 100;
		}
	}
	return value;
}

void BlankEvaluate::evaluate_all(int ai_color, int user_color)
{
	for (int i = 1; i < GRID_NUM; i++)
	{
		for (int j = 1; j < GRID_NUM; j++)
		{
			valueBoard[i][j] = evaluate(make_pair(i, j), AI, ai_color, user_color) + evaluate(make_pair(i, j), USER, ai_color, user_color);
		}
	}
}


BlankEvaluate::BlankEvaluate()
{
}


BlankEvaluate::~BlankEvaluate()
{
}
