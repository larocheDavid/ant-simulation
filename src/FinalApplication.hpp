/*
 * infosv
 * 2013
 * Marco Antognini
 */

#ifndef INFOSV_FINAL_APPLICATION_HPP
#define INFOSV_FINAL_APPLICATION_HPP

#include "Application.hpp"

class FinalApplication : public Application
{
public:
    virtual void onInit(int argc, char** argv);
    virtual void onEvent(sf::Event event, sf::RenderWindow& window);
    virtual void onUpdate(sf::Time dt);
};

#endif // INFOSV_FINAL_APPLICATION_HPP
