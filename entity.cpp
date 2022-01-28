
#include "entity.h"
#include <raylib.h>
#include <iostream>
#define JUMP_STRENGTH 0.2f
using namespace std;
Vector3 Entity::getPos() {
    return this->pos;
}

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
    float ePosX = this->pos.x+this->vpos.x;
    float ePosY = this->pos.y+this->vpos.y;
    float eRightX = ePosX + this->dim.x;
    float eLeftX = ePosX - this->dim.x;
    float eTopY = ePosY + this->dim.y;
    float eBottomY = ePosY - this->dim.y;

    float oRightX = object.getPos().x + object.getDim().x;
    float oLeftX = object.getPos().x - object.getDim().x;
    float oTopY = object.getPos().y + object.getDim().y;
    float oBottomY = object.getPos().y - object.getDim().y;
    
    if (eBottomY  <= oTopY
            && eBottomY >= object.getPos().y
            && ePosX > object.getPos().x - 0.2 
            && ePosX < oRightX) {
        blockedDown = true;
        if (eBottomY > object.getPos().y + object.getDim().y) {
        
            this->pos.y += this->pos.y + this->pos.y - (this->dim.y - object.getPos().y + object.getDim().y);
        }
        this->stopY();
    }
    if (eTopY  <= oTopY
            && eTopY >= object.getPos().y
            && ePosX > object.getPos().x - 0.2 
            && ePosX < oRightX) {
        blockedUp = true;
        if (eBottomY > object.getPos().y + object.getDim().y) {
        
            this->pos.y += this->pos.y + this->pos.y - (this->dim.y - object.getPos().y + object.getDim().y);
        }
        this->vpos.y = -0.1f;
    }
    if (
            ePosY > object.getPos().y &&
            ePosY  < oTopY &&
            eRightX >= object.getPos().x &&
            eRightX <= oRightX)
    {
        blockedRight = true;
        this->stopX();
    }
    if (
            ePosY > object.getPos().y &&
            ePosY < oTopY &&
            eLeftX >= object.getPos().x &&
            eLeftX <= oRightX)
    {
        blockedLeft = true;
        this->stopX();
    }
}
void Entity::render(Camera camera) {
            DrawBillboard(camera,this->tex,{this->pos.x, this->pos.y, this->pos.z}, this->scale, WHITE);

}
