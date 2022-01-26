#include "object.h"
#include <raylib.h>
#include <iostream>
using namespace std;
void Object::tick(float gravity) {
}
Vector3 Object::getVpos() {
    return this->vpos;
}
Vector3 Object::getPos() {
    return this->pos;
}
Vector3 Object::getDim() {
    return this->dim;
}
void Object::render(Camera camera) {
                DrawModel(this->model, {this->pos.x + this->dim.x/2, this->pos.y+ this->dim.y/2, this->pos.z+ this->dim.z/2},
                        0.5f, BROWN);

}
