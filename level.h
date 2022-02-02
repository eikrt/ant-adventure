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
        float startZ;
        string title;
        vector<vector<char>> bytes;
        map<string,Model> models;
        map<string, Texture2D> textures;
        Level(string title, string path, map<string,Model> models, map<string, Texture2D> textures) {
            this->bytes.push_back(vector<char>());
            this->bytes.push_back(vector<char>());
            this->bytes.push_back(vector<char>());
            this->models = models;
            this->textures = textures;
            this->title = title;
            for (int i = 0; i < 3; i++) { 
                char byte = 0;
                ifstream file(path + to_string(i)); 
                    while (file.get(byte)) {
                        if (byte != '\n')
                            this->bytes[i].push_back(byte);
                        
                    }

            file.close();
            }
            
        }
    void initLevel();
    void reset();
    vector<Object> getObjects();
    vector<Entity> getEntities();
};
#endif
