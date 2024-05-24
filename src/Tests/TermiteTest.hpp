/*
 * infosv
 * 2013
 * Marco Antognini
 */

#ifndef INFOSV_TERMITE_TEST_HPP
#define INFOSV_TERMITE_TEST_HPP

#include "../Application.hpp"

class TermiteTest : public Application
{
public:
    virtual void onEvent(sf::Event event, sf::RenderWindow& window);
};

#endif // INFOSV_TERMITE_TEST_HPP

