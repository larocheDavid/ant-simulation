/*
 * infosv
 * 2013
 * Marco Antognini
 */

#ifndef INFOSV_DRAWABLE_HPP
#define INFOSV_DRAWABLE_HPP

#include <SFML/Graphics.hpp>

/*!
 * @class Drawable
 *
 * @brief Represents an entitiy that can be represented graphically
 */
class Drawable
{
public:
    virtual ~Drawable() = default;

    virtual void draw(sf::RenderTarget& target) const = 0;
};

#endif // INFOSV_DRAWABLE_HPP

