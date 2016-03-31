#include <Managers/TextureManager.hpp>

TextureManager::TextureManager(void)
{
}

TextureManager::~TextureManager(void)
{

}


void TextureManager::loadTextures(void)
{
    m_Textures.insert(std::pair<Texture, zeno::Texture>(Texture::CreepBasic, zeno::Texture()));
    m_Textures[Texture::CreepBasic].loadFromFile("Resources/Textures/Creeps/Basic.png");

    m_Textures.insert(std::pair<Texture, zeno::Texture>(Texture::ProjectileBasic, zeno::Texture()));
    m_Textures[Texture::ProjectileBasic].loadFromFile("Resources/Textures/Projectiles/Basic.png");

    m_Textures.insert(std::pair<Texture, zeno::Texture>(Texture::TowerBasic, zeno::Texture()));
    m_Textures[Texture::TowerBasic].loadFromFile("Resources/Textures/Towers/Basic.png");

    m_Textures.insert(std::pair<Texture, zeno::Texture>(Texture::Waypoint, zeno::Texture()));
    m_Textures[Texture::Waypoint].loadFromFile("Resources/Textures/Miscellaneous/Waypoint.png");
}

zeno::Texture& TextureManager::getTexture(Texture _texture)
{
    return m_Textures[_texture];
}