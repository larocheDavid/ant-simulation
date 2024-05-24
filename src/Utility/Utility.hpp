/*
 * infosv
 * 2013
 * Marco Antognini
 */

#ifndef INFOSV_UTILITY_HPP
#define INFOSV_UTILITY_HPP

#include <string>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Vec2d.hpp"
#include "../Environment/Positionable.hpp"
#include "../Environment/ToricPosition.hpp"


/* A few typedefs */
using Angle      = double;
using Prob       = double;
using Probs      = std::vector<Prob>;
using Intervals  = std::vector<Angle>;
using Quantity   = double;
using Quantities = std::vector<Quantity>;
using Uid        = unsigned int; ///< Unique Identifier, @see createUid()


/* A few constants */
double const DEG_TO_RAD = 0.0174532925; ///< Degree to Radian conversion constant
double const TAU = 6.283185307; ///< TAU constant (= 2 * PI)
double const PI = 3.141592654; ///< PI constant
double const EPSILON = 1e-8; ///< a small epsilon value

/*!
 * @brief Creates a new unique id.
 *
 * @return a new unique id.
 */
Uid createUid();

/*!
 * @brief Constructs a sf::Sprite object fully set up.
 *
 * @param position the position of the centre of the sprite
 * @param size size of the side
 * @param texture the texture
 * @return a sprite with all these parameters set
 */
sf::Sprite buildSprite(Vec2d position, double size, sf::Texture const& texture);

/*!
 * @brief Constructs a sf::Text object fully set up.
 *
 * @param msg text to display
 * @param position centre position of the text
 * @param font the font to use
 * @param size the font size to use
 * @param color the color of the text
 * @return a text with all these parameters set
 */
sf::Text buildText(std::string const& msg, Vec2d position, sf::Font const& font, unsigned int size, sf::Color color);

/*!
 * @brief Constructs a circle with a sf::CircleShape.
 *
 * @param position the position of the centre of the circle
 * @param radius the radius of the circle
 * @param color the color of the circle
 * @return a shape with all these parameters set
 */
sf::CircleShape buildCircle(Vec2d position, double radius, sf::Color color);

/*!
 * @brief Constructs an annulus with a sf::CircleShape.
 *
 * @param position position of the centre of the ring
 * @param radius inner radius of the ring
 * @param color the color of the ring
 * @param thickness width of the ring
 * @return a shape with all these parameters set
 */
sf::CircleShape buildAnnulus(Vec2d position, double radius, sf::Color color, double thickness);

/*!
 * @brief Constructs a square with a sf::RectangleShape.
 *
 * @param position the centre of the square
 * @param side size of a side of the square
 * @param color the color of the square
 * @return a shape with all these parameters set
 */
sf::RectangleShape buildSquare(Vec2d position, double side, sf::Color color);

/*!
 * @brief Checks if x is equal to y, with a predefined precision.
 *
 * @param x a real number
 * @param y another real number
 * @return true is the difference between x and y is less than a small epsilon
 */
bool isEqual(double x, double y);

/*!
 * @brief Checks if x is equal to y with a precision of epsilon.
 *
 * @param x a real number
 * @param y another real number
 * @param epsilon precision of the equality test
 * @return true if the difference between x and y is less than the given epsilon
 */
bool isEqual(double x, double y, double epsilon);

/*!
 * @brief Computes the delta between two angles in radians.
 *
 * @param a an angle (rad)
 * @param b a second angle (rad)
 * @return (a-b) in [-PI, PI]
 */
double angleDelta(double a, double b);

/*!
 * @brief Splits a string.
 *
 * @param str string to split
 * @param delim char delimiter
 * @return an array of the tokens
 */
std::vector<std::string> split(std::string const& str, char delim);

/*!
 * @brief Searches in a collection for the element closest to a given point.
 *
 * @param point a point
 * @param entities a collection of non-null pointer to [subclass(es)] Positionable
 * @return the closest pointer or nullptr if the collection is empty
 *
 * @tparam Container a container of Positionable* [or subclass(es)]
 */
template <typename Container>
typename Container::value_type closestFromPoint(ToricPosition const& point, Container entities);

/*!
 * @brief Copies src at the end of dest.
 *
 * @param src the data that should be copied
 * @param dest the data is appended to this container
 *
 * @tparam C a container like std::vector<T>
 * @tparam D another container of T.
 */
template <typename C, typename D>
void append(C const& src, D& dest);

/*!
 * @brief Copies [first, last) at the end of dest.
 *
 * @param first start of the data
 * @param last iterator after the last element to copy
 * @param dest the data is appended to this container
 *
 * @tparam C a container like std::vector<T>
 * @tparam InputIt an input iterator with element type T
 */
template <typename C, typename InputIt>
void append(InputIt const first, InputIt const last, C& dest);

/*!
 * @brief Implements erase + remove_if equivalent for std::map.
 *
 * @link http://stackoverflow.com/a/7008476
 */
template <typename Map, typename F>
void map_erase_if(Map& m, F pred);

#include "Utility.tpp"

#endif // INFOSV_UTILITY_HPP
