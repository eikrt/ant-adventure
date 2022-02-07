#include <vector>
#include "level.h"
#include "entity.h"
using namespace std;
void Level::initLevel() {
    this->levelSize = sqrt(this->bytes[0].size());
    this->reset();
    for (int k = 0; k < this->bytes.size(); k++) 
    {
        for (int h = 0; h < levelSize / this->chunkSize; h++) {
            this->chunks.push_back(vector<Chunk>());
            for (int n = 0; n < levelSize / this->chunkSize; n++) {
            this->chunks[h].push_back(Chunk());
                for (int i = h * this->chunkSize; i < h * this->chunkSize +  this->chunkSize; i++) {
                    for (int j = n * this->chunkSize; j < n * this->chunkSize + this->chunkSize; j++) {
                        float x = j;
                        float y = -i + levelSize - 2.0;
                        float z = 0.0;
                        float gz = 0.3;
                        if (k == 0) {
                            z = -1.0; 
                        } 
                        if (k == 1) {
                            z = 0.0; 
                        } 
                        if (k == 2) {
                            z = 1.0;
                        }
                        if (k == 3) {
                            z = 2.0;
                        } 
                        if (this->bytes[k][i * levelSize + j] == '|'){
                            this->chunks[h][n].objects.push_back(Object({(float) x ,(float) y,z},z, 0.0f, {1.0f,1.0f,1.0f}, false,"cube", this->models["stone_brick_dark"]));
                        }
                        if (this->bytes[k][i * levelSize + j] == '1'){
                            float f = (float)rand()/(float)(RAND_MAX/0.2);
                            this->chunks[h][n].objects.push_back(Object({(float) x ,(float) y,z + f},z, 0.0f,{1.0f,1.0f,1.0f}, true, "cube", this->models["stone_brick_dark"]));
                        }
                        if (this->bytes[k][i * levelSize + j] == '2'){
                            float fz = (float)rand()/(float)(RAND_MAX/0.2);
                            float fy = (float)rand()/(float)(RAND_MAX/0.1);
;
                            this->chunks[h][n].objects.push_back(Object({(float) x ,(float) y,z + fz},z, fy, {1.0f,1.0f,1.0f}, true, "cube", this->models["stone_brick_light"]));
                        }
                        if (this->bytes[k][i * levelSize + j] == 'w') {
                            for (int l = 0; l < 3; l++) {
                                this->chunks[h][n].objects.push_back(Object({(float) x ,(float) y,l},l, 0.0f, {1.0f,1.0f,1.0f}, true,"water", this->models["water_1"]));


                            }
                        }

                        if (this->bytes[k][i * levelSize + j] == 'f'){
                            float f = (float)rand()/(float)(RAND_MAX/0.2);
                            this->chunks[h][n].objects.push_back(Object({(float) x ,(float) y,z},z, 0.0, {1.0f,1.0f,1.0f}, true, "floor", this->models["stone_brick_light"]));
                        }
                        if (this->bytes[k][i * levelSize + j] == '^'){
                            float f = (float)rand()/(float)(RAND_MAX/0.2);
                            this->chunks[h][n].objects.push_back(Object({(float) x ,(float) y,z},z, 0.0, {1.0f,1.0f,1.0f}, true, "moving_cube_up", this->models["stone_brick_dark"]));
                        }
                        if (this->bytes[k][i * levelSize + j] == '_'){
                            float f = (float)rand()/(float)(RAND_MAX/0.2);
                            this->chunks[h][n].objects.push_back(Object({(float) x ,(float) y,z},z, 0.0, {1.0f,1.0f,1.0f}, true, "moving_cube_side", this->models["stone_brick_dark"]));
                        }

                        if (this->bytes[k][i * levelSize + j] == 'r') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["roboant"]);

                            Entity entity = Entity(rand(), 0.01, "roboant", "enemy", 3.0f, {(float)x+0.5f,y+0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            entity.left();
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == '[') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["fungus_monster"]);

                            Entity entity = Entity(rand(), 30.0f, "fungus_monster", "enemy", 3.0f, {(float)x+0.5f,y+0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == ']') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["fungus_monster"]);

                            Entity entity = Entity(rand(), 30.0f, "fungus_monster_higher", "enemy", 3.0f, {(float)x+0.5f,y+0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == 'i') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["bird"]);
                            Entity entity = Entity(rand(), 0.00, "bird", "enemy", 3.0f, {(float)x,y+1.0f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == 'c') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["coin"]);
                            Entity entity = Entity(rand(), 0, "coin", "collectible", 0.03f, {(float)x + 0.5f,y+0.5f, z+ gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == 'v') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["valuable_coin"]);
                            Entity entity = Entity(rand(), 0, "valuable_coin", "collectible", 0.03f, {(float)x + 0.5,y+0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == '.') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["blocker"]);
                            Entity entity = Entity(rand(), 0, "blocker", "enemy", 0.03f, {(float)x + 0.5,y+0.5f,z + gz},z, {1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == 'd') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["door_next_level"]);
                            texs.push_back(this->textures["door_next_level_locked"]);
                            Entity entity = Entity(rand(), 0, "door_next_level", "prop", 0.03f, {(float)x + 0.5,y+0.5f + 0.2f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            entity.moveMode = string("locked");

                            this->chunks[h][n].entities.push_back(entity);

                        }
                        if (this->bytes[k][i * levelSize + j] == '<') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["belt"]);
                            Entity entity = Entity(rand(), 0, "belt_left", "prop", 0.03f, {(float)x + 0.5,y+0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == '>') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["belt"]);
                            Entity entity = Entity(rand(), 0, "belt_right", "prop", 0.03f, {(float)x + 0.5,y+0.5f,z + gz},z, {1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }

                        if (this->bytes[k][i * levelSize + j] == '*') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["treasure"]);
                            Entity entity = Entity(rand(), 0, "diamond", "artifact",0.03f, {(float)x + 0.5f,y+0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == 't') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["token"]);
                            Entity entity = Entity(rand(), 0, "token", "collectible", 0.03f, {(float)x + 0.5f,y+0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == 'l') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["ladder"]);
                            Entity entity = Entity(rand(), 0, "ladder", "collectible", 0.03f, {(float)x + 0.5f,y+0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == 'b') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["trampoline"]);
                            Entity entity = Entity(rand(), 0, "trampoline", "prop", 0.03f, {(float)x+0.5f,y+0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == 'y') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["trampoline"]);
                            Entity entity = Entity(rand(), 0, "super_trampoline", "prop", 0.03f, {(float)x+0.5f,y+0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == 'u') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["trampoline"]);
                            Entity entity = Entity(rand(), 0, "mini_trampoline", "prop", 0.03f, {(float)x+0.5f,y+0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == 's') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["spike"]);
                            Entity entity = Entity(rand(), 0, "spike", "prop", 0.00f, {(float)x + 0.5f,y + 0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == '+') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["key"]);
                            Entity entity = Entity(rand(), 10.0f, "key", "carriable", 0.00f, {(float)x + 0.5f,y + 0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == '-') {
                            vector<Texture2D> texs;
                            texs.push_back(this->textures["key_door"]);
                            Entity entity = Entity(rand(), 0, "key_door", "prop", 0.00f, {(float)x + 0.5f,y + 0.5f,z + gz},z,{1.0f,0.5f,0.1f}, 1.0f, texs);
                            this->chunks[h][n].entities.push_back(entity);


                        }
                        if (this->bytes[k][i * levelSize + j] == 'p') {
                            this->startPos = {x,y+1.0,z};
                            startZ = z;
                        }

                    }

                }

            }//
        }
    }
}
void Level::reset() {
    for (int i = 0; i < this->chunks.size(); i++) {
    for (int j = 0; j < this->chunks.size(); j++) {
        this->chunks.clear();
        }
    }
}
