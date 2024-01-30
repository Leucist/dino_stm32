#include "GameObject.cpp"  // Assuming GameObject is in this header file

class Obstacle : GameObject {
public:
    // Constructor - uses the GameObject constructor to set initial position
	Obstacle(char* texture, int xPos, int yPos) : GameObject(texture, xPos, yPos) {

    }

    // Override the move function from GameObject
    void move(){
        GameObject::move(-1, 0);
    }

    int collides()
    {
    	if (GameObject::getX() == 1 && GameObject::getY() == 2) { // if collides
    		return 0;
    	}
    	else{ // if not
    		return 1;
    	}
    }

};
