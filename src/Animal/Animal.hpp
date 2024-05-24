 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "../Random/Uniform.hpp"

class Ant;
class Termite;
class Bob;

struct intervalProbs {
	Intervals thetas;
	Probs probas;
};

enum State {ATTACK, IDLE, ESCAPING};

class Animal : public Positionable, public Drawable, public Updatable
{
public:
	//constructeurs & destructeur
	Animal(const ToricPosition& position, int _hp = 10, int _lifespan = 0);
	Animal(Animal const& autre);
	virtual ~Animal();
	
	//setters
	void setDirection(const Angle& angle);
	void updateState(sf::Time dt);
	
	//getters virtuels purs
	virtual double getSpeed() const = 0;
	virtual int getStrength() const = 0;
	virtual double getAttackDuration() const = 0;
	virtual int getSize() const = 0;
	
	//getter direction
	double const& getDirection() const;
	
	//methodes is Enemy
	virtual bool isEnemyDispatch(Bob const*) const;
	virtual bool isEnemyDispatch(Termite const*) const = 0;
	virtual bool isEnemyDispatch(Ant const*) const = 0;
	virtual bool isEnemy(Animal const* entity) const = 0;
		
	//méthodes
	virtual intervalProbs computeRotationProbs() const;
	void move(sf::Time dt);
	virtual void update(sf::Time dt);
	virtual bool isPredator() const;
	void attack(Animal* other);
	bool isDead() const;
	
protected:
	double hp; //nb points de vie
	sf::Time lifeSpan; //esperance de vie
	Angle direction; //direction de déplacement
	sf::Clock clock; 
	sf::Time timer;
	State etat; //etat mode: combat, fuite ou normal
	sf::Time freeze;
	bool onPills;
	sf::Time peak;
	int flash;
};
#endif
