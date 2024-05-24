 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#include <fstream>
#include <vector>

#include "ConfigManager.hpp"
#include "../Utility/Utility.hpp"

//methodes
//type int
int ConfigManager::getInt(std::string const& key) const
{
	auto it(entiers.find(key)); //utilisation de find et d'un interateur pour etre sur que l'element de clef key existe
	if(it != entiers.end()) {
		return it-> second;
	} else {
		std::cerr << "Error : No match fund in this dictionary !" << key << std::endl;
		return 0;
	}
}
void ConfigManager::setInt(std::string const& key, int value)
{
	entiers[key] = value; //entrees de la valeur et de la clee correspondante. "tests de types" dans la fonction load
}
//type double
double ConfigManager::getDouble(std::string const& key) const
{
	auto it(rationels.find(key)); //utilisation de find et d'un iterateur pour etre sur que l'element de clef key existe
	if(it != rationels.end()) {
		return it-> second;
	} else {
		std::cerr << "Error : No match fund in this dictionary !" << key << std::endl;
		return 0;
	}
}
void ConfigManager::setDouble(std::string const& key, double value) 
{
	rationels[key] = value; //entrees de la valeur et de la clee correspondante. "tests de types" dans la fonction load
}
//type string	
std::string ConfigManager::getString(std::string const& key) const
{
	auto it(chaines.find(key)); //utilisation de find et d'un iterateur pour etre sur que l'element de clef key existe
	if(it != chaines.end()) {
		return it-> second;
	} else {
		std::cerr << "Error : No match fund in this dictionary !" << key << std::endl;
		return 0;
	}
}
void ConfigManager::setString(std::string const& key, std::string value)
{
	chaines[key] = value; //entrees de la valeur et de la clee correspondante. "tests de types" dans la fonction load
}
//type bool
bool ConfigManager::getBool(std::string const& key) const
{
	auto it(booleens.find(key)); //utilisation de find et d'un interateur pour etre sur que l'element de clef key existe
	if(it != booleens.end()) {
		return it-> second;
	} else {
		std::cerr << "Error : No match fund in this dictionary !" << key << std::endl;
		return 0;
	}
}
void ConfigManager::setBool(std::string const& key, bool value)
{
	booleens[key] = value; //entrees de la valeur et de la clee correspondante. "tests de types" dans la fonction load
}



//initialisaton ou MAJ dictionnaires
bool ConfigManager::load(std::string const& filename, bool clear)
{
	if (clear) { //test si le booleen clear est true, si c'est le cas, il efface tous les dictionnaires
		entiers.clear();
		rationels.clear();
		chaines.clear();
		booleens.clear();
	} 
	std::ifstream fileIn; //ouverture d'un flux entrant filename.c_str()
	fileIn.open(filename);	//c_str()
	if(fileIn.fail()) { //test si l'ouverture du fichier est possible
		std::cerr << "ConfigManager has encountered an error : Couldn't open " << fileIn << std::endl;
		return false;
	}  	
	while (! fileIn.eof()) {
		std::string ligne;
		getline(fileIn, ligne); //lit une ligne après l'autre du fichier fileIN
		std::vector<std::string> data; //initialise le vector des donnees a traiter	
		if (ligne == "") { //si ligne vide, continue
			continue; 
		}
		if (ligne[0] == '#') {
			continue;
		}
		data = split(ligne, ':'); //coupe la ligne pour les differents types de donnes et remplis le vector	
		if(data.size() != 3) {
			std::cerr << "ConfigManager has encountered an error : Invalid line " << ligne << std::endl;
			return false;
		}
		if(data[1] == "int") { //appel de la fonction set correspondant au type, renvoit erreur si type inexistant  strcmp(data[1].c_str(),a.c_str()) == 0
			setInt(data[0], std::stoi(data[2])); //stoi converts char* to int	
		} else if (data[1] == "double") {
			setDouble(data[0], std::stod(data[2])); //stod converts char* to double
				
		} else if (data[1] == "string") {
			setString(data[0], data[2]);
		} else if (data[1] == "bool") {
				
			std::string booleen(data[2]); //test if entry correspond 
			for (auto& carac: booleen) {
				carac = tolower(carac);
			}
			if (booleen == "true" || booleen == "t" || booleen == "yes" || booleen == "y") {		
				setBool(data[0], true);
			} else if (booleen == "false" || booleen == "f" || booleen == "no" || booleen == "n") {		
				setBool(data[0], false);
			} else {
				std::cerr << "ConfigManager has encountered an error : Invalid line " << ligne << std::endl;
				return false;
			}
		} else {
			std::cerr << "ConfigManager has encountered an error : Invalid line " << ligne << std::endl;
			return false;
		} 
	}	
	fileIn.close();
	return true;
}
