#include <ncurses.h>
#include <time.h>

#include <random>

#include "constants.hpp"
#include "logger.hpp"
#include "point.hpp"

#pragma once

class Food {
public:
  Food() : is_eaten_{false}, point_{0, 0} { foodChar_ = new char('X'); }

  Food(unsigned int x, unsigned int y, char foodChar) : is_eaten_{false}, point_{x, y} {
    foodChar_ = new char(foodChar);
  }

  ~Food() { delete foodChar_; }

  const Point GetPoint() { return point_; }
  const char* GetFoodChar() { return foodChar_; }
  const std::string& GetID() { return id_; }

  void SetPoint(Point point) {
    point_.x_ = point.x_;
    point_.y_ = point.y_;
    id_ = CreateIDFromPoint(point_);
  }

  void SetIsEatenTrue() { is_eaten_ = true; }

  bool IsEaten() { return is_eaten_; }

private:
  friend class FoodProxy;

  static std::string CreateIDFromPoint(Point point) { return std::to_string(point.x_) + std::to_string(point.y_); }

  Point point_;
  const char* foodChar_;
  bool is_eaten_;
  std::string id_;
};
