 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#include "FoodGenerator.hpp"
#include "Food.hpp"
#include "../Constants.hpp"
#include "../Random/Normal.hpp"
#include "../Random/Uniform.hpp"
#include "../Application.hpp"

//constructeur destructeur
FoodGenerator::FoodGenerator()
{
	timer = sf::Time::Zero;
}

FoodGenerator::~FoodGenerator() {}

//methode update
void FoodGenerator::update(sf::Time dt)
{
	timer += dt; //augmente le timer de dt
	
	if (timer > sf::seconds(getAppConfig().getDouble("FOOD_GENERATOR_DELTA"))) {
		timer = sf::Time::Zero; //remet le timer a 0
		
		//ajoute nourriture dans un environnement avec la loi normale (fonction"normal")
		double posx(normal(getAppConfig().getInt("WORLD_WIDTH")/2, 
			((getAppConfig().getInt("WORLD_WIDTH")/4)*(getAppConfig().getInt("WORLD_WIDTH")/4)))); 
		double posy(normal(getAppConfig().getInt("WORLD_HEIGHT")/2, 
			((getAppConfig().getInt("WORLD_HEIGHT")/4)*(getAppConfig().getInt("WORLD_HEIGHT")/4))));
		ToricPosition foodPosition(posx, posy);
		double foodQuantity(uniform(getAppConfig().getDouble("NEW_FOOD_QUANTITY_MIN"), getAppConfig().getDouble("NEW_FOOD_QUANTITY_MAX")));
		Food* food(new Food(foodPosition, foodQuantity));
		//ajoute des foods selon la loi normale grace a la fonction uniform
		getAppEnv().addFood(food);
	}
}
