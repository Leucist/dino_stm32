#include "GameObject.cpp"

class Score : public GameObject
{
private:
    int delay;
public:
    static const int SCORE_LIMIT = 99;
    static int MAX_SCORE;

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
