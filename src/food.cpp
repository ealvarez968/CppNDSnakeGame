#include "food.h"
#include <iostream>


void Food::SetX  ( const int x) {
	position.x = x;
}

void Food::SetY  (const int y) {
	position.y = y;
}
void Food::SetSpecial  (const bool special) {
	this->special = special;

}
bool Food::IsSpecial() const{

	return special;
}

int Food::GetX() const{
	return position.x;
}

int Food::GetY() const{
	return position.y;
}

