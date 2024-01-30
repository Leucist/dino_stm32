#include "GameObject.cpp"  // Assuming GameObject is in this header file

class Dino : GameObject
{
private:
    const int FLY_TIME = 3;
    int delay;
public:
    Dino(char* texture, int xPos, int yPos) : GameObject(texture, xPos, yPos) {

      }

    void jump(){
            GameObject::move(0, 1);
            delay = FLY_TIME;
        }

    void fall(){
    	if(delay > 0){
    		delay--;
    	}
    	else if(delay == 0){
    		delay = 0;
    		GameObject::move(0, -1);
    	}
    }

};
