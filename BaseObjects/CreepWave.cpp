#include <BaseObjects/CreepWave.hpp>

CreepWave::CreepWave(CreepPath& _path) :
m_IsFinished(false),
m_Path(_path)
{

}

bool CreepWave::hasFinished(void) const
{
    return m_IsFinished;
}