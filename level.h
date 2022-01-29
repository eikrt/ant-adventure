#ifndef LEVEL_H
#define LEVEL_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <raylib.h>
#include "object.h"
#include "entity.h"
#include "monster.h"
using namespace std;
class Level {
    private:
    public:
        vector<Object> objects; 
        vector<Entity> entities; 
        Level(string path, map<string,Model> models, map<string, Texture2D> textures) {
            vector<vector<char>> bytes;
            bytes.push_back(vector<char>());
            bytes.push_back(vector<char>());
            bytes.push_back(vector<char>());
            for (int i = 0; i < 3; i++) { 
                char byte = 0;
                ifstream file(path + to_string(i)); 
                    while (file.get(byte)) {
                        if (byte != '\n')
                            bytes[i].push_back(byte);
                        
                    }

            file.close();
            }
            int levelSize = sqrt(bytes[0].size());
            for (int k = 0; k < bytes.size(); k++) {
            for (int i = 0; i < levelSize; i++) {
                for (int j = 0; j < levelSize; j++) {
                    float x = j;
                    float y = -i + levelSize - 2.0;
                    float z = 0.0;
                    if (k == 0) {
                       z = -1; 
                    } 
                    if (k == 1) {
                        z = 0;
                    }
                    if (k == 2) {
                        z = 1;
                    } 

                    if (bytes[k][i * levelSize + j] == '1'){
                        this->objects.push_back(Object({(float) x ,(float) y,z},{1.0f,1.0f,1.0f}, models["cube"]));
                        }
                        if (bytes[k][i * levelSize + j] == 'f') {
                            Entity entity = Entity(rand(), "roboant", "enemy", 0.03f, {(float)x,y+1.0f,z},{1.0f,0.5f,0.1f}, 1.0f, textures["roboant"]);
                            entity.left();
                            this->entities.push_back(entity);


                        }

                }
            }
        }
        }
    vector<Object> getObjects();
    vector<Entity> getEntities();
};
#endif
