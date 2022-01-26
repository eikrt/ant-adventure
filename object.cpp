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
void Object::render(Camera camera) {
            DrawBillboard(camera,this->tex,this->pos, 0.5f, WHITE);

}
