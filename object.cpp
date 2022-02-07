#include "object.h"
#include <raylib.h>
#include <iostream>
using namespace std;
void Object::tick(float delta) {
    if (this->type == string("moving_cube_up")) {
        if (this->pos.y <= this->startPos.y + 2.0f) {
            this->vpos.y += 0.5f;
        } 
        else if (this->pos.y > this->startPos.y - 2.0f) {
            this->vpos.y -= 0.5f;
        } 
    }
    if (this->type == string("moving_cube_side")) {
        if (this->pos.x <= this->startPos.x + 2.0f) {
            this->vpos.x += 0.1f;
        } 
        else if (this->pos.x > this->startPos.x - 2.0f) {
            this->vpos.x -= 0.1f;
        } 
    }
        this->pos.y += this->vpos.y * delta / 1000;
        this->pos.x += this->vpos.x * delta / 1000;
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
int Object::getHp() {
    return this->hp;
}
void Object::render(Camera camera) {
            if (this->visible && this->type != string("water"))
                DrawModel(this->model, {this->pos.x + this->dim.x/2, this->pos.y+ this->dim.y/2 + this->offsetY, this->pos.z+ this->dim.z/2},
                        0.5f, BROWN);
            else if (this->type == string("water")) {
               DrawCubeV({this->pos.x + this->dim.x/2, this->pos.y+ this->dim.y/2 + this->offsetY, this->pos.z+ this->dim.z/2}, {1.0f,1.0f,1.0f}, {0,0,255,20}); 
            

        }
}
