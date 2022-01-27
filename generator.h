#ifndef GENERATOR_H
#define GENERATOR_H
#include "entity.h"
#include <vector>
#include <string>
#include <map>
using namespace std;
vector<Entity> generate(vector<Entity> entities, map<string, Texture2D> textures);

#endif 
