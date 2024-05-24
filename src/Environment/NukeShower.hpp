 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#ifndef NUKESHOWER_HPP
#define NUKESHOWER_HPP

#include <SFML/Graphics.hpp>

class NukeShower
{
public:
	//constructeur destructeur
	NukeShower();
	~NukeShower();
	void update(sf::Time dt);

private:
	sf::Time timer;
};
#endif
