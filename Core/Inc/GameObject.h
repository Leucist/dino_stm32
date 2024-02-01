#pragma once

#include <cstring>				// for strcpy()
#include <cstdint>				// for uint8_t
#include "lcd.h"

class GameObject
{
private:
//    char* texture_;
	uint8_t textureNum_;
    uint8_t xPos_;
    uint8_t yPos_;

public:
	GameObject(uint8_t textureNum, uint8_t xPos, uint8_t yPos)
    {
		textureNum_ = textureNum;
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

//    uint8_t getTexture(){
//        return textureNum_;
//	}

    virtual void draw(){
    	lcd_char(yPos_, xPos_, textureNum_);
	}

protected:
    void move(uint8_t diffX, uint8_t diffY) {
		xPos_ += diffX;
		yPos_ += diffY;
	}

    void setTexture(uint8_t textureNum) {
//    	std::strcpy(texture_, new_texture);
    	this->textureNum_ = textureNum;
    }
};
