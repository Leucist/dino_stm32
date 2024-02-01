#include "GameObject.h"


class Dino : public GameObject
{
private:
	uint8_t delay;
	uint8_t frame;
	uint8_t textures_[2];

public:
    static const uint8_t FLY_TIME = 3;

    Dino(uint8_t textures[2], uint8_t xPos, uint8_t yPos) : GameObject(textures[0], xPos, yPos) {
    	for (int i = 0; i < 2; i++) {
    		textures_[i] = textures[i];
    	}
//    	for (int i = 0; i < 2; i++) {
//			std::memcpy(textures_[i], textures[i], sizeof(textures[i]));
//		}
    	delay = 0;
    	frame = 0;
      }

    void jump(){
//            GameObject::move(0, -1);
    		this->move(0, -1);
            delay = FLY_TIME;
        }

    void fall(){
    	if(delay > 0){
    		delay--;
    	}
    	else {
//    		GameObject::move(0, 1);
    		this->move(0, 1);
    	}
    }

    void draw() {
    	lcd_char(this->getY(), this->getX(), textures_[frame++]);
    	if (frame > 1) frame = 0;
    }
};
