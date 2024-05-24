 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#ifndef POISON_HPP
#define POISON_HPP

#include "Positionable.hpp"
#include "../Interface/Drawable.hpp"

class Poison: public Positionable, public Drawable
{
public:
	//constructeur & destructeur
	Poison(const ToricPosition& position);
	~Poison();
	//getter
	int const& getRadius() const;
	//methodes
	void infect();
	void draw(sf::RenderTarget& target) const; 
private:
	int radius;
};
#endif
