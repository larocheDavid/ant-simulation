/*
 *infosv
 *2014
 *Maxime Ameho
 *
 */

#ifndef INFOSV_ANT_TEST_HPP
#define INFOSV_ANT_TEST_HPP

#include "../Application.hpp"

class AntTest : public Application
{
public:
  virtual void onEvent(sf::Event event, sf::RenderWindow&);
};

#endif //INFOSV_ANT_TEST_HPP
