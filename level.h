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
        Vector3 startPos;
        string title;
        Level(string title, string path, map<string,Model> models, map<string, Texture2D> textures) {
            vector<vector<char>> bytes;
            bytes.push_back(vector<char>());
            bytes.push_back(vector<char>());
            bytes.push_back(vector<char>());
            this->title = title;
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
                       z = -2; 
                    } 
                    if (k == 1) {
                       z = -1; 
                    } 
                    if (k == 2) {
                        z = 0;
                    }
                    if (k == 3) {
                        z = 1;
                    } 
                    if (bytes[k][i * levelSize + j] == '1'){
                        this->objects.push_back(Object({(float) x ,(float) y,z},{1.0f,1.0f,1.0f}, "cube", models["stone_brick_dark"]));
                        }
                    if (bytes[k][i * levelSize + j] == '2'){
                        this->objects.push_back(Object({(float) x ,(float) y,z},{1.0f,1.0f,1.0f}, "cube", models["stone_brick_light"]));
                        }

                    if (bytes[k][i * levelSize + j] == 'f'){
                        this->objects.push_back(Object({(float) x ,(float) y,z},{1.0f,1.0f,1.0f}, "floor", models["stone_brick_light"]));
                        }

                        if (bytes[k][i * levelSize + j] == 'r') {
                            vector<Texture2D> texs;
                            texs.push_back(textures["roboant"]);
                            Entity entity = Entity(rand(), 0.01, "roboant", "enemy", 0.03f, {(float)x,y+1.0f,z},{1.0f,0.5f,0.1f}, 1.0f, texs);
                            entity.left();
                            this->entities.push_back(entity);


                        }
                        if (bytes[k][i * levelSize + j] == 'i') {
                            vector<Texture2D> texs;
                            texs.push_back(textures["bird"]);
                            Entity entity = Entity(rand(), 0.00, "bird", "enemy", 0.03f, {(float)x,y+1.0f,z},{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->entities.push_back(entity);


                        }
                        if (bytes[k][i * levelSize + j] == 'c') {
                            vector<Texture2D> texs;
                            texs.push_back(textures["coin"]);
                            Entity entity = Entity(rand(), 0, "coin", "collectible", 0.03f, {(float)x,y+1.0f,z},{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->entities.push_back(entity);


                        }
                        if (bytes[k][i * levelSize + j] == 'v') {
                            vector<Texture2D> texs;
                            texs.push_back(textures["valuable_coin"]);
                            Entity entity = Entity(rand(), 0, "valuable_coin", "collectible", 0.03f, {(float)x,y+1.0f,z},{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->entities.push_back(entity);


                        }
                        if (bytes[k][i * levelSize + j] == 'a') {
                            vector<Texture2D> texs;
                            texs.push_back(textures["treasure"]);
                            Entity entity = Entity(rand(), 0,"treasure", "collectible",0.03f, {(float)x,y+1.0f,z},{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->entities.push_back(entity);


                        }
                        if (bytes[k][i * levelSize + j] == 't') {
                            vector<Texture2D> texs;
                            texs.push_back(textures["token"]);
                            Entity entity = Entity(rand(), 0, "token", "collectible", 0.03f, {(float)x,y+1.0f,z},{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->entities.push_back(entity);


                        }
                        if (bytes[k][i * levelSize + j] == 'l') {
                            vector<Texture2D> texs;
                            texs.push_back(textures["ladder"]);
                            Entity entity = Entity(rand(), 0, "ladder", "collectible", 0.03f, {(float)x,y+1.0f,z},{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->entities.push_back(entity);


                        }
                        if (bytes[k][i * levelSize + j] == 'b') {
                            vector<Texture2D> texs;
                            texs.push_back(textures["trampoline"]);
                            Entity entity = Entity(rand(), 0, "trampoline", "prop", 0.03f, {(float)x,y+1.0f,z},{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->entities.push_back(entity);


                        }
                        if (bytes[k][i * levelSize + j] == 's') {
                            vector<Texture2D> texs;
                            texs.push_back(textures["spike"]);
                            Entity entity = Entity(rand(), 0, "spike", "prop", 0.03f, {(float)x,y+1.0f,z},{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->entities.push_back(entity);


                        }
                        if (bytes[k][i * levelSize + j] == 'p') {
                            this->startPos = {x,y+1.0,z};
                        }

                }
            }
        }
        }
    vector<Object> getObjects();
    vector<Entity> getEntities();
};
#endif
