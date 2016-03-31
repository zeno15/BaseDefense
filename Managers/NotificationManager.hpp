#ifndef BASEDEFENSE_NOTIFICATIONMANAGER_HPP
#define BASEDEFENSE_NOTIFICATIONMANAGER_HPP

#include <BaseObjects/Creep.hpp>

#include <functional>

class NotificationManager {
public:
    static NotificationManager& getInstance() {
        static NotificationManager manager = NotificationManager();

        return manager;
    }

    void onCreepDied(const Creep& _creep);
    void registerCreepDiedCallback(std::function<bool(const Creep&)> _creepDiedCallback);

    void onCreepReachedEnd(const Creep& _creep, const CreepPath& _creepPath);
    void registerCreepReachedEndCallback(std::function<bool(const Creep&, const CreepPath&)> _creepReachedEndCallback);

private:
    NotificationManager(void);
    ~NotificationManager(void);

private:
    std::vector<std::function<bool(const Creep&)>> m_CreepDiedCallbacks;
    std::vector<std::function<bool(const Creep&, const CreepPath&)>> m_CreepReachedEndCallbacks;
};

#define sNotification NotificationManager::getInstance()

#endif //BASEDEFENSE_NOTIFICATIONMANAGER_HPP
