/*
 * infosv
 * 2013
 * Marco Antognini
 */

#include "PheromoneTest.hpp"
#include "../Animal/AntWorker.hpp"
#include "../Environment/Pheromone.hpp"
#include "../Constants.hpp"

IMPLEMENT_MAIN(PheromoneTest)

void PheromoneTest::onUpdate(sf::Time dt)
{
    // If needed, create our «special» ant in the middle of the world
    if (mAnt == nullptr) {
        Vec2d const worldSize = {
            WORLD_WIDTH,
            WORLD_HEIGHT
        };
        mAnt = new AntWorker(worldSize / 2, mAntId);
        mAnt->displayProbs = true;
    }

    // When in «live» mode, update our «special» ant like the others
    if (mLive) {
        mAnt->update(dt);
        if (mAnt->isDead()) {
            // Create another ant
            delete mAnt;
            mAnt = nullptr;
        }
    }
}

void PheromoneTest::onDraw(sf::RenderTarget& target)
{
    if (mAnt != nullptr) {
        mAnt->draw(target);
    }
}

void PheromoneTest::onEvent(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            default: break;

            case sf::Keyboard::P:
                getAppEnv().addPheromone(new Pheromone(getCursorPositionInView(), 5.0));
                break;

            case sf::Keyboard::A:
                getAppEnv().addAnimal(new AntWorker(getCursorPositionInView(), mAntId));
                break;

            case sf::Keyboard::Return:
                mLive = !mLive; // toggle «live» mode
                break;

            case sf::Keyboard::S:
                mAnt->update(sf::seconds(0.05f));
                break;

            case sf::Keyboard::R:
                getAppEnv().reset();
                delete mAnt;
                mAnt = nullptr; // will be regenerated in `onUpdate`
                break;
        }
    }

    // Generate segment of pheromones?
    if (event.type == sf::Event::MouseButtonPressed) {
        if (mWasFirstClick) { // yes
            // This code is basically the same as the one in Ant::spreadPheromones()
            // but without considering the world as toric (easier).
            // It spawn enough pheromone between `end` and `start` based on the pheromone density.
            auto const end = getCursorPositionInView();
            auto const start = mFirstClick;
            auto const NB_STEPS_PER_PIXEL = TEST_PHEROMONE_DENSITY;
            auto const direction = end - start;
            auto const nb_steps = direction.length() * NB_STEPS_PER_PIXEL;
            auto const step = direction / nb_steps;
            for (int i = 0; i < nb_steps; ++i) {
                getAppEnv().addPheromone(new Pheromone(start + i * step, 5.0));
            }

            // If shift key pressed then link the segment's start with this one's end.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
                mFirstClick = getCursorPositionInView();
            } else {
                mWasFirstClick = false;
            }
        } else { // no, first click only
            mWasFirstClick = true;
            mFirstClick = getCursorPositionInView();
        }
    }
}
