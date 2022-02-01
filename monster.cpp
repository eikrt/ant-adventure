#include "monster.h"
#include "entity.h"
#include <iostream> 
using namespace std;
void Monster::tick(float delta) {
    Entity::tick(delta);
    if (this->type == "fungus") {
    }
}
