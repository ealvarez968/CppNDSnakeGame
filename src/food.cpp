#include "food.h"
#include <iostream>


void Food::setX  ( const int x) {
	position.x = x;
}

void Food::setY  (const int y) {
	position.y = y;
}
void Food::setSpecial  (const int special) {
	this->special = special == 0?false: true;
}
bool Food::isSpecial() const{
	return special;
}

int Food::getX() const{
	return position.x;
}

int Food::getY() const{
	return position.y;
}

SDL_Point Food::getPosition() const{
	return position;
}


		/*int getX const ()
		int getY const ()
		SDL_Point getPosition() const()*/