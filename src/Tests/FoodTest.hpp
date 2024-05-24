/*
 * infosv
 * 2014
 * Maxime Ameho
 */

#ifndef INFOSV_FOOD_TEST_HPP
#define INFOSV_FOOD_TEST_HPP

#include "../Application.hpp"
#include "../Environment/Food.hpp"

class FoodTest : public Application
{
    virtual void onEvent(sf::Event event, sf::RenderWindow& window);

private:
    Food* lastCreated = nullptr;
};

#endif //INFOSV_FOOD_TEST_HPP
