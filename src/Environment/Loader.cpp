 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#include <fstream>
#include <iostream>
#include "Loader.hpp"
#include "../Utility/Utility.hpp"
#include "../Application.hpp"
#include "../Animal/Termite.hpp"
#include "../Environment/Anthill.hpp"


void loadMap(std::string const& filePath){
	std::ifstream fileIn;
	fileIn.open(filePath);
	if(fileIn.fail()) { //test si l'ouverture du fichier est possible
	std::cerr << "Loader has encountered an error : Couldn't open " << fileIn << std::endl;
	} else { 
		while(! fileIn.eof()) {
			std::string ligne;
			getline(fileIn, ligne);
			if (ligne == "" || ligne [0] == '#') { //si ligne vide ou commentaire, continue
				continue; 
			}
			std::vector<std::string> data;
			data = split(ligne, ' '); //coupe la ligne pour les differents types de donnes et remplis le vector	
			// cas anthill
			if(data[0] == "anthill") {
				if(data.size() == 4 || data.size() == 3) {
					ToricPosition anthillPosition(std::stod(data[1]),std::stod(data[2]));
					getAppEnv().addAnthill(new Anthill(anthillPosition));
				} else {
				std::cerr << "Loader has encountered an error : Invalid line \n";
				std::cerr << ligne << "\n";
				std::cerr << " (incorrect anthill) \n";
				std::cerr << std::endl;
				}
			}
			// cas food
			else if(data[0] == "food") {
				if(data.size() == 4) {
					ToricPosition foodPosition(std::stod(data[1]),std::stod(data[2]));
					getAppEnv().addFood(new Food(foodPosition, std::stoi(data[3])));
				} else {
				std::cerr << "Loader has encountered an error : Invalid line \n";
				std::cerr << ligne;
				std::cerr << " (incorrect food) \n";
				std::cerr << std::endl;
				}
			}
			// cas termite
			else if(data[0] == "termite") {
				if(data.size() == 3) {
					ToricPosition position(std::stod(data[1]),std::stod(data[2]));
					getAppEnv().addAnimal(new Termite(position));
				} else {
				std::cerr << "Loader has encountered an error : Invalid line  \n ";
				std::cerr << ligne;
				std::cerr << " (incorrect Termite) \n";
				std::cerr << std::endl;
				}
			}
			//to load other type, the code is the same
			//choose the right constructor
			//and include the class
		}
		fileIn.close();
	}
}
