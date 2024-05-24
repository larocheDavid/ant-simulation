/*
 *infosv
 *2014
 *Maxime Ameho
 *
 */

#ifndef INFOSV_ANIMAL_TEST_HPP
#define INFOSV_ANIMAL_TEST_HPP

#include "../Application.hpp"

class AnimalTest : public Application
{
public:
    virtual void onEvent(sf::Event event, sf::RenderWindow&);
};

#endif //INFOSV_ANIMAL_TEST_HPP
