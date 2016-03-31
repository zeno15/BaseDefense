#include <Managers/TowerManager.hpp>



TowerManager::TowerManager(void)
{

}
TowerManager::~TowerManager(void)
{
    for(Tower *tower : m_Towers) {
        delete tower;
    }
}


void TowerManager::update(float _delta)
{
    for (unsigned int i = 0; i < m_Towers.size(); i += 1) {
        m_Towers.at(i)->update(_delta);
    }
}

void TowerManager::render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection)
{
    for (unsigned int i = 0; i < m_Towers.size(); i += 1) {
        m_Towers.at(i)->render(_view, _projection);
    }
}