/*
 * infosv
 * 2013
 * Marco Antognini
 */

#ifndef INFOSV_ANTHILL_TEST_HPP
#define INFOSV_ANTHILL_TEST_HPP

#include "../Application.hpp"

class Ant;

/*
 * Cette classe sert à tester que les fourmis parviennent à ramener de la nourriture à
 * leur fourmilière en suivant les traces de phéromone.
 *
 * Les actions disponibles sont :
 *  - mettre en pause le monde avec la touche ESPACE.
 *  - créer une fourmilière avec la touche H.
*/
class AnthillTest : public Application
{
public:
    AnthillTest() = default;
    virtual ~AnthillTest() = default;

    virtual void onEvent(sf::Event event, sf::RenderWindow& window);
};

#endif // INFOSV_ANTHILL_TEST_HPP

