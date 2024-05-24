 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#include <cmath>
#include <iostream>

#include "Environment.hpp"
#include "Anthill.hpp"
#include "../Animal/Animal.hpp"

//constructeur & destructeur
Environment::Environment() 
	: colors({sf::Color(255,0,255,70), sf::Color(0,255,0,70), 
		sf::Color(0,0,255,70), sf::Color(255,0,0,70), sf::Color(255,255,0,70)}) {}
Environment::~Environment() {}

//getter
std::vector<sf::Color> Environment::getColors() 
{
	return colors;
}

//méthodes
void Environment::addAnimal(Animal* animal)
{	//permet d'ajouter un animal
	if(animal != nullptr) {
		lesAnimaux.push_back(animal);
	}
}

void Environment::addFood(Food* food)
{	//permet d'ajouter un food
	if(food != nullptr) {
		totalFood.push_back(food);
	}
}

void Environment::addAnthill(Anthill* anthill)
{	//permet d'ajouter une fourmiliere
	if(anthill != nullptr) {
		totalAnthill.push_back(anthill);
	}
}

void Environment::addPheromone(Pheromone* pheromone)
{	//permet d'ajouter une pheromone
	if(pheromone != nullptr) {
		totalPheromone.push_back(pheromone);
	}
}

void Environment::addPoison(Poison* poison)
{	//permet d'ajouter une zone empoisonnee
	if(poison != nullptr) {
		totalPoison.push_back(poison);
	}
}

void Environment::addPollution(Pollution* pollution)
{	//permet d'ajouter une zone poluee
	if(pollution != nullptr) {
		totalPollution.push_back(pollution);
	}
}

void Environment::addNuke(Nuke* nuke)
{	//permet d'ajouter une zone poluee
	if(nuke != nullptr) {
		totalNuke.push_back(nuke);
	}
}

void Environment::addPill(Pill* pill)
{	//permet d'ajouter une zone poluee
	if(pill != nullptr) {
		pills.push_back(pill);
	}
}

void Environment::update(sf::Time dt)
{
	foodGen.update(dt);
	if (getAppConfig().getBool("APOCALYPSE_MODE")) {
		nukem.update(dt);
	}
	//actualise chaque type en appelant sa methode update
	//met à jour chaque animal
	for (auto& animal : lesAnimaux) {
		animal->update(dt);
		//entre dans le if si la fonction isDead() de animal est true
		if (animal->isDead()) {
			//efface l'entite
			delete animal;
			//animal pointe sur nullptr
			animal = nullptr;
		}
	}
	for (auto& food : totalFood) {
		if (food->isEmpty()) {
			delete food;
			food = nullptr;
		}
	}
	for (auto& pheromone : totalPheromone) {
		pheromone->update(dt);
		if (pheromone->isNull()) {
			delete pheromone;
			pheromone = nullptr;
		}
	}
	//actualise la fourmiliere en appelant sa methode update
	for (auto& anthill: totalAnthill) {
		anthill->update(dt);
		if (anthill->isEmpty()) {
			delete anthill;
			anthill = nullptr;
		}
	}
	for (auto& poison : totalPoison) {
		poison->infect();
		//supprime le poison si dans rayon de la bombe A
		if (getNuked(poison->getPosition())) {
			delete poison;
			poison = nullptr;
		}
	}
	for (auto& pill: pills) {
		//supprime la pill si pris par une fourmis ou dans rayon de la bombe A
		if (pill->getDropped() || getNuked(pill->getPosition())) {
			delete pill;
			pill = nullptr;
		}
	}
	for (auto& pollution: totalPollution) {
		//supprime la pill si pris par une fourmis ou dans rayon de la bombe A
		if (getNuked(pollution->getPosition())) {
			delete pollution;
			pollution = nullptr;
		}
	}
	for (auto& nuke: totalNuke) {
		nuke->update();
		//supprime la bombe si taille maximale atteinte
		if (nuke->finished()) {
			delete nuke;
			nuke = nullptr;
		}
	}

	//supprime tous les pointeurs nuls des entites ci dessus
	lesAnimaux.erase(std::remove(lesAnimaux.begin(), lesAnimaux.end(), nullptr), lesAnimaux.end());
	totalFood.erase(std::remove(totalFood.begin(), totalFood.end(), nullptr), totalFood.end());
	totalPheromone.erase(std::remove(totalPheromone.begin(), totalPheromone.end(), nullptr), totalPheromone.end());
	totalAnthill.erase(std::remove(totalAnthill.begin(), totalAnthill.end(), nullptr), totalAnthill.end());
	pills.erase(std::remove(pills.begin(), pills.end(), nullptr), pills.end());
	totalNuke.erase(std::remove(totalNuke.begin(), totalNuke.end(), nullptr), totalNuke.end());
	totalPoison.erase(std::remove(totalPoison.begin(), totalPoison.end(), nullptr), totalPoison.end());
	totalPollution.erase(std::remove(totalPollution.begin(), totalPollution.end(), nullptr), totalPollution.end());
}

void Environment::draw(sf::RenderTarget& target) const
{	//auto const& permet d'éviter de creer des copies et ne modifie pas l'original
	//boucle sur chaque type pour l'affichage
	for (auto const& anthill : totalAnthill) {
		//dessine chaque fourmiliere
		anthill->draw(target);
	}
	for (auto const& pheromone : totalPheromone) {
		//dessine chaque animal
		pheromone->draw(target);
	}
	for(auto const& food : totalFood) {
		//dessine chaque nourriture
		food->draw(target);
	}
	for (auto const& animal : lesAnimaux) {
		//dessine chaque animal
		animal->draw(target);
	}
	for (auto const& poison : totalPoison) {
		//dessine chaque poison
		poison->draw(target);
	}
	for (auto const& pollution : totalPollution) {
		//dessine chaque pollution
		pollution->draw(target);
	}
	for (auto const& nuke : totalNuke) {
		//dessine chaque bombe
		nuke->draw(target);
	}
	for (auto const& pill : pills) {
		//dessine chaque pill
		pill->draw(target);
	}
}

//methode reset permet d'effacer toutes les entites
void Environment::reset()
{
	for(auto& food : totalFood) {	
		delete food;
		food = nullptr;
	}
	totalFood.clear();
	
	for(auto& animal : lesAnimaux) {	
		delete animal;
		animal = nullptr;
	}
	lesAnimaux.clear();
	
	for(auto& anthill : totalAnthill) {	
		delete anthill;
		anthill = nullptr;
	}
	totalAnthill.clear();
	
	for(auto& pheromone : totalPheromone) {	
		delete pheromone;
		pheromone = nullptr;
	}
	totalPheromone.clear();
	
	for(auto& poison : totalPoison)
	{	
		delete poison;
		poison = nullptr;
	}
	totalPoison.clear();
	
	for(auto& pollution : totalPollution)
	{	
		delete pollution;
		pollution = nullptr;
	}
	totalPollution.clear();
	
	for(auto& nuke : totalNuke)
	{	
		delete nuke;
		nuke = nullptr;
	}
	totalNuke.clear();	
	
	for(auto& pill : pills)
	{	
		delete pill;
		pill = nullptr;
	}
	pills.clear();	
}

Food* Environment::getClosestFoodForAnt(ToricPosition const& position)
{	//renvoie le pointeur sur la food la plus proche comprise à une distance de AMPD
	double candidate_dist(0);
	//initialise un vec2d à la distance maximale
	Vec2d diagonal(getAppConfig().getInt("WORLD_HEIGHT"),getAppConfig().getInt("WORLD_WIDTH"));
	double min_dist = diagonal.length();
	Food* closestFood = nullptr;
	for(auto const& food : totalFood) {
		candidate_dist = toricDistance(position, food->getPosition());
		if(candidate_dist < getAppConfig().getDouble("ANT_MAX_PERCEPTION_DISTANCE") && candidate_dist < min_dist)  {
			closestFood = food; //memorise la food la plus proche
			min_dist = candidate_dist;
		}
	}
	//retourne nullptr si aucune food
	return closestFood;
}

Anthill* Environment::getAnthillForAnt(ToricPosition const& position, Uid anthillId)
{	//renvoie le pointeur sur la fourmiliere si l'id est la meme que la fourmiliere et qui est dans un rayon inferieur à AMPD
	for (auto const& anthill : totalAnthill) {
		if((anthillId == anthill->getId()) && 
			(toricDistance(position, anthill->getPosition())< getAppConfig().getDouble("ANT_MAX_PERCEPTION_DISTANCE"))) {
			return anthill;
		}
	}
	return nullptr;
}

Quantities Environment::getPheromoneQuantitiesPerIntervalForAnt
(ToricPosition const& position, Angle direction_rad, Intervals const& angles, Uid antId)
{
	Quantities Q(angles.size()); //init un tab de la taille de angles
	for(auto const& pheromone : totalPheromone) {
		if(toricDistance(position, pheromone->getPosition()) < 
			getAppConfig().getDouble("ANT_SMELL_MAX_DISTANCE") && pheromone->getId() == antId) {
			//seconde condition pour que fourmis suivent phero de leur propre fourmillere
			Vec2d v(toricVector(position, pheromone->getPosition()));
			Angle beta((v.angle() - direction_rad) / DEG_TO_RAD); //
			//correction de l'angle a 2kpi
			while (beta < 0)	beta += 360;
			while (beta > 360)  beta -= 360;
			//croissance degrés dans le sens horaire
			//chiffres negatifs après >180 degres
			if (beta > 180 && beta <360) beta = -(360-beta);
			
			Angle candida_angle(0), min_angle(360);
			
			int compteur(0), i(0);
			//fait correspondre empl phero avec prob
			//compteur # de la case correspondant a l'angle le plus proche de l'emp de la phero
			for(auto const& angle : angles) {
				candida_angle = abs(angle-beta); //difference d'angle
				if(candida_angle < min_angle) {
					min_angle = candida_angle;
					i = compteur;
				}
				++compteur;
			}
			Q[i] += pheromone->getPheromone();
		}
	}
	return Q; 
}

Animal* Environment::getClosestEnemy(Animal* other)
{
	//mm fonctionnement que getClosestFood
	double candidate_dist(0);
	Vec2d diagonal(getAppConfig().getInt("WORLD_HEIGHT"),getAppConfig().getInt("WORLD_WIDTH"));
	double min_dist = diagonal.length();
	Animal* closestEnemy = nullptr;
	for(auto const& animal : lesAnimaux) { 
		if(animal != nullptr) {
			candidate_dist = toricDistance(other->getPosition(), animal->getPosition());
			if(candidate_dist < getAppConfig().getDouble("ANIMAL_SIGHT_DISTANCE") && 
				candidate_dist < min_dist && animal->isEnemy(other) && animal != other) {
				closestEnemy = animal;
				min_dist = candidate_dist;
			}
		}
	}
	return closestEnemy;
}

void Environment::isPoisoned(ToricPosition const& position, double const& radius)
{
	//boucle sur totalFood
	//si food dans rayon du poison, set la food en mode empoisonnee
	for(auto& food : totalFood) { 
		if(food != nullptr) {
			if(((toricDistance(position, food->getPosition()) - radius) <= 0)) {
				food->setPoisoned(true);
			}
		}
	}
}

Poison* Environment::getPoisonForAnthill(ToricPosition const& position)
{	
	//retourne le pointeur sur poison si dans son rayon
	for (auto const& poison : totalPoison) {
		if((toricDistance(position, poison->getPosition()) - poison->getRadius()) <= 0) {
			return poison;
		}
	}
	return nullptr;
}

bool Environment::getPollutionAnimal(ToricPosition const& position)
{
	//retourne un bool si dans son rayon
	for (auto const& pollution : totalPollution) {
		if((toricDistance(position, pollution->getPosition()) - pollution->getRadius()) <= 0) {
			return true;
		}
	}
	return false;
}

bool Environment::getNuked(ToricPosition const& position)
{
	//retourne un bool si dans son rayon
	for (auto const& nuke : totalNuke) {
		if((toricDistance(position, nuke->getPosition()) - nuke->getRadius()) <= 0) {
			return true;
		}
	}
	return false;
}

bool Environment::getPill(ToricPosition const& position)
{
	//renvoie un bool sur la pill la plus proche comprise à une distance de AMPD
	//fonctionne comme getClosestFood
	double candidate_dist(0);
	Vec2d diagonal(getAppConfig().getInt("WORLD_HEIGHT"),getAppConfig().getInt("WORLD_WIDTH"));
	double min_dist = diagonal.length();
	for(auto& pill : pills) {
		candidate_dist = toricDistance(position, pill->getPosition());
		if(candidate_dist < getAppConfig().getDouble("ANT_MAX_PERCEPTION_DISTANCE") && candidate_dist < min_dist)  {
			min_dist = candidate_dist;
			//permet de supprimer la pill si prise
			pill->setDropped(true);
			return true;
		}
	}
	return false;
}
