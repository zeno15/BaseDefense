#ifndef BASEDEFENSE_CREEPWAVEMANAGER_HPP
#define BASEDEFENSE_CREEPWAVEMANAGER_HPP

#include <BaseObjects/CreepWave.hpp>

#include <vector>

class CreepWaveManager
{
public:
    static CreepWaveManager& getInstance() {
        static CreepWaveManager manager = CreepWaveManager();

        return manager;
    }

    void update(float _delta);

    void addWave(CreepWave *_wave);

private:
    CreepWaveManager(void);
    ~CreepWaveManager(void);

    std::vector<CreepWave *> m_Waves;

};

#define sCreepWaveManager CreepWaveManager::getInstance()

#endif //BASEDEFENSE_CREEPWAVEMANAGER_HPP
