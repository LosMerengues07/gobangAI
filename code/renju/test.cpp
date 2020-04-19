#include "test.h"
#define USE_MINMAX 1
#define USE_ALPHA 2
#define USE_HEAU 4
#define USE_ZOBRIST 8
#define USE_HEAU_ZOBRIST 16
//选项使用时，a|b|c代表测试a和b和c

void testSearch(GameLoop & game, int option) {
	clock_t st, endt;

	if (option & USE_HEAU) {
		st = clock();
		minMaxHeauSearch(black, DEPTH, -inf, +inf, game);
		endt = clock();
		cout << "heuristic search time:" << (double)(endt - st) / CLOCKS_PER_SEC << endl;
	}

	if (option & USE_ALPHA) {
		st = clock();
		minMaxAlphaSearch(black, DEPTH, -inf, +inf, game);
		endt = clock();
		cout << "alpha beta time:" << (double)(endt - st) / CLOCKS_PER_SEC << endl;
	}

	if (option & USE_MINMAX) {
		st = clock();
		minMaxSearch(black, DEPTH, game);
		endt = clock();
		cout << "min max time:" << (double)(endt - st) / CLOCKS_PER_SEC << endl;
	}

	if (option & USE_ZOBRIST) {
		st = clock();
		game.cal_zobrist();
		minMaxZobristSearch(black, DEPTH, -inf, +inf, game);
		endt = clock();
		cout << "zobrist time:" << (double)(endt - st) / CLOCKS_PER_SEC << endl;
	}

	if (option & USE_HEAU_ZOBRIST) {
		st = clock();
		game.cal_zobrist();
		minMaxHeauZobristSearch(black, DEPTH, -inf, +inf, game);
		endt = clock();
		cout << "zobrist heau time:" << (double)(endt - st) / CLOCKS_PER_SEC << endl;
	}
}

void test() {
	GameLoop game = GameLoop(true);

	
	game.clearBoard();
	cout << "-----------start2----------- " << endl;
	chessBoard[7][8] = black;
	chessBoard[7][7] = white;
	DEPTH = 2;

	
	testSearch(game, 31);

	game.clearBoard();
	cout << "-----------middle2----------- " << endl;
	int black_list[][2] = {
		5, 6,	// 中盘
		5, 9,	//	的
		6, 6,	//	一个例子
		7, 7,	//	的黑棋
		8, 7,	//	坐标
		8, 8,
		9, 7,
		9, 8,
		10, 9
	};

	int white_list[][2] = {
		5, 8,
		6, 7,
		6, 8,
		6, 9,
		7, 6,
		7, 8, 
		7, 9,
		8, 9,
		9, 9
	};
	
	for (auto x : black_list) {
		chessBoard[x[0]][x[1]] = black;
	}

	for (auto x : white_list) {
		chessBoard[x[0]][x[1]] = white;
	}

	DEPTH = 2;

	testSearch(game, 31);


	game.clearBoard();
	cout << "-----------start4----------- " << endl;
	chessBoard[7][8] = black;
	chessBoard[7][7] = white;
	DEPTH = 4;


	testSearch(game, 31);

	game.clearBoard();
	cout << "-----------middle4----------- " << endl;
	for (auto x : black_list) {
		chessBoard[x[0]][x[1]] = black;
	}

	for (auto x : white_list) {
		chessBoard[x[0]][x[1]] = white;
	}

	DEPTH = 4;

	testSearch(game, 30);

	game.clearBoard();
	cout << "-----------start6----------- " << endl;
	chessBoard[7][8] = black;
	chessBoard[7][7] = white;
	DEPTH = 6;


	testSearch(game, 30);

	game.clearBoard();
	cout << "-----------middle6----------- " << endl;
	for (auto x : black_list) {
		chessBoard[x[0]][x[1]] = black;
	}

	for (auto x : white_list) {
		chessBoard[x[0]][x[1]] = white;
	}

	DEPTH = 6;

	testSearch(game, USE_HEAU | USE_HEAU_ZOBRIST);
}