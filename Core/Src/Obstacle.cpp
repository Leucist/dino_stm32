//#include "GameObject.cpp"  // Assuming GameObject is in this header file
#include "Dino.cpp"

class Obstacle : public GameObject {
public:
    // Constructor - uses the GameObject constructor to set initial position
	Obstacle(char* texture, int xPos, int yPos, Dino& dinosaur) : GameObject(texture, xPos, yPos) {
		this->setX(15);
		dinosaur_ = &dinosaur;
    }

    // Override the move function from GameObject
    void move(){
        GameObject::move(-1, 0);
    }

    int collides()
    {
    	if ( (this->getX() == dinosaur_->getX()) && (this->getY() == dinosaur_->getY()) ) { // if collides
    		return true;
    	}
    	else{ // if not
    		return false;
    	}
    }
private:
    Dino* dinosaur_;


};
