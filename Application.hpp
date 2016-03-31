#ifndef BASEDEFENSE_APPLICATION_HPP
#define BASEDEFENSE_APPLICATION_HPP

#include <zeno/Window/Window.hpp>

#include <zeno/Graphics/Font.hpp>
#include <zeno/System/Mat4x4.hpp>

class Application
{
public:
    static Application& getInstance(void)
    {
        static Application app;

        return app;
    }

    void initialise(void);

    void run(int _argc, char **_argv);

    zeno::Vector2i getTileCoordinates(const zeno::Vector2f& _pixelCoordinates);

public:
    zeno::Font  font;

    zeno::Window m_Window;

    static constexpr float TileSize = 64.0f;

private:
    Application(void);

    ~Application(void);

    bool m_Running;
};

#define sApp Application::getInstance()

#endif //BASEDEFENSE_APPLICATION_HPP
