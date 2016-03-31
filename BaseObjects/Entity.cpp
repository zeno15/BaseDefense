#include <BaseObjects/Entity.hpp>


Entity::Entity(zeno::Texture& _texture) :
sprite(_texture),
m_Alive(true)
{

}


void Entity::render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection)
{
    sprite.render(_view, _projection);
}

void Entity::kill(void)
{
    m_Alive = false;
}
bool Entity::isAlive(void)
{
    return m_Alive;
}

zeno::Vector2f Entity::getPosition(void) const
{
    return sprite.getPosition();
}