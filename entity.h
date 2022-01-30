#ifndef ENTITY_H
#define ENTITY_H
#include <raylib.h>
#include <string>
#include <vector>
#include "entity.h"
#include "object.h"
using namespace std;
class Entity {
    protected: 
        Vector3 pos;
        Vector3 vpos;
        Vector3 dim;
        vector<Texture2D> texs;
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
        string mode;
        float rot;
        float launchSpeed;
    Entity(int id, const char* type, const char* category, float speed, Vector3 pos, Vector3 dim, float scale, vector<Texture2D> texs) {
        this->pos = pos;
        this->texs = texs;
        this->dim = dim;
        this->scale = scale;
        this->vpos = {0.0f,0.0f,0.0f};
        this->speed = speed;
        this->hp = 1;
        this->id = id;
        this->type = type;
        this->category = category;
        this->mode = "normal";
        this->rot = 0.0;
        this->launchSpeed = 7.0f;
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
    void cannon();
    void launch();
    void shortJump();
    void tilt(float t);
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
