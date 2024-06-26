/*
 * infosv
 * 2013
 * Marco Antognini
 */

#ifndef INFOSV_PHEROMONE_TEST_HPP
#define INFOSV_PHEROMONE_TEST_HPP

#include "../Application.hpp"
#include "../Utility/Utility.hpp"

class Ant;

/*
 * Cette classe sert à tester :
 *  - la création de phéromones,
 *  - le déplacement des fourmis en présence de phéromones.
 *
 * Ce test propose une fourmis «spéciale» (voir commandes
 * ci-dessous) affichant ses probabilités de déplacements
 * en présence de phéromones (displayprobs = true).
 *
 * Les actions disponibles sont :
 *  - créer des phéromones :
 *     - à l'aide de la souris; un premier clic défini le
 *       début d'un ségment de phéromones, un deuxième clic
 *       crée le ségment, tenir MAJUSCULE permet d'enchainer
 *       les ségments.
 *     - à l'aide de la touche P; crée un seul phéromone à
 *       l'emplacement de la souris.
 *  - créer des fourmis :
 *     - à l'aide de la touche A; crée une seule fourmis à
 *       l'emplacement de la souris.
 *  - mettre en pause le monde avec la touche ESPACE.
 *  - remettre à zéro le monde avec la touche R.
 *  - la fourmis spéciale est contrôlable indépendament :
 *     - la touche S permet de la faire bouger d'un petit dt
 *       à la fois pour contrôler finement son déplacement.
 *     - la touche ENTER (dés)active le mode 'live'; elle se
 *       comporte alors comme les autres fourmis du monde.
*/
class PheromoneTest : public Application
{
public:
    PheromoneTest() = default;
    virtual ~PheromoneTest() = default;

    virtual void onEvent(sf::Event event, sf::RenderWindow& window);
    virtual void onUpdate(sf::Time dt);
    virtual void onDraw(sf::RenderTarget& target);

private:
    // Properties for generating segment of pheromones
    Vec2d mFirstClick;
    bool mWasFirstClick = false;

    // Properties for the «special» ant that display probabilities
    Ant* mAnt = nullptr;
    bool mLive = false;
    Uid const mAntId = createUid();
};

#endif // INFOSV_PHEROMONE_TEST_HPP

