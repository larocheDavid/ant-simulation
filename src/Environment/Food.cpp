 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#include "Food.hpp"
#include "../Application.hpp"
#include "../Constants.hpp"

//constructeur & destructeur
Food::Food(const ToricPosition& position, Quantity const& food)
: Positionable(position) // utilise attribut superclasse positionable car herite de positionable(utlise son constructeur)
, mFood(food), mPoisoned(false) {}

Food::~Food() {}

void Food::setPoisoned(bool isPoisoned)
{
	mPoisoned = isPoisoned;
}

bool Food::getPoisoned()
{
	return mPoisoned;
}

Quantity Food::getQuantity()
{
	return mFood;
}
//methodes
Quantity Food::takeQuantity(Quantity take)
{
	if(take < 0.0) {
		take = 0.0;
		
    } else if(take > mFood) {
		take = mFood;
        mFood = 0.0;
        
    } else {
        mFood -= take;
    }
    return take;
}

void Food::draw(sf::RenderTarget& target) const
{	//getPosition() vient de Positionable, donne la position en toricposition
	if (getAppConfig().getBool("WATER_MODE")) {
		auto const foodSprite = buildSprite(getPosition().toVec2d() , 20.0, getAppTexture(getAppConfig().getString("FOOD_TEXTURE2"))); // 
		target.draw(foodSprite);
	} else { 
		auto const foodSprite = buildSprite(getPosition().toVec2d() , mFood/2, getAppTexture(getAppConfig().getString("FOOD_TEXTURE")));
		target.draw(foodSprite);
	}
	if (getAppConfig().getBool("DEBUG_MODE2")) {
		Vec2d pos(0, 12);
		auto const text = buildText(std::to_string(lround(mFood)), getPosition().toVec2d()+pos, getAppFont(), 12, sf::Color::Black); //permet d'afficher une string dans la fenetre (construit un objet dessinable)
		target.draw(text);
	
		auto const text2 = buildText(std::to_string(mPoisoned), getPosition().toVec2d()+2*pos, getAppFont(), 12, sf::Color::Green); //permet d'afficher une string dans la fenetre (construit un objet dessinable)
		target.draw(text2);
	}
}

bool Food::isEmpty()
{	// s'efface si la nourriture vaut 0 ou est atteint par une bombe
	return ((mFood == 0.0) || getAppEnv().getNuked(getPosition()));
}
