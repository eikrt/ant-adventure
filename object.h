
#ifndef OBJECT_H
#define OBJECT_H
#include <raylib.h>
class Object {
    public: 
        Vector3 pos;
        Vector3 startPos;
        Vector3 vpos;
        Vector3 dim;
        Model model;
        int hp;
        float z;
        const char* type;
        bool visible;
        float offsetY;

    Object(Vector3 pos, float z, float offsetY, Vector3 dim, bool visible, const char* type, Model model) {
        this->pos = pos;
        this->startPos = pos;
        this->model = model;
        this->dim = dim;
        this->z = z;
        this->offsetY = offsetY;
        this->type = type;
        this->visible = visible;
        this->vpos = {0.0f,0.0f,0.0f};
        this->hp = 1;
    }
    Vector3 getPos();
    Vector3 getVpos();
    Vector3 getDim();
    int getHp();
    void render(Camera camera);
    void tick(float delta);
    void collision(float gravity);
};
#endif
