//#include "GameObject.cpp"  // Assuming GameObject is in this header file
#include "Dino.cpp"

class Obstacle : public GameObject {
public:
    // Constructor - uses the GameObject constructor to set initial position
	Obstacle(char* texture) : GameObject(texture, 15, 2) {}

    // Call the move function from GameObject
    void move(){
        GameObject::move(-1, 0);
    }

    int collides(GameObject obj)
    {
    	if ((this->getX() == obj.getX()) && (this->getY() == obj.getY())) {		// if collides
    		return true;
    	}
    	else{ 																	// if not
    		return false;
    	}
    }
};
