#ifndef MONSTER_H
#define MONSTER_H
#include "entity.h"
class Monster : public Entity {
    using Entity::Entity;
    public:
    void tick(float gravity);
};
#endif
