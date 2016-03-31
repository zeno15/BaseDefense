#ifndef BASEDEFENSE_BASICCREEPWAVE_HPP
#define BASEDEFENSE_BASICCREEPWAVE_HPP

#include <BaseObjects/CreepWave.hpp>

class BasicCreepWave : public CreepWave
{
public:
    BasicCreepWave(CreepPath& _path, float _interArrivalTime, unsigned int _maxSpawn);

    virtual void update(float _delta);
private:
    float m_ElapsedTime;
    float m_TriggerTime;

    unsigned int m_Spawned;
    unsigned int m_MaxSpawn;
};


#endif //BASEDEFENSE_BASICCREEPWAVE_HPP
