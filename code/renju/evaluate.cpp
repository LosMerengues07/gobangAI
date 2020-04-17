#include "define.h"

int getLine(pair<int, int> node, int i, int j)
{ // node：当前点  i：方向  j：坐标相对值 
    int x = node.first;
    int y = node.second;
    switch (i)
    {
    case 0:
        break;
    case 1:
        x = x + j;
        break;
    case 2:
        x = x + j;
        y = y + j;
        break;
    case 3:
        y = y + j;
        break;
    case 4:
        x = x - j;
        y = y + j;
        break;
    case 5:
        x = x - j;
        break;
    case 6:
        x = x - j;
        y = y - j;
        break;
    case 7:
        y = y - j;
        break;
    case 8:
        x = x + j;
        y = y - j;
    }
    if(!inboard(x,y))
    { // 越界处理
        return out;
    }
    return chessBoard[x][y];
}

int evaluate(pair<int, int> node, int target_player, int ai_color, int user_color)
{ //  target_player:当前计算的player的代号
    if (getLine(node, 0, 0) != blank) //判断此位置是否已经落子
    {
        return -1000;
    }
    int value = 0;
    int numoftwo = 0;
    int target_color = 0;
    int other_color = 0;
    if (target_player == AI)
    {
        target_color = ai_color;
        other_color = user_color;
    }else if (target_player == USER)
    {
        target_color = user_color;
        other_color = ai_color;
    }
    for (int i = 1; i <= 8; i++)
    { // 8个方向
// 活四 01111* *代表当前空位置  0 代表其他空位置    下同 
        if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
            && getLine(node, i, -3) == target_color && getLine(node, i, -4) == target_color
            && getLine(node, i, -5) == blank)
        {
            value += 300000;
            if (target_player != AI) { value -= 500; }
            continue;
        }
        // 死四A 21111*
        if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
            && getLine(node, i, -3) == target_color && getLine(node, i, -4) == target_color
            && (getLine(node, i, -5) == other_color || getLine(node, i, -5) == out))
        {
            value += 250000;
            if (target_player != AI) { value -= 500; }
            continue;
        }
        // 死四B 111*1
        if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
            && getLine(node, i, -3) == target_color && getLine(node, i, 1) == target_color)
        {
            value += 240000;
            if (target_player != AI) { value -= 500; }
            continue;
        }
        // 死四C 11*11
        if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
            && getLine(node, i, 1) == target_color && getLine(node, i, 2) == target_color)
        {
            value += 230000;
            if (target_player != AI) { value -= 500; }
            continue;
        }
        // 活三 近3位置 111*0
        if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
            && getLine(node, i, -3) == target_color)
        {
            if (getLine(node, i, 1) == blank)
            {
                value += 750;
                if (getLine(node, i, -4) == blank)
                {
                    value += 3150;
                    if (target_player != AI) { value -= 300; }
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
        // 活三 远3位置 1110*
        if (getLine(node, i, -1) == blank && getLine(node, i, -2) == target_color
            && getLine(node, i, -3) == target_color && getLine(node, i, -4) == target_color)
        {
            value += 350;
            continue;
        }
        // 死三 11*1
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
        //活二的个数   
        if (getLine(node, i, -1) == target_color && getLine(node, i, -2) == target_color
            && getLine(node, i, -3) != other_color && getLine(node, i, 1) != other_color)
        {
            numoftwo++;
        }
        //其余散棋
        int numOfplyer = 0; // 因为方向会算两次？
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
        if (target_player != AI)
        {
            value -= 100;
        }
    }
    return value;
}

void evaluate_all(int ai_color, int user_color)
{
    for (int i = 1; i < GRID_NUM; i++)
    {
        for (int j = 1; j < GRID_NUM; j++)
        {
            valueBoard[i][j] = evaluate(make_pair(i, j), AI, ai_color, user_color) + evaluate(make_pair(i, j), USER, ai_color, user_color);
        }
    }
}

int evaluate(int now_color) {
	int ai_color = now_color, user_color = 3 - now_color;

	evaluate_all(ai_color, user_color);
	int max = valueBoard[0][0];
	int max_x = 1, max_y = 1;
	for (int i = 0; i < GRID_NUM; i++)
	{
		for (int j = 0; j < GRID_NUM; j++)
		{
			if (valueBoard[i][j] > max)
			{
				max = valueBoard[i][j];
				max_x = i;
				max_y = j;
			}
		}
	}
	return max;
}
//由于五子棋搜索分支庞大，通常无法直接搜索到胜负终局，当搜索到一定深度时需要根据局面返回搜索结果。
//参考资料：
//张明亮, 吴俊, 李凡长. 五子棋机器博弈系统评估函数的设计[J]. 计算机应用, 2012, 32(07):1969-1972.
//裴博文. 五子棋人工智能权重估值算法[J]. 电脑编程技巧与维护, 2008(6):69-75.
//https://www.cnblogs.com/maxuewei2/p/4825520.html