#include "GameObject.h"


class Dino : public GameObject
{
private:
	uint8_t delay;
	uint8_t frame;
    char textures_[2][8];

public:
    static const uint8_t FLY_TIME = 3;

    Dino(char textures[2][8], uint8_t xPos, uint8_t yPos) : GameObject(textures[1], xPos, yPos) {
//    	textures_ = textures;
    	for (int i = 0; i < 2; i++) {
			std::memcpy(textures_[i], textures[i], sizeof(textures[i]));
		}
    	delay = 0;
    	frame = 0;
      }

    void jump(){
            GameObject::move(0, 1);
            delay = FLY_TIME;
        }

    void fall(){
    	if(delay > 0){
    		delay--;
    	}
    	else {
    		delay = 0;
    		GameObject::move(0, -1);
    	}
    }

    void draw() {
    	lcd_print(this->getX(), this->getY(), textures_[frame++]);
    	if (frame > 1) frame = 0;
    }
};
