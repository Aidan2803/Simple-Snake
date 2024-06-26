#include "game.hpp"

void Game::InitGame() {
  initscr();
  // Don't echo user input
  noecho();
  // Hide the cursor
  curs_set(0);
  // Enable keypad mode to capture function keys
  keypad(stdscr, TRUE);

  timer_->StartTimer();
}

void Game::MapUserInput() {
  switch (user_input_) {
    case 'a':
      direction_ = SnakeDirection::LEFT;
      break;
    case 'd':
      direction_ = SnakeDirection::RIGHT;
      break;
    case 'w':
      direction_ = SnakeDirection::UP;
      break;
    case 's':
      direction_ = SnakeDirection::DOWN;
      break;
    default:
      break;
  }
}

void Game::Render() {
  snake_.get()->RenderSnake();
  food_proxy_.get()->RenderFood();
}

std::pair<bool, Point> Game::IsSnakeFoodCollision() {
  const auto snake_head = snake_.get()->get_head();

  for (auto &food : food_proxy_.get()->GetFoodVector()) {
    const auto food_point = food.GetPoint();
    if (food_point.x_ == snake_head.x_ && food_point.y_ == snake_head.y_) {
      Logger::log("[GAME] Snake food colision true ", snake_head.x_, " ", snake_head.y_);
      return std::pair<bool, Point>(true, snake_head);
    }
  }
  return std::pair<bool, Point>(false, snake_head);
}

void Game::GameLoop() {
  nodelay(stdscr, TRUE);
  while (is_game_running_) {
    clear();
    Render();
    refresh();

    int ch = getch();
    if (ch != ERR) {
      user_input_ = ch;
      MapUserInput();
      snake_.get()->SetDirection(direction_);
    }

    snake_.get()->Move();
    auto snake_found_food = IsSnakeFoodCollision();
    if (snake_found_food.first && food_proxy_.get()->IsEaten(snake_found_food.second) == false) {
      food_proxy_.get()->SetIsEatenTrue(snake_found_food.second);
      snake_.get()->Eat();
    }

    MangaeFoodSpawning();
    napms(100);
  }
  nodelay(stdscr, FALSE);
}