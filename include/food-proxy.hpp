#include <vector>

#include "food.hpp"

#pragma once

class FoodProxy {
public:
  FoodProxy() = default;
  void SpawnFood() {
    srand(time(NULL));

    for (auto food : food_vector_) {
      food.SetPoint(Point(rand() % kGameField_X_Asix, rand() % kGameField_Y_Asix));
    }
  }
  void RenderFood() {
    for (auto food : food_vector_) {
      if(!food.IsEaten()){
        mvprintw(food.GetPoint().y_, food.GetPoint().x_, food.GetFoodChar());
      }
    }
  }

  void SetIsEatenTrue(Point point) {
    auto eaten_food_id = Food::CreateIDFromPoint(point);
    for (auto& food : food_vector_) {
      if (eaten_food_id == food.GetID()) {
        food.SetIsEatenTrue();
      }
    }
  }
  bool IsEaten(Point point) {
    auto eaten_food_id = Food::CreateIDFromPoint(point);
    for (auto& food : food_vector_) {
      if (eaten_food_id == food.GetID()) {
        food.IsEaten();
      }
    }
  }

  Point GetFoodPoint(Point point) {
    auto eaten_food_id = Food::CreateIDFromPoint(point);
    for (auto& food : food_vector_) {
      if (eaten_food_id == food.GetID()) {
        return food.GetPoint();
      }
    }
  }

  const std::vector<Food>& GetFoodVector() { return food_vector_; }

private:
  std::vector<Food> food_vector_;
};
