 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "../Interface/Updatable.hpp"
#include "../Interface/Drawable.hpp"
#include "FoodGenerator.hpp"
#include "Food.hpp"
#include "Pheromone.hpp"
#include "Poison.hpp"
#include "Pollution.hpp"
#include "Nuke.hpp"
#include "Pill.hpp"
#include "NukeShower.hpp"

class Animal;
class Anthill;


class Environment : public Updatable, public Drawable
{
public :
	//constructeur et destructeur
	Environment();
	virtual ~Environment();

	//getter
	std::vector<sf::Color> getColors();

	//méthodes
	void addAnimal(Animal* animal);
    void addFood(Food* food);
    void addAnthill(Anthill* anthill);
    void addPheromone(Pheromone* pheromone);
    void addPoison(Poison* poison);
    void addPollution(Pollution* pollution);
    void addNuke(Nuke* nuke);
    void addPill(Pill* pill);
    void update(sf::Time dt);
    void draw(sf::RenderTarget& target) const;
    void reset();
    Quantities getPheromoneQuantitiesPerIntervalForAnt
		(ToricPosition const& position, Angle direction_rad, Intervals const& angles, Uid antId);
	
	Food* getClosestFoodForAnt(ToricPosition const& position);
	Anthill* getAnthillForAnt(ToricPosition const& position, Uid anthillId);
	Animal* getClosestEnemy(Animal* other);
	void isPoisoned(ToricPosition const& position, double const& radius);
	Poison* getPoisonForAnthill(ToricPosition const& position);
	bool getPollutionAnimal(ToricPosition const& position);
	bool getNuked(ToricPosition const& position);
	bool getPill(ToricPosition const& position);
	
private:
	std::vector<Animal*> lesAnimaux;
	std::vector<Food*> totalFood;
	std::vector<Anthill*> totalAnthill;
	std::vector<Pheromone*> totalPheromone;
	std::vector<Poison*> totalPoison;
	std::vector<Pollution*> totalPollution;
	std::vector<Nuke*> totalNuke;
	std::vector<Pill*> pills;
	std::vector<sf::Color> colors; //tableau de couleurs pour pheromones
	FoodGenerator foodGen;
	NukeShower nukem;
};
#endif
