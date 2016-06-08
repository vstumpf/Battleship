#pragma once

#ifndef __BATTLESHIP_H__

#define __BATTLESHIP_H__
#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Dense>


enum SQUARE_TYPES {
	WATER_SQUARE = 1,
	WATER_MISS = 2, //guessed
	SHIP_HIT = 3,		//guessed
	SHIP_MIN = 10,
	SHIP_21 = SHIP_MIN,
	SHIP_22,
	SHIP_31,
	SHIP_32,
	SHIP_33,
	SHIP_41,
	SHIP_42,
	SHIP_43,
	SHIP_44,
	SHIP_51,
	SHIP_52,
	SHIP_53,
	SHIP_54,
	SHIP_55,
	SHIP_MAX = SHIP_55,
	SHIP_HIT_MIN = 30,	//guessed
	SHIP_21_HIT = SHIP_HIT_MIN,	//...
	SHIP_22_HIT,
	SHIP_31_HIT,
	SHIP_32_HIT,
	SHIP_33_HIT,
	SHIP_41_HIT,
	SHIP_42_HIT,
	SHIP_43_HIT,
	SHIP_44_HIT,
	SHIP_51_HIT,
	SHIP_52_HIT,
	SHIP_53_HIT,
	SHIP_54_HIT,
	SHIP_55_HIT,
	SHIP_HIT_MAX = 59	//guessed
};

typedef Eigen::Matrix<int, 10, 10> Board;
typedef Eigen::Matrix<int, 2, 2> Square;

class Battleship {

public:
	Battleship();
	~Battleship();
	Board playerBoard;
	Board computerBoard;
	void initComputerBoard();
	void initPlayerBoard();
	int canAddBoat(Board * b, Square botleft, int rotate, int len);
	void addBoat(Board * b, Square botleft, int rotate, int len);
	int guess(Board * b, int x, int y);
	int computerGuess();
	int playerGuess(int x, int y);
	int checkBoard(Board * b);
	int checkWinner();
};

#endif