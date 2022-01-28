#include <vector>
#include "level.h"
#include "entity.h"
using namespace std;
vector<Object> Level::getObjects() {
    return this->objects;
}
vector<Entity> Level::getEntities() {
    return this->entities;
}
