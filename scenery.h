#ifndef SCENERY_H
#define SCENERY_H
#include <raylib.h>
#include <vector>
#include <map>
#include <string>
#include "entity.h"
#include "generator.h"
using namespace std;
class Scenery {
    private: 
        Vector3 pos;
        Vector3 vpos;
        Vector3 dim;
        Model model;
        vector<Entity> entities;
    public: 
        Color skyColor;
    Scenery(Vector3 pos, Vector3 dim, Color skyColor, Model model, map<string, Texture2D> textures) {
        this->pos = pos;
        this->model = model;
        this->dim = dim;
        this->vpos = {0.0f,0.0f,0.0f};
        this->entities = generate(entities, textures);
        this->skyColor = skyColor;
    }
    Vector3 getPos();
    Vector3 getVpos();
    Vector3 getDim();
    void render(Camera camera);
    void tick(float gravity);
    void collision(float gravity);
};
#endif
