#include <Application.hpp>

#include <zeno/Graphics/ShaderManager.hpp>
#include <zeno/System/Clock.hpp>

#include <GL/glew.h>

#include <iostream>

#include <BaseObjects/Creep.hpp>
#include <BaseObjects/CreepPath.hpp>

#include <MiscellaneousRenderables/HealthBar.hpp>

#include <Managers/EntityManager.hpp>
#include <Managers/CreepWaveManager.hpp>

#include <CreepWaves/BasicCreepWave.hpp>
#include <Managers/TowerManager.hpp>

#include <Towers/BasicTower.hpp>
#include <Managers/ProjectileManager.hpp>
#include <Managers/NotificationManager.hpp>
#include <Forces/PlayerForce.hpp>

Application::Application(void) :
        m_Running(false)
{
}

Application::~Application(void)
{
}

void Application::initialise(void)
{
    font.loadFromFile("Resources/Fonts/arial.ttf", 32);

    zeno::ShaderManager::getInstance().addShader("Sprite", "Resources/Shaders/Sprite.Vertex.glsl", "Resources/Shaders/Sprite.Fragment.glsl");
    zeno::ShaderManager::getInstance().getShader("Sprite").getLocationOfUniform("view");
    zeno::ShaderManager::getInstance().getShader("Sprite").getLocationOfUniform("model");
    zeno::ShaderManager::getInstance().getShader("Sprite").getLocationOfUniform("projection");
    zeno::ShaderManager::getInstance().getShader("Sprite").getLocationOfUniform("colour");

    zeno::ShaderManager::getInstance().addShader("HealthBar", "Resources/Shaders/HealthBar.Vertex.glsl", "Resources/Shaders/HealthBar.Fragment.glsl");
    zeno::ShaderManager::getInstance().getShader("HealthBar").getLocationOfUniform("view");
    zeno::ShaderManager::getInstance().getShader("HealthBar").getLocationOfUniform("model");
    zeno::ShaderManager::getInstance().getShader("HealthBar").getLocationOfUniform("projection");
    zeno::ShaderManager::getInstance().getShader("HealthBar").getLocationOfUniform("barColour");

    sTextureManager.loadTextures();

    sNotification.registerCreepDiedCallback([](const Creep& _creep) {
        std::cout << "Creep died at " << _creep.getPosition() << std::endl;
        return false;
    });
}

void Application::run(int _argc, char **_argv) {
    m_Window.create(zeno::VideoMode(1280, 720), "Tower Defense", zeno::WindowStyle::Titlebar | zeno::WindowStyle::Close);

    glClearColor(100.0f / 255.0f, 149.0f / 255.0f, 247.0f / 255.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_Running = true;

    initialise();

    PlayerForce player = PlayerForce(10);

    sNotification.registerCreepReachedEndCallback([&](const Creep& _creep, const CreepPath& _creepPath) {
        player.removeHealth(1);
        if (player.isAlive()) {
            std::cout << "Player health: " << player.getHealth() << std::endl;
        }
        else {
            std::cout << "Player died :/" << std::endl;
        }

        return false;
    });

    std::vector<zeno::Vector2u> pathWaypoints = {
            zeno::Vector2u(0,0),
            zeno::Vector2u(4,0),
            zeno::Vector2u(4,4),
            zeno::Vector2u(8,4),
            zeno::Vector2u(12,8),
            zeno::Vector2u(16,8),
    };

    CreepPath& creepPath = sCreepPath;

    creepPath.initialiseFromPathWaypoints(pathWaypoints);

    creepPath.finalisePath();


    float frameTime;
    float timer = 0.0f;
    float accumulator = 0.0f;

    float rate = 1.0f / 60.0f;

    unsigned int updates = 0;
    unsigned int renders = 0;

    float fraction = 1.0f;

    zeno::Clock clock;

    while (m_Running)
    {
        frameTime = clock.restart().asSeconds();

        if (frameTime > 0.25f)
        {
            frameTime = 0.25f;
            std::cout << "Frame time > 0.25s, spiral of deaaaaaaaaath!" << std::endl;
        }

        accumulator += frameTime;
        timer += frameTime;

        if (timer >= 1.0f)
        {
            timer -= 1.0f;
            //std::cout << "Updates: " << updates << ", Renders: " << renders << std::endl;
            updates = 0;
            renders = 0;
        }

        while (accumulator >= rate) {
            updates += 1;

            zeno::Event event;
            while (m_Window.pollEvent(event)) {
                if (event.type == zeno::Event::EventType::WindowClosed) {
                    m_Running = false;
                }
                if (event.type == zeno::Event::EventType::KeyUp) {
                    if (event.key.key == zeno::Keyboard::Key::Space) {
                        sCreepWaveManager.addWave(new BasicCreepWave(creepPath, 0.25f, 10));
                    }
                }
                if (event.type == zeno::Event::EventType::MouseButtonReleased) {
                    if (event.mouseButton.button == zeno::Mouse::Left) {
                        zeno::Vector2i tileCoords = getTileCoordinates(zeno::Vector2f(event.mouseButton.x, m_Window.getSize().y - event.mouseButton.y));

                        player.addTower<BasicTower>(TextureManager::Texture::TowerBasic, tileCoords);
                    }
                }
            }

            sEntityManager.update(rate);
            sTowerManager.update(rate);
            sProjectileManager.update(rate);
            sCreepWaveManager.update(rate);

            accumulator -= rate;
        }

        float alpha = accumulator / rate;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        zeno::Mat4x4 view = zeno::Mat4x4(1.0f);//::createTranslation(zeno::Vector3f(0.0f, 0.0f, 0.0f));
        zeno::Mat4x4 proj = zeno::Mat4x4::Orthographic2D(0.0f, static_cast<float>(m_Window.getSize().x), static_cast<float>(m_Window.getSize().y), 0.0f);

        sEntityManager.render(view, proj);
        sTowerManager.render(view, proj);
        sProjectileManager.render(view, proj);
        sCreepPath.render(view, proj);

        player.render(view, proj);

        m_Window.display();
        renders += 1;
    }

    m_Window.close();
}

zeno::Vector2i Application::getTileCoordinates(const zeno::Vector2f& _pixelCoordinates)
{
    zeno::Vector2i tileCoordinates = zeno::Vector2i(_pixelCoordinates);

    tileCoordinates.x = tileCoordinates.x / static_cast<int>(TileSize);
    tileCoordinates.y = tileCoordinates.y / static_cast<int>(TileSize);

    std::cout << "Pixel: " << _pixelCoordinates << std::endl;
    std::cout << "Tile: " << tileCoordinates << std::endl;

    return tileCoordinates;
}