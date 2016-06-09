#pragma once

#ifndef __BATTLESHIP_H__

#define __BATTLESHIP_H__
#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Dense>


enum SQUARE_TYPES {
	SQ_WATER_SQUARE = 1,
	SQ_WATER_MISS = 2, //guessed
	SQ_SHIP_HIT = 3,		//guessed
	SQ_SHIP_MIN = 10,
	SQ_SHIP_21 = SQ_SHIP_MIN,
	SQ_SHIP_22,
	SQ_SHIP_31,
	SQ_SHIP_32,
	SQ_SHIP_33,
	SQ_SHIP_41,
	SQ_SHIP_42,
	SQ_SHIP_43,
	SQ_SHIP_44,
	SQ_SHIP_51,
	SQ_SHIP_52,
	SQ_SHIP_53,
	SQ_SHIP_54,
	SQ_SHIP_55,
	SQ_SHIP_MAX = SQ_SHIP_55,
	SQ_SHIP_HIT_MIN = 30,	//guessed
	SQ_SHIP_21_HIT = SQ_SHIP_HIT_MIN,	//...
	SQ_SHIP_22_HIT,
	SQ_SHIP_31_HIT,
	SQ_SHIP_32_HIT,
	SQ_SHIP_33_HIT,
	SQ_SHIP_41_HIT,
	SQ_SHIP_42_HIT,
	SQ_SHIP_43_HIT,
	SQ_SHIP_44_HIT,
	SQ_SHIP_51_HIT,
	SQ_SHIP_52_HIT,
	SQ_SHIP_53_HIT,
	SQ_SHIP_54_HIT,
	SQ_SHIP_55_HIT,
	SQ_SHIP_HIT_MAX = 59	//guessed
};

typedef Eigen::Matrix<int, 10, 10> Board;
typedef Eigen::Vector2i Square;

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
	void printBoard();
	int getSquareMat(Board * b, int x, int y);
	int getPlayerSquareMat(int x, int y) { return getSquareMat(&playerBoard, x, y); };
	int getComputerSquareMat(int x, int y);

};

#endif