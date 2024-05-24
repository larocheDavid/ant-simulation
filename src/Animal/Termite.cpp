 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#include "Termite.hpp"

Termite::Termite(const ToricPosition& position)
	:Animal(position, TERMITE_HP, TERMITE_LIFESPAN) 
{
	getAppStats().incrementSlot("Termites");
}

Termite::~Termite()
{
	getAppStats().decrementSlot("Termites");
}

//getter vitesse
double Termite::getSpeed() const
{	
	int factor(1);
	if (getAppEnv().getPill(getPosition())) factor = 2;
	return factor*getAppConfig().getDouble("TERMITE_SPEED");
}

//methode retourne texture termite
std::string Termite::getTexture() const
{
	if(getAppConfig().getBool("WATER_MODE")) {
		return getAppConfig().getString("TERMITE_TEXTURE2");
	} else {
		return getAppConfig().getString("TERMITE_TEXTURE");
	}
}
int Termite::getSize() const
{	//renvoie 2eme texture si mode eau activé dans constants
	if(getAppConfig().getBool("WATER_MODE")) {
		return getAppConfig().getInt("TERMITE_SIZE2");
	} else {
		return getAppConfig().getInt("ANIMAL_SIZE");
	}
}

int Termite::getStrength() const
{	//attaque maximale = TERMITE_STRENGTH
	return uniform(0, getAppConfig().getInt("TERMITE_STRENGTH"));
}

double Termite::getAttackDuration() const
{
	return getAppConfig().getDouble("TERMITE_ATTACK_DELAY");
}

//methode draw
void Termite::draw(sf::RenderTarget& target) const
{
	auto termiteSprite = buildSprite(getPosition().toVec2d(),
	getSize(), getAppTexture(getTexture())); 
	termiteSprite.setRotation(direction/DEG_TO_RAD); //direction de radians en degrés
	target.draw(termiteSprite); //dessine la termite au moyen d'un sprite texturé
	if (getAppConfig().getBool("DEBUG_MODE2")) {
		auto const circleShape = 
		buildAnnulus(getPosition().toVec2d(), ANIMAL_SIGHT_DISTANCE, sf::Color::Blue, 2);
		target.draw(circleShape);
		
		Vec2d pos(0, 30);
		auto const text2 = buildText("HP: "+std::to_string(lround(hp)), 
		getPosition().toVec2d()+pos, getAppFont(), 12, sf::Color::Red);
		target.draw(text2);
		
		auto const text3 = buildText("Etat: "+std::to_string(etat), 
		getPosition().toVec2d()+pos*1.4, getAppFont(), 12, sf::Color::Black);
		target.draw(text3);
		
		auto const text1 = buildText("Lifespan: "+std::to_string(lround(lifeSpan.asSeconds())), 
		getPosition().toVec2d()-pos, getAppFont(), 12, sf::Color::Blue);
		target.draw(text1);
	}
}

bool Termite::isEnemyDispatch(Termite const*) const
{
  return false;
}

bool Termite::isEnemyDispatch(Ant const*) const
{
  return true;
}

bool Termite::isEnemy(Animal const* animal) const
{
  // si other est de type Termite alors retourner faux
  // si other est de type Ant, alors retourner true
  return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this);
}

