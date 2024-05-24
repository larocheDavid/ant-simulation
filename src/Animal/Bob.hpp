 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#ifndef BOB_HPP 
#define BOB_HPP
 
#include "Animal.hpp"

class Bob : public Animal
{
public:
	//constructeur
	Bob(ToricPosition const& position);
	//destructeur
	virtual ~Bob();
	//getters
	sf::Time getLifeSpan() const;
	double getSpeed() const;
	std::string getTexture() const;
	int getSize() const;
	int getStrength() const;
	double getAttackDuration() const;
	
	intervalProbs computeRotationProbs() const;
	void draw(sf::RenderTarget& target) const;
	
	//methodes ennemi
	bool isEnemyDispatch(Bob const*) const;
	bool isEnemyDispatch(Termite const*) const;
	bool isEnemyDispatch(Ant const*) const;
	bool isEnemy(Animal const* animal) const;
};
#endif

