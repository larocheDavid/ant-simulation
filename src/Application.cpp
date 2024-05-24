/*
 * infosv
 * 2013
 * Marco Antognini
 */

#include "Application.hpp"
#include "Constants.hpp"

#include <iostream>
#include <cassert>

namespace {
    Application* currentApp = nullptr; ///< Current application
}

Application::Application()
    : mEnv(nullptr)
	  // A DECOMMENTER LORSQUE CONFIGMANAGER SERA CODEE
	  , mConfig(nullptr)
    , mStats(nullptr)
	  // A DECOMMENTER LORSQUE CONFIGMANAGER SERA CODEE
	  , mCfgFile(RES_LOCATION + DEFAULT_CFG)
    , mPaused(false)
{
    assert(currentApp == nullptr);
    currentApp = this;

    // Most of the work is done in init() or create()
}

Application::~Application()
{
    delete mEnv;
    mEnv = nullptr;

    delete mStats;
    mStats = nullptr;

    // Release textures
    for (auto& kv : mTextures) {
        delete kv.second;
        kv.second = nullptr;
    }
    mTextures.clear();

	// A DECOMMENTER LORSQUE CONFIGMANAGER SERA CODEE
	
    delete mConfig;
    mConfig = nullptr;
	

    currentApp = nullptr;
}

void Application::init(int argc, char** argv)
{
    assert(argc >= 1);

    // Get the launch command (e.g. ./build/application)
    mAppDirectory = argv[0];
    // and keep only the directory (i.e. until the last '/')
    std::string::size_type lastSlashPos = mAppDirectory.rfind('/');
    if (lastSlashPos == std::string::npos) {
        mAppDirectory = "./";
    } else {
        mAppDirectory = mAppDirectory.substr(0, lastSlashPos + 1);
    }

    // If available, get the cfg file name
    if (argc >= 2) {
        mCfgFile = RES_LOCATION + argv[1];
    } // else : we keep the default cfg file

	// A DECOMMENTER LORSQUE CONFIGMANAGER SERA CODEE
    loadConfig();

    mStats = new Stats();

    mEnv = new Environment();

    // Load the font
    if (!mFont.loadFromFile(mAppDirectory + FONT_LOCATION)) {
        std::cerr << "Couldn't load " << getAppConfig().getString("FONT_LOCATION") << std::endl;
    }

    // Notify subclass(es)
    onInit(argc, argv);
}

void Application::run()
{
    // Create the window
    create();

    // Init borders
    Vec2d const worldSize = {
        getConfig().getInt("WORLD_WIDTH"),
        getConfig().getInt("WORLD_HEIGHT")
    };
    sf::RectangleShape limits(worldSize);
    limits.setPosition(0, 0);
    limits.setOutlineColor(sf::Color::Black);
    limits.setOutlineThickness(5);
    if (getConfig().getBool("WATER_MODE")) {
		limits.setTexture(&getAppTexture(getConfig().getString("SIMULATION_BACKGROUND_SEA")));
	} else {
		limits.setTexture(&getAppTexture(getConfig().getString("SIMULATION_BACKGROUND_SAND")));
	}
    // Use a clock to track time
    sf::Clock clk;

	 // Use this clock only to measure the drawing performance
    sf::Clock fpsClk;
    int fpsCounter = 0;

    // Main loop
    while (mWindow.isOpen()) {
        // Handle events
        sf::Event event;
        while (mWindow.pollEvent(event)) {
            handleEvent(event, mWindow);
        }

        // Update logics

		const sf::Time dtReal = sf::seconds(clk.getElapsedTime().asSeconds() * getConfig().getDouble("TIME_FACTOR"));
        // We need allow a 5% error margin to avoid aliasing between our pacing and the vsync signal
        if (dtReal.asSeconds() < (1.0 / FPS * 0.95)) {
            // Do not update, to limit the number of frames per second
        } else {
            // Pretend that only 1.0 / FPS seconds have passed from the last update.
            // For fast machines, this is correct (with a very small error).
            // For slow machines, this will slow down the simulation from the user's point of view.
            const sf::Time dtLogical(sf::seconds(1.0 /  FPS));
            clk.restart();
            if (!mPaused) {
                getEnv().update(dtLogical);
                onUpdate(dtLogical);
            }
            // Compute and show fps
            fpsCounter++;
            if (fpsClk.getElapsedTime().asSeconds() > 5.0) {
                if (PRINT_FPS) {
                    std::cerr << "Frames per second: "
                              << (fpsCounter / fpsClk.getElapsedTime().asSeconds())
                              << std::endl;
                }
                fpsClk.restart();
                fpsCounter = 0;
            }
        }
       

        // Clear the screen
        mWindow.clear(sf::Color::White);

        // Set the main view
        mWindow.setView(mMainView);

        // Draw borders
        mWindow.draw(limits);

        // Draw stuff
        getEnv().draw(mWindow);
        onDraw(mWindow);

        // Set the aux view and draw stats
        mWindow.setView(mAuxView);
        getStats().draw(mWindow);

        // Display everything on the window
        mWindow.display();
    }
}

Environment& Application::getEnv()
{
    return *mEnv;
}

 //A DECOMMENTER LORSQUE LA CLASSE CONFIGMANAGER SERA CODEE 
ConfigManager& Application::getConfig()
{
    if (mConfig == nullptr) mConfig = new ConfigManager();
    return *mConfig;
}

sf::Font const& Application::getFont() const
{
    return mFont;
}

sf::Texture& Application::getTexture(std::string const& name)
{
    auto const it = mTextures.find(name);
    if (it != mTextures.end()) return *it->second;
    else {
        // The texture is not yet in memory so we load it now
        sf::Texture* newTexture = new sf::Texture;
        if (newTexture->loadFromFile(getResPath() + name)) {
            // The texture was correctly loaded so we save it
            mTextures[name] = newTexture;
            // And return the texture
            return *newTexture;
        } else {
            // The file was not loaded correctly so we clean up the mess
            delete newTexture;
            newTexture = nullptr;
            // And return the default texture
            return mDefaultTexture;
        }
    }
}

Stats& Application::getStats()
{
    return *mStats;
}

std::string Application::getResPath() const
{
    return mAppDirectory + RES_LOCATION;
}

void Application::onInit(int, char**)
{
    // By default nothing is done here
}

void Application::onEvent(sf::Event, sf::RenderWindow&)
{
    // By default nothing is done here
}

void Application::onUpdate(sf::Time)
{
    // By default nothing is done here
}

void Application::onDraw(sf::RenderTarget&)
{
    // By default nothing is done here
}

Vec2d Application::getCursorPositionInView() const
{
    return mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow), mMainView);
}

// A DECOMMENTER LORSQUE LA CLASSE CONFIGMANAGER SERA CODEE
void Application::loadConfig()
{
    getConfig().load(mAppDirectory + mCfgFile, true);
}

void Application::create()
{
    // Create the window
    sf::VideoMode vm(getAppConfig().getInt("APP_WIDTH"), getAppConfig().getInt("APP_HEIGHT"));
    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 8; // This might not work very fast on the VMs...
    mWindow.create(vm, APP_TITLE, sf::Style::Close, contextSettings);

    mWindow.setKeyRepeatEnabled(true);

    // Construct two views :
    //  - the main one for the simulation
    //  - a secondary one for statistics

    double const WIDTH = getAppConfig().getInt("APP_WIDTH");
    double const HEIGHT = getAppConfig().getInt("APP_HEIGHT");
    double const MAIN_VIEW_WIDTH = WIDTH - getAppConfig().getInt("APP_STATS_VIEW_WIDTH");
    double const MAIN_VIEW_HEIGHT = HEIGHT;
    double const MAIN_VIEW_OFFSET_X = WIDTH - MAIN_VIEW_WIDTH;
    double const MAIN_VIEW_OFFSET_Y = HEIGHT - MAIN_VIEW_HEIGHT;

    double const AUX_VIEW_WIDTH = WIDTH - MAIN_VIEW_WIDTH;
    double const AUX_VIEW_HEIGHT = HEIGHT;
    double const AUX_VIEW_OFFSET_X = 0;
    double const AUX_VIEW_OFFSET_Y = HEIGHT - AUX_VIEW_HEIGHT;

    double const MAIN_VIEW_DISPLAY_WIDTH = WORLD_WIDTH;
    double const MAIN_VIEW_DISPLAY_HEIGHT = WORLD_HEIGHT;

    mMainView.reset({ 0, 0, MAIN_VIEW_DISPLAY_WIDTH, MAIN_VIEW_DISPLAY_HEIGHT });
    mMainView.zoom(1.02); // initially, we want to see the whole world + a small margin
    mMainView.setViewport({
        MAIN_VIEW_OFFSET_X / WIDTH, MAIN_VIEW_OFFSET_Y / HEIGHT,
        MAIN_VIEW_WIDTH / WIDTH, MAIN_VIEW_HEIGHT / HEIGHT
    });

    mAuxView.reset({ 0, 0, AUX_VIEW_WIDTH, AUX_VIEW_HEIGHT });
    mAuxView.setViewport({
        AUX_VIEW_OFFSET_X / WIDTH, AUX_VIEW_OFFSET_Y / HEIGHT,
        AUX_VIEW_WIDTH / WIDTH, AUX_VIEW_HEIGHT / HEIGHT
    });
}

void Application::handleEvent(sf::Event event, sf::RenderWindow& window)
{
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;

                case sf::Keyboard::L:
					// A DECOMMENTER LORSQUE CONFIGMANAGER SERA CODEE
                    loadConfig();
                    break;

                case sf::Keyboard::Z:
                    zoomView(!event.key.shift); // if shift is pressed we zoom out
                    break;

                case sf::Keyboard::Left:
                    moveView(MoveDirection::Left);
                    break;

                case sf::Keyboard::Right:
                    moveView(MoveDirection::Right);
                    break;

                case sf::Keyboard::Up:
                    moveView(MoveDirection::Up);
                    break;

                case sf::Keyboard::Down:
                    moveView(MoveDirection::Down);
                    break;

                case sf::Keyboard::Space:
                    mPaused = ! mPaused; // toggle pause
                    break;

                default:
                    onEvent(event, window);
                    break;
            }
            break;

        default:
            onEvent(event, window);
            break;
    }
}

void Application::zoomView(bool in)
{
    double const factor = in ? 1.0/1.5 : 1.5;

    mMainView.zoom(factor);

    mWindow.setView(mMainView);
}

void Application::moveView(MoveDirection direction)
{
    Vec2d vect;
    switch (direction) {
        case MoveDirection::Left:
            vect = { -1, 0 };
            break;

        case MoveDirection::Right:
            vect = { 1, 0 };
            break;

        case MoveDirection::Up:
            vect = { 0, -1 };
            break;

        case MoveDirection::Down:
            vect = { 0, 1 };
            break;
    }

    float const factor = 100;
    mMainView.move(vect * factor);

    // Force the view within the limits of the world
    int const width = getAppConfig().getInt("WORLD_WIDTH");
    int const height = getAppConfig().getInt("WORLD_HEIGHT");

    Vec2d center = mMainView.getCenter();
    if (center.x < 0) center.x = 0;
    if (center.x > width) center.x = width;
    if (center.y < 0) center.y = 0;
    if (center.y > height) center.y = height;
    mMainView.setCenter(center);

    mWindow.setView(mMainView);
}

Application& getApp()
{
    assert(currentApp != nullptr);

    return *currentApp;
}

Environment& getAppEnv()
{
    return getApp().getEnv();
}
// A DECOMMENTER LORSQUE LA CLASSE CONFIGMANAGER SERA CODEE 
ConfigManager const& getAppConfig()
{
    return getApp().getConfig();
}

sf::Font const& getAppFont()
{
    return getApp().getFont();
}

sf::Texture& getAppTexture(std::string const& name)
{
    return getApp().getTexture(name);
}

Stats& getAppStats()
{
    return getApp().getStats();
}

bool isDebugOn()
{
    return getAppConfig().getBool("DEBUG_MODE");
}

