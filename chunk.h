#ifndef CHUNK_H
#define CHUNK_H
#include <vector>
#include "entity.h"
#include "object.h"
using namespace std;
class Chunk {
    public:
        vector<Entity> entities;
        vector<Object> objects;
    Chunk() {

    }
    void clear();
};
#endif
