#include "generator.h"
#include "perlin.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
using namespace std;
#define ENTITYDIST 280.0f
#define CLOUDDIST 450.0f
vector<Object> generate_objects(vector<Object> objects, map<string, Model> models) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> distr(0, 8.0f);
        uniform_real_distribution<> distr2(0, 32.0f);
        uniform_real_distribution<> distr3(0, 64.0f);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                float offsetX = distr2(gen);
                float offsetZ = distr2(gen);
                float offsetY = distr3(gen);
                    
            }
        }
        return objects;
}


vector<Entity> generate_entities(vector<Entity> entities, map<string, Texture2D> textures) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> distr(0, 8.0f);
        uniform_real_distribution<> distr2(0, 32.0f);
        uniform_real_distribution<> distr3(0, 64.0f);
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 20; j++) {
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
                        entities.push_back(Entity(rand(), 0, "tree", "scenery", 0.0f, {(float)i - 128.0 + offsetX,5.0f,(float) j - ENTITYDIST - offsetZ}, -1,{0.4f,0.25f,0.1f}, 10.0f, texs));
                }
            }
        }
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                float offsetX = distr2(gen);
                float offsetZ = distr2(gen);
                float offsetY = distr3(gen);
                    
                       /* vector<Texture2D> texs;
                         texs.push_back(textures["cloud_2"]);
                        entities.push_back(Entity(rand(), 0, "cloud", "scenery", 0.0f, {(float)i * 200.0f - 128.0f,155.0f,(float) j - CLOUDDIST - offsetZ}, -1,{0.4f,0.25f,0.1f}, 100.0f, texs));*/
            }
        }
        return entities;
}

