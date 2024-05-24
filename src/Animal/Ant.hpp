 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#ifndef ANT_HPP
#define ANT_HPP

#include "Animal.hpp"
#include "../Environment/Anthill.hpp"

class AntWorker;
class AntSoldier;

class Ant : public Animal
{
public:
	//constructeur & destructeur
	Ant(const ToricPosition& position, Uid id = 0, int _hp = 99, int _lifeSpan = 0);
	virtual ~Ant();

	//getters
	virtual std::string getTexture() const = 0;
	double getSpeed() const;
	double getAttackDuration() const;
	
	//methode update override car redefinition de update animal
	virtual void update(sf::Time dt);
	
	void afficheProb(sf::RenderTarget& target) const;

	//methode draw
	virtual void draw(sf::RenderTarget& target) const;
	
	//methode spreadpheromones
	virtual void spreadPheromones();
	
	//methode calculant les probabilites de rotation
	intervalProbs computeRotationProbs() const;
	
	//methode ennemi
	bool isEnemyDispatch(Ant const*) const;
	bool isEnemyDispatch(Termite const*) const;
	bool isEnemy(Animal const* animal) const;
	
	//attribut
	bool displayProbs;
	
protected:
	Uid mId;
	ToricPosition mlastPos;
	int compteur;
	double factor;
	sf::Color mColor;
};
#endif
