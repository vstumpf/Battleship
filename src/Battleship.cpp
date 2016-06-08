#include "Battleship.h"

#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Dense>

//gives random number below x
#define rnd(x) (rand() % (x))

#define isGuessed(x) (!(x) == WATER_SQUARE || (SHIP_MIN < (x) && (x) < SHIP_MAX))
#define isUnhitShip(x) (SHIP_MIN < (x) && (x) < SHIP_MAX)
#define SHIP_HIT_DIFF (SHIP_HIT_MIN - SHIP_MIN)

Battleship::Battleship() {
	initComputerBoard();
	initPlayerBoard();

}

void Battleship::initPlayerBoard() {
	playerBoard.fill(WATER_SQUARE);
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
	computerBoard.fill(WATER_SQUARE);
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
		if ((*b)(botleft.x, botleft.y) != WATER_SQUARE)
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
		square_type = SHIP_21;
		break;
	case 3:
		square_type = SHIP_31;
		break;
	case 4:
		square_type = SHIP_41;
		break;
	case 5:
		square_type = SHIP_51;
		break;
	default:
		return;
	}

	for (int i = 0; i < len; i++) {
		(*b)(botleft.x, botleft.y) = square_type;
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
	if ((*b)(x, y) == WATER_SQUARE) {
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
	if (ret == 1) {
		playerBoard(x, y) += SHIP_HIT_DIFF;
	}
	else {
		playerBoard(x, y) = WATER_MISS;
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
		computerBoard(x, y) = WATER_MISS;
	} else if (ret == 1) {
		computerBoard(x, y) += SHIP_HIT_DIFF;
	}

	return ret;
}

/*
 * If board b has no more ships, return 0
 * else, return 1
 */
int Battleship::checkBoard(Board * b) {
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (isUnhitShip((*b)(x, y)))
				return 1;
		}
	}
	return 0;
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