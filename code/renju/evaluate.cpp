#include "evaluate.h"

int getLine(pair<int, int> node, int direction, int offset)
{ // node：当前点  i：方向  j：坐标相对值 
    int x = node.first;
    int y = node.second;
    switch (direction)
    {
    case 0:
        break;
    case 1:
        x = x + offset;
        break;
    case 2:
        x = x + offset;
        y = y + offset;
        break;
    case 3:
        y = y + offset;
        break;
    case 4:
        x = x - offset;
        y = y + offset;
    }
    if(!inboard(x,y))
    { // 越界处理
        return out;
    }
    return chessBoard[x][y];
}

void getPoints(int x, int y, int offset, int direction, pair<int, int>* nodes)
{
    switch (direction)
    {
    case 0:
        break;
    case 1:
        for (int i = 0; i < 5; i++)
        {
            nodes[i] = make_pair(x + (offset + i), y);
        }
        break;
    case 2:
        for (int i = 0; i < 5; i++)
        {
            nodes[i] = make_pair(x + (offset + i), y + (offset + i));
        }
        break;
    case 3:
        for (int i = 0; i < 5; i++)
        {
            nodes[i] = make_pair(x, y + (offset + i));
        }
        break;
    case 4:
        for (int i = 0; i < 5; i++)
        {
            nodes[i] = make_pair(x - (offset + i), y + (offset + i));
        }
    }
}

int cal_score(pair<int, int> node, int direction ,int my_player, int ai_color, int user_color, vector<map<string, int>>* score_all_arr)
{
    int my_color = 0;
    int enemy_color = 0;
    map<string, int> max_score_shape;
    max_score_shape["score"] = 0;
    max_score_shape["direction"] = direction;
    if (my_player == AI)
    {
        my_color = ai_color;
        enemy_color = user_color;
    }else if (my_player == USER)
    {
        my_color = user_color;
        enemy_color = ai_color;
    }

    for (auto item : *score_all_arr)
    {
        pair<int, int> arr[5];
        getPoints(item["x"], item["y"], item["offset"], item["direction"], arr);
        for (auto pt : arr)
        {
            if (pt == node && direction == item["direction"])
                return 0;
        }
    }

    for (int offset = -5; offset <= 0; offset++)
    {
        string pos[6];
        for (int i = 0; i <= 5; i++)
        {
            if (getLine(node, direction, i + offset) == blank)
            {
                pos[i] = "0";
            }
            else if (getLine(node, direction, i + offset) == my_color)
            {
                pos[i] = "1";
            }
            else
            {
                pos[i] = "2";
            }
        }
        string tmp_shap5 = pos[0] + pos[1] + pos[2] + pos[3] + pos[4];
        string tmp_shap6 = pos[0] + pos[1] + pos[2] + pos[3] + pos[4] + pos[5];
        cout << tmp_shap5 << "   " << tmp_shap6 << endl;
        for (map<string, int>::iterator it = score_map.begin(); it != score_map.end(); ++it)
        {
            if (tmp_shap5 == it->first || tmp_shap6 == it->first)
            {
                if (it->second > max_score_shape["score"])
                {
                    max_score_shape["x"] = node.first;
                    max_score_shape["y"] = node.second;
                    max_score_shape["offset"] = offset;
                    max_score_shape["score"] = it->second;
                    max_score_shape["direction"] = direction;
                }
            }
        }
    }
    int add_score = 0;
    if (max_score_shape["score"] != 0)
    {
        for (auto item : *score_all_arr)
        {
            pair<int, int> arr1[5], arr2[5];
            getPoints(item["x"], item["y"], item["offset"], item["direction"], arr1);
            getPoints(max_score_shape["x"], max_score_shape["y"], max_score_shape["offset"], max_score_shape["direction"], arr2);
            for (auto pt1 : arr1)
            {
                for (auto pt2 : arr2)
                {
                    if (pt1 == pt2 && item["score"] > 10 && max_score_shape["score"] > 10)
                    {
                        add_score += item["score"] + max_score_shape["score"];
                    }
                }

            }
        }
        score_all_arr->push_back(max_score_shape);
    }
    return add_score + max_score_shape["score"];
}

float evaluate(int ai_color, int user_color)
{
    int my_score = 0;
    int enemy_score = 0;
    vector<map<string, int>> score_all_arr_my;
    vector<map<string, int>> score_all_arr_enemy;
    for (int i = 1; i < GRID_NUM; i++)
    {
        for (int j = 1; j < GRID_NUM; j++)
        {
            pair<int, int> node = make_pair(i, j);
            if (getLine(node, 0, 0) == ai_color) //判断此位置是否已经落子
            {
                my_score += cal_score(make_pair(i, j), 1, AI, ai_color, user_color, &score_all_arr_my);
                my_score += cal_score(make_pair(i, j), 2, AI, ai_color, user_color, &score_all_arr_my);
                my_score += cal_score(make_pair(i, j), 3, AI, ai_color, user_color, &score_all_arr_my);
                my_score += cal_score(make_pair(i, j), 4, AI, ai_color, user_color, &score_all_arr_my);
            }
            else if (getLine(node, 0, 0) == user_color)
            {
                enemy_score += cal_score(make_pair(i, j), 1, USER, ai_color, user_color, &score_all_arr_enemy);
                enemy_score += cal_score(make_pair(i, j), 2, USER, ai_color, user_color, &score_all_arr_enemy);
                enemy_score += cal_score(make_pair(i, j), 3, USER, ai_color, user_color, &score_all_arr_enemy);
                enemy_score += cal_score(make_pair(i, j), 4, USER, ai_color, user_color, &score_all_arr_enemy);
            }
        }
    }
    cout << "ai score: " << my_score << endl;
    cout << "user score: " << enemy_score << endl;
    return my_score - 0.1*enemy_score;
}
//由于五子棋搜索分支庞大，通常无法直接搜索到胜负终局，当搜索到一定深度时需要根据局面返回搜索结果。
//参考资料：
//张明亮, 吴俊, 李凡长. 五子棋机器博弈系统评估函数的设计[J]. 计算机应用, 2012, 32(07):1969-1972.
//裴博文. 五子棋人工智能权重估值算法[J]. 电脑编程技巧与维护, 2008(6):69-75.
//https://www.cnblogs.com/maxuewei2/p/4825520.html