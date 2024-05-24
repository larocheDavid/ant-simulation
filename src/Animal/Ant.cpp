 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#include "Ant.hpp"

//constructeur
Ant::Ant(const ToricPosition& position, Uid id, int _hp, int _lifeSpan)
	:Animal(position, _hp, _lifeSpan), displayProbs(false), mId(id), 
	mlastPos(position), factor(1)
{
	getAppStats().incrementSlot("Ants");
	int i = mId;
	if (i>4) { i = 0;}
	mColor = getAppEnv().getColors()[i];
}
	
//destructeur
Ant::~Ant() 
{
	//affichage de statistiques
	getAppStats().decrementSlot("Ants");
	getAppStats().decrementSlot("Anthill #"+std::to_string(mId)+" pop");
}

//getters
double Ant::getSpeed() const
{
	return getAppConfig().getDouble("ANT_SPEED");
}

double Ant::getAttackDuration() const
{
	return getAppConfig().getDouble("ANT_ATTACK_DELAY");
}

void Ant::afficheProb(sf::RenderTarget& target) const
{
	auto const interProbs = computeRotationProbs();
	for (std::size_t i = 0; i < interProbs.thetas.size()-1; ++i) {
		auto const msg = std::to_string(interProbs.probas[i]).substr(2, 4);
		auto const angle = interProbs.thetas[i];
		auto const local = Vec2d::fromAngle(getDirection() + angle * DEG_TO_RAD) * 250;
		auto const text = buildText(msg, getPosition().toVec2d() + local, getAppFont(), 15, sf::Color::Black);
		target.draw(text);
	}
	auto const quantities = getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(getPosition(), getDirection(), interProbs.thetas, mId);
	for (std::size_t i = 0; i < quantities.size()-1; ++i) {
		auto const msg = std::to_string(quantities[i]).substr(0, 4);
		auto const angle = interProbs.thetas[i];
		auto const local = Vec2d::fromAngle(getDirection() + angle * DEG_TO_RAD) * 200;
		auto const text = buildText(msg, getPosition().toVec2d() + local, getAppFont(), 15, sf::Color::Red);
		target.draw(text);
	}
}

//methode d'affichage à la fenetre
void Ant::draw(sf::RenderTarget& target) const
{
	auto antSprite = buildSprite(getPosition().toVec2d(),
	getSize(), getAppTexture(getTexture())); 
	antSprite.setRotation(direction/DEG_TO_RAD); //direction de radians en degrés
	target.draw(antSprite); //dessine la fourmi au moyen d'un sprite texturé

	if (getAppConfig().getBool("DEBUG_MODE")) {
		//permet d'afficher la trajectoire de la fourmi
		sf::VertexArray ligne(sf::PrimitiveType::Lines, 2);
		ligne[0] = { getPosition().toVec2d(), sf::Color::Black };
		ligne[1] = { getPosition().toVec2d()+(getAppConfig().getInt("WORLD_HEIGHT")/2)*Vec2d::fromAngle(direction), sf::Color::Blue };       
		target.draw(ligne);
		
		afficheProb(target);
		
		auto const circleShape = buildAnnulus(getPosition().toVec2d(), getAppConfig().getDouble("ANT_SMELL_MAX_DISTANCE"), sf::Color::Blue, 2);
		target.draw(circleShape);
	}
	if (getAppConfig().getBool("DEBUG_MODE2")) {
		//affichage pos permet de ne pas dessiner sur la fourmi
		Vec2d pos(0, 30);
		auto const text = buildText("ID: "+std::to_string(mId), 
		getPosition().toVec2d()+pos, getAppFont(), 12, sf::Color::Blue);
		target.draw(text);

		auto const text2 = buildText("HP: "+std::to_string(lround(hp)), 
		getPosition().toVec2d()+1.4*pos, getAppFont(), 12, sf::Color::Red);
		target.draw(text2);
		
		auto const text3 = buildText("Lifespan: "+std::to_string(lround(lifeSpan.asSeconds())), 
		getPosition().toVec2d()-pos, getAppFont(), 12, sf::Color::Blue);
		target.draw(text3);
		
		auto const circleShape = buildAnnulus(getPosition().toVec2d(), getAppConfig().getDouble("ANT_SMELL_MAX_DISTANCE"), mColor, 2);
		target.draw(circleShape);
	}
}

//methode pheromones
void Ant::spreadPheromones()
{	
	//ajoute un pheromone à une distance de distance de 0,85 calculee avec toricdistance
	if(toricDistance(mlastPos, getPosition())*factor*getAppConfig().getDouble("ANT_PHEROMONE_DENSITY") >= 0.85) {
		
		getAppEnv().addPheromone(new Pheromone(getPosition(), getAppConfig().getDouble("ANT_PHEROMONE_ENERGY"), mId));
		mlastPos = getPosition();
	}
}

void Ant::update(sf::Time dt)
{
	Animal::update(dt);
	spreadPheromones();
}

intervalProbs Ant::computeRotationProbs() const
{
	Intervals I = { -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
	Quantities Q = getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(getPosition(), getDirection(), I, mId);
	Probs Pm = {0.0000, 0.0000, 0.0005, 0.0010, 0.0050, 0.9870, 0.0050, 0.0010, 0.0005, 0.0000, 0.0000};
	Probs Psol = {0.0000, 0.00, 0.02, 0.1, 0.2, 0.36, 0.2, 0.1, 0.0005, 0.02, 0.0000};
	double z(0);
	Probs Pphi(I.size());
	//algorithme deplacements sensoriels
	for(unsigned int n(0); n < Pphi.size();++n) {
		Pphi[n] = 1/(1 + exp(-BETA_D *(Q[n] - Q_ZERO)));
		z += Pm[n] * pow(Pphi[n], ALPHA);
	}
	Probs Pm2(I.size());
	for(unsigned int n(0); n < Pm2.size(); ++n) {
		Pm2[n] = Pm[n] * pow(Pphi[n], ALPHA) / z;
	}
	intervalProbs crp = {{I},{Pm2}};
	return crp; // retourne tableau de probabilites
}

bool Ant::isEnemyDispatch(Ant const* other) const
{	//retourne true si l'autre ant a un iD different
	return this->mId != other->mId;
}

bool Ant::isEnemyDispatch(Termite const*) const
{	//ant combat toujour une termite
	return true;
}

bool Ant::isEnemy(Animal const* animal) const
{
	//retourne true si lui-meme et l'autre ne sont pas morts et s'ils sont ennemis
	return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this);
}
