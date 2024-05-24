 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#ifndef FOOD_HPP
#define FOOD_HPP

#include "../Utility/Utility.hpp"
#include "../Interface/Drawable.hpp"

class Food: public Positionable, public Drawable
{
public:
	//constructeur & destructeur
	Food(const ToricPosition& position, Quantity const& food);
	~Food();

	void setPoisoned(bool isPoisoned);
	bool getPoisoned();
	Quantity getQuantity();
	
	//methodes
	bool isEmpty();
	Quantity takeQuantity(Quantity take);
	void draw(sf::RenderTarget& target) const;
	 
private:
	Quantity mFood;
	bool mPoisoned;
};
#endif
