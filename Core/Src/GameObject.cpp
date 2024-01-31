#include <cstring>
#include "lcd.h"

class GameObject
{
private:
    char* texture_;
    int xPos_, yPos_;

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

    char* getTexture(){
        return texture_;
	}

    virtual void draw(int row, int column){
    	lcd_print(row, column, texture_);
	}

protected:
    void move(int diffX, int diffY) {
		xPos_ += diffX;
		yPos_ += diffY;
	}

    void setTexture(char* new_texture) {
    	std::strcpy(texture_, new_texture);
    }
};
