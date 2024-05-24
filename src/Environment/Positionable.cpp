/*
 * infosv
 * 2013
 * Marco Antognini
 */

#include "Positionable.hpp"

ToricPosition const& Positionable::getPosition() const
{
    return mPosition;
}

Positionable::Positionable(ToricPosition const& position)
{
    setPosition(position);
}

void Positionable::setPosition(ToricPosition const& position)
{
    mPosition = position;
}
