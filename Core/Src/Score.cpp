#include <cstdio>				// for sprintf()
#include "GameObject.h"

class Score : public GameObject {
private:
//	int score = 0;
	uint8_t score;

public:
	static const uint8_t SCORE_LIMIT = 99;
	uint8_t MAX_SCORE;

	Score(uint8_t xPos, uint8_t yPos) : GameObject("00", xPos, yPos) {
		score = 0;
		MAX_SCORE = 0;
	}

	int get() {
		return score;
	}

	void up() {
		char scoreFromInt[3];
		score++;										// rises current score
		std::sprintf(scoreFromInt, "%d", score);		// converts score int -> char*
		this->setTexture(scoreFromInt);					// updates score texture
	}

	void calculateMaxScore() {
		this->MAX_SCORE = this->MAX_SCORE > this->score ? this->MAX_SCORE : this->score;
	}

	void reset() {
		score = 0;
		char zeroScore[] = "00";
		this->setTexture(zeroScore);
	}
};
