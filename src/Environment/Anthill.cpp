 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#include <string>
#include <iostream>
#include "Anthill.hpp"
#include "../Random/Uniform.hpp"
#include "../Application.hpp"
#include "../Animal/AntWorker.hpp"
#include "../Animal/AntSoldier.hpp"

//constructeur & destructeur
Anthill::Anthill(ToricPosition const& position, double proba)
	: Positionable(position), mId(createUid()), delay(sf::seconds(getAppConfig().getDouble("ANTHILL_SPAWN_DELAY"))),
		lifespan(sf::Time::Zero), mFood(getAppConfig().getInt("ANTHILL_SPARE")),workerProb(proba) {}

Anthill::~Anthill() {}

//getters
Uid Anthill::getId() const
{
	return mId;
}

double Anthill::getSpeed() const
{
	return getAppConfig().getDouble("ANTHILL_SPEED");
}

//methodes
void Anthill::update(sf::Time dt)
{
	//si dans rayon de bombe, isEmpty passe a true
	//l'instance "meurt"
	if (getAppEnv().getNuked(getPosition())) {
		lifespan = sf::Time::Zero;
		mFood = 0;
	}
	//cherche si dans rayon de poison
	//si pointeur non nulle, anthill se deplace avec direction opposee
	Poison* closestPoison(getAppEnv().getPoisonForAnthill(getPosition()));
	if (closestPoison != nullptr) {
		Vec2d speed = getSpeed()*-(closestPoison->getPosition().toVec2d() - getPosition().toVec2d());
		setPosition(getPosition()+speed*dt.asSeconds());
	}
	//creation d'une nouvelle fourmis
	//si delai depasse et suffisamment de food
	if (delay > sf::seconds(getAppConfig().getDouble("ANTHILL_SPAWN_DELAY")) && mFood >= getAppConfig().getInt("ANT_COST")) {
		getAppStats().incrementSlot("Anthill #"+std::to_string(mId)+" pop");
		mFood -= getAppConfig().getInt("ANT_COST");
		// initialise une valeur aléatoire entre 0 et 1 suivant la distribution gaussienne
		//sort un antworker si uniform() <= ANTHILL_WORKER_PROB_DEFAULT sinon un antsoldier
		if(uniform(0.0,1.0) <= getAppConfig().getDouble("ANTHILL_WORKER_PROB_DEFAULT")) { 
			//appelle addAnimal de Environment et ajoute une Antworker initialisée à la position de anthill et à l'ID de la anthill courante
			getAppEnv().addAnimal(new AntWorker(getPosition(), mId));
			lifespan = sf::seconds(getAppConfig().getInt("ANT_WORKER_LIFESPAN"));
		} else {
			getAppEnv().addAnimal(new AntSoldier(getPosition(), mId));
			lifespan = sf::seconds(getAppConfig().getInt("ANT_SOLDIER_LIFESPAN"));
		}
	delay = sf::Time::Zero; //remet le délais a 0
	}
	delay += dt;
	lifespan -= dt;
}

std::string Anthill::getTexture() const
{
	if(getAppConfig().getBool("WATER_MODE")) {
		return getAppConfig().getString("ANTHILL_TEXTURE2");
	} else {
		return getAppConfig().getString("ANTHILL_TEXTURE");
	}
}

//methode draw
void Anthill::draw(sf::RenderTarget& target) const
{	//dessin de la fourmi
	auto anthillSprite =
	buildSprite(getPosition().toVec2d(), 70.0, getAppTexture(getTexture())); 
	target.draw(anthillSprite);//affiche la fourmi
	
	if (getAppConfig().getBool("DEBUG_MODE2")) {
		
		Vec2d pos(0, 40);
		auto const text1 = buildText("ID: "+std::to_string(mId) , 
		getPosition().toVec2d()+pos, getAppFont(), 12, sf::Color::Blue);
		target.draw(text1);
		
		auto const text2 = buildText("Food: "+std::to_string(lround(mFood)), 
		getPosition().toVec2d()+1.3*pos, getAppFont(), 12, sf::Color(33,102,28,255));
		target.draw(text2);
		
		Vec2d pos2(0, -40);
		auto const text3 = buildText("Lifespan: "+std::to_string(lround(lifespan.asSeconds())), 
		getPosition().toVec2d()+pos2, getAppFont(), 12, sf::Color::Blue);
		target.draw(text3);
	}
}

//methode addfoodquantity
void Anthill::addFoodQuantity(Quantity food)
{
	mFood += food;//ajoute à l'attribut mFood de anthill la valeur passee en parametre
}

bool Anthill::isEmpty() const
{
	return (mFood < getAppConfig().getInt("ANT_COST") && lifespan < sf::Time::Zero);
}
