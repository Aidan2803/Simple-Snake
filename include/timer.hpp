#include <unistd.h>

#include <memory>
#include <mutex>
#include <thread>

#include "logger.hpp"

#pragma once

class Timer {
public:
  Timer(bool is_game_running, bool *flag, std::mutex &m) : is_game_running_{is_game_running}, m_{m} { flag_ = flag; }
  ~Timer() {
    if (timer_thread_.joinable()) {
      timer_thread_.join();
    }
  }
  void StartTimer() {
    timer_thread_ = std::thread(&Timer::TimerFunction, this);
    Logger::logToFile("after thread was created and started");
  }
  void UpdateIsGamerunningState(bool is_game_running) { is_game_running_ = is_game_running; }

private:
  void TimerFunction() {
    while (is_game_running_) {
      m_.lock();
      *flag_ = true;
      m_.unlock();
      sleep(8);
    }
  }

  std::mutex &m_;
  bool *flag_;
  bool is_game_running_;
  std::thread timer_thread_;
};