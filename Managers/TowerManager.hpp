#ifndef BASEDEFENSE_TOWERMANAGER_HPP
#define BASEDEFENSE_TOWERMANAGER_HPP

#include <BaseObjects/Tower.hpp>

#include <vector>
#include <iostream>
#include <functional>

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

    bool createTower(const std::string& _towerName, const zeno::Vector2f& _position);

private:

    TowerManager(void);

    ~TowerManager(void);

    std::vector<Tower *> m_Towers;

    std::vector<std::pair<std::string, std::function<Tower *(const zeno::Vector2f&)>>> m_TowerCreationMethods;
};

#define sTowerManager TowerManager::getInstance()

#endif //BASEDEFENSE_TOWERMANAGER_HPP
