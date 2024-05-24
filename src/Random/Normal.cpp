/*
 * infosv
 * 2013
 * Marco Antognini
 */

#include "Normal.hpp"

double normal(double mu, double sigma2)
{
    static std::mt19937 algo;

    static bool initialise = true;
    if (initialise) {
        initialise = false;
        std::random_device rd;
        algo.seed(rd());
    }

    using distribution_type = std::normal_distribution<>;

    distribution_type dist(mu, std::sqrt(sigma2));

    return dist(algo);
}
