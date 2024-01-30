#include "GameObject.cpp"  // Assuming GameObject is in this header file


class Dino : public GameObject
{
private:
    int delay;
public:
    static const int FLY_TIME = 3;

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
