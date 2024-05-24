 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#include "AntSoldier.hpp"

//constructeur
AntSoldier::AntSoldier(ToricPosition const& position, Uid id)
	:Ant(position, id, getAppConfig().getInt("ANT_SOLDIER_HP"),
	getAppConfig().getInt("ANT_SOLDIER_LIFESPAN")) 
{
	getAppStats().incrementSlot("Ant Soldiers");
}

//destructeur
AntSoldier::~AntSoldier() 
{
	getAppStats().decrementSlot("Ant Soldiers");
}

//methode retourne texture antsoldier
std::string AntSoldier::getTexture() const
{
	if(getAppConfig().getBool("WATER_MODE")) {
		return getAppConfig().getString("ANT_SOLDIER_TEXTURE2");
	} else {
		return getAppConfig().getString("ANT_SOLDIER_TEXTURE");
	}
}

int AntSoldier::getSize() const
{	
	//adapte la taille du dessin selon le mode
	if(getAppConfig().getBool("WATER_MODE")) {
		return getAppConfig().getInt("ANT_SOLDIER_SIZE2");
	} else {
		return getAppConfig().getInt("ANIMAL_SIZE");
	}
}

int AntSoldier::getStrength() const
{
	//prend une force uniformement choisie entre 0 et sa force maximale 
	return uniform(0, getAppConfig().getInt("ANT_SOLDIER_STRENGTH"));
}
