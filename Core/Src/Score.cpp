#include "GameObject.cpp"

class Score : public GameObject
{
private:
	int score = 0;

public:
	Score(int xPos, int yPos) : GameObject(char("00"), xPos, yPos) {}

	static int MAX_SCORE;

	int getMAX_SCORE(){
		return MAX_SCORE;
	}

	void up(){
		score++;
	}

};
