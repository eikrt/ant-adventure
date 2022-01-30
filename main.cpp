#include <raylib.h>
#include <iostream>
#include "player.h"
#include "monster.h"
#include "button.h"
#include "scenery.h"
#include "level.h"
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
const float SCENEDIST =0.0f;
#define WIDTH 640
#define HEIGHT 420
#define CAMERAY 8.0
#define CAMERAZ 15.0
#define TARGETY 6.0
using namespace std;

int main(int argc, char* argv[])
{
    enum Mode {overworld, game, mainMenu, gameOver};
    Mode currentMode = mainMenu;
    const int screenWidth = 1024;
    const int screenHeight = 576;
    int currentLevel = 0;
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    InitWindow(screenWidth, screenHeight, "Ant Adventure");

    SetTargetFPS(60);

    SetExitKey(KEY_DELETE);
    

    // physics
    Camera camera = {
            .position = {0.0f, CAMERAY, CAMERAZ},
            .target   = {0.0f, TARGETY, 0.0f},
            .up       = {0.0f, 1.0f, 0.0f},
            .fovy     = 50.0f,
    };

    // fonts
    Font fonts[1] = {0};
    fonts[0] = LoadFont("fonts/romulus.png");
    int levelAlpha = 255;
    int selectedButton = 0;
    map<string, Model> models;
    map<string, Texture2D> textures;
    models["cube_0"] = LoadModel("models/cube.obj");
    models["cube_1"] = LoadModel("models/cube.obj");
    models["cube_2"] = LoadModel("models/cube.obj");
    models["ground"] = LoadModel("models/scenery.obj");

    textures["player"] = LoadTexture("res/ant_worker_side_1.png");
    textures["roboant"] = LoadTexture("res/mechant.png");
    textures["spruce"] = LoadTexture("res/spruce.png");
    textures["stoneBrick"] = LoadTexture("res/stone_brick.png");
    textures["grass"] = LoadTexture("res/grass.png");
    textures["fungus"] = LoadTexture("res/fungus_monster.png");
    textures["egg"] = LoadTexture("res/ant_egg_4.png");
    textures["coin"] = LoadTexture("res/leaf.png");
    textures["mainMenuButton0"] = LoadTexture("res/menu_button.png");
    textures["mainMenuButton1"] = LoadTexture("res/menu_button_hovered.png");
    textures["mainMenuButton2"] = LoadTexture("res/menu_button_pressed.png");
    vector<Texture2D> buttonTextures;
    buttonTextures.push_back(textures["mainMenuButton0"]);
    buttonTextures.push_back(textures["mainMenuButton1"]);
    buttonTextures.push_back(textures["mainMenuButton2"]);
    vector<Button> mainMenuButtons;
    mainMenuButtons.push_back(Button({32.0, 32.0}, buttonTextures));
    vector<Button> gameOverButtons;
    gameOverButtons.push_back(Button({32.0, 32.0}, buttonTextures));
    models["cube_0"].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textures["stoneBrick"];
    models["cube_1"].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textures["stoneBrick"];
    models["cube_2"].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textures["stoneBrick"];
    models["ground"].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textures["grass"];
    vector<Texture2D> texs;
    texs.push_back(textures["player"]);
    texs.push_back(textures["egg"]);
    Entity player(0, "player", "player", 0.05f, {0.1f,8.0f,SCENEDIST},{0.4f,0.5f,0.1f}, 1.0f, texs);
    vector<Level> levels;
    levels.push_back(Level("levels/level_0_", models, textures));
    // start position
    camera.position = {levels[currentLevel].startPos.x,levels[currentLevel].startPos.y + 8,levels[currentLevel].startPos.z + 15};
    camera.target = {levels[currentLevel].startPos.x,levels[currentLevel].startPos.y + 6,levels[currentLevel].startPos.z};
    player.pos.x = levels[currentLevel].startPos.x;
    player.pos.y = levels[currentLevel].startPos.y;
    player.pos.z = levels[currentLevel].startPos.z;
    vector<Scenery> scenes;
    
    scenes.push_back(Scenery({0.0f,-1.0f,0.0f},{200.0f,0.0f,200.0f}, models["ground"], textures));
    float gravity = 0.008f;
    RenderTexture2D target = LoadRenderTexture(WIDTH, HEIGHT);

    // shaders
        map<const char*, Shader> shaders;
        shaders["default"] = LoadShader(TextFormat("shaders/base_lightning.vs"), TextFormat("shaders/lightning.fs"));
        shaders["default"].locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shaders["default"], "viewPos");
        models["cube_0"].materials[0].shader = shaders["default"];
        while (!WindowShouldClose())
        {
            if (currentMode == mainMenu) {
                if (IsKeyDown(KEY_DOWN)) {
                    if (selectedButton < mainMenuButtons.size() - 1) {
                        selectedButton+=1;
                        
                    }
                }
                if (IsKeyDown(KEY_UP)) {
                    if (selectedButton > 0) {
                        selectedButton-=1;
                    }
                }
                if (IsKeyDown(KEY_SPACE)) {
                    if (selectedButton == 0) {
                        currentMode = game;
                    }
                }
            BeginDrawing();
                ClearBackground(RAYWHITE);
                mainMenuButtons[selectedButton].selected = true;
                for (auto& b : mainMenuButtons) {

                    b.render(camera);
                    b.tick();
                }
                EndDrawing();
            }
            else if (currentMode == gameOver) {
                if (IsKeyDown(KEY_DOWN)) {
                    if (selectedButton < gameOverButtons.size() - 1) {
                        selectedButton+=1;
                        
                    }
                }
                if (IsKeyDown(KEY_UP)) {
                    if (selectedButton > 0) {
                        selectedButton-=1;
                    }
                }
                if (IsKeyDown(KEY_SPACE)) {
                    if (selectedButton == 0) {
                        exit(0);
                    }
                }
            BeginDrawing();
                ClearBackground(RAYWHITE);
                gameOverButtons[selectedButton].selected = true;
                for (auto& b : gameOverButtons) {

                    b.render(camera);
                    b.tick();
                }
                EndDrawing();

            }
            else if (currentMode == game) {
            float cameraW = 10.0f;
            float cameraH = 6.0f;
            if (player.getPos().x - camera.position.x > cameraW) {
            
                camera.position.x = player.getPos().x + cameraW;
                camera.target.x = player.getPos().x + cameraW;
            }
            else if (player.getPos().x - camera.position.x < -cameraW) {
                camera.position.x = player.getPos().x - cameraW;
                camera.target.x = player.getPos().x - cameraW;
            }
            if (player.getPos().y - camera.position.x > cameraH) {
            
                camera.position.y = player.getPos().y + cameraH + CAMERAY;
                camera.target.y = player.getPos().y + cameraH + CAMERAY;
            }
            else if (player.getPos().y - camera.position.y < -cameraH) {
                camera.position.y = player.getPos().y - cameraH + CAMERAY;
                camera.target.y = player.getPos().y - cameraH + CAMERAY;
            }

            player.tick(gravity);
            if (player.getHp() <= 0) {
                currentMode = gameOver;
            }

            for (auto &e : levels[currentLevel].entities) {
                if (e.getHp() <= 0) {
                    continue;
                }

                for (auto &obj : levels[currentLevel].getObjects()) {
                    if (obj.getHp() <= 0) {
                        continue;
                    }
                    e.collision_object(obj);
                }
                e.tick(gravity);
            }
            for (auto &obj : levels[currentLevel].getObjects()) {
                if (obj.getHp() <= 0) {
                    continue;
                }
                player.collision_object(obj);
            }
            for (auto &e : levels[currentLevel].entities) {
                if (e.getHp() <= 0) {
                    continue;
                }
                player.collision_entity(e);
            }
           // player.collision_object(ground);
            //player.collision_object(cube);
            BeginTextureMode(target);
            {
                ClearBackground(SKYBLUE);

                if (IsKeyPressed(KEY_SPACE)) {
                    if (player.mode == string("normal")) {
                        player.jump();

                    } else if (player.mode == string("jump")) {
                        player.cannon();
                    }
                    else if (player.mode == string("cannon")) {
                        player.launch();
                    }
                }
                if (IsKeyDown(KEY_D)){
                    if (player.mode == string("jump") || player.mode == string("normal"))
                        player.right();
                }
                if (IsKeyDown(KEY_A)) {
                    if(player.mode == string("jump") || player.mode == string("normal")) 
                        player.left();
                }
                if (IsKeyPressed(KEY_A)){
                    if(player.mode == string("cannon")) 
                        player.tilt(3.14/4);
                }
                if (IsKeyPressed(KEY_D)) {
                    if(player.mode == string("cannon")) 
                        player.tilt(-3.14/4);
                }
                if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)){
                    if (player.mode == string("normal") || (player.mode == string("jump")))
                    player.slowX();
                }
                if (IsKeyPressed(KEY_W)) {
                    player.back();
                }
                if (IsKeyPressed(KEY_S)) {
                    player.forward();
                }
                BeginMode3D(camera);
                    for (auto &obj : levels[currentLevel].getObjects()) {

                        if (obj.getHp() <= 0) {
                            continue;
                        }
                        obj.render(camera);
                    }
                    for (auto &e : levels[currentLevel].getEntities()) {

                    if (e.getHp() <= 0) {
                        continue;
                    }
                    e.render(camera);
                }
                for (auto &s : scenes) {
                    s.render(camera);
                }
            player.render(camera);
            EndMode3D();
            EndTextureMode();

        }
        BeginDrawing();
            DrawTexturePro(target.texture, (Rectangle){0, 0, (float)WIDTH, (float)-HEIGHT},{0,0,(float)screenWidth, (float)screenHeight} ,Vector2{0, 0}, 0, WHITE);
            if (levelAlpha > 0) {
                levelAlpha -= 2;
            }
            else {
                levelAlpha = 0;
            }
            // level texts
            if (levelAlpha > 0) {
            DrawTextEx(fonts[0], "Ruins", {screenWidth / 2 - 16,screenHeight / 2},18, 2, {255,255,255, levelAlpha});
            }
            // hud
            DrawTextEx(fonts[0], (string("Leafs: ") + to_string(player.coins)).c_str(), {screenWidth - 90,screenHeight - 16},18, 2, {255,255,255, 255});
        EndDrawing();
    }
    }
    

    // end stuff
    for (auto const& t : textures) {
        UnloadTexture(t.second);
    }
    for (auto const& m : models) {
        UnloadModel(m.second);
    }
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}

