#include "generator.h"
#include "perlin.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
using namespace std;
#define ENTITYDIST 128.0f

vector<Entity> generate(vector<Entity> entities, map<string, Texture2D> textures) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> distr(0, 8.0f);
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                float offsetX = distr(gen);
                float offsetZ = distr(gen);
                if (perlin2d(i,j,0.1,1) > 0.8f) {
                    
                        vector<Texture2D> texs;
                       /* int r = rand() % 2;
                        if (r == 0) {
                            texs.push_back(textures["spruce"]);
                        }
                        else if (r == 1) {
                            texs.push_back(textures["pine"]);
                        }
                        else {
                            texs.push_back(textures["oak"]);
                        }*/
                        texs.push_back(textures["spruce"]);
                        entities.push_back(Entity(rand(), 0, "tree", "scenery", 0.0f, {(float)i - 16.0 + offsetX,8.0f,(float) j - ENTITYDIST - offsetZ}, -1,{0.4f,0.25f,0.1f}, 10.0f, texs));
                }
            }
        }
        return entities;
}

