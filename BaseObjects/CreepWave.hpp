#ifndef BASEDEFENSE_CREEPWAVE_HPP
#define BASEDEFENSE_CREEPWAVE_HPP


#include <BaseObjects/CreepPath.hpp>

class CreepWave
{
public:
    CreepWave(CreepPath& _path);

    virtual void update(float _delta) = 0;

    bool hasFinished(void) const;

protected:
    bool m_IsFinished;

    CreepPath& m_Path;
};


#endif //BASEDEFENSE_CREEPWAVE_HPP
