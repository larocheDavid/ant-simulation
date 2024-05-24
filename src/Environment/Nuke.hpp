 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#ifndef NUKE_HPP
#define NUKE_HPP

#include "Positionable.hpp"
#include "../Interface/Drawable.hpp"

class Nuke: public Positionable, public Drawable
{
public:
	//constructeur & destructeur
	Nuke(const ToricPosition& position);
	~Nuke();
	
	int const& getRadius() const;
	void update();
	bool finished();
	//methodes
	void draw(sf::RenderTarget& target) const; 
private:
	int radius;
};
#endif
