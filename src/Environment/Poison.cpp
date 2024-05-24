/*
* Projet 2014 infosv
* Laurent Kilchoer
* David Laroche
*/

#include "Poison.hpp"
#include "../Application.hpp"
#include "../Constants.hpp"

Poison::Poison(const ToricPosition& position) 
	: Positionable(position), radius(getAppConfig().getInt("POISON_RADIUS")) {}
Poison::~Poison() {}

int const& Poison::getRadius() const
{
	return radius;
}

void Poison::infect() 
{
	//appel isPoisoned de environment
	//isPoisoned renvoie true si dans rayon
	getAppEnv().isPoisoned(getPosition(), getRadius());
}
void Poison::draw(sf::RenderTarget& target) const
{
	sf::CircleShape leakingZone;
	leakingZone.setRadius(radius);
	leakingZone.setOrigin(radius, radius);
	leakingZone.setFillColor(sf::Color(128,255,0,20)); 
	leakingZone.setPosition(getPosition().toVec2d());
	target.draw(leakingZone);

	if (getAppConfig().getBool("DEBUG_MODE2")) {
		auto const poisonSprite = buildSprite(getPosition().toVec2d(), 20, getAppTexture(getAppConfig().getString("POISON_TEXTURE")));
		target.draw(poisonSprite);
	}
}
