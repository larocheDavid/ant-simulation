 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#ifndef ANTWORKER_HPP
#define ANTWORKER_HPP
 
#include "Ant.hpp"

class AntWorker : public Ant
{
public:
	//constructeur
	AntWorker(ToricPosition const& position, Uid id);
	//destructeur
	virtual ~AntWorker();
	
	//getters
	std::string getTexture() const;
	int getSize() const;
	int getStrength() const;
	
	bool isPredator() const;
	void draw(sf::RenderTarget& target) const override;
	void update(sf::Time dt) override;
	
private:
	Quantity mFood;
	bool infected;
	sf::Time reinforce;
};
#endif
