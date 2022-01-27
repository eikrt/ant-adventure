
#include "entity.h"
#include <raylib.h>
#include <iostream>
#define JUMP_STRENGTH 0.2f
using namespace std;
void Entity::tick(float gravity) {
     
    if (!this->blockedDown) {
    this->vpos.y -= gravity;
        this->pos.y += this->vpos.y;
    }
    if (!(this->blockedRight && this->blockedLeft)) {
        
    this->pos.x += this->vpos.x;
    }
    this->pos.z += this->vpos.z;
    this-> blockedRight = false;
    this-> blockedLeft = false;
    this->blockedDown = false;
    this->blockedUp = false;
}
void Entity::jump() {
    if (blockedDown) {
        this->vpos.y = JUMP_STRENGTH;
    }
}
void Entity::left() {
    blockedRight = false;
    if (!blockedLeft)
    this->vpos.x = -this->speed;
}
void Entity::right() {
    blockedLeft = false;
    if (!blockedRight)
    this->vpos.x = this->speed;
}
void Entity::stopX() {
    this->vpos.x = 0.0f;
}
void Entity::stopY() {
    this->vpos.y = 0.0f;
}
void Entity::stopZ() {
    this->vpos.z = 0.0f;
}
void Entity::slowX() {
    if (this->vpos.x < -0.01) {
        this->vpos.x += 0.01;
    }
    else if (this->vpos.x > 0.01) {
        this->vpos.x -= 0.01;
    }
    else {
        this->stopX();
    }
}
void Entity::collision_object(Object object) {
    if (this->pos.y+this->vpos.y - this->dim.y  <= object.getPos().y + object.getDim().y && this->pos.x > object.getPos().x && this->pos.x < object.getPos().x + object.getDim().x ){
        blockedDown = true;
        if (this->pos.y + this->vpos.y - this->dim.y > object.getPos().y + object.getDim().y) {
        
            this->pos.y += this->pos.y + this->pos.y - (this->dim.y - object.getPos().y + object.getDim().y);
        }
        this->stopY();
    }
    if (
            this->pos.y + this->vpos.y > object.getPos().y &&
            this->pos.y+ this->vpos.y  < object.getPos().y + object.getDim().y &&
            this->pos.x + this->vpos.x + this->dim.x >= object.getPos().x &&
            this-> pos.x + this->vpos.x + this->dim.x <= object.getPos().x + object.getDim().x 
            )
    {
        blockedRight = true;
        this->stopX();
    }
    if (
            this->pos.y > object.getPos().y &&
            this->pos.y < object.getPos().y + object.getDim().y &&
            this->pos.x + this->vpos.x - this->dim.x >= object.getPos().x &&
            this-> pos.x + this->vpos.x - this->dim.x <= object.getPos().x + object.getDim().x 
            )
    {
        blockedLeft = true;
        this->stopX();
    }
}
void Entity::render(Camera camera) {
            DrawBillboard(camera,this->tex,{this->pos.x, this->pos.y, this->pos.z}, this->scale, WHITE);

}
