#include <Managers/TowerManager.hpp>
#include <Towers/BasicTower.hpp>


TowerManager::TowerManager(void)
{
    auto basicTowerCreationMethod = [](const zeno::Vector2f& _position){
        return new BasicTower(sTextureManager.getTexture(TextureManager::Texture::TowerBasic), _position);
    };

    m_TowerCreationMethods.push_back(std::make_pair("BasicTower", basicTowerCreationMethod));
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

bool TowerManager::createTower(const std::string& _towerName, const zeno::Vector2f& _position)
{
    zeno::Vector2f newTowerCoords = zeno::Vector2f(_position) * Application::TileSize + zeno::Vector2f(Application::TileSize, Application::TileSize) * 0.5f;

    for(auto pair : m_TowerCreationMethods)
    {
        if (pair.first == _towerName) {

            for (auto tower : m_Towers) {
                if (newTowerCoords == tower->getPosition()) {
                    return false;
                }
            }
            m_Towers.push_back(pair.second(newTowerCoords));

            return true;
        }
    }

    return false;
}