#ifndef SPACEDEFENDERS_HPP
#define SPACEDEFENDERS_HPP

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "LuaHandler.hpp"

class SpaceDefenders
{
public:
    SpaceDefenders();
    void run();

private:
    void gameLoop();

    void handleEvent(const sf::Event& e);
    void update(float dt);
    void draw();

    void reloadLua();

    sf::RenderWindow m_window;
    sf::Clock m_fpsDelay;

    std::unique_ptr<LuaHandler> m_luaHandler;
    std::unique_ptr<sf::Font> m_fontDejavu;
    std::unique_ptr<sf::SoundBuffer> m_soundBufExplode;
    std::unique_ptr<sf::SoundBuffer> m_soundBufShoot;
};

#endif //SPACEDEFENDERS_HPP
