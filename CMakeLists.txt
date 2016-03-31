cmake_minimum_required(VERSION 3.3)
project(BaseDefense)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static")

set(CMAKE_BUILD_TYPE Debug)

set(LIBS
        glfw3
        glew32s
        opengl32
        freetype
        ssl
        crypto
        ws2_32
        )

add_definitions(-DGLEW_STATIC)
add_definitions(-D_WIN32)
link_directories("C:/Users/Mark/.CLion12/system/cmake/generated/586cc0cb/586cc0cb/Debug")
include_directories(C:/Users/Mark/Documents/Github/zeno/include)
include_directories(${CMAKE_SOURCE_DIR})

set(TOWER_DEFENSE_SOURCE_FILES
        Application.cpp

        BaseObjects/Creep.cpp
        BaseObjects/CreepPath.cpp
        BaseObjects/CreepWave.cpp
        BaseObjects/Entity.cpp
        BaseObjects/Force.cpp
        BaseObjects/Projectile.cpp
        BaseObjects/Sprite.cpp
        BaseObjects/Tower.cpp

        CreepWaves/BasicCreepWave.cpp

        Forces/CreepForce.cpp
        Forces/PlayerForce.cpp

        Managers/CreepWaveManager.cpp
        Managers/EntityManager.cpp
        Managers/NotificationManager.cpp
        Managers/ProjectileManager.cpp
        Managers/TextureManager.cpp
        Managers/TowerManager.cpp

        MiscellaneousRenderables/HealthBar.cpp

        Projectiles/BasicProjectile.cpp

        Towers/BasicTower.cpp
        )
set(TOWER_DEFENSE_HEADER_FILES
        Application.hpp
        Waypoint.hpp

        BaseObjects/Creep.hpp
        BaseObjects/CreepPath.hpp
        BaseObjects/CreepWave.hpp
        BaseObjects/Entity.hpp
        BaseObjects/Force.hpp
        BaseObjects/Projectile.hpp
        BaseObjects/Sprite.hpp
        BaseObjects/Tower.hpp

        CreepWaves/BasicCreepWave.hpp

        Forces/CreepForce.hpp
        Forces/PlayerForce.hpp

        Managers/CreepWaveManager.hpp
        Managers/EntityManager.hpp
        Managers/NotificationManager.hpp
        Managers/ProjectileManager.hpp
        Managers/TextureManager.hpp
        Managers/TowerManager.hpp

        MiscellaneousRenderables/HealthBar.hpp

        Projectiles/BasicProjectile.hpp

        Towers/BasicTower.hpp
        )

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp ${TOWER_DEFENSE_SOURCE_FILES} ${TOWER_DEFENSE_HEADER_FILES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
        zeno-window-s-d
        zeno-network-s-d
        zeno-gui-s-d
        zeno-graphics-s-d
        zeno-system-s-d
        ${LIBS}
        )

add_custom_target(CopyResources ALL
        COMMAND ${CMAKE_COMMAND} -E remove_directory "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Resources" "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Resources"
        COMMENT "Copying ${PROJECT_NAME} Resources to build tree"
        VERBATIM)