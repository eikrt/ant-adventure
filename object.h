
#ifndef OBJECT_H
#define OBJECT_H
#include <raylib.h>
class Object {
    private: 
        Vector3 pos;
        Vector3 vpos;
        Vector3 dim;
        Texture2D tex;
    public: 
    Object(Vector3 pos, Vector3 dim, Texture2D tex) {
        this->pos = pos;
        this->tex = tex;
        this->dim = dim;
        this->vpos = {0.0f,0.0f,0.0f};
    }
    Vector3 getPos();
    Vector3 getVpos();
    void render(Camera camera);
    void tick(float gravity);
    void collision(float gravity);
};
#endif
