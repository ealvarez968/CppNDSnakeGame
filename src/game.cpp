#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)), random_food(1, static_cast<int>(10)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  int seconds_counter = 0;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update(running);
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;
    
    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      if(food.IsSpecial() == true){
        seconds_counter++;
        //after 5 seconds set special food FALSE
        if (seconds_counter >= 5) {
          seconds_counter = 0;
          food.SetSpecial(false);
        }
      }
      
      renderer.UpdateWindowTitle(score, special, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    

    
    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y, special_food;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    special_food = random_food(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.SetX(x);
      food.SetY(y);

      //if its an  even random number then is special for 5 seconds
      if((special_food%2)==0){
        food.SetSpecial(true);
      }else{
        food.SetSpecial(false);
      }
      return;
    }
  }
}

void Game::Update(bool &running) {
  if (!snake.alive){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                         "Game Over.",
                         "Your snake has eaten itself, sorry.",
                         NULL);

    running = false;
    return;

  } 
  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  //if (food.x == new_x && food.y == new_y) {
  if (food.GetX() == new_x && food.GetY() == new_y) {
    
    
    // Grow snake and increase speed.
    snake.GrowBody();
    if(food.IsSpecial()){
       special++;
    }else{
      score++;
    }

    PlaceFood();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
int Game::GetSpecial() const { return special; }