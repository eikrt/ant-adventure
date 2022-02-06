#ifndef SCENERY_H
#define SCENERY_H
#include <raylib.h>
#include <vector>
#include <map>
#include <string>
#include "entity.h"
#include "generator.h"
#include "skybox.h"
using namespace std;
class Scenery {
    private: 
        Vector3 pos;
        Vector3 vpos;
        Vector3 dim;
        Model model;
        vector<Entity> entities;
    public: 
        vector<SkyBox> skyboxes;
        Color skyColor;
        Color lightColor;
    Scenery(Vector3 pos, Vector3 dim, Color skyColor, Color lightColor, Model model, map<string, Texture2D> textures) {
        this->pos = pos;
        this->model = model;
        this->dim = dim;
        this->vpos = {0.0f,0.0f,0.0f};
        this->entities = generate(entities, textures);
        this->skyColor = skyColor;
        this->lightColor = lightColor;
        this->skyboxes.push_back(SkyBox(textures["skybox_1"], skyColor, Vector3({0.0f,0.0f,-500.0f})));
    }
    Vector3 getPos();
    Vector3 getVpos();
    Vector3 getDim();
    void render(Camera camera);
    void tick(float gravity);
    void collision(float gravity);
};
#endif
