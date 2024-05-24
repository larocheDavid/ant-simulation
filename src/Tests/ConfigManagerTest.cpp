/*
 * infosv
 * 2013
 * Marco Antognini
 */

#include "../ConfigManager/ConfigManager.hpp"
#include "../Utility/Diagnostic.hpp"

// Ce test vérifie uniquement les conversion valides (étant donné que les exceptions
// ne sont pas gérées par les étudiants) mais il teste aussi des lignes invalides
// (e.g. identifiant ou type au mauvais format).

int main(int, char** argv)
{
    // Récupère le dossier contenant le binaire
    std::string appDir = argv[0];
    std::string::size_type lastSlashPos = appDir.rfind('/');
    if (lastSlashPos == std::string::npos) {
        appDir = "./";
    } else {
        appDir = appDir.substr(0, lastSlashPos + 1);
    }

    exec(ConfigManager cm, "Création d'un manager");

    exec(std::string const doesnexist("doesnexist.cfg"), "Fichier inexistant");
    eqAssert(cm.load(doesnexist), false);

    exec(std::string const invalid(appDir + "../res/tests/invalid.cfg"), "Fichier invalid");
    eqAssert(cm.load(invalid), false);

    exec(std::string const valid(appDir + "../res/tests/var.cfg"), "Fichier valid");
    eqAssert(cm.load(valid), true);

    // Test entiers
    eqAssert(cm.getInt("x"), -23);
    eqAssert(cm.getInt("y"), 10);

    // Test réels
    eqAssert(cm.getDouble("a"), 3.1415);
    eqAssert(cm.getDouble("b"), -56.2);

    // Test strings
    eqAssert(cm.getString("title"), "Hello, World!");
    eqAssert(cm.getString("year"), "2013");

    // Test booleans
    for (int i = 1; i <= 5; ++i) {
        exec(std::string key = "t" + std::to_string(i), "Clef correspondant à true");
        std::cout << "key = " << key << std::endl;
        eqAssert(cm.getBool(key), true);
    }

    for (int i = 1; i <= 4; ++i) {
        exec(std::string key = "f" + std::to_string(i), "Clef correspondant à false");
        std::cout << "key = " << key << std::endl;
        eqAssert(cm.getBool(key), false);
    }


    diagnostic();

    return 0;
}

