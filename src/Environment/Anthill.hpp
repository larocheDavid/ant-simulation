 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#ifndef ANTHILL_HPP
#define ANTHILL_HPP

#include "../Utility/Utility.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp" 
#include "../Application.hpp"
#include "../ConfigManager/ConfigManager.hpp"


class Anthill : public Positionable, public Drawable, public Updatable
{
public:
	//constructeur destructeur
	Anthill(ToricPosition const& position, double proba = getAppConfig().getDouble("ANTHILL_WORKER_PROB_DEFAULT"));
	virtual ~Anthill();
	
	//getters
	Uid getId() const;
	double getSpeed() const;
	
	//methodes
	void addFoodQuantity(Quantity food);
	void update(sf::Time dt);
	std::string getTexture() const;
	void draw(sf::RenderTarget& target) const;
	bool isEmpty() const;

private:
	Uid mId;
	sf::Time delay;
	sf::Time lifespan;
	sf::Clock clock;
	Quantity mFood;
	double workerProb;
};
#endif
