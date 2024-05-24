 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#ifndef PHEROMONE_HPP
#define PHEROMONE_HPP

#include "../Utility/Utility.hpp"

class Pheromone : public Positionable
{
public:
	//constructeur & destructeur
	Pheromone(ToricPosition const& position, Quantity pheromone = 0, Uid id = 0);
	virtual ~Pheromone();
	
	//getter
	double getPheromone() const;
	double getId() const;
	
	//methodes
	void draw(sf::RenderTarget& target) const;
	bool isNull();
	void update(sf::Time dt);
private:
	Quantity mPheromone;
	Uid mId;
	sf::Color mColor;
};
#endif
