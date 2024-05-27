#include <ncurses.h>
#include <time.h>

#include <random>

#include "constants.hpp"
#include "logger.hpp"
#include "point.hpp"

#pragma once

class Food {
public:
  Food() : is_eaten_{false} {
    point_.x = -1;
    point_.y = -1;
    foodChar_ = new char('X');
  }
  Food(int x, int y, char foodChar) : is_eaten_{false} {
    point_.x = x;
    point_.y = y;
    foodChar_ = new char(foodChar);
  }
  Point& GetPoint() { return point_; }
  ~Food() { delete foodChar_; }
  const char* GetFoodChar() { return foodChar_; }

  void SetIsEatenTrue() { is_eaten_ = true; }
  bool IsEaten() { return is_eaten_; }

private:
  Point point_;
  const char* foodChar_;
  bool is_eaten_;
};
