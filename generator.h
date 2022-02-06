#ifndef GENERATOR_H
#define GENERATOR_H
#include "entity.h"
#include <vector>
#include <string>
#include <map>
using namespace std;
vector<Entity> generate_entities(vector<Entity> entities, map<string, Texture2D> textures);
vector<Object> generate_objects(vector<Object> objects, map<string, Model> models);

#endif 
