/*
* Projet 2014 infosv
* Laurent Kilchoer
* David Laroche
*/
 
#include "Pill.hpp"
#include "../Application.hpp"
#include "../Constants.hpp"

Pill::Pill(const ToricPosition& position) 
	: Positionable(position), dropped(false) {}
Pill::~Pill() {}

void Pill::setDropped(bool on) 
{
	dropped = on;
}

bool const& Pill::getDropped() const
{
	return dropped;
}

void Pill::draw(sf::RenderTarget& target) const
{
	//dessine l'entite 
	auto const pollutionSprite = buildSprite(getPosition().toVec2d(), 20, getAppTexture(getAppConfig().getString("PILL_TEXTURE")));
	target.draw(pollutionSprite);
}

