#ifndef BASEDEFENSE_TOWERMANAGER_HPP
#define BASEDEFENSE_TOWERMANAGER_HPP

#include <BaseObjects/Tower.hpp>

#include <vector>
#include <iostream>

#include <Managers/TextureManager.hpp>

#include <zeno/System/Mat4x4.hpp>
#include <Application.hpp>

class TowerManager {
public:
    static TowerManager& getInstance() {
        static TowerManager manager = TowerManager();

        return manager;
    }


    void update(float _delta);

    void render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection);

    template <typename T>
    bool addTower(TextureManager::Texture _texture, const zeno::Vector2i& _tilecoordinates) {
        zeno::Vector2f newTowerCoords = zeno::Vector2f(_tilecoordinates) * Application::TileSize + zeno::Vector2f(Application::TileSize, Application::TileSize) * 0.5f;

        for (auto tower : m_Towers) {
            if (newTowerCoords == tower->getPosition()) {
                return false;
            }
        }

        T *tower = new T(sTextureManager.getTexture(_texture), newTowerCoords);

        m_Towers.push_back(tower);

        return true;
    }

private:

    TowerManager(void);

    ~TowerManager(void);

    std::vector<Tower *> m_Towers;
};

#define sTowerManager TowerManager::getInstance()

#endif //BASEDEFENSE_TOWERMANAGER_HPP
