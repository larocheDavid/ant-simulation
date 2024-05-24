#ifndef INFOSV_CONSTANTS_HPP
#define INFOSV_CONSTANTS_HPP

#include <string>

// Define the location of the config file
std::string const DEFAULT_CFG = "app.cfg";

const std::string APP_TITLE = "INFOSV Simulation";
const int APP_WIDTH = 1200;
const int APP_HEIGHT = 1000;
const int APP_STATS_VIEW_WIDTH = 200;

// Define resources location
std::string const RES_LOCATION = "../res/";

// Define the location of the font file (could be in the config instead of here)
std::string const FONT_LOCATION = RES_LOCATION + "sansation.ttf";

const int ANT_COST = 90;
const int ANTHILL_SPARE = 5000;

//modifs poison
const std::string POISON_TEXTURE = "poison.png";
const std::string ANT_WORKER_TEXTURE3 = "green_ant2.png";
const double ANTHILL_SPEED = 1.0;
const int POISON_RADIUS = 50;

//MODE WATER
//const std::string SIMULATION_BACKGROUND = "sea.png";
const bool WATER_MODE = false;
const int ANIMAL_SIZE = 22;
const int ANT_WORKER_SIZE2 = 40;
const int ANT_SOLDIER_SIZE2 = 40;
const int TERMITE_SIZE2 = 40;
const int BOB_SIZE = 200;
const std::string ANT_WORKER_TEXTURE2 = "gary.png";
const std::string ANT_SOLDIER_TEXTURE2 = "patrick.png";
const std::string TERMITE_TEXTURE2 = "crab.png";
const std::string ANTHILL_TEXTURE2 = "house.png";
const std::string FOOD_TEXTURE2 = "burger.png";

//Bob specs
const int BOB_HP = 100;
const int BOB_STRENGTH = 12;
const int BOB_LIFESPAN = 6000;
const double BOB_SPEED = 400.0;
const double BOB_ATTACK_DURATION = 0.4;
const std::string BOB_TEXTURE = "green_ant2.png";
const std::string BOB_TEXTURE2 = "bob.png";

const bool DEBUG_MODE = false;
const bool DEBUG_MODE2 = true;
const double TIME_FACTOR = 1.0;
const double FPS = 60.0;
const bool PRINT_FPS = false;
const int WORLD_WIDTH = 1000;
const int WORLD_HEIGHT = 1000;

const std::string SIMULATION_BACKGROUND = "sand.png";

const double ANIMAL_NEXT_ROTATION_DELAY = 0.05;
const double ANIMAL_SIGHT_DISTANCE = 20;

const double BETA_D = 1.0;
const double Q_ZERO = 5.0;
const int ALPHA = 5;

const double ANT_SPEED = 100.0;
const double ANT_ATTACK_DURATION = 0.2;
const double ANT_SMELL_MAX_DISTANCE = 20.0;
const double TEST_PHEROMONE_DENSITY = 1;
const double ANT_PHEROMONE_DENSITY = 0.1;
const double ANT_PHEROMONE_ENERGY = 5;
const double ANT_MAX_FOOD = 10;
const double ANT_MAX_PERCEPTION_DISTANCE = 30.0;

const int ANT_WORKER_HP = 1;
const int ANT_WORKER_LIFESPAN = 900;
const int ANT_WORKER_STRENGTH = 1;
const std::string ANT_WORKER_TEXTURE = "black_ant2.png";

const int ANT_SOLDIER_HP = 100;
const int ANT_SOLDIER_STRENGTH = 4;
const int ANT_SOLDIER_LIFESPAN = 900;
const std::string ANT_SOLDIER_TEXTURE = "red_ant2.png";

const int TERMITE_HP = 70;
const int TERMITE_LIFESPAN = 900;
const double TERMITE_SPEED = 120.0;
const double TERMITE_ATTACK_DURATION = 0.3;
const int TERMITE_STRENGTH = 3;
const std::string TERMITE_TEXTURE = "termite2.png";

const double PHEROMONE_THRESHOLD = 0.01;
const double PHEROMONE_EVAPORATION_RATE = 0.9;

const double ANTHILL_SPAWN_DELAY = 10.0;
const double ANTHILL_WORKER_PROB_DEFAULT = 0.7;
const std::string ANTHILL_TEXTURE = "anthill.png";

const double FOOD_GENERATOR_DELTA = 2.0;
const double NEW_FOOD_QUANTITY_MIN = 2.0;
const double NEW_FOOD_QUANTITY_MAX = 50.0;

const std::string FOOD_TEXTURE = "food.png";

const std::string MAP_NAME = "map1.map";

#endif // INFOSV_CONFIG_HPP
