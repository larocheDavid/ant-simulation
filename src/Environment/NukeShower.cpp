 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#include "NukeShower.hpp"
#include "Nuke.hpp"
#include "../Constants.hpp"
#include "../Random/Normal.hpp"
#include "../Random/Uniform.hpp"
#include "../Application.hpp"

//constructeur destructeur
NukeShower::NukeShower()
{
	timer = sf::Time::Zero;
}

NukeShower::~NukeShower() {}

//methode update
void NukeShower::update(sf::Time dt)
{
	timer += dt; //augmente le timer de dt
	
	if (timer > sf::seconds(getAppConfig().getDouble("NUKE_GENERATOR_DELTA"))) {
		timer = sf::Time::Zero; //remet le timer a 0
		
		//ajoute nourriture dans un environnement avec la loi normale (fonction"normal")
		double posx(normal(getAppConfig().getInt("WORLD_WIDTH")/2, 
			((getAppConfig().getInt("WORLD_WIDTH")/4)*(getAppConfig().getInt("WORLD_WIDTH")/4)))); 
		double posy(normal(getAppConfig().getInt("WORLD_HEIGHT")/2, 
			((getAppConfig().getInt("WORLD_HEIGHT")/4)*(getAppConfig().getInt("WORLD_HEIGHT")/4))));
		ToricPosition nukePosition(posx, posy);
		
		Nuke* nuke(new Nuke(nukePosition));
		getAppEnv().addNuke(nuke);
	}
}
