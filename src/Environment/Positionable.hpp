/*
 * infosv
 * 2013
 * Marco Antognini
 */

#ifndef INFOSV_POSITIONABLE_HPP
#define INFOSV_POSITIONABLE_HPP

#include "ToricPosition.hpp"

/*!
 * @brief Manages a position in a toric world.
 *
 * @note This class is not instantiable as-is. It needs to be subclassed.
 */
class Positionable
{
public:
    /// Virtual destructor for inheritance
    virtual ~Positionable() = default;

    /// Read access for everybody
    ToricPosition const& getPosition() const;

protected:
    /// Constructor for subclasses
    Positionable(ToricPosition const& position);

    /// Change the position
    void setPosition(ToricPosition const& position);

private:
    ToricPosition mPosition; ///< Position data
};


#endif // INFOSV_POSITIONABLE_HPP

