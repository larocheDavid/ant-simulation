/*
 *infosv
 *2014
 *Maxime Ameho
 *
 */

#include "AnimalTest.hpp"
#include "../Animal/Animal.hpp"

IMPLEMENT_MAIN(AnimalTest);

void AnimalTest::onEvent(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::A:
                getAppEnv().addAnimal(new Animal(getCursorPositionInView()));
                break;

            case sf::Keyboard::R:
                getAppEnv().reset();
                break;

            default:
                break;
        }
    }
}
