/*
 * infosv
 * 2013
 * Marco Antognini
 */

#ifndef INFOSV_APPLICATION_HPP
#define INFOSV_APPLICATION_HPP

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
// A DECOMMENTER LORSQUE CONFIGMANAGER SERA CODEE
#include "ConfigManager/ConfigManager.hpp"
#include "Environment/Environment.hpp"
#include "Utility/Vec2d.hpp"
#include "Stats/Stats.hpp"


/*!
 * @class Application
 *
 * @brief Abstract class managing the core of the program
 *
 * Subclass can optionally re-implement onInit(), onEvent(), onUpdate() and onDraw().
 *
 * The Environment class handles the drawing and update of the system.
 */
class Application
{
public:
    /*!
     * @brief Constructor
     */
    Application();

    /// Forbid copy
    Application(Application const&) = delete;
    Application& operator=(Application const&) = delete;

    /*!
     * @brief Destructor
     */
    virtual ~Application();

    /*!
     * @brief Init the application
     *
     * This method should be called once (and only once) before run().
     *
     * @param argc argument count
     * @param argv launch arguments
     *
     * @see onInit()
     */
    void init(int argc, char** argv);

    /*!
     * @brief Run the application
     *
     * This function is the main loop.
     *
     * @note Don't forget to call init() before run() !
     */
    void run();

    /*!
     * @brief Get access to the environment
     *
     * @note This breaks the encapsulation but simplify everything!
     *
     * @return the app's environment
     */
    Environment& getEnv();

    /*!
     * @brief Get access to the application's configuration
     *
     * @return the app's config
     */
	// A DECOMMENTER LORSQUE CONFIGMANAGER SERA CODEE
    ConfigManager& getConfig();

    /*!
     * @brief Get the app's font
     *
     * @return a font
     */
    sf::Font const& getFont() const;

    /*!
     * @brief Get a texture
     *
     * The texture is loaded on the fly from the 'res' folder and is owned
     * by this application.
     *
     * The returned texture is read-write capable but in most case a read-only
     * access should be enough.
     *
     * The application guarantees that the texture is not moved in memory and
     * is not destroyed until the destruction of the application. This ensures
     * that the returned reference will be valid until the end of the application
     * and therefore can be given to a sprite.
     *
     * If the corresponding texture couldn't be loaded a default white texture is
     * returned and an error message is displayed on sf::Err by SFML.
     *
     * @param name name of the texture
     * @return a reference to the corresponding texture
     */
    sf::Texture& getTexture(std::string const& name);

    /*!
     * @brief Get the app's stats displayer
     *
     * @return the app's stats displayer
     */
    Stats& getStats();

    /*!
     * @brief Get the path to the resource folder
     */
    std::string getResPath() const;

protected:
    /*!
     * @brief Subclass can to override this method to initialize its attributes.
     *
     * The default implementation does nothing.
     */
    virtual void onInit(int argc, char** argv);

    /*!
     * @brief Subclass can override this method to handle events
     *
     * The default implementation does nothing.
     *
     * @param event an event
     * @param window the window that emitted the event
     */
    virtual void onEvent(sf::Event event, sf::RenderWindow& window);

    /*!
     * @brief Subclass can override this method to update their data
     *
     * The default implementation does nothing. However, the env is always updated first.
     *
     * @param dt elapsed time
     */
    virtual void onUpdate(sf::Time dt);

    /*!
     * @brief Subclass can override this method to draw their data
     *
     * The default implementation does nothing. However, the env is always displayed first.
     *
     * @param target a render target
     */
    virtual void onDraw(sf::RenderTarget& target);

    /*!
     * @brief Get the cursor position in the view coordinates (i.e. pixel coordinates)
     *
     * @return The cursor position converted in the view coordinates
     */
    Vec2d getCursorPositionInView() const;

private:
    /*!
     * @brief Load config
     */
		// A DECOMMENTER LORSQUE CONFIGMANAGER SERA CODEE
    void loadConfig();

    /*!
     * @brief Create the window
     */
    void create();

    /*!
     * @brief Do the logic for a given event
     *
     * @param event Event to handle
     * @param window the window that emitted the event
     */
    void handleEvent(sf::Event event, sf::RenderWindow& window);

    void zoomView(bool in);

    enum class MoveDirection { Left, Right, Up, Down };
    void moveView(MoveDirection direction);

private:
    sf::RenderWindow mWindow; ///< SFML window / render target
    Environment* mEnv; ///< Simulated environment
		// A DECOMMENTER LORSQUE CONFIGMANAGER SERA CODEE
    ConfigManager* mConfig; ///< Application configuration
    Stats* mStats; ///< Statistics

    sf::View mMainView; ///< View for simulation
    sf::View mAuxView; ///< View for stats

    std::string mAppDirectory; ///< Path to the executable's directory, get from argc/v
    std::string mCfgFile; ///< Path to the CFG
    sf::Font mFont; ///< a font

    using TexturePool = std::map<std::string, sf::Texture*>;
    TexturePool mTextures; ///< Pool of textures
    sf::Texture mDefaultTexture; ///< Default, white texture
    // mDefaultTexture is used when a texture in the pool is not available

    bool mPaused; ///< Tells if the application is in pause or not
};

/*!
 * @brief Get the current instance of Application
 *
 * @return a reference to the current instance of Applicaton
 */
Application& getApp();

/*!
 * @brief Get the environement of the current application
 *
 * Shorthand for getApp().getEnv()
 *
 * @see Application::getEnv() comment about encapsulation
 *
 * @return the app's env.
 */
Environment& getAppEnv();

/*!
 * @brief Get the config of the current application
 *
 * Shorthand for getApp().getConfig()
 *
 * @return the app's config [read only]
 */
	// A DECOMMENTER LORSQUE CONFIGMANAGER SERA CODEE
ConfigManager const& getAppConfig();

/*!
 * @brief Get the app's font
 *
 * Shorthand for getApp().getFont()
 *
 * @return a font
 */
sf::Font const& getAppFont();

/*!
 * @brief Get a texture
 *
 * Shorthand for getApp().getTexture(name)
 *
 * @param name name of the texture
 * @return a reference to the texture
 *
 * @see Application::getTexture
 */
sf::Texture& getAppTexture(std::string const& name);

/*!
 * @brief Get the stats displayer
 *
 * Shorthand for getApp().getStats()
 *
 * @return the app's stats displayer
 */
Stats& getAppStats();

/*!
 * @brief Determine if debug mode is active or not
 *
 * Shorthand for getAppConfig().getConfig().getBool(DEBUG_MODE)
 *
 * @return true if cfg specify DEBUG=TRUE
 */
bool isDebugOn();


/// Define a few macros


/*!
 * @brief Implement the main() function with a given subclass of Application
 *
 * @param APPLICATION_CLASS a class name (it must be a subclass of Application)
 */
#define IMPLEMENT_MAIN(APPLICATION_CLASS) \
int main(int argc, char** argv) { \
    APPLICATION_CLASS app; \
    app.init(argc, argv); \
    app.run(); \
    return 0; \
}

#define INIT_DEFAULT_APP(argc, argv) \
    Application app; \
    app.init((argc), (argv));


#endif // INFOSV_APPLICATION_HPP

