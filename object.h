
#ifndef OBJECT_H
#define OBJECT_H
#include <raylib.h>
class Object {
    private: 
        Vector3 pos;
        Vector3 vpos;
        Vector3 dim;
        Model model;
        int hp;
    public: 
    Object(Vector3 pos, Vector3 dim, Model model) {
        this->pos = pos;
        this->model = model;
        this->dim = dim;
        this->vpos = {0.0f,0.0f,0.0f};
        this->hp = 1;
    }
    Vector3 getPos();
    Vector3 getVpos();
    Vector3 getDim();
    int getHp();
    void render(Camera camera);
    void tick(float gravity);
    void collision(float gravity);
};
#endif
