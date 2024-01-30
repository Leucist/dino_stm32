#include <iostream>
#include "lcd.h"

class GameObject
{
public:
    GameObject(char* texture, int xPos, int yPos)
    {
    	texture_ = texture;
    	xPos_ = xPos;
		yPos_ = yPos;
    }

    int getX(){
    	return xPos_;
        }

    int getY(){
        return yPos_;
        }

    int getTexture(){
        return *texture_;
        }

    void draw(int raw, int column){
    	lcd_print(raw, column, texture_);
        }

private:
    char* texture_;
    int xPos_, yPos_;

protected:
    void move(int diffX, int diffY)
        {
    	    xPos_ += diffX;
    	    yPos_ += diffY;
        }
};
