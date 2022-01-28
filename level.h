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
                    if (bytes[i * levelSize + j] == 'f') {
                        Entity entity = Entity(rand(), "fungus", 0.03f, {(float)x,y+1.0f,0.0f},{0.4f,0.5f,0.1f}, 1.0f, textures["fungus"]);
                        entity.left();
                        this->entities.push_back(entity);


                    }

                }
            }
            file.close();
        }
    vector<Object> getObjects();
    vector<Entity> getEntities();
};
