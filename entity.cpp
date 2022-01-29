
#include "entity.h"
#include <raylib.h>
#include <iostream>
#define JUMP_STRENGTH 0.2f
#define BOUNCE 0.1f
using namespace std;
Vector3 Entity::getVpos() {
    return this->vpos;
}
Vector3 Entity::getPos() {
    return this->pos;
}
Vector3 Entity::getDim() {
    return this->dim;
}
int Entity::getHp(){
    return this->hp;
}
int Entity::getId() {
    return this->id;
}
void Entity::damage() {
    this->hp -= 1;
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
void Entity::shortJump() {
    if (blockedDown) {
        this->vpos.y = JUMP_STRENGTH / 2;
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
            eBottomY + 0.1 > object.getPos().y &&
            eBottomY + 0.1 < oTopY &&
            eRightX >= object.getPos().x &&
            eRightX <= oRightX)
    {
        blockedRight = true;
        this->stopX();
        if (string(this->type) == "fungus" ){
            this->left();

        }
    }
    if (
            eBottomY + 0.1 > object.getPos().y &&
            eBottomY + 0.1 < oTopY &&
            eLeftX >= object.getPos().x &&
            eLeftX <= oRightX)
    {
        blockedLeft = true;
        this->stopX();
        if (string(this->type) == "fungus" ){
            this->right();

        }
    }
}
void Entity::collision_entity(Entity& otherEntity) {
    float ePosX = this->pos.x+this->vpos.x;
    float ePosY = this->pos.y+this->vpos.y;
    float eRightX = ePosX + this->dim.x;
    float eLeftX = ePosX - this->dim.x;
    float eTopY = ePosY + this->dim.y;
    float eBottomY = ePosY - this->dim.y;

    float oRightX = otherEntity.getPos().x + otherEntity.getDim().x;
    float oLeftX = otherEntity.getPos().x - otherEntity.getDim().x;
    float oTopY = otherEntity.getPos().y + otherEntity.getDim().y;
    float oBottomY = otherEntity.getPos().y - otherEntity.getDim().y;
    
    if (eBottomY  <= oTopY
            && eBottomY >= otherEntity.getPos().y
            && ePosX > otherEntity.getPos().x - 0.2 
            && ePosX < oRightX) {
        blockedDown = true;
        if (eBottomY > otherEntity.getPos().y + otherEntity.getDim().y) {
        
            this->pos.y += this->pos.y + this->pos.y - (this->dim.y - otherEntity.getPos().y + otherEntity.getDim().y);
        }
        otherEntity.damage();
        this->stopY();
        this->jump();
    }
    if (eTopY  <= oTopY
            && eTopY >= otherEntity.getPos().y
            && ePosX > otherEntity.getPos().x - 0.2 
            && ePosX < oRightX) {
        blockedUp = true;
        if (eBottomY > otherEntity.getPos().y + otherEntity.getDim().y) {
        
            this->pos.y += this->pos.y + this->pos.y - (this->dim.y - otherEntity.getPos().y + otherEntity.getDim().y);
        }
        this->vpos.y = BOUNCE;
    }
    if (
            ePosY > otherEntity.getPos().y &&
            ePosY  < oTopY &&
            eRightX >= otherEntity.getPos().x &&
            eRightX <= oRightX)
    {
        blockedRight = true;
        this->stopX();
        if (string(this->type) == "player" && string(otherEntity.type) == "fungus") {
            this->damage();
        }
    }
    if (
            ePosY > otherEntity.getPos().y &&
            ePosY < oTopY &&
            eLeftX >= otherEntity.getPos().x &&
            eLeftX <= oRightX)
    {
        blockedLeft = true;
        this->stopX();
        if (string(this->type) == "player" && string(otherEntity.type) == "fungus") {
            this->damage();
        }
    }
}
void Entity::render(Camera camera) {
            DrawBillboard(camera,this->tex,{this->pos.x, this->pos.y, this->pos.z}, this->scale, WHITE);

}
