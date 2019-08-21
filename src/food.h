#ifndef SNAKE_H
#define SNAKE_H
#include "SDL.h"

class Food{
	public:
		Food(int x, int y){
			position.x = x;
			position.y = y;
		}
		void setX(const int x);
		void setY(const int y);
		void setSpecial(const int special);
		bool isSpecial() const;
		int getX() const;
		int getY() const;
		SDL_Point getPosition() const;

	private:
		SDL_Point position; 
		bool special;


};

#endif