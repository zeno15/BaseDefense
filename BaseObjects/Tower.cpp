#include <BaseObjects/Tower.hpp>
#include <Managers/EntityManager.hpp>
#include <zeno/System/VectorMath.hpp>
#include <c++/limits>


Tower::Tower(zeno::Texture& _texture, const zeno::Vector2f& _position, float _range, float _damage) :
sprite(_texture),
m_Range(_range),
m_CurrentTarget(nullptr),
m_Damage(_damage)
{
    sprite.setPosition(_position);
}

void Tower::render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection)
{
    sprite.render(_view, _projection);
}

Creep *Tower::getMostDangerousCreepInRange(void)
{
    std::vector<Creep *> closestCreeps;
    unsigned int latestWaypointIndex = 0;

    for (auto iter = sEntityManager.getEntityStart(); iter != sEntityManager.getEntityEnd(); iter++) {
        Creep *creep = static_cast<Creep *>(*iter);

        if (isInRange(creep) && (creep->getUnreservedHealth() > 0))
        {
            if (creep->getPathIndex() > latestWaypointIndex)
            {
                closestCreeps.clear();
                closestCreeps.push_back(creep);

                latestWaypointIndex = creep->getPathIndex();
            }
            else if (creep->getPathIndex() == latestWaypointIndex) {
                closestCreeps.push_back(creep);
            }
        }
    }

    Creep *mostDangerousCreep = nullptr;

    float minDistanceToWaypoint = std::numeric_limits<float>::max();

    for (Creep *creep : closestCreeps) {
        if (creep->getDistanceToWaypoint() < minDistanceToWaypoint) {
            minDistanceToWaypoint = creep->getDistanceToWaypoint();
            mostDangerousCreep = creep;
        }
    }

    return mostDangerousCreep;
}

bool Tower::isInRange(Creep *_creep) const
{
    return zeno::distance(sprite.getPosition(), _creep->getPosition()) <= m_Range;
}

void Tower::faceCurrentTarget(void)
{
    zeno::Vector2f creepPos = m_CurrentTarget->getPosition();

    auto difference = creepPos - sprite.getPosition();
    zeno::normalise(difference);

    float angle = std::atan2(-difference.y, difference.x);

    angle  = angle * 180.0f / 3.14159265f;

    if (angle < 0.0f) {
        angle += 360.0f;
    }

    sprite.setRotation(angle);
}

zeno::Vector2f Tower::getPosition(void) const
{
    return sprite.getPosition();
}