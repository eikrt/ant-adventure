#include "monster.h"
#include "entity.h"
#include <iostream> 
using namespace std;
void Monster::tick(float gravity) {
    Entity::tick(gravity);
    if (this->type == "fungus") {
    }
}
