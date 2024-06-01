#include <vector>

#include "food.hpp"

#pragma once

class FoodProxy {
public:
  FoodProxy(){
    for(int i = 0; i < kAmountOfFood; i++){
      food_vector_.push_back(Food());
    }
    for(int i = 0; i < food_vector_.size(); i++){
    }
  }

  void SpawnFood() {
    srand(time(NULL));

    for (auto &food : food_vector_) {
      food.SetPoint(Point(rand() % kGameField_X_Asix, rand() % kGameField_Y_Asix));
    }
  }
  void RenderFood() {
    for (auto &food : food_vector_) {
      if(!food.IsEaten()){
        mvprintw(food.GetPoint().y_, food.GetPoint().x_, "%c", food.GetFoodChar());
      }
    }
  }

  void SetIsEatenTrue(Point point) {
    int i = 0;
    auto eaten_food_id = Food::CreateIDFromPoint(point);
    for (auto& food : food_vector_) {
      if (eaten_food_id == food.GetID()) {
        food.SetIsEatenTrue();
      }
      i++;
    }
  }

  bool IsEaten(Point point) {
    int i = 0;
    auto eaten_food_id = Food::CreateIDFromPoint(point);
    for (auto& food : food_vector_) {
      if (eaten_food_id == food.GetID()) {
        return food.IsEaten();
      }
      i++;
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
