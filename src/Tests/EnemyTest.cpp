/*
 * infosv
 * 2013
 * Marco Antognini
 */

#include "../Utility/Diagnostic.hpp"
#include "../Utility/Utility.hpp"
#include "../Application.hpp"
#include "../Animal/AntWorker.hpp"
#include "../Animal/AntSoldier.hpp"
#include "../Animal/Termite.hpp"

int main(int argc, char** argv)
{
    INIT_DEFAULT_APP(argc, argv);

    // Create a few entities
    Uid colony1 = createUid();
    Uid colony2 = createUid();

    Animal* termite1a = new Termite({0, 0});
    Animal* termite1b = new Termite({0, 0});

    Animal* antSoldier1a = new AntSoldier({0, 0}, colony1);
    Animal* antSoldier1b = new AntSoldier({0, 0}, colony1);
    Animal* antSoldier2a = new AntSoldier({0, 0}, colony2);
    Animal* antSoldier2b = new AntSoldier({0, 0}, colony2);

    Animal* antWorker1a = new AntWorker({0, 0}, colony1);
    Animal* antWorker1b = new AntWorker({0, 0}, colony1);
    Animal* antWorker2a = new AntWorker({0, 0}, colony2);
    Animal* antWorker2b = new AntWorker({0, 0}, colony2);

    // Bunch of tests (symmetrical and enemy)

    // First, all non enemy tests

    // Termites
    eqAssert(termite1a->isEnemy(termite1b), termite1b->isEnemy(termite1a));
    eqAssert(termite1a->isEnemy(termite1b), false);

    // Same colony (#1)
    eqAssert(antSoldier1a->isEnemy(antSoldier1b), antSoldier1b->isEnemy(antSoldier1a));
    eqAssert(antSoldier1a->isEnemy(antSoldier1b), false);
    eqAssert(antWorker1a->isEnemy(antWorker1b), antWorker1b->isEnemy(antWorker1a));
    eqAssert(antWorker1a->isEnemy(antWorker1b), false);
    eqAssert(antWorker1a->isEnemy(antSoldier1a), antSoldier1a->isEnemy(antWorker1a));
    eqAssert(antWorker1a->isEnemy(antSoldier1a), false);
    eqAssert(antWorker1b->isEnemy(antSoldier1b), antSoldier1b->isEnemy(antWorker1b));
    eqAssert(antWorker1b->isEnemy(antSoldier1b), false);
    eqAssert(antWorker1a->isEnemy(antSoldier1b), antSoldier1b->isEnemy(antWorker1a));
    eqAssert(antWorker1a->isEnemy(antSoldier1b), false);
    eqAssert(antWorker1b->isEnemy(antSoldier1a), antSoldier1a->isEnemy(antWorker1b));
    eqAssert(antWorker1b->isEnemy(antSoldier1a), false);

    // Same colony (#2)
    eqAssert(antSoldier2a->isEnemy(antSoldier2b), antSoldier2b->isEnemy(antSoldier2a));
    eqAssert(antSoldier2a->isEnemy(antSoldier2b), false);
    eqAssert(antWorker2a->isEnemy(antWorker2b), antWorker2b->isEnemy(antWorker2a));
    eqAssert(antWorker2a->isEnemy(antWorker2b), false);
    eqAssert(antWorker2a->isEnemy(antSoldier2a), antSoldier2a->isEnemy(antWorker2a));
    eqAssert(antWorker2a->isEnemy(antSoldier2a), false);
    eqAssert(antWorker2b->isEnemy(antSoldier2b), antSoldier2b->isEnemy(antWorker2b));
    eqAssert(antWorker2b->isEnemy(antSoldier2b), false);
    eqAssert(antWorker2a->isEnemy(antSoldier2b), antSoldier2b->isEnemy(antWorker2a));
    eqAssert(antWorker2a->isEnemy(antSoldier2b), false);
    eqAssert(antWorker2b->isEnemy(antSoldier2a), antSoldier2a->isEnemy(antWorker2b));
    eqAssert(antWorker2b->isEnemy(antSoldier2a), false);

    // Self
    eqAssert(termite1a->isEnemy(termite1a), false);
    eqAssert(termite1b->isEnemy(termite1b), false);
    eqAssert(antSoldier1a->isEnemy(antSoldier1a), false);
    eqAssert(antSoldier1b->isEnemy(antSoldier1b), false);
    eqAssert(antWorker1a->isEnemy(antWorker1a), false);
    eqAssert(antWorker1b->isEnemy(antWorker1b), false);
    eqAssert(antSoldier2a->isEnemy(antSoldier2a), false);
    eqAssert(antSoldier2b->isEnemy(antSoldier2b), false);
    eqAssert(antWorker2a->isEnemy(antWorker2a), false);
    eqAssert(antWorker2b->isEnemy(antWorker2b), false);


    // Second, all enemy tests

    // Termite VS Ants (a)
    eqAssert(termite1a->isEnemy(antSoldier1a), antSoldier1a->isEnemy(termite1a));
    eqAssert(termite1a->isEnemy(antSoldier1a), true);
    eqAssert(termite1a->isEnemy(antSoldier1b), antSoldier1b->isEnemy(termite1a));
    eqAssert(termite1a->isEnemy(antSoldier1b), true);
    eqAssert(termite1a->isEnemy(antWorker1a), antWorker1a->isEnemy(termite1a));
    eqAssert(termite1a->isEnemy(antWorker1a), true);
    eqAssert(termite1a->isEnemy(antWorker1b), antWorker1b->isEnemy(termite1a));
    eqAssert(termite1a->isEnemy(antWorker1b), true);

    // Termite VS Ants (b)
    eqAssert(termite1b->isEnemy(antSoldier1a), antSoldier1a->isEnemy(termite1b));
    eqAssert(termite1b->isEnemy(antSoldier1a), true);
    eqAssert(termite1b->isEnemy(antSoldier1b), antSoldier1b->isEnemy(termite1b));
    eqAssert(termite1b->isEnemy(antSoldier1b), true);
    eqAssert(termite1b->isEnemy(antWorker1a), antWorker1a->isEnemy(termite1b));
    eqAssert(termite1b->isEnemy(antWorker1a), true);
    eqAssert(termite1b->isEnemy(antWorker1b), antWorker1b->isEnemy(termite1b));
    eqAssert(termite1b->isEnemy(antWorker1b), true);

    // Colony #1 VS Colony #2
    eqAssert(antSoldier1a->isEnemy(antSoldier2a), antSoldier2a->isEnemy(antSoldier1a));
    eqAssert(antSoldier1a->isEnemy(antSoldier2b), antSoldier2b->isEnemy(antSoldier1a));
    eqAssert(antSoldier1a->isEnemy(antWorker2a),  antWorker2a->isEnemy(antSoldier1a));
    eqAssert(antSoldier1a->isEnemy(antWorker2b),  antWorker2b->isEnemy(antSoldier1a));
    eqAssert(antSoldier1a->isEnemy(antSoldier2a), true);
    eqAssert(antSoldier1a->isEnemy(antSoldier2b), true);
    eqAssert(antSoldier1a->isEnemy(antWorker2a),  true);
    eqAssert(antSoldier1a->isEnemy(antWorker2b),  true);

    eqAssert(antSoldier1b->isEnemy(antSoldier2a), antSoldier2a->isEnemy(antSoldier1b));
    eqAssert(antSoldier1b->isEnemy(antSoldier2b), antSoldier2b->isEnemy(antSoldier1b));
    eqAssert(antSoldier1b->isEnemy(antWorker2a),  antWorker2a->isEnemy(antSoldier1b));
    eqAssert(antSoldier1b->isEnemy(antWorker2b),  antWorker2b->isEnemy(antSoldier1b));
    eqAssert(antSoldier1b->isEnemy(antSoldier2a), true);
    eqAssert(antSoldier1b->isEnemy(antSoldier2b), true);
    eqAssert(antSoldier1b->isEnemy(antWorker2a),  true);
    eqAssert(antSoldier1b->isEnemy(antWorker2b),  true);

    eqAssert(antWorker1a->isEnemy(antSoldier2a), antSoldier2a->isEnemy(antWorker1a));
    eqAssert(antWorker1a->isEnemy(antSoldier2b), antSoldier2b->isEnemy(antWorker1a));
    eqAssert(antWorker1a->isEnemy(antWorker2a),  antWorker2a->isEnemy(antWorker1a));
    eqAssert(antWorker1a->isEnemy(antWorker2b),  antWorker2b->isEnemy(antWorker1a));
    eqAssert(antWorker1a->isEnemy(antSoldier2a), true);
    eqAssert(antWorker1a->isEnemy(antSoldier2b), true);
    eqAssert(antWorker1a->isEnemy(antWorker2a),  true);
    eqAssert(antWorker1a->isEnemy(antWorker2b),  true);

    eqAssert(antWorker1b->isEnemy(antSoldier2a), antSoldier2a->isEnemy(antWorker1b));
    eqAssert(antWorker1b->isEnemy(antSoldier2b), antSoldier2b->isEnemy(antWorker1b));
    eqAssert(antWorker1b->isEnemy(antWorker2a),  antWorker2a->isEnemy(antWorker1b));
    eqAssert(antWorker1b->isEnemy(antWorker2b),  antWorker2b->isEnemy(antWorker1b));
    eqAssert(antWorker1b->isEnemy(antSoldier2a), true);
    eqAssert(antWorker1b->isEnemy(antSoldier2b), true);
    eqAssert(antWorker1b->isEnemy(antWorker2a),  true);
    eqAssert(antWorker1b->isEnemy(antWorker2b),  true);


    // Clean up (reverse order, as usual)
    delete antWorker2b;
    delete antWorker2a;
    delete antWorker1b;
    delete antWorker1a;

    delete antSoldier2b;
    delete antSoldier2a;
    delete antSoldier1b;
    delete antSoldier1a;

    delete termite1b;
    delete termite1a;

    diagnostic();

    return gErrors;
}

