#include <ncurses.h>

#include <memory>
#include <mutex>

#include "enums.hpp"
#include "food-proxy.hpp"
#include "logger.hpp"
#include "snake.hpp"
#include "timer.hpp"

#pragma once

class Game {
public:
  Game() {
    is_timer_exceeded_flag_ = new bool(false);
    mutex_ = new std::mutex();
    timer_ = new Timer(is_game_running_, is_timer_exceeded_flag_, *mutex_);
    is_game_running_ = true;
  }
  ~Game() {
    Logger::logToFile("<|||||||||||||||||||||||||||||| Game exits ||||||||||||||||||||||||||||||>");
    ChangeIsGameRunningToFalse();
    delete is_timer_exceeded_flag_;
    delete timer_;
  }
  void InitGame();
  void GameLoop();
  void Render();

  void MapUserInput();

  void ChangeIsGameRunningToFalse() {
    is_game_running_ = false;
    timer_->UpdateIsGamerunningState(false);
  }

  void MangaeFoodSpawning() {
    if (*is_timer_exceeded_flag_ == true) {
      food_proxy_.get()->SpawnFood();

      mutex_->lock();
      *is_timer_exceeded_flag_ = false;
      mutex_->unlock();
    }
  }

  std::pair<bool, Point> IsSnakeFoodCollision();

private:
  char user_input_;
  SnakeDirection direction_;
  const std::unique_ptr<Snake> snake_ = std::make_unique<Snake>();
  const std::unique_ptr<FoodProxy> food_proxy_ = std::make_unique<FoodProxy>();
  bool *is_timer_exceeded_flag_;

  bool is_game_running_;
  Timer *timer_;
  std::mutex *mutex_;
};
