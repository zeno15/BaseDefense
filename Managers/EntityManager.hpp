#ifndef BASEDEFENSE_ENTITYMANAGER_HPP
#define BASEDEFENSE_ENTITYMANAGER_HPP

#include <vector>

#include <BaseObjects/Entity.hpp>

class EntityManager {
public:
    static EntityManager& getInstance() {
        static EntityManager manager = EntityManager();

        return manager;
    }


    void update(float _delta);

    void render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection);

    void addEntity(Entity *_entity);

    std::vector<Entity *>::iterator getEntityStart(void);
    std::vector<Entity *>::iterator getEntityEnd(void);

private:

    EntityManager(void);

    ~EntityManager(void);

    std::vector<Entity *> m_Entities;
};

#define sEntityManager EntityManager::getInstance()

#endif //BASEDEFENSE_ENTITYMANAGER_HPP
