#include "GameObject.cpp"

class Score : public GameObject {
private:
//	int score = 0;
	int score;

public:
	static int MAX_SCORE;

	Score(int xPos, int yPos) : GameObject("00", xPos, yPos) { score = 0; }

	int get() {
		return score;
	}

	void up() {
		char scoreFromInt[3];
		score++;										// rises current score
		std::sprintf(scoreFromInt, "%d", score);		// converts score int -> char*
		this->setTexture(scoreFromInt);					// updates score texture
	}

	void reset() {
		score = 0;
		this->setTexture("00");
	}
};
