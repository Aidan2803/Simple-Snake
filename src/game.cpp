#include "game.hpp"

void Game::InitGame() {
  initscr();
  // Don't echo user input
  noecho();
  // Hide the cursor
  curs_set(0);
  // Enable keypad mode to capture function keys
  keypad(stdscr, TRUE);
  Logger::logToFile("right before timer start!");

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
  food_.get()->RenderFood();
}

bool Game::IsSnakeFoodCollision() {
  const auto food_point = food_.get()->GetFoodPoint();
  const auto snake_head = snake_.get()->get_head();

  if (food_point.x == snake_head.x && food_point.y == snake_head.y) {
    return true;
  } else {
    return false;
  }
}

void Game::GameLoop() {
  while (is_game_running_) {
    clear();
    Render();
    refresh();

    user_input_ = getch();
    MapUserInput();

    snake_.get()->SetDirection(direction_);
    snake_.get()->Move();
    auto snake_to_perform_eat = IsSnakeFoodCollision();
    if (snake_to_perform_eat) {
      food_.get()->SetIsEatenTrue();
      food_.get()->DeleteFoodFromScreen();
      snake_.get()->Eat();
    }

    MangaeFoodSpawning();
  }
}