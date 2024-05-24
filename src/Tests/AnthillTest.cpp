/*
 * infosv
 * 2013
 * Marco Antognini
 */

#include "AnthillTest.hpp"
#include "../Environment/Anthill.hpp"
#include "../Constants.hpp"
#include "../Animal/AntWorker.hpp"
#include "../Environment/Food.hpp"
#include "../Animal/Bob.hpp"

#include <iostream>

IMPLEMENT_MAIN(AnthillTest);

void AnthillTest::onEvent(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            default: break;

            case sf::Keyboard::H:
                getAppEnv().addAnthill(new Anthill(getCursorPositionInView()));
                break;
               
            case sf::Keyboard::B:
				getAppEnv().addAnimal(new Bob(getCursorPositionInView()));
				break;
				
			case sf::Keyboard::D:
				DEBUG_MODE = false;
				break;

            case sf::Keyboard::R:
                getAppEnv().reset();
                break;
        }
    }
}
