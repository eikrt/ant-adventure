#ifndef ENTITY_H
#define ENTITY_H
#include <raylib.h>
#include <string>
#include "entity.h"
#include "object.h"
class Entity {
    protected: 
        Vector3 pos;
        Vector3 vpos;
        Vector3 dim;
        Texture2D tex;
        bool blockedLeft;
        bool blockedRight;
        bool blockedDown;
        bool blockedUp;
        float speed;
        float scale;
        int hp = 1;
        int id;
    public: 
        const char* type;
        const char* category;
    Entity(int id, const char* type, const char* category, float speed, Vector3 pos, Vector3 dim, float scale, Texture2D tex) {
        this->pos = pos;
        this->tex = tex;
        this->dim = dim;
        this->scale = scale;
        this->vpos = {0.0f,0.0f,0.0f};
        this->speed = speed;
        this->hp = 1;
        this->id = id;
        this->type = type;
        this->category = category;
        blockedLeft = false;
        blockedRight = false;
        blockedDown = false;
        blockedUp = false;
    }
    void render(Camera camera);
    void tick(float gravity);
    Vector3 getPos();
    Vector3 getVpos();
    Vector3 getDim();
    int getHp();
    int getId();
    void collision_object(Object object);
    void collision_entity(Entity& otherEntity);
    void damage();
    void jump();
    void shortJump();
    void left();
    void right();
    void forward();
    void back();
    void stopX();
    void slowX();
    void stopY();
    void stopZ();

};
#endif
