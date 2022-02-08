#ifndef ENTITY_H
#define ENTITY_H
#include <raylib.h>
#include <string>
#include <vector>
#include "entity.h"
#include "object.h"
using namespace std;
class Entity {
    public: 
        vector<Texture2D> texs;
        bool blockedLeft;
        bool blockedRight;
        bool blockedDown;
        bool blockedUp;
        float speed;
        float scale;
        int hp = 1;
        int id;
        int blockersLeft = 0;
        Vector3 pos;
        Vector3 startPos;
        Vector3 vpos;
        Vector3 dim;
        const char* type;
        const char* category;
        string moveMode;
        float rot;
        float cannonChange;
        float cannonTime;
        float launchSpeed;
        int coins;
        int tokens;
        int lastCoins;
        int lastTokens;
        vector<string> artifacts;
        vector<string> lastArtifacts;
        float startZ;
        float gravity;
        bool nextLevel;
        float z;
        Vector3 carrierPos;
        bool carried;
        bool checkpointed;
        int carrierId;
    Entity(int id, float gravity, const char* type, const char* category, float speed, Vector3 pos, float z, Vector3 dim, float scale, vector<Texture2D> texs) {
        this->pos = pos;
        this->startPos = {pos.x, pos.y, pos.z};
        this->carrierPos = Vector3({0.0f,0.0f,0.0f});
        this->carried = false;
        this->carrierId = -1;
        this->texs = texs;
        this->dim = dim;
        this->z = z;
        this->scale = scale;
        this->vpos = {0.0f,0.0f,0.0f};
        this->speed = speed;
        this->hp = 1;
        this->id = id;
        this->type = type;
        this->category = category;
        this->moveMode = "normal";
        this->rot = 0.0;
        this->launchSpeed = 9.0f;
        this->cannonTime = 500;
        this->cannonChange = 0;
        this->coins = 0;
        this->lastCoins = 0;
        this->lastTokens = 0;
        this-> gravity = gravity;
        this->tokens = 0;
        this->blockersLeft = 0;
        this->nextLevel = false;
        this->z = z;
        this->checkpointed = false;
        blockedLeft = false;
        blockedRight = false;
        blockedDown = false;
        blockedUp = false;
    }
    void render(Camera camera);
    void tick(float delta);
    Vector3 getPos();
    Vector3 getVpos();
    Vector3 getDim();
    int getHp();
    int getId();
    void collision_object(float delta, Object& object);
    void collision_entity(float delta, Entity& otherEntity);
    void damage();
    void jump(float f);
    void cannon();
    void launch();
    void collectCoin(int value);
    void collisionAction(float delta, Entity& otherEntity, const char* dir);
    void tilt(float t);
    void left();
    void right();
    void forward();
    void back();
    void up();
    void down();
    void stopX();
    void slowX(float delta, float strength);
    void slowY(float delta, float strength);
    void stopY();
    void stopZ();

};
#endif
