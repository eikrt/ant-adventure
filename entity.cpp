
#include "entity.h"
#include <raylib.h>
#include <iostream>
using namespace std;
void Entity::tick(float gravity) {
    
    this->pos.x += vpos.x;
    if (!blockedDown) {
    this->vpos.y -= gravity;
        this->pos.y += vpos.y;
    }
    this->pos.z += vpos.z;
}
void Entity::jump() {
    if (blockedDown) {
        this->vpos.y = 0.2f;
    }
}
void Entity::collision_object(Object object) {
    blockedDown = false;
    blockedLeft = false;
    blockedRight = false;
    blockedUp = false;
    if (this->pos.y+this->vpos.y - this->dim.y <= object.getVpos().y) {
        blockedDown = true;
    }
}
void Entity::render(Camera camera) {
            DrawBillboard(camera,this->tex,this->pos, 0.5f, WHITE);

}
