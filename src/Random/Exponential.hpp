/*
 * infosv
 * 2013
 * Marco Antognini
 */

#ifndef INFOSV_RANDOM_EXPONENTIAL_HPP
#define INFOSV_RANDOM_EXPONENTIAL_HPP

#include <cmath>
#include <random>

/*!
 * @brief Randomly generate a number from an exponential distribution
 *
 * @param lambda rate
 * @return a random number fitting the exp(lambda) distribution
 */
double exponential(double lambda);

#endif // INFOSV_RANDOM_EXPONENTIAL_HPP

