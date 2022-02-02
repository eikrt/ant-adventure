#include "math.h"
#include "entity.h"
#include <raylib.h>
#include <iostream>
#define JUMP_STRENGTH 10.0f
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
void Entity::collectCoin(int value) {
    this->coins += value;
}
void Entity::tick(float delta){
    if (this->pos.y < 0) {
        this->damage();
    }
    if (this->type == string("player")) {
    }
    if (this->type == string("bird")) {
        this->rot += 3.14 / 64;
        this->pos.x += cos(this->rot)  * delta * this->speed / 1000;
        this->pos.y += sin(this->rot)  * delta * this->speed / 1000;
    }
    if (this->mode == string("cannon")) {
        this->cannonChange += 10;
        if (this->cannonChange > this->cannonTime) {
            this-> cannonChange = 0;
            this->launch();
        }
    }
    if ( !this->blockedDown && (this->mode != string("cannon") && this->mode != string("ladder"))) {
        this->vpos.y -= this->gravity * delta / 1000;
    }
    if (this->type != string("bird"))
        this->pos.y += this->vpos.y * delta / 1000;
    if (!(this->blockedRight && this->blockedLeft)) {
        
    this->pos.x += this->vpos.x * delta / 1000;
    }
    this->pos.z += this->vpos.z;
    this-> blockedRight = false;
    this-> blockedLeft = false;
    this->blockedDown = false;
    this->blockedUp = false;
    if (this->mode == string("ladder")) {
        this->mode = string("normal");
    }
}
void Entity::jump(float f) {
    if (blockedDown) {
        this->mode = string("jump");
        this->vpos.y = JUMP_STRENGTH * f;
    }
}
void Entity::cannon() {
    this->mode = string("cannon");
    this->rot = 3.14/2;
    this->stopX();
    this->vpos.y = 0.0f;
}
void Entity::launch() {
    this->cannonChange = 0;
    this->mode = string("flying");
    this->vpos.x += cos(this->rot) * this->launchSpeed;
    this->vpos.y += sin(this->rot) * this->launchSpeed;
}
void Entity::left() {
    blockedRight = false;
    if (!blockedLeft && this->mode != string("cannon"))
    this->vpos.x = -this->speed;
}
void Entity::right() {
    blockedLeft = false;
    if (!blockedRight && this->mode != string("cannon"))
    this->vpos.x = this->speed;
}
void Entity::forward() {
    if (this->z < 2.0f) { 
        this->pos.z += 1.0;
        this->z += 1.0;
    }
}
void Entity::back() {
    if (this->z > 0.0f) {
        this->pos.z -= 1.0;
        this->z -= 1.0;
    }
}
void Entity::down() {
    this->vpos.y =-this->speed;
}
void Entity::up() {
    this->vpos.y = this->speed;
}
void Entity::stopX() {
    this->vpos.x = 0.0f;
}
void Entity::stopY() {
    this->vpos.y = 0.0f;
    this->mode = string("normal");
}
void Entity::stopZ() {
    this->vpos.z = 0.0f;
}
void Entity::slowX(float delta) {
    if (this->vpos.x < -0.2) {
        this->vpos.x += 25 * delta / 1000;
    }
    else if (this->vpos.x > 0.2) {
        this->vpos.x -= 25 * delta / 1000;
    }
    else {
        this->stopX();
    }
}
void Entity::tilt(float t) {
    this->rot += t;
}
void Entity::collision_object(float delta, Object& object) {
    float ePosX = this->pos.x+this->vpos.x *delta / 1000;
    float ePosY = this->pos.y+this->vpos.y * delta / 1000;
    float eRightX = ePosX + this->dim.x;
    float eLeftX = ePosX - this->dim.x;
    float eTopY = ePosY + this->dim.y;
    float eBottomY = ePosY - this->dim.y;

    float oRightX = object.getPos().x + object.getDim().x;
    float oLeftX = object.getPos().x - object.getDim().x;
    float oTopY = object.getPos().y + object.getDim().y;
    float oBottomY = object.getPos().y - object.getDim().y;
    if (this->z == object.z) { 
    if (vpos.y <= 0 && eBottomY  <= oTopY
            && eBottomY >= oBottomY
            && ePosX > object.getPos().x - 0.2 
            && ePosX < oRightX) {
        if (object.visible) {
        blockedDown = true;

            if (eBottomY <= oTopY && this->category != string("prop")) {
                //this->pos.y += this->pos.y + this->pos.y - (this->dim.y - object.getPos().y + object.getDim().y);
                this->pos.y = oTopY + this->dim.y;
            }
            this->stopY();
        }
    }
    if (eTopY  <= oTopY
            && eTopY >= object.getPos().y
            && ePosX > object.getPos().x - 0.2 
            && ePosX < oRightX) {
        if (object.type == string("cube")) {

        if (object.visible) {
        blockedUp = true;
        if (eBottomY > object.getPos().y + object.getDim().y) {
        
           // this->pos.y += this->pos.y + this->pos.y - (this->dim.y - object.getPos().y + object.getDim().y);
        }
        this->vpos.y = -0.1f;
            }
        }
    }
    if (
            eTopY + 0.1 > object.getPos().y &&
            eBottomY + 0.1 < oTopY &&
            eRightX >= object.getPos().x &&
            eRightX <= oRightX)
    {
        if (object.visible) {
        blockedRight = true;
        this->stopX();
        }
        if (string(this->type) == "roboant" ){
            this->left();

        }
    }
    if (
            eTopY + 0.1 > object.getPos().y &&
            eBottomY + 0.1 < oTopY &&
            eLeftX >= object.getPos().x &&
            eLeftX <= oRightX)
    {
        if (object.visible) {
            blockedLeft = true;
            this->stopX();
        }
        if (string(this->type) == "roboant" ){
            this->right();

        }
    }

    }
}
void Entity::collision_entity(float delta, Entity& otherEntity) {
    float ePosX = this->pos.x+this->vpos.x*delta/1000;
    float ePosY = this->pos.y+this->vpos.y*delta/1000;
    float eRightX = ePosX + this->dim.x;
    float eLeftX = ePosX - this->dim.x;
    float eTopY = ePosY + this->dim.y;
    float eBottomY = ePosY - this->dim.y;
    float eCenterX = ePosX + this->dim.x/2;

    float oRightX = otherEntity.getPos().x + otherEntity.getDim().x;
    float oLeftX = otherEntity.getPos().x - otherEntity.getDim().x;

    float oTopY = otherEntity.getPos().y + otherEntity.getDim().y;
    float oBottomY = otherEntity.getPos().y - otherEntity.getDim().y;
    if (this->z == otherEntity.z) { 
    if (eBottomY  <= oTopY
            && eBottomY >= otherEntity.getPos().y
            && eCenterX> otherEntity.getPos().x - 0.2 
            && eCenterX < oRightX) {
        blockedDown = true;
        this->collisionAction(delta, otherEntity, "up");
        if (otherEntity.category == string("enemy")) {
            otherEntity.damage();
            this->stopY();
            this->jump(0.5f);
            if (otherEntity.type == string("blocker")) {
                this->blockersLeft -= 1;
            }
        }
    }
    if (eTopY  <= oTopY
            && eTopY >= otherEntity.getPos().y
            && ePosX > otherEntity.getPos().x - 0.2 
            && ePosX < oRightX) {
        blockedUp = true;
        this->collisionAction(delta, otherEntity, "down");
    }
    if (
            ePosY > otherEntity.getPos().y &&
            ePosY  < oTopY &&
            eRightX >= otherEntity.getPos().x &&
            eRightX <= oRightX)
    {
        this->collisionAction(delta, otherEntity, "side");
    }
    if (
            ePosY > otherEntity.getPos().y &&
            ePosY < oTopY &&
            eLeftX >= otherEntity.getPos().x &&
            eLeftX <= oRightX)
    {
        this->collisionAction(delta, otherEntity, "side");
    }

    }
}
void Entity::collisionAction(float delta, Entity& otherEntity, const char* dir) {

        if (this->type == string("player")) {
            if (dir != "up" && string(otherEntity.category) == "enemy") {
                this->damage();
            }
            if (dir == "up"&& string(otherEntity.type) == "spike") {
                this->damage();
            }
            if (dir == "up" && string(otherEntity.type) == "trampoline") {
                this->jump(2);
            }
            if (dir == "up" && string(otherEntity.type) == "super_trampoline") {
                this->jump(3.5);
            }
            if (dir == "up" && string(otherEntity.type) == "mini_trampoline") {
                this->jump(1.5);
            }
            if (string(otherEntity.type) == "belt_left") {
                this->vpos.x -= 20 * delta / 1000;
            }
            if (string(otherEntity.type) == "belt_right") {
                this->vpos.x += 20 * delta / 1000;
            }
            if (string(otherEntity.type) == "door_next_level") {
                if (IsKeyPressed(KEY_W))
                    this->nextLevel = true; 
            }
            if (string(otherEntity.type) == "coin") {
                this->collectCoin(1);
                otherEntity.damage();
            }
            if (string(otherEntity.type) == "valuable_coin") {
                this->collectCoin(5);
                otherEntity.damage();
            }
            if (string(otherEntity.type) == "token") {
                this->tokens += 1;
                otherEntity.damage();
            }
            if (string(otherEntity.category) == "artifact") {
                this->artifacts.push_back(string(otherEntity.category));
                otherEntity.damage();
            }
            if (string(otherEntity.type) == "ladder") {
                this->mode="ladder";
            }

            }
}
void Entity::render(Camera camera) {
            if (mode == string("normal")) {
                DrawBillboard(camera,this->texs[0],{this->pos.x, this->pos.y, this->pos.z}, this->scale, WHITE);
            }
            else if (mode == string("jump")) {
                DrawBillboard(camera,this->texs[0],{this->pos.x, this->pos.y, this->pos.z}, this->scale, WHITE);
            }
            else if (mode == string("flying")) {
                DrawBillboard(camera,this->texs[0],{this->pos.x, this->pos.y, this->pos.z}, this->scale, WHITE);
            }
            else if (mode == string("ladder")) {
                DrawBillboard(camera,this->texs[0],{this->pos.x, this->pos.y, this->pos.z}, this->scale, WHITE);
            }
            else if (mode == string("cannon")) {
                DrawSphere({this->pos.x + cos(this->rot) * 1.0, this->pos.y + sin(this->rot) * 1.0, this->pos.z}, 0.1, RED);
                DrawBillboard(camera,this->texs[1],{this->pos.x, this->pos.y, this->pos.z}, this->scale, WHITE);
            }
            else if (mode == string("locked")) {
                DrawBillboard(camera,this->texs[1],{this->pos.x, this->pos.y, this->pos.z}, this->scale, WHITE);
           }
}
