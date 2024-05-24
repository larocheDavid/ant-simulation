 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#include "AntWorker.hpp"
#include <iostream>

//constructeur
AntWorker::AntWorker(ToricPosition const& position, Uid id)
	:Ant(position, id, getAppConfig().getInt("ANT_WORKER_HP"),
	getAppConfig().getInt("ANT_WORKER_LIFESPAN")), mFood(0), infected(false)
{
	reinforce = sf::Time::Zero;
	getAppStats().incrementSlot("Ant Workers");
}

//destructeur
AntWorker::~AntWorker()
{
	getAppStats().decrementSlot("Ant Workers");
}

//retourne texture de antworker
std::string AntWorker::getTexture() const
{	
	if(getAppConfig().getBool("WATER_MODE")) {
		return getAppConfig().getString("ANT_WORKER_TEXTURE2");
	} else {
		if(infected) {
			return getAppConfig().getString("ANT_WORKER_TEXTURE3");
		} else  {
			return getAppConfig().getString("ANT_WORKER_TEXTURE");
		}
	}
}

int AntWorker::getSize() const
{
	//adapte la taille du dessin selon le mode
	if(getAppConfig().getBool("WATER_MODE")) {
		return getAppConfig().getInt("ANT_WORKER_SIZE2");
	} else {
		return getAppConfig().getInt("ANIMAL_SIZE");
	}
}

int AntWorker::getStrength() const
{
	//prend une force uniformement choisie entre 0 et sa force maximale 
	return uniform(0, getAppConfig().getInt("ANT_WORKER_STRENGTH"));
}

bool AntWorker::isPredator() const 
{
	return false;
}

void AntWorker::draw(sf::RenderTarget& target) const
{
	Ant::draw(target);
	if (getAppConfig().getBool("DEBUG_MODE2")) {
		Vec2d pos(0, 35);
		//affichage pos permet de ne pas dessiner sur la fourmi
		auto const text3 = buildText("Food: "+std::to_string(lround(mFood)), 
		getPosition().toVec2d()+1.5*pos, getAppFont(), 12, sf::Color(33,102,28,255));
		target.draw(text3);
	}
}

void AntWorker::update(sf::Time dt)
{
	Ant::update(dt); //permet de ne pas dupliquer du code
	//initialise  un pointeur sur le food le plus proche
	Food* closestFood(getAppEnv().getClosestFoodForAnt(getPosition()));
	if(closestFood != nullptr && mFood != getApp().getConfig().getDouble("ANT_MAX_FOOD")) {
		//augmente le nombre de pheromones portees si la source de nourriture est suffisante
		if(closestFood->getQuantity() > getApp().getConfig().getDouble("ANT_MAX_FOOD")) {
			reinforce = sf::seconds(5);
			factor = 2;
		}
		//Prend une quantité de food ne pouvant depasser AMF
		mFood =  closestFood->takeQuantity(getApp().getConfig().getDouble("ANT_MAX_FOOD")-mFood);
		setDirection(getDirection()+ PI);//fait un 180
		//divise son lifespan par 2 si empoisonne
		if(closestFood->getPoisoned()) {
			infected = true;
			lifeSpan = sf::seconds(lifeSpan.asSeconds()/2);
		}	
	}
	reinforce -= dt;
	if(reinforce < sf::Time::Zero) {
		factor = 1;
	}
	//permet de déposer la nourriture dans la fourmiliere pointee
	//enleve facteur 2
	Anthill* myAnthill(getAppEnv().getAnthillForAnt(getPosition(), mId));
	if((myAnthill != nullptr) && (mFood != 0)) {
		setDirection(getDirection()+ PI);
		myAnthill->addFoodQuantity(mFood); //ajoute à la fourmiliere la quantité de food portée
		mFood = 0; //vide sa nourriture
		reinforce = sf::Time::Zero;
	}
}
