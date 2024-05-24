 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#ifndef ANTSOLDIER_HPP 
#define ANTSOLDIER_HPP
 
#include "Ant.hpp"

class AntSoldier : public Ant
{
public:
	//constructeur & destructeur
	AntSoldier(ToricPosition const& position, Uid id);
	virtual ~AntSoldier();
	
	//getters
	std::string getTexture() const;
	int getSize() const;
	int getStrength() const;
};
#endif
