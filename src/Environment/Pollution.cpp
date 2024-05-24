/*
* Projet 2014 infosv
* Laurent Kilchoer
* David Laroche
*/

#include "Pollution.hpp"
#include "../Application.hpp"
#include "../Constants.hpp"

Pollution::Pollution(const ToricPosition& position) 
	: Positionable(position), radius(getAppConfig().getInt("POLLUTION_RADIUS")) {}
Pollution::~Pollution() {}

int const& Pollution::getRadius() const
{
	return radius;
}

void Pollution::draw(sf::RenderTarget& target) const
{
	sf::CircleShape leakingZone;
	leakingZone.setRadius(radius);
	leakingZone.setOrigin(radius, radius);
	leakingZone.setFillColor(sf::Color(255,255,0,40));
	leakingZone.setPosition(getPosition().toVec2d());
	target.draw(leakingZone);
	
	if (getAppConfig().getBool("DEBUG_MODE2")) {
		auto const pollutionSprite = buildSprite(getPosition().toVec2d(), 40, getAppTexture(getAppConfig().getString("POLLUTION_TEXTURE")));
		target.draw(pollutionSprite);
	}
}
