/*
 * infosv
 * 2013
 * Marco Antognini
 */

#include "TermiteTest.hpp"
#include "../Animal/AntWorker.hpp"
#include "../Animal/AntSoldier.hpp"
#include "../Animal/Termite.hpp"
#include "../Environment/Anthill.hpp"
#include "../Animal/Bob.hpp"

IMPLEMENT_MAIN(TermiteTest);

void TermiteTest::onEvent(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            default: break;

            case sf::Keyboard::T:
                getAppEnv().addAnimal(new Termite(getCursorPositionInView()));
                break;

            case sf::Keyboard::H:
                getAppEnv().addAnthill(new Anthill(getCursorPositionInView()));
                break;

            case sf::Keyboard::W:
                getAppEnv().addAnimal(new AntWorker(getCursorPositionInView(), 0));
                break;

            case sf::Keyboard::S:
                getAppEnv().addAnimal(new AntSoldier(getCursorPositionInView(), 0));
                break;
             
            case sf::Keyboard::B:
				getAppEnv().addAnimal(new Bob(getCursorPositionInView()));
				break;
			
			case sf::Keyboard::P:
				getAppEnv().addPoison(new Poison(getCursorPositionInView()));
				break;
				
			case sf::Keyboard::O:
				getAppEnv().addPollution(new Pollution(getCursorPositionInView()));
				break;

			case sf::Keyboard::N:
				getAppEnv().addNuke(new Nuke(getCursorPositionInView()));
				break;
				
			case sf::Keyboard::A:
				getAppEnv().addPill(new Pill(getCursorPositionInView()));
				break;
				
            case sf::Keyboard::R:
                getAppEnv().reset();
                break;
        }
    }
}
