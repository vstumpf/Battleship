#include "Battleship.h"

#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Dense>
#include <cassert>
#include <cstring>
#include <iostream>
#include "Material.h"

using namespace std;

//gives random integer in [0, x)
#define rnd(x) (rand() % (x))

#define isGuessed(x) (!((x) == SQ_WATER_SQUARE || (SQ_SHIP_MIN <= (x) && (x) <= SQ_SHIP_MAX)))
#define isUnhitShip(x) (SQ_SHIP_MIN <= (x) && (x) <= SQ_SHIP_MAX)
#define isHitShip(x) (SQ_SHIP_HIT_MIN <= (x) && (x) <= SQ_SHIP_HIT_MAX)
#define SHIP_HIT_DIFF (SQ_SHIP_HIT_MIN - SQ_SHIP_MIN)

Battleship::Battleship() {
	initComputerBoard();
	initPlayerBoard();
}

void Battleship::initPlayerBoard() {
	playerBoard.fill(SQ_WATER_SQUARE);
	for (int i = 2; i < 6; i++) {
		int added = 0, rotate = 0;
		Square botleft;
		do {
			botleft = Square(rnd(10 - i), rnd(10 - i));
			rotate = rnd(2);
			added = canAddBoat(&playerBoard, botleft, rotate, i);
		} while (added == 0);
		addBoat(&playerBoard, botleft, rotate, i);
	}
}

void Battleship::initComputerBoard() {
	computerBoard.fill(SQ_WATER_SQUARE);
	for (int i = 2; i < 6; i++) {
		int added = 0, rotate = 0;
		Square botleft;
		do {
			botleft = Square(rnd(10 - i), rnd(10 - i));
			rotate = rnd(2);
			added = canAddBoat(&computerBoard, botleft, rotate, i);
		} while (added == 0);
		addBoat(&computerBoard, botleft, rotate, i);
	}
}


/*
 * Tries to add boat to the board b
 * Returns 1 if success, 0 if failure
 */
int Battleship::canAddBoat(Board * b, Square botleft, int rotate, int len) {
	Square diff;
	if (rotate)
		diff = Square(0, 1);
	else
		diff = Square(1, 0);
	for (int i = 0; i < len; i++) {
		if ((*b)(botleft[0], botleft[1]) != SQ_WATER_SQUARE)
			return 0;
		botleft += diff;
	}
}

/* 
 * Adds boat to the gameboard b
 */
void Battleship::addBoat(Board * b, Square botleft, int rotate, int len) {
	Square diff;
	int square_type;
	if (rotate)
		diff = Square(0, 1);
	else
		diff = Square(1, 0);
	switch (len) {
	case 2:
		square_type = SQ_SHIP_21;
		break;
	case 3:
		square_type = SQ_SHIP_31;
		break;
	case 4:
		square_type = SQ_SHIP_41;
		break;
	case 5:
		square_type = SQ_SHIP_51;
		break;
	default:
		return;
	}

	for (int i = 0; i < len; i++) {
		(*b)(botleft[0], botleft[1]) = square_type;
		botleft += diff;
		square_type++;
	}
	return;
}

/*
 * If empty, return 0
 * If Board b[x][y] is occupied, return 1
 * If already guessed, return 2
 */
int Battleship::guess(Board * b, int x, int y) {
	if ((*b)(x, y) == SQ_WATER_SQUARE) {
		return 0;
	}
	
	if (isGuessed((*b)(x, y))) {
		return 2;
	}

	return 1;
}

/*
 * Computer generates a guess
 * Sets the playerBoard square to WATER_MISS or SHIP_Xx_HIT
 * returns 0 if empty
 * returns 1 if hit
 */
int Battleship::computerGuess() {
	int ret = 2;
	int x, y;
	while (ret == 2) {
		x = rnd(10);
		y = rnd(10);
		ret = guess(&playerBoard, x, y);
	}

	cout << "Computer guessed " << x << " " << y << endl;
	if (ret == 1) {
		playerBoard(x, y) += SHIP_HIT_DIFF;
	}
	else {
		playerBoard(x, y) = SQ_WATER_MISS;
	}

	return ret;
}

/*
 * If empty, return 0
 * If Board b[x][y] is occupied, return 1
 * If already guessed, return 2
 */
int Battleship::playerGuess(int x, int y) {
	int ret = guess(&computerBoard, x, y);
	if (ret == 0) {
		computerBoard(x, y) = SQ_WATER_MISS;
	} else if (ret == 1) {
		computerBoard(x, y) += SHIP_HIT_DIFF;
	}
	return ret;
}

/*
 * If board b has no more ships, return 1
 * else, return 0
 */
int Battleship::checkBoard(Board * b) {
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (isUnhitShip((*b)(x, y)))
				return 0;
		}
	}
	return 1;
}

/*
 * If no one won yet, return 0
 * IF player won, return 1
 * If computer won, return 2
 */
int Battleship::checkWinner() {
	if (checkBoard(&computerBoard)) {
		return 1;
	}
	if (checkBoard(&playerBoard)) {
		return 2;
	}
	return 0;
}

void Battleship::printBoard() {
	cout << "====================================" << endl;
	cout << computerBoard.transpose() << endl;
	cout << "====================================" << endl;
}


/*Returns material type for square at Board b[x, y]*/
int Battleship::getSquareMat(Board * b, int x, int y) {
	int type = (*b)(x, y);
	if (type == SQ_WATER_SQUARE) {
		return MAT_WATER;
	}
	else if (type == SQ_WATER_MISS) {
		return MAT_WATER_MISS;
	}
	else if (isUnhitShip(type)) {
		return MAT_SHIP;
	}
	else {
		return MAT_SHIP_HIT;
	}
}

int Battleship::getComputerSquareMat(int x, int y) {
	int type = computerBoard(x, y);
	if (isHitShip(type)) {
		return MAT_SHIP_HIT;
	}
	else if (type == SQ_WATER_MISS) {
		return MAT_WATER_MISS;
	}
	else {
		return MAT_WATER;
	}
}