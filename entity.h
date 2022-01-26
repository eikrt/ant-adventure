#ifndef ENTITY_H
#define ENTITY_H
#include <raylib.h>
#include "entity.h"
#include "object.h"
class Entity {
    private: 
        Vector3 pos;
        Vector3 vpos;
        Vector3 dim;
        Texture2D tex;
        bool blockedLeft;
        bool blockedRight;
        bool blockedDown;
        bool blockedUp;
    public: 
    Entity(Vector3 pos, Vector3 dim, Texture2D tex) {
        this->pos = pos;
        this->tex = tex;
        this->dim = dim;
        this->vpos = {0.0f,0.0f,0.0f};
        blockedLeft = false;
        blockedRight = false;
        blockedDown = false;
        blockedUp = false;
    }
    void render(Camera camera);
    void tick(float gravity);
    void collision_object(Object object);
    void jump();

};
#endif