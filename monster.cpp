#include "monster.h"
#include "entity.h"
#include <iostream> 
using namespace std;
void Monster::tick() {
    Entity::tick();
    if (this->type == "fungus") {
    }
}
