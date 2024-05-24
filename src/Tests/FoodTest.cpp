#include "FoodTest.hpp"
#include "../Environment/Food.hpp"
#include <iostream>
IMPLEMENT_MAIN(FoodTest);

void FoodTest::onEvent(sf::Event event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::R:
                getAppEnv().reset();
                break;

            case sf::Keyboard::F:

                lastCreated = new Food(getCursorPositionInView(), 50); //partie decomentée
                getAppEnv().addFood(lastCreated); //partie decomentée
			
                break;

            case sf::Keyboard::C:
				
                if (lastCreated != nullptr) //partie decomentée
                    lastCreated->takeQuantity(15); //partie decomentée
				
                break;
            default:
                break;
        }
    }
}


