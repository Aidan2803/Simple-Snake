#include <ncurses.h>

#include <deque>

#include "enums.hpp"
#include "logger.hpp"
#include "point.hpp"

#define SNAKE_HPP
#ifdef SNAKE_HPP

class Snake {
public:
  Snake() : direction_{SnakeDirection::RIGHT} {
    snake_.push_front(Point{5, 5});
    snake_char_ = new char('@');
  };
  Snake(int x, int y, char snake_char, SnakeDirection initial_snake_direction) : direction_{initial_snake_direction} {
    snake_char_ = new char(snake_char);
    snake_.push_front(Point{x, y});
  }
  Snake(const Snake& other) = delete;
  Snake(Snake&& other) = delete;
  ~Snake() { delete snake_char_; }

  void Move();
  void Eat();

  void SetDirection(SnakeDirection direction);
  void RenderSnake();
  bool CheckForCollisions();

  friend class Game;

private:
  Point get_head() { return snake_.front(); }

  std::deque<Point> snake_;
  SnakeDirection direction_;
  const char* snake_char_;
};

#endif