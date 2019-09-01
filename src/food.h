#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include <random>

class Food{
	public:
		Food() : random_x(0, static_cast<int>(10)),
      random_y(0, static_cast<int>(10)),engine(dev()){
      		position.x = random_x(engine);
			position.y = random_y(engine);

      }
		Food(int x, int y){
			position.x = x;
			position.y = y;
		}
		void SetX(const int x);
		void SetY(const int y);
		void SetSpecial(const bool special);
		bool IsSpecial() const;
		int GetX() const;
		int GetY() const;

	private:
		SDL_Point position; 
		bool special;

	

		std::random_device dev;
  		std::mt19937 engine;
  		std::uniform_int_distribution<int> random_x;
  		std::uniform_int_distribution<int> random_y;


};

#endif