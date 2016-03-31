#ifndef BASEDEFENSE_TOWER_HPP
#define BASEDEFENSE_TOWER_HPP


#include <BaseObjects/Creep.hpp>
#include <BaseObjects/Sprite.hpp>

class Tower {
public:
    Tower(zeno::Texture& _texture, const zeno::Vector2f& _position, float _range, float _damage);

    virtual void update(float _delta) = 0;

    void render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection);

    Creep *getMostDangerousCreepInRange(void);

    bool isInRange(Creep *_creep) const;

    void faceCurrentTarget(void);

    zeno::Vector2f getPosition(void) const;

protected:
    Sprite sprite;

    Creep *m_CurrentTarget;

    float m_Range;

    float m_Damage;
};


#endif //BASEDEFENSE_TOWER_HPP
