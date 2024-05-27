#include "food.hpp"

#pragma once

class FoodProxy {
public:
  FoodProxy() = default;
  void SpawnFood() {
    srand(time(NULL));

    food_.GetPoint().x = rand() % kGameField_X_Asix;
    food_.GetPoint().y = rand() % kGameField_Y_Asix;
  }
  void RenderFood() { mvprintw(food_.GetPoint().y, food_.GetPoint().x, food_.GetFoodChar());}
  void DeleteFoodFromScreen() {
    mvprintw(food_.GetPoint().y, food_.GetPoint().x, "_");
    Logger::logToFile("delete food from the screen");
    refresh();
  }
  void SetIsEatenTrue(){food_.SetIsEatenTrue();}
  bool IsEaten(){return food_.IsEaten();}

  Point GetFoodPoint() { return food_.GetPoint(); }

private:
  Food food_;
};
