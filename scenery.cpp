#include "scenery.h"
#include <raylib.h>
#include <iostream>
#include "entity.h"
using namespace std;
void Scenery::tick(float gravity) {
}
Vector3 Scenery::getVpos() {
    return this->vpos;
}
Vector3 Scenery::getPos() {
    return this->pos;
}
Vector3 Scenery::getDim() {
    return this->dim;
}
void Scenery::render(Camera camera) {
                this->skyboxes[0].render(camera);
                DrawModel(this->model, {this->pos.x + this->dim.x/2, this->pos.y+ this->dim.y/2, this->pos.z+ this->dim.z/2},
                        0.5f, GREEN);
                for (Entity e : this->entities) {
                    e.render(camera);
                };
                for (Object o : this->objects) {
                    o.render(camera);
                };

}
