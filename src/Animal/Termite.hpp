 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#ifndef TERMITE_HPP
#define TERMITE_HPP

#include "Animal.hpp"

class Termite : public Animal
{
public:
	//constructeur & destructeur
	Termite(const ToricPosition& position);
	virtual ~Termite();
	
	//getters
	double getSpeed() const;
	std::string getTexture() const;
	int getSize() const;
	int getStrength() const;
	double getAttackDuration() const;
	
	//methode draw
	void draw(sf::RenderTarget& target) const;
	
	//methodes ennemi
	bool isEnemyDispatch(Termite const*) const;
	bool isEnemyDispatch(Ant const*) const;
	bool isEnemy(Animal const* animal) const;
};

#endif
