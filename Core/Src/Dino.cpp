#include "GameObject.cpp"  // Assuming GameObject is in this header file


class Dino : public GameObject
{
private:
    int delay;
    int frame;
    char textures_[2][8];

public:
    static const int FLY_TIME = 3;

    Dino(char textures[2][8], int xPos, int yPos) : GameObject(textures[1], xPos, yPos) {
//    	textures_ = textures;
    	for (int i = 0; i < 2; i++) {
			std::memcpy(textures_[i], textures[i], sizeof(textures[i]));
		}
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
