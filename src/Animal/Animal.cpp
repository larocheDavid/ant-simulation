 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */

#include "Animal.hpp"

//constructeurs
Animal::Animal(const ToricPosition& position, int _hp, int _lifeSpan)
	:Positionable(position), hp(_hp), lifeSpan(sf::seconds(_lifeSpan)),
	onPills(false), peak(sf::seconds(getAppConfig().getDouble("PILL_DELAY"))), flash(1)
{
	direction = uniform(0.0, TAU); //Initialise un angle entre 0 et 2pi
	etat = IDLE; //init etat a normal = IDLE
	freeze = sf::Time::Zero; //timer de temps de combat
	getAppStats().incrementSlot("Animals"); //affiche le nombre d'animaux qui sont nés
}

//constructeur de copie
Animal::Animal(Animal const& autre)
	:Positionable(autre.getPosition()), 
	 hp(autre.hp), lifeSpan(autre.lifeSpan) {}

//destructeur
Animal::~Animal()
{	//affichage du nombre d'animaux "morts"
	getAppStats().decrementSlot("Animals");
}

//setter direction 
void Animal::setDirection(const Angle& angle)
{
	direction = angle;
}

//setter etat
void Animal::updateState(sf::Time dt) 
{
	switch (etat)
	{
		case ATTACK:
		if (freeze > sf::Time::Zero) {
			freeze -= dt;
		}
		else if (freeze < sf::Time::Zero) { //mode escaping après écoulement du temps
			etat = ESCAPING;
		} 
		if (getAppEnv().getClosestEnemy(this) == nullptr) { //mode IDLE si animal mort
			etat = IDLE;
		}
		break;
		
		case IDLE: //mode ATTACK si un ennemi existe et que c'est un prédateur ou/et est un prédateur lui meme
			if(getAppEnv().getClosestEnemy(this) != nullptr && 
				(getAppEnv().getClosestEnemy(this)->isPredator() || this->isPredator())) {
				etat = ATTACK;
				//fait face à son ennemi lors du combat
				setDirection((getAppEnv().getClosestEnemy(this)->getPosition().toVec2d() - getPosition().toVec2d()).angle());
				//condition permettant le combat au temps attack_duration le plus long
				if (getAppEnv().getClosestEnemy(this)->getAttackDuration() > this->getAttackDuration()) {
					freeze = sf::seconds(getAppEnv().getClosestEnemy(this)->getAttackDuration());
				} else {
					freeze = sf::seconds(this->getAttackDuration());
				}
			}
		break;
		case ESCAPING: //se remet en IDLE s'il n'y a plus d'ennemi
			if (getAppEnv().getClosestEnemy(this) == nullptr) {
			etat = IDLE;
			}
		break;
	}
}

//getter direction 
Angle const& Animal::getDirection() const
{
	return direction;
}

//methodes
bool Animal::isDead() const
{
	return (hp <= 0 || lifeSpan <= sf::Time::Zero);
}

bool Animal::isPredator() const 
{
	return true;
}

//bob combat n'importe quel animal car il n'a peur de rien
bool Animal::isEnemyDispatch(Bob const*) const
{
  return true;
}

intervalProbs Animal::computeRotationProbs() const
{	//liste d'angles et liste de probabilités pour chaques angles							
	intervalProbs interprob = {{ -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180},
	{0.0000,0.0000,0.0005,0.0010,0.0050,0.9870, 0.0050,0.0010,0.0005,0.0000,0.0000}};				
	return interprob;
}

void Animal::move(sf::Time dt)
{	
	//s'il prend pill, modification d'un coefficient(flash) multipliant sa vitesse
	// et sa direction pendant un délai PILL_DELAY
	if (onPills) { 
		peak = sf::Time::Zero;
		onPills = false;
	}
	if (peak < sf::seconds(getAppConfig().getDouble("PILL_DELAY"))) { 
		flash = 2;
		lifeSpan -= dt;
	} else {
		flash = 1;
	}
	peak += dt;
	//initialisation du vecteur vitesse créé par sa vitesse*sa direction transformée en Vec2d
	Vec2d speed = flash*getSpeed()*Vec2d::fromAngle(direction);
	timer += dt;
	intervalProbs mInterProb(computeRotationProbs());
		//effectue le code suivant lorsque le compte a rebours depasse 20 ms
	if (clock.getElapsedTime().asMilliseconds()>=20) {
		if (timer >=  sf::seconds(getAppConfig().getDouble("ANIMAL_NEXT_ROTATION_DELAY"))) {
			timer = sf::Time::Zero; //remet le timer a 0
				
			//algorithme de distribution linéaire
			static std::mt19937 algo;
			static bool initialise = true;
			if(initialise){
				initialise = false;
				std::random_device rd;
				algo.seed(rd());
			}
			// Compute a random direction
			std::piecewise_linear_distribution<> dist
			(mInterProb.thetas.begin(), mInterProb.thetas.end(), 
			mInterProb.probas.begin());
				
			//ajoute à direction l'angle trouvé par computeRotationProbs
			direction += flash*dist(algo)*DEG_TO_RAD;
		}
		//déplace l'animal en multipliant son vecteur vitesse par le temps depuis sa dernière position
		setPosition(getPosition()+ speed*dt.asSeconds());
		//remet le compte à rebours à 0
		clock.restart(); 
	}
}

void Animal::attack(Animal* other)
{	//attaque si l'ennemi est encore vivant
	if (getAppEnv().getClosestEnemy(this) != nullptr) {
		other->hp -= this->getStrength();
	}
}

void Animal::update(sf::Time dt)
{	
	//onPills vrai s'il trouve une pill
	if (getAppEnv().getPill(getPosition())) { onPills = true; }
	//lifespan diminué s'il entre dans une zone poluée
	if (getAppEnv().getPollutionAnimal(getPosition())) {
		lifeSpan -= dt+dt+dt;
	}
	//"meurt" s'il entre dans la zone de la bombe
	if (getAppEnv().getNuked(getPosition())) {
		lifeSpan = sf::Time::Zero;
	}
	lifeSpan -= dt;
	updateState(dt);
	if (etat == ATTACK) {
		attack(getAppEnv().getClosestEnemy(this));
	} else {
		move(dt);
	}
}
