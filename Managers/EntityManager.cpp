#include <Managers/EntityManager.hpp>

#include <iostream>

EntityManager::EntityManager() {

}
EntityManager::~EntityManager(void) {
    for(Entity *entity : m_Entities) {
        delete entity;
    }
}


void EntityManager::update(float _delta) {
    for (unsigned int i = 0; i < m_Entities.size(); i += 1) {
        m_Entities.at(i)->update(_delta);

        if (!m_Entities.at(i)->isAlive()) {
            delete m_Entities.at(i);

            m_Entities.erase(m_Entities.begin() + i);
        }
    }
}

void EntityManager::render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection) {
    for (unsigned int i = 0; i < m_Entities.size(); i += 1) {
        m_Entities.at(i)->render(_view, _projection);
    }
}

void EntityManager::addEntity(Entity *_entity) {
    m_Entities.push_back(_entity);
}

std::vector<Entity *>::iterator EntityManager::getEntityStart(void)
{
    return m_Entities.begin();
}
std::vector<Entity *>::iterator EntityManager::getEntityEnd(void)
{
    return m_Entities.end();
}