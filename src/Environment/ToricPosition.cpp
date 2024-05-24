/*
 * infosv
 * 2013
 * Marco Antognini
 */

#include "ToricPosition.hpp"
#include "../Application.hpp"
#include "../Constants.hpp"
#include <cassert>

using namespace std;

ToricPosition::ToricPosition()
: ToricPosition(0.0, 0.0)
{
  // Done.
}

ToricPosition::ToricPosition(double x, double y)
: ToricPosition(Vec2d(x, y))
{
  // Done.
}

ToricPosition::ToricPosition(Vec2d const& position)
: mPosition(position)
{
    recompute();
}

Vec2d const& ToricPosition::toVec2d() const
{
    return mPosition;
}

double& ToricPosition::operator[](unsigned int i)
{
  assert(i<2);
  return mPosition[i];
}

double ToricPosition::operator[](unsigned int i) const
{
  assert(i<2);
  return mPosition[i];
}

ToricPosition operator+(ToricPosition a, const ToricPosition& b)
{
  a+=b;
  return a;
}

ToricPosition& ToricPosition::operator+=(ToricPosition const& b)
{
    mPosition += b.toVec2d();
    recompute();
    return *this;
}

void ToricPosition::recompute()
{
    // Clamp the position inside the toric world
    auto const width  = WORLD_WIDTH;
    auto const height = WORLD_HEIGHT;

    while (mPosition.x < 0)          mPosition.x += width;
    while (mPosition.x >= width)     mPosition.x -= width;
    while (mPosition.y < 0)          mPosition.y += height;
    while (mPosition.y >= height)    mPosition.y -= height;
}

Vec2d toricVector(ToricPosition const& from, ToricPosition const& to)
{
    // a === from, b === to
    auto const a = from.toVec2d();
    auto const b = to.toVec2d();

    int const width  = WORLD_WIDTH;
    int const height = WORLD_HEIGHT;

    // Let's fix a and find the closest b possible in this world
    // There are 9 candidates:
    // - b itself
    // - b in the "world above" (shifted by { 0, height })
    // - b in the "world below" (shifted by { 0, -height })
    // - b shifted by { width, 0 }
    // - b shifted by { -width, 0 }
    // - b shifted by { width, height }
    // - b shifted by { -width, height }
    // - b shifted by { width, -height }
    // - b shifted by { -width, -height }

    auto min_b = b;
    auto min_dist = distance(min_b, a);
    for (auto i : { -1, 0, 1 }) {
        for (auto j : { -1, 0, 1 }) {
            auto const candidate = b + Vec2d{ width * i, height * j };
            auto const candidate_dist = distance(candidate, a);
            if (candidate_dist < min_dist) {
                min_dist = candidate_dist;
                min_b = candidate;
            }
        }
    }

    return min_b - a;
}

double toricDistance(ToricPosition const& a, ToricPosition const& b)
{
    return toricVector(a, b).length();
}

std::ostream& operator<<(std::ostream& out, ToricPosition const& v)
{
  out << "(" << v[0] << ", " << v[1] << ")";
  return out;
}
