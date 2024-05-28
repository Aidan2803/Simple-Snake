#include "snake.hpp"

void Snake::Move() {
  Point head = get_head();
  Logger::logToFile("x ", head.x, " y ", head.y);

  switch (direction_) {
    case SnakeDirection::UP:
      head.y--;
      break;
    case SnakeDirection::DOWN:
      head.y++;
      break;
    case SnakeDirection::RIGHT:
      head.x++;
      break;
    case SnakeDirection::LEFT:
      head.x--;
      break;
    default:
      break;
  }
  snake_.push_front(head);
  snake_.pop_back();
}

void Snake::Eat() {
  Point newNodePoint = snake_.back();
  if (direction_ == SnakeDirection::LEFT) {
    newNodePoint.x--;
    snake_.push_back(newNodePoint);
  } else if (direction_ == SnakeDirection::RIGHT) {
    newNodePoint.x++;
    snake_.push_back(newNodePoint);
  } else if (direction_ == SnakeDirection::UP) {
    newNodePoint.y--;
    snake_.push_back(newNodePoint);
  } else if (direction_ == SnakeDirection::DOWN) {
    newNodePoint.y++;
    snake_.push_back(newNodePoint);
  }
}

void Snake::SetDirection(SnakeDirection direction) {
  if ((direction_ == SnakeDirection::LEFT && direction == SnakeDirection::RIGHT) ||
      (direction_ == SnakeDirection::RIGHT && direction == SnakeDirection::LEFT) ||
      (direction_ == SnakeDirection::UP && direction == SnakeDirection::DOWN) ||
      (direction_ == SnakeDirection::DOWN && direction == SnakeDirection::UP)) {
    return;
  }

  direction_ = direction;
}

bool Snake::CheckForCollisions(){
  Point head = snake_.front();

  for(auto a : snake_){
    if(head.x == a.x && head.y == a.y){
      return true;
    }
  }
  return false;
}

void Snake::RenderSnake(){
  for(auto node : snake_){
    mvprintw(node.y, node.x, snake_char_);
  }

}