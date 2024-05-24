/*
 * infosv
 * 2013
 * Marco Antognini
 */

#ifndef INFOSV_RANDOM_UNIFORM_HPP
#define INFOSV_RANDOM_UNIFORM_HPP

#include "../Utility/Vec2d.hpp"

#include <type_traits>
#include <random>

/*!
 * @brief Randomly generate a number from an uniform distribution
 *
 * @param min lower bound
 * @param max upper bound
 * @return a random number fitting the uniform distribution
 */
template <typename T>
T uniform(T min, T max)
{
    static std::mt19937 algo;
    
    static bool initialise = true;
    if (initialise) {
        initialise = false;
        std::random_device rd;
        algo.seed(rd());
    }

    using condition = typename std::is_integral<T> ;
    using integer_dist = typename std::uniform_int_distribution<T>;
    using real_dist = typename std::uniform_real_distribution<T>;

    using distribution_type = typename std::conditional<condition::value, integer_dist, real_dist>::type;

    distribution_type dist(min, max);

    return dist(algo);
}

template <>
Vec2d uniform<Vec2d>(Vec2d topLeft, Vec2d bottomRight);

#endif // INFOSV_RANDOM_UNIFORM_HPP

