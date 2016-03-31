#include <Managers/CreepWaveManager.hpp>

#include <iostream>

CreepWaveManager::CreepWaveManager(void)
{

}
CreepWaveManager::~CreepWaveManager(void)
{

}



void CreepWaveManager::update(float _delta)
{
    for (unsigned int i = 0; i < m_Waves.size(); i += 1) {
        m_Waves.at(i)->update(_delta);

        if (m_Waves.at(i)->hasFinished()) {
            delete m_Waves.at(i);

            m_Waves.erase(m_Waves.begin() + i);

            std::cout << "Removing wave" << std::endl;
        }
    }
}

void CreepWaveManager::addWave(CreepWave *_wave)
{
    m_Waves.push_back(_wave);
}
