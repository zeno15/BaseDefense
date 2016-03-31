#include <CreepWaves/BasicCreepWave.hpp>

#include <Managers/EntityManager.hpp>
#include <BaseObjects/Creep.hpp>

#include <iostream>
#include <Managers/TextureManager.hpp>

BasicCreepWave::BasicCreepWave(CreepPath& _path, float _interArrivalTime, unsigned int _maxSpawn) :
CreepWave(_path),
m_ElapsedTime(0.0f),
m_TriggerTime(_interArrivalTime),
m_Spawned(0),
m_MaxSpawn(_maxSpawn)
{
}


void BasicCreepWave::update(float _delta)
{
    m_ElapsedTime += _delta;

    if (!m_IsFinished && m_ElapsedTime >= m_TriggerTime) {
        m_ElapsedTime -= m_TriggerTime;

        sEntityManager.addEntity(new Creep(sTextureManager.getTexture(TextureManager::Texture::CreepBasic), m_Path, 8.0f));
        m_Spawned += 1;

        std::cout << "Spawned: " << m_Spawned << "/" << m_MaxSpawn << " creeps." << std::endl;

        if (m_Spawned >= m_MaxSpawn) {
            m_IsFinished = true;
        }
    }
}