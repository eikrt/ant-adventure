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
#include <clocale>
#include <math.h>
#include "raymath.h"
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"
const float SCENEDIST = 0.0f;
//#define WIDTH 640
//#define HEIGHT 420
#define WIDTH 1024
#define HEIGHT 576
#define CAMERAY 16.0
#define CAMERAZ 15.0
#define TARGETY 6.0
#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif
const float SCREENMARGIN_X = 256.0;
const float SCREENMARGIN_Y = 64.0;
using namespace std;
void startLevel(Camera& camera, Entity& player, Level& level, vector<Level> levels, int currentLevel) {
    player.hp = 1;
    player.coins = 0;
    player.tokens = 0;
    level.initLevel();
    camera.position = {levels[currentLevel].startPos.x,levels[currentLevel].startPos.y + 8,levels[currentLevel].startPos.z + 15};
    camera.target = {levels[currentLevel].startPos.x,levels[currentLevel].startPos.y + 6,levels[currentLevel].startPos.z};
    player.hp = 1;
    player.pos.x = levels[currentLevel].startPos.x + 0.1f;
    player.pos.y = levels[currentLevel].startPos.y;
    player.pos.z = levels[currentLevel].startPos.z + 0.5f;
    player.z = levels[currentLevel].startPos.z;
    player.blockersLeft = 2; 

}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "utf-8");
    enum Mode {overworld, game, mainMenu, gameOver};
    Mode currentMode = mainMenu;
    const int screenWidth = 1024;
    const int screenHeight = 576;
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
            .projection = CAMERA_PERSPECTIVE
    };
    float cvx = 0.0f;
    float cvy = 0.0f;
    SetCameraMode(camera, CAMERA_CUSTOM);
    // fonts
    Font fonts[1] = {0};
    fonts[0] = LoadFont("fonts/romulus.png");
    int levelAlpha = 255;
    int selectedButton = 0;
    map<string, Model> models;
    map<string, Texture2D> textures;
    models["stone_brick_dark"] = LoadModel("models/cube_larger.obj");
    models["stone_brick_light"] = LoadModel("models/cube.obj");
    models["ground"] = LoadModel("models/scenery.obj");

    textures["player"] = LoadTexture("res/ant_worker_side_1.png");
    textures["roboant"] = LoadTexture("res/mechant.png");
    textures["spruce"] = LoadTexture("res/spruce.png");
    textures["stone_brick_dark"] = LoadTexture("res/medieval_stone_bricks_dark.png");
    textures["stone_brick_light"] = LoadTexture("res/medieval_stone_bricks_dark.png");
    textures["grass"] = LoadTexture("res/grass.png");
    textures["fungus"] = LoadTexture("res/fungus_monster.png");
    textures["bird"] = LoadTexture("res/stinger.png");
    textures["egg"] = LoadTexture("res/ant_egg_4.png");
    textures["coin"] = LoadTexture("res/leaf.png");
    textures["valuable_coin"] = LoadTexture("res/autumn_leaf.png");
    textures["treasure"] = LoadTexture("res/diamond.png");
    textures["token"] = LoadTexture("res/token.png");
    textures["ladder"] = LoadTexture("res/ladder.png");
    textures["spike"] = LoadTexture("res/spikes.png");
    textures["trampoline"] = LoadTexture("res/trampoline.png");
    textures["blocker"] = LoadTexture("res/blocker.png");
    textures["belt"] = LoadTexture("res/belt.png");
    textures["door_next_level"] = LoadTexture("res/door_next_level.png");
    textures["door_next_level_locked"] = LoadTexture("res/door_next_level_locked.png");
    textures["mainMenuButton0"] = LoadTexture("res/menu_button.png");
    textures["mainMenuButton1"] = LoadTexture("res/menu_button_hovered.png");
    textures["mainMenuButton2"] = LoadTexture("res/menu_button_pressed.png");
    vector<Texture2D> buttonTextures;
    buttonTextures.push_back(textures["mainMenuButton0"]);
    buttonTextures.push_back(textures["mainMenuButton1"]);
    buttonTextures.push_back(textures["mainMenuButton2"]);
    vector<Button> mainMenuButtons;
    mainMenuButtons.push_back(Button({32.0, 64.0},"Play", fonts[0], buttonTextures));
    mainMenuButtons.push_back(Button({32.0, 110.0},"Quit", fonts[0], buttonTextures));
    vector<Button> gameOverButtons;
    gameOverButtons.push_back(Button({32.0, 64.0},"Continue", fonts[0], buttonTextures));
    gameOverButtons.push_back(Button({32.0, 120.0},"Quit", fonts[0], buttonTextures));
    models["stone_brick_light"].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textures["stone_brick_light"];
    models["stone_brick_dark"].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textures["stone_brick_dark"];
    models["ground"].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textures["grass"];
    vector<Texture2D> texs;
    texs.push_back(textures["player"]);
    texs.push_back(textures["egg"]);
    
    Entity player(0, 20, "player", "player", 5.0f, {0.5f,8.0f,SCENEDIST},SCENEDIST,{0.4f,0.5f,0.1f}, 1.0f, texs);
    int currentLevel = 2;
    // levels
    int chunkX = 0, chunkY = 0;
    // start position
    
    vector<Scenery> scenes;
    
    scenes.push_back(Scenery({0.0f,-1.0f,0.0f},{200.0f,0.0f,200.0f}, models["ground"], textures));
    RenderTexture2D target = LoadRenderTexture(WIDTH, HEIGHT);
    int chunkW = 2;
    int chunkH = 2;
    // shaders
        map<const char*, Shader> postShaders;
        postShaders["bloom"] = LoadShader(0, TextFormat("shaders/bloom.fs"));
        postShaders["pixelizer"] = LoadShader(0, TextFormat("shaders/pixelizer.fs"));
        postShaders["posterization"] = LoadShader(0, TextFormat("shaders/posterization.fs"));
        map<const char*, Shader> shaders;
        shaders["default"] = LoadShader(TextFormat("shaders/base_lightning.vs"), TextFormat("shaders/lightning.fs"));
        shaders["default"].locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shaders["default"], "viewPos");
        int ambientLoc = GetShaderLocation(shaders["default"], "ambient");
        float dim[4] = {0.2f,0.2f,0.2f,0.2f};
        SetShaderValue(shaders["default"], ambientLoc, dim, SHADER_UNIFORM_VEC4);
        Light lights[4] = { 0 };
        lights[0] = CreateLight(LIGHT_POINT, (Vector3){ 10, 100, 10 }, Vector3Zero(), {215,215,190,255}, shaders["default"]);
        lights[0].enabled = true;
    vector<Level> levels;
    levels.push_back(Level("Test Level", "levels/level_0_", models, textures));
    levels.push_back(Level("Ruins", "levels/level_1_", models, textures));
    levels.push_back(Level("Ruins", "levels/level_2_", models, textures));
    startLevel(camera,player,levels[currentLevel],levels,currentLevel);
        for (auto &m : models) {
            m.second.materials[0].shader = shaders["default"];
        }
        //models["cube_0"].materials[0].shader = shaders["default"];
        while (!WindowShouldClose())
        {
            float delta = GetFrameTime() * 1000.0f;
            if (currentMode == mainMenu) {
                if (IsKeyDown(KEY_DOWN)||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
                    if (selectedButton < mainMenuButtons.size() - 1) {
                        selectedButton+=1;
                        
                    }
                }
                if (IsKeyDown(KEY_UP)||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
                    if (selectedButton > 0) {
                        selectedButton-=1;
                    }
                }
                if (IsKeyDown(KEY_SPACE)||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
                    if (selectedButton == 0) {
                        currentMode = game;
                    }
                }
            BeginDrawing();
                ClearBackground(BROWN);
                mainMenuButtons[selectedButton].selected = true;
                for (auto& b : mainMenuButtons) {

                    b.render(camera);
                    b.tick();
                }
                DrawTextEx(fonts[0], "Ant Adventure", {16,16},18, 2, {255,255,255, 255});
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
            UpdateCamera(&camera);
            for (auto &l : lights) {
                UpdateLightValues(shaders["default"], l);

            }
                float shaderPos[3] = {camera.position.x, camera.position.y, camera.position.z};
                SetShaderValue(shaders["default"], shaders["default"].locs[SHADER_LOC_VECTOR_VIEW], shaderPos, SHADER_UNIFORM_VEC3);




            float cameraW = 5.0f;
            float cameraH = 6.0f;
            int worldToScreenX = GetWorldToScreen(player.pos, camera).x;
            int worldToScreenY = GetWorldToScreen(player.pos, camera).y;
            float marginX = 5.0f;
            float marginY = 2.0f;
            float cameraRot = atan2(camera.position.x - player.pos.x, camera.position.y - player.pos.y) + 3.14 / 2;
            float dist = sqrt(pow(camera.position.x - player.pos.x, 2) + sqrt(pow(camera.position.y - player.pos.y - 0.0f,2))); 
            if (dist > 2.0f)
            {
                cvx = cos(cameraRot) * 5.0f * delta / 1000.0f;
                cvy = -sin(cameraRot) * 5.0f * delta / 1000.0f;
            }
            else {
                cvx = 0;
                cvy = 0;
            }
            camera.target.x += cvx; 
            camera.target.y += cvy;
            camera.position.x += cvx; 
            camera.position.y += cvy;
            if (player.pos.x < levels[currentLevel].levelSize && player.pos.x > 0)
                chunkX = ceil(player.pos.x / (float)levels[currentLevel].chunkSize) -1 ;
            if (levels[currentLevel].levelSize - player.pos.y < levels[currentLevel].levelSize &&player.pos.y > 0  )
                chunkY = ceil((levels[currentLevel].levelSize - player.pos.y) / (float)levels[currentLevel].chunkSize) - 1;
            //chunkX = 2;
            //chunkY = 1;
                //chunkY = ceil(player.pos.y / levels[currentLevel].chunkSize);
            player.tick(delta);
            if (player.getHp() <= 0) {
                startLevel(camera,player,levels[currentLevel],levels,currentLevel);
                levels[currentLevel].initLevel();
                levelAlpha = 255; 
            }
            if (player.blockersLeft <= 0) {
                for (Entity &e : levels[currentLevel].chunks[chunkY][chunkX].entities) {
                    e.mode = string("normal");
                }
            }
            if (player.nextLevel) {
                exit(0);
            }
                int chunkWa = chunkX - chunkW;
                int chunkWb = chunkX + chunkW;
                int chunkHa = chunkY - chunkH;
                int chunkHb = chunkY + chunkH;
                if (chunkWa < 0) {
                    chunkWa = 0;
                }
                if (chunkHa < 0) {
                    chunkHa = 0;
                }
                if (chunkWb > levels[currentLevel].levelSize) {
                    chunkWb = levels[currentLevel].levelSize;
                }
                if (chunkHb > levels[currentLevel].levelSize / levels[currentLevel].chunkSize) {
                    chunkHb = levels[currentLevel].levelSize / levels[currentLevel].chunkSize;
                }
                for (int i = chunkHa; i < chunkHb; i++){
                for (int j = chunkWa; j < chunkWb; j++){
                    for (auto &e : levels[currentLevel].chunks[i][j].entities) {
                        if (e.getHp() <= 0) {
                            continue;
                        }
                        for (auto &obj : levels[currentLevel].chunks[i][j].objects) {
                            if (obj.getHp() <= 0){
                                continue;
                            }
                            e.collision_object(delta, obj);
                        }
                        e.tick(delta);
                    }
                }
                }
            for (auto &obj : levels[currentLevel].chunks[chunkY][chunkX].objects) {
                if (obj.getHp() <= 0) {
                    continue;
                }
                player.collision_object(delta, obj);
            }
            for (auto &e : levels[currentLevel].chunks[chunkY][chunkX].entities) {
                if (e.getHp() <= 0) {
                    continue;
                }
                player.collision_entity(delta, e);
            }
           // player.collision_object(ground);
            //player.collision_object(cube);
            BeginTextureMode(target);
            {
                ClearBackground(SKYBLUE);

                if (IsKeyPressed(KEY_SPACE) ||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
                    if (player.mode == string("normal")) {
                        player.jump(1.0);

                    } else if (player.mode == string("jump")) {
                        player.cannon();
                    }
                    else if (player.mode == string("cannon")) {
                        player.launch();
                    }
                }
                if (IsKeyDown(KEY_D)||IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)){
                    if (player.mode == string("jump") ||player.mode == string("normal") ||player.mode == string("ladder"))
                        player.right();
                }
                if (IsKeyDown(KEY_A)||IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
                    if(player.mode == string("jump") ||player.mode == string("normal") ||player.mode == string("ladder")) 
                        player.left();
                }
                if (IsKeyDown(KEY_W)||IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
                    if(player.mode == string("ladder")) {
                        player.up();
                    }
                }
                if (IsKeyReleased(KEY_W)||IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
                    if(player.mode == string("ladder")) {
                        player.vpos.y = 0;
                    }
                    
                }
                if (IsKeyReleased(KEY_S)||IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
                    if(player.mode == string("ladder")) {
                        player.vpos.y= 0;
                    }
                    
                }
                if (IsKeyDown(KEY_S)||IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
                    if(player.mode == string("ladder")) {
                        player.down();
                    }
                }
                if (IsKeyPressed(KEY_A) ||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
                    if(player.mode == string("cannon")) 
                        player.tilt(3.14/4);
                }
                if (IsKeyPressed(KEY_D)||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
                    if(player.mode == string("cannon")) 
                        player.tilt(-3.14/4);
                }
                if ((!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))||(IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT && IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)))){
                    if (player.mode == string("normal") || (player.mode == string("jump") ||player.mode == string("ladder")))
                    player.slowX(delta);
                }
                if (IsKeyPressed(KEY_X)||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) {
                    player.back();
                }
                if (IsKeyPressed(KEY_Z)||IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) {
                    player.forward();
                }
                BeginMode3D(camera);
                for (int i = 0; i < levels[currentLevel].chunks.size(); i++) {
                    for (int j = 0; j < levels[currentLevel].chunks[i].size(); j++) {
                    for (auto &obj : levels[currentLevel].chunks[i][j].objects) {

                        if (obj.getHp() <= 0) {
                            continue;
                        }
                        obj.render(camera);
                    }
                    }
                }
                for (int i = 0; i < levels[currentLevel].chunks.size(); i++) {
                    for (int j = 0; j < levels[currentLevel].chunks[i].size(); j++) {
                    for (auto &e : levels[currentLevel].chunks[i][j].entities) {

                    if (e.getHp() <= 0) {
                        continue;
                    }
                    e.render(camera);
                }
                    }
                }
                for (auto &s : scenes) {
                    s.render(camera);
                }
            
            player.render(camera);
            EndMode3D();
            EndTextureMode();

        }
        BeginDrawing();
           // BeginShaderMode(postShaders["posterization"]);
                DrawTexturePro(target.texture, (Rectangle){0, 0, (float)WIDTH, (float)-HEIGHT},{0,0,(float)screenWidth, (float)screenHeight} ,Vector2{0, 0}, 0, WHITE);
            //EndShaderMode();
            if (levelAlpha > 0) {
                levelAlpha -= 2;
            }
            else {
                levelAlpha = 0;
            }
            // level texts
            if (levelAlpha > 0) {
            DrawTextEx(fonts[0], levels[currentLevel].title.c_str(), {screenWidth / 2 - 16,screenHeight / 2},18, 2, {255,255,255, levelAlpha});
            }
            // hud
            DrawFPS(0,0);
            DrawTextEx(fonts[0], (string("Leafs: ") + to_string(player.coins)).c_str(), {screenWidth - 90,screenHeight - 16},18, 2, {255,255,255, 255});
            DrawTextEx(fonts[0], (string("Tokens: ") + to_string(player.tokens)).c_str(), {screenWidth - 200,screenHeight - 16},18, 2, {255,255,255, 255});
            DrawTextEx(fonts[0], (string("Artifacts: ") + to_string(player.artifacts.size())).c_str(), {screenWidth - 325,screenHeight - 16},18, 2, {255,255,255, 255});
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
    for (auto const& s : shaders) {
        UnloadShader(s.second);
    }
    for (auto const& s : postShaders) {
        UnloadShader(s.second);
    }
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}

