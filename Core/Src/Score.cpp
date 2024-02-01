#include <cstdio>				// for sprintf()
#include "GameObject.h"

class Score : public GameObject {
private:
	uint8_t score;

public:
	static const uint8_t SCORE_LIMIT = 99;
	uint8_t MAX_SCORE;

	Score(uint8_t xPos, uint8_t yPos) : GameObject(0, xPos, yPos) {
		score = 0;
		MAX_SCORE = 0;
	}

	int get() {
		return score;
	}

	void draw() {
		char scoreFromInt[3];
		std::sprintf(scoreFromInt, "%02d", score);				// converts score int -> char*
		lcd_print(this->getY(), this->getX(), scoreFromInt);
	}

	void up() {
		score++;		// rises current score
	}

	void calculateMaxScore() {
		this->MAX_SCORE = this->MAX_SCORE > this->score ? this->MAX_SCORE : this->score;
	}

	void reset() {
		score = 0;
//		char zeroScore[] = "00";
//		this->setTexture("00");
	}
};
