#ifndef BASEDEFENSE_TEXTUREMANAGER_HPP
#define BASEDEFENSE_TEXTUREMANAGER_HPP

#include <Map>

#include <zeno/Graphics/Texture.hpp>

class TextureManager
{
public:
    enum Texture {
        CreepBasic,
        TowerBasic,
        ProjectileBasic,
        Waypoint
    };

    static TextureManager& getInstance() {
        static TextureManager manager = TextureManager();

        return manager;
    }

    void loadTextures(void);

    zeno::Texture& getTexture(Texture _texture);

private:
    TextureManager(void);

    ~TextureManager(void);

    std::map<Texture, zeno::Texture> m_Textures;
};

#define sTextureManager TextureManager::getInstance()

#endif //BASEDEFENSE_TEXTUREMANAGER_HPP
