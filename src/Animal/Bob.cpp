 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#include "Bob.hpp"

//constructeur
Bob::Bob(ToricPosition const& position)
	:Animal(position, getAppConfig().getInt("BOB_HP"), getAppConfig().getInt("BOB_LIFESPAN")) 
{
	getAppStats().incrementSlot("Bob the destroyer");
}

//destructeur
Bob::~Bob() 
{
	getAppStats().decrementSlot("Bob the destroyer");
}

//getter vitesse
double Bob::getSpeed() const
{
	int factor(1);
	if (getAppEnv().getPill(getPosition())) factor = 2;
	return factor*getAppConfig().getDouble("BOB_SPEED");
}

std::string Bob::getTexture() const
{
	return getAppConfig().getString("BOB_TEXTURE2");
}

int Bob::getStrength() const
{
	return uniform(0, getAppConfig().getInt("BOB_STRENGTH"));
}

int Bob::getSize() const
{
	return getAppConfig().getInt("BOB_SIZE");
}

double Bob::getAttackDuration() const
{
	return getAppConfig().getDouble("BOB_ATTACK_DURATION");
}

intervalProbs Bob::computeRotationProbs() const
{	//liste d'angles et liste de probabilités pour chaques angles							
	intervalProbs interprob = {{ -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180},
	{0.001,0.002,0.003,0.004,0.0050,0.9870, 0.0050,0.0010,0.0004,0.002,0.001}};				
	return interprob;
}

void Bob::draw(sf::RenderTarget& target) const
{
	//dessine bob
	auto BobSprite = buildSprite(getPosition().toVec2d(),
	200.0, getAppTexture(getTexture())); 
	BobSprite.setRotation(90+direction/DEG_TO_RAD); //direction de radians en degrés
	target.draw(BobSprite); //dessine la fourmi au moyen d'un sprite texturé
}

bool Bob::isEnemyDispatch(Bob const*) const
{
  return false;
}

bool Bob::isEnemyDispatch(Termite const*) const
{
  return true;
}

bool Bob::isEnemyDispatch(Ant const*) const
{
  return true;
}

bool Bob::isEnemy(Animal const* animal) const
{
  // si other est de type Termite alors retourner faux
  // si other est de type Ant, alors retourner true
  return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this);
}
