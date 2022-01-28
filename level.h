#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <raylib.h>
#include "object.h"
#include "entity.h"
using namespace std;
class Level {
    private:
        vector<Object> objects; 
        vector<Entity> entities; 
    public:
        Level(string path, map<string,Model> models, map<string, Texture2D> textures) {
             vector<char> bytes;
             char byte = 0;
             
             ifstream file(path);
            while (file.get(byte)) {
                if (byte != '\n')
                bytes.push_back(byte);
            }
            int levelSize = sqrt(bytes.size());
            for (int i = 0; i < levelSize; i++) {
                for (int j = 0; j < levelSize; j++) {
                    float x = j;
                    float y = -i + levelSize;
                    if (bytes[i * levelSize + j] == '1')
                    this->objects.push_back(Object({(float) x ,(float) y,0.0f},{1.0f,1.0f,1.0f}, models["cube"]));
                    if (bytes[i * levelSize + j] == 'f')
                    this->entities.push_back(Entity({(float)x,y+0.5f,0.0f},{0.4f,0.25f,0.1f}, 1.0f, textures["fungus"]));

                }

            }
            file.close();
        }
    vector<Object> getObjects();
    vector<Entity> getEntities();
};
