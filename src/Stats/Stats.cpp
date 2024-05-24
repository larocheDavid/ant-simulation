/*
 * infosv
 * 2013
 * Marco Antognini
 */

#include "Stats.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

void Stats::draw(sf::RenderTarget& target) const
{
    unsigned int const fontSize = 20;
    double const initialPadding = 5;
    double const padding = fontSize + 5;
    Vec2d position = { initialPadding, initialPadding };

    for (auto& slot: mSlots) {
        auto msg = slot.first + ": " + std::to_string(slot.second);
        auto text = buildText(msg, position, getAppFont(), fontSize, sf::Color::Black);
		if(std::to_string(slot.second) == "0") {
			msg = "";
		}
       
        text.setOrigin(0, 0);
        target.draw(text);
		position.y += padding;
    }
}

void Stats::reset()
{
	mSlots.clear();
}

    // Here, more data can be drawn if needed.
    //
    // For example, a graph can be displayed with sf::Vertex and sf::VertexArray
    // by using sf::PrimitiveType::LinesStrip. One can initialise the array
    // with a flat line and then, with some "append()" function and an iterator,
    // override the current vertex pointed by the iterator and move the iterator
    // to next vertex.

void Stats::incrementSlot(Title const& title, Count incr)
{
    mSlots[title] += incr;
}

void Stats::decrementSlot(Title const& title, Count decr)
{
    mSlots[title] -= decr;
}
