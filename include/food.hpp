#include <ncurses.h>
#include <time.h>

#include <random>

#include "constants.hpp"
#include "logger.hpp"
#include "point.hpp"

#pragma once

class Food {
public:
  Food() : foodChar_{'X'}, is_eaten_{false}, point_{0, 0} {}

  Food(unsigned int x, unsigned int y, char foodChar) : foodChar_{foodChar}, is_eaten_{false}, point_{x, y}{}

  ~Food() {
    Logger::log("Food destructor");
  }

  const Point GetPoint() const { return point_; }
  const char GetFoodChar() const { return foodChar_; }
  const std::string& GetID() const { return id_; }

  void SetPoint(Point point) {
    point_.x_ = point.x_;
    point_.y_ = point.y_;
    id_ = CreateIDFromPoint(point_);
  }

  void SetIsEatenTrue() { is_eaten_ = true; }
  void SetIsEatenFalse() { is_eaten_ = false; }

  bool IsEaten() { return is_eaten_; }

private:
  friend class FoodProxy;

  static std::string CreateIDFromPoint(Point point) { return std::to_string(point.x_) + std::to_string(point.y_); }

  Point point_;
  const char foodChar_;
  bool is_eaten_;
  std::string id_;
};
