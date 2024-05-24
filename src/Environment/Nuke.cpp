/*
* Projet 2014 infosv
* Laurent Kilchoer
* David Laroche
*/

#include "Nuke.hpp"
#include "../Application.hpp"
#include "../Constants.hpp"

Nuke::Nuke(const ToricPosition& position) //getAppConfig().getInt("NUKE_RADIUS"
	: Positionable(position), radius(0) {}
Nuke::~Nuke() {}

int const& Nuke::getRadius() const
{
	return radius;
}

void Nuke::update() //simule explosion
{
	radius += 1;
}

bool Nuke::finished()
{
	if (radius > 200) {
		return true;
	}
	return false;
}

void Nuke::draw(sf::RenderTarget& target) const
{
	sf::CircleShape leakingZone;
	leakingZone.setRadius(radius);
	leakingZone.setOrigin(radius, radius);
	leakingZone.setFillColor(sf::Color(255,255,0,255));
	leakingZone.setPosition(getPosition().toVec2d());
	target.draw(leakingZone);
	
	if (getAppConfig().getBool("DEBUG_MODE2")) {
		auto const pollutionSprite = buildSprite(getPosition().toVec2d(), 20, getAppTexture(getAppConfig().getString("NUKE_TEXTURE")));
		target.draw(pollutionSprite);
	}
}
