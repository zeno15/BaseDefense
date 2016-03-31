#ifndef BASEDEFENSE_ENTITY_HPP
#define BASEDEFENSE_ENTITY_HPP

#include <BaseObjects/Sprite.hpp>

class Entity {
public:
    Entity(zeno::Texture& _texture);

    virtual void update(float _delta) = 0;

    virtual void render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection);

    void kill(void);
    bool isAlive(void);

    zeno::Vector2f getPosition(void) const;

protected:
    Sprite sprite;

    bool m_Alive;
};


#endif //BASEDEFENSE_ENTITY_HPP
