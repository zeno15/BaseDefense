#ifndef BASEDEFENSE_WAYPOINT_HPP
#define BASEDEFENSE_WAYPOINT_HPP

#include <zeno/System/Vector2.hpp>

struct Waypoint {
    enum WaypointType {
        OnRoute,
        Decision,
        Start,
        End
    };

    Waypoint(const zeno::Vector2f& _position, WaypointType _type) :
    position(_position),
    type(_type)
    {

    }


    zeno::Vector2f position;

    WaypointType type;
};

#endif //BASEDEFENSE_WAYPOINT_HPP
