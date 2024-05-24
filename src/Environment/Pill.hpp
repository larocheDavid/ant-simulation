 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#ifndef PILL_HPP
#define PILL_HPP

#include "Positionable.hpp"
#include "../Interface/Drawable.hpp"

class Pill: public Positionable, public Drawable
{
public:
	//constructeur & destructeur
	Pill(const ToricPosition& position);
	~Pill();
	//setter & getter
	void setDropped(bool on);
	bool const& getDropped() const;
	//methodes
	void draw(sf::RenderTarget& target) const; 
private:
	bool dropped;
};
#endif
