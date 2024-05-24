/*
 * infosv
 * 2013
 * Marco Antognini
 */

#include "Utility.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

Uid createUid()
{
    static Uid last = 0u;

    assert(last < std::numeric_limits<Uid>::max());

    last += 1u;
    return last;
}

sf::Sprite buildSprite(Vec2d position, double size, sf::Texture const& texture)
{
    sf::Sprite sprite(texture);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    sprite.setPosition(position);
    double const maxSide = std::max(texture.getSize().x, texture.getSize().y);
    sprite.setScale(Vec2d(size, size) / maxSide);
    return sprite;
}

sf::Text buildText(std::string const& msg, Vec2d position, sf::Font const& font, unsigned int size, sf::Color color)
{
    sf::Text txt(msg, font, size);
    txt.setPosition(position);
    txt.setColor(color);
    txt.setCharacterSize(size);
    auto const bounds = txt.getLocalBounds();
    txt.setOrigin(bounds.width / 2, bounds.height / 2);

    return txt;
}

sf::CircleShape buildCircle(Vec2d position, double radius, sf::Color color)
{
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(position);
    circle.setFillColor(color);

    return circle;
}

sf::CircleShape buildAnnulus(Vec2d position, double radius, sf::Color color, double thickness)
{
    auto const circleRadius = radius - thickness / 2;
    sf::CircleShape annulus(circleRadius);
    annulus.setPosition(position);
    annulus.setOrigin(circleRadius, circleRadius);
    annulus.setFillColor(sf::Color::Transparent);
    annulus.setOutlineThickness(thickness);
    annulus.setOutlineColor(color);

    return annulus;
}

sf::RectangleShape buildSquare(Vec2d position, double side, sf::Color color)
{
    Vec2d const size{side, side};
    sf::RectangleShape square(size);
    square.setPosition(position);
    square.setOrigin(size / 2.0);
    square.setFillColor(color);

    return square;
}

bool isEqual(double x, double y)
{
    return isEqual(x, y, EPSILON);
}

bool isEqual(double x, double y, double epsilon)
{
    return std::abs(x - y) < epsilon;
}

double angleDelta(double a, double b)
{
    double delta = a - b;
    while (delta <  -PI)
        delta += TAU;
    while (delta >=  PI)
        delta -= TAU;
    return delta;
}

std::vector<std::string> split(std::string const& str, char delim)
{
    std::stringstream ss(str);
    std::vector<std::string> tokens;
    std::string currentToken;

    while (std::getline(ss, currentToken, delim)) {
        tokens.push_back(currentToken);
    }

    return tokens;
}
