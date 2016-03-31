#ifndef BASEDEFENSE_PROJECTILEMANAGER_HPP
#define BASEDEFENSE_PROJECTILEMANAGER_HPP

#include <BaseObjects/Projectile.hpp>

class ProjectileManager
{
public:
    static ProjectileManager& getInstance() {
        static ProjectileManager manager = ProjectileManager();

        return manager;
    }


    void update(float _delta);

    void render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection);

    void addProjectile(Projectile *_projectile);


private:

    ProjectileManager(void);

    ~ProjectileManager(void);

    std::vector<Projectile *> m_Projectiles;
};

#define sProjectileManager ProjectileManager::getInstance()

#endif //BASEDEFENSE_PROJECTILEMANAGER_HPP
