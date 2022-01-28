#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <raylib.h>
#include "object.h"
using namespace std;
class Level {
    private:
        vector<Object> objects; 
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
                    if (bytes[i * levelSize + j] == '1')
                    this->objects.push_back(Object({(float) j ,(float) -i + levelSize ,0.0f},{1.0f,1.0f,1.0f}, models["cube"]));

                }

            }
            file.close();
        }
    vector<Object> getObjects();
};
