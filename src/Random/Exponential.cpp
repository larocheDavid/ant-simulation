/*
 * infosv
 * 2013
 * Marco Antognini
 */

#include "Exponential.hpp"

double exponential(double lambda)
{
    static std::mt19937 algo;

    static bool initialise = true;
    if (initialise) {
        initialise = false;
        std::random_device rd;
        algo.seed(rd());
    }

    using distribution_type = std::exponential_distribution<>;

    distribution_type dist(lambda);

    return dist(algo);
}
