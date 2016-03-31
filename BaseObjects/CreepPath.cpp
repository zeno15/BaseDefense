#include <BaseObjects/CreepPath.hpp>

#include <iostream>
#include <Application.hpp>
#include <Managers/TextureManager.hpp>

CreepPath::~CreepPath(void) {
    for (Sprite *sprite : m_WaypointSprites) {
        delete sprite;
    }
}

void CreepPath::initialiseFromPathWaypoints(const std::vector<zeno::Vector2u>& _points)
{
    if (_points.size() < 2) {
        throw std::runtime_error("Too few points for CreepPath");
    }

    addWaypoint(Waypoint(zeno::Vector2f(Application::TileSize / 2.0f + Application::TileSize * _points.front().x, Application::TileSize / 2.0f + Application::TileSize * _points.front().y), Waypoint::WaypointType::Start));

    m_WaypointSprites.push_back(new Sprite(sTextureManager.getTexture(TextureManager::Texture::Waypoint)));
    m_WaypointSprites.back()->setPosition(m_Waypoints.back().position);
    m_WaypointSprites.back()->setColour(zeno::Colour::Green);

    for (unsigned int i = 1; i < _points.size() - 1; i += 1) {
        addWaypoint(Waypoint(zeno::Vector2f(Application::TileSize / 2.0f + Application::TileSize * _points.at(i).x, Application::TileSize / 2.0f + Application::TileSize * _points.at(i).y), Waypoint::WaypointType::OnRoute));
        m_WaypointSprites.push_back(new Sprite(sTextureManager.getTexture(TextureManager::Texture::Waypoint)));
        m_WaypointSprites.back()->setPosition(m_Waypoints.back().position);
    }

    addWaypoint(Waypoint(zeno::Vector2f(Application::TileSize / 2.0f + Application::TileSize * _points.back().x, Application::TileSize / 2.0f + Application::TileSize * _points.back().y), Waypoint::WaypointType::End));
    m_WaypointSprites.push_back(new Sprite(sTextureManager.getTexture(TextureManager::Texture::Waypoint)));
    m_WaypointSprites.back()->setPosition(m_Waypoints.back().position);
    m_WaypointSprites.back()->setColour(zeno::Colour::Red);
}

void CreepPath::addWaypoint(Waypoint _waypoint)
{
    if (!m_Finalised) {
        m_Waypoints.push_back(_waypoint);
    }
}

void CreepPath::finalisePath(void)
{
    m_Finalised = true;
}


const Waypoint& CreepPath::getWaypointAtIndex(unsigned int _index)
{
    return m_Waypoints.at(_index);
}

void CreepPath::render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection)
{
    for(Sprite* sprite : m_WaypointSprites) {
        sprite->render(_view, _projection);
    }
}