 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#ifndef POLLUTION_HPP
#define POLLUTION_HPP

#include "Positionable.hpp"
#include "../Interface/Drawable.hpp"

class Pollution: public Positionable, public Drawable
{
public:
	//constructeur & destructeur
	Pollution(const ToricPosition& position);
	~Pollution();
	
	int const& getRadius() const;
	//methodes
	void draw(sf::RenderTarget& target) const; 
private:
	int radius;
};
#endif
