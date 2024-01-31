#pragma once

#include <cstring>				// for strcpy()
#include <cstdint>				// for uint8_t
#include "lcd.h"

class GameObject
{
private:
    char* texture_;
    uint8_t xPos_;
    uint8_t yPos_;

public:
	GameObject(char* texture, uint8_t xPos, uint8_t yPos)
    {
    	texture_ = texture;
    	xPos_ = xPos;
		yPos_ = yPos;
    }

	// Defines virtual default destructor
	virtual ~GameObject() = default;

	uint8_t getX(){
    	return xPos_;
	}

	uint8_t getY(){
        return yPos_;
	}

    char* getTexture(){
        return texture_;
	}

    virtual void draw(){
    	lcd_print(yPos_, xPos_, texture_);
	}

protected:
    void move(uint8_t diffX, uint8_t diffY) {
		xPos_ += diffX;
		yPos_ += diffY;
	}

    void setTexture(char* new_texture) {
    	std::strcpy(texture_, new_texture);
    }
};
