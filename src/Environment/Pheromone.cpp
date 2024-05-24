 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#include "Pheromone.hpp"
#include "../Constants.hpp"
#include "../Application.hpp"

//constructeur & destructeur
Pheromone::Pheromone(ToricPosition const& position, Quantity pheromone, Uid id)
	: Positionable(position), mPheromone(pheromone), mId(id) 
{
	//choisi une couleur selon l'id
	//retoumbe a 0 si depasse 4
	int i = mId;
	if (i>4) { i = 0;}
	mColor = getAppEnv().getColors()[i];
}
	
Pheromone::~Pheromone() {}

//getter
double Pheromone::getPheromone() const
{
	return mPheromone;
}

double Pheromone::getId() const
{
	return mId;
}
//methodes
void Pheromone::draw(sf::RenderTarget& target) const
{
	auto PheromoneShape = buildCircle(getPosition().toVec2d(), 5.0, mColor);
	target.draw(PheromoneShape);
}

bool Pheromone::isNull()
{
	//s'efface si en-dessous du seuil de detection ou si dans rayon bombe
	return (mPheromone < getAppConfig().getDouble("PHEROMONE_THRESHOLD") || getAppEnv().getNuked(getPosition()));
}

void Pheromone::update(sf::Time dt)
{	
	//change the value of mPheromone for the evaporation
	mPheromone = mPheromone - (dt.asSeconds() * getAppConfig().getDouble("PHEROMONE_EVAPORATION_RATE"));
}
