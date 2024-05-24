/*
 * infosv
 * 2013
 * Marco Antognini
 */

#ifndef INFOSV_STATS_HPP
#define INFOSV_STATS_HPP

#include "../Interface/Drawable.hpp"

#include <string>
#include <map>

/*!
 * @class Stats
 *
 * @brief This class handles the display of statistics
 *
 * Each slot is displayed with the following pattern:
 * <Title>: <Count>
 *
 * Slots are sorted alphanumerically (title)
 */
class Stats : public Drawable
{
public:
	// Define aliases of types useful for the class
    using Count         = int;
    using Title         = std::string;
    using Key           = Title;
    using Value         = Count;
    using Dictionary    = std::map<Key, Value>;

public:
    Stats() = default;
    virtual ~Stats() noexcept = default;

    // Forbid copy
    Stats(Stats const&) = delete;
    Stats& operator=(Stats const&) = delete;

    // Implement Drawable
    virtual void draw(sf::RenderTarget& target) const;

    /*!
     * @brief Increment a slot by incr
     *
     * If the slot doesn't exist, it is created with an initial count of 0
     */
    void incrementSlot(Title const& title, Count incr = 1);

    /*!
     * @brief Decrement a slot by decr
     *
     * If the slot doesn't exist, it is create with an initial count of 0
     */
    void decrementSlot(Title const& title, Count decr = 1);
    
    //reset 
    void reset();

private:
    Dictionary mSlots; ///< Data to be displayed
};

#endif // INFOSV_STATS_HPP

