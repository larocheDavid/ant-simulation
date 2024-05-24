 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP

#include <SFML/Graphics.hpp>

class FoodGenerator
{
public:
	//constructeur destructeur
	FoodGenerator();
	~FoodGenerator();
	void update(sf::Time dt);

private:
	sf::Time timer;
};
#endif
