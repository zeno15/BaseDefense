#include <Managers/NotificationManager.hpp>


NotificationManager::NotificationManager(void)
{

}
NotificationManager::~NotificationManager(void)
{

}


void NotificationManager::onCreepDied(const Creep& _creep)
{
    for (auto creepDiedMethod : m_CreepDiedCallbacks) {
        if (creepDiedMethod(_creep)) {
            return;
        }
    }
}
void NotificationManager::registerCreepDiedCallback(std::function<bool(const Creep&)> _creepDiedCallback)
{
    m_CreepDiedCallbacks.push_back(_creepDiedCallback);
}

void NotificationManager::onCreepReachedEnd(const Creep& _creep, const CreepPath& _creepPath)
{
    for (auto creepReachedEndMethod : m_CreepReachedEndCallbacks) {
        if (creepReachedEndMethod(_creep, _creepPath)) {
            return;
        }
    }
}
void NotificationManager::registerCreepReachedEndCallback(std::function<bool(const Creep&, const CreepPath&)> _creepReachedEndCallback)
{
    m_CreepReachedEndCallbacks.push_back(_creepReachedEndCallback);
}