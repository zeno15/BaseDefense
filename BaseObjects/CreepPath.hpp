#ifndef BASEDEFENSE_CREEPPATH_HPP
#define BASEDEFENSE_CREEPPATH_HPP

#include <BaseObjects/Creep.hpp>
#include <Waypoint.hpp>

#include <vector>

class CreepPath {
public:
    static CreepPath& getInstance(void)
    {
        static CreepPath path = CreepPath();

        return path;
    }

    void initialiseFromPathWaypoints(const std::vector<zeno::Vector2u>& _points);

    void addWaypoint(Waypoint _waypoint);

    void finalisePath(void);

    const Waypoint& getWaypointAtIndex(unsigned int _index);

    void render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection);

protected:
    std::vector<Waypoint> m_Waypoints;

    std::vector<Sprite *> m_WaypointSprites;

    bool m_Finalised;

private:
    CreepPath(void) :
        m_Finalised(false)
    {
    }

    ~CreepPath(void);
};

#define sCreepPath CreepPath::getInstance()

#endif //BASEDEFENSE_CREEPPATH_HPP
