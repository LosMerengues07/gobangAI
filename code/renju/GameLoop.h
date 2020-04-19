#pragma once
#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "evaluate.h"
class GameLoop
{
	int user_color;//�û�ִ����ɫ
	int ai_color;//aiִ����ɫ
	int cur_turn;//��ǰ��Ϊ�û�����ai
	string log = "";
	void printMenu();//��ӡ�˵�
	void printLog();//��ӡ������Ϣ

	void userLoop();//ÿ��ѭ��ʱ�û��Ĳ���,��Ҫ�Ǵ�������
	void aiLoop();//ÿ��ѭ��ʱai�Ĳ���


public:
	GameLoop(bool ai_is_black);
	inline void clearBoard() {
		for (int i = 0; i < GRID_NUM; i++)
			for (int j = 0; j < GRID_NUM; j++)
				chessBoard[i][j] = blank;
	}//�������

	bool isWin(); //�Ƿ�ʤ��,On2
	bool isLose(); //�Ƿ�ʧ�� On2
	bool isGameOver(int last_x, int last_y, int last_color); //ֻ������һ�������ж��Ƿ�ʤ��,O1
	void run();
	~GameLoop();

	map<pair<long long, long long>, int> zobrist_map;//zobristɢ�б�
	long long cur_zobrist[2] = { 0,0 };//���壬�����zobristֵ
	long long zobrist[GRID_NUM][GRID_NUM];//zobrist��ͼ

	void cal_zobrist(){
		cur_zobrist[0] = cur_zobrist[1] = 0;
		for (int i = 0; i < GRID_NUM; i++)
			for (int j = 0; j < GRID_NUM; j++) {
				if (chessBoard[i][j] == white) {
					cur_zobrist[0] ^= zobrist[i][j];
				}
				if (chessBoard[i][j] == black) {
					cur_zobrist[1] ^= zobrist[i][j];
				}
			}
	}

	void update_zobrist(int x, int y, int color) {
		if (color == white)
			cur_zobrist[0] ^= zobrist[x][y];
		if(color == black)
			cur_zobrist[1] ^= zobrist[x][y];
	}
};

