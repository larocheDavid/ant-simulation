/*
 *infosv
 *2014
 *Maxime Ameho
 *
 */

#include "AntTest.hpp"
#include "../Animal/AntWorker.hpp"
#include "../Animal/AntSoldier.hpp"
#include "../Utility/Utility.hpp"

IMPLEMENT_MAIN(AntTest);

void AntTest::onEvent(sf::Event event, sf::RenderWindow&)
{
	if(event.type==sf::Event::KeyPressed)
    {
		switch(event.key.code)
		{
			case sf::Keyboard::S:
				getAppEnv().addAnimal(new AntSoldier(getCursorPositionInView(), createUid()));
				break;
			case sf::Keyboard::W:
				getAppEnv().addAnimal(new AntWorker(getCursorPositionInView(), createUid()));
				break;
			case sf::Keyboard::R:
				getAppEnv().reset();
				break;

			default:
				break;
		}
    }
}
