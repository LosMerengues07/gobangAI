#include "test.h"
#define USE_HEU 1
#define USE_ALPHA 2
#define USE_MINMAX 4

void testSearch(GameLoop & game, int option) {
	clock_t st, endt;

	if (option & 1) {
		st = clock();
		minMaxSearch(black, DEPTH, -inf, +inf, game);
		endt = clock();
		cout << "heuristic search time:" << (double)(endt - st) / CLOCKS_PER_SEC << endl;
	}

	if (option & 2) {
		st = clock();
		minMaxSimpleSearch(black, DEPTH, -inf, +inf, game);
		endt = clock();
		cout << "alpha beta time:" << (double)(endt - st) / CLOCKS_PER_SEC << endl;
	}

	if (option & 4) {
		st = clock();
		minMaxNoAlphaSearch(black, DEPTH, game);
		endt = clock();
		cout << "min max time:" << (double)(endt - st) / CLOCKS_PER_SEC << endl;
	}
}

void test() {
	GameLoop game = GameLoop(true);


	game.clearBoard();
	cout << "-----------start2----------- " << endl;
	chessBoard[7][8] = black;
	chessBoard[7][7] = white;
	DEPTH = 2;

	
	testSearch(game, USE_ALPHA | USE_HEU | USE_MINMAX);

	game.clearBoard();
	cout << "-----------middle2----------- " << endl;
	int black_list[][2] = {
		5, 6,
		5, 9,
		6, 6,
		7, 7,
		8, 7,
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

	testSearch(game, USE_ALPHA | USE_HEU | USE_MINMAX);


	game.clearBoard();
	cout << "-----------start4----------- " << endl;
	chessBoard[7][8] = black;
	chessBoard[7][7] = white;
	DEPTH = 4;


	testSearch(game, USE_ALPHA | USE_HEU | USE_MINMAX);

	game.clearBoard();
	cout << "-----------middle4----------- " << endl;
	for (auto x : black_list) {
		chessBoard[x[0]][x[1]] = black;
	}

	for (auto x : white_list) {
		chessBoard[x[0]][x[1]] = white;
	}

	DEPTH = 4;

	testSearch(game, USE_ALPHA | USE_HEU );

	game.clearBoard();
	cout << "-----------start6----------- " << endl;
	chessBoard[7][8] = black;
	chessBoard[7][7] = white;
	DEPTH = 6;


	testSearch(game, USE_ALPHA | USE_HEU);

	game.clearBoard();
	cout << "-----------middle6----------- " << endl;
	for (auto x : black_list) {
		chessBoard[x[0]][x[1]] = black;
	}

	for (auto x : white_list) {
		chessBoard[x[0]][x[1]] = white;
	}

	DEPTH = 6;

	testSearch(game, USE_ALPHA | USE_HEU);
}