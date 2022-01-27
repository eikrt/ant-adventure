#include <raylib.h>
#include <iostream>
#include "player.h"
#include "scenery.h"
#include <vector>
#include <map>
const float SCENEDIST =0.0f;
#define WIDTH 640
#define HEIGHT 420
using namespace std;

int main(int argc, char* argv[])
{
    enum Mode {game, editor};
    Mode currentMode = game;
    if (argc == 1){
        currentMode = game;
    }
    else if (argc > 0) {
        if (argv[1] == "editor") {
            currentMode = editor;
        }
    }
    const int screenWidth = 1024;
    const int screenHeight = 576;
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    InitWindow(screenWidth, screenHeight, "Ant Adventure");

    SetTargetFPS(60);

    SetExitKey(KEY_DELETE);
    

    // physics
    Camera camera = {
            .position = {0.0f, 5.0f, 80.0f},
            .target   = {0.0f, 6.0f, 0.0f},
            .up       = {0.0f, 1.0f, 0.0f},
            .fovy     = 10.0f,
    };
    //Image cube_img = LoadImage("res/stone_brick.png"); 
    //Mesh mesh = GenMeshCubicmap(cube_img, (Vector3){ 1.0f, 1.0f, 1.0f });
   // Model cube = LoadModelFromMesh(mesh);
    Model cube = LoadModel("models/cube.obj");
    Model ground = LoadModel("models/scenery.obj");

    map<string, Texture2D> textures;
    textures["player"] = LoadTexture("res/ant_worker_side_1.png");
    textures["spruce"] = LoadTexture("res/spruce.png");
    textures["stoneBrick"] = LoadTexture("res/stone_brick.png");
    textures["grass"] = LoadTexture("res/grass.png");
    cube.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textures["stoneBrick"];
    ground.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textures["grass"];
    Entity player({0.1f,1.0f,SCENEDIST},{0.4f,0.5f,0.1f}, 1.0f, textures["player"]);
    vector<Object> objects;
    objects.push_back(Object({0.0f,-1.0f,SCENEDIST},{1.0f,1.0f,1.0f}, cube));
    objects.push_back(Object({-2.0f,-1.0f,SCENEDIST},{1.0f,1.0f,1.0f}, cube));
    objects.push_back(Object({-1.0f,-1.0f,SCENEDIST},{1.0f,1.0f,1.0f}, cube));
    objects.push_back(Object({1.0f,-1.0f,SCENEDIST},{1.0f,1.0f,1.0f}, cube));
    objects.push_back(Object({1.0f,0.0f,SCENEDIST},{1.0f,1.0f,1.0f}, cube));
    objects.push_back(Object({2.0f,1.0f,SCENEDIST},{1.0f,1.0f,1.0f}, cube));
    vector<Scenery> scenes;
    
    scenes.push_back(Scenery({0.0f,-1.0f,0.0f},{200.0f,0.0f,200.0f}, ground, textures));
    float gravity = 0.01f;
    RenderTexture2D target = LoadRenderTexture(WIDTH, HEIGHT);
    while (!WindowShouldClose())
    {
        player.tick(gravity);
        for (auto &obj : objects) {
            player.collision_object(obj);
        }
       // player.collision_object(ground);
        //player.collision_object(cube);
        BeginTextureMode(target);
        {
            ClearBackground(SKYBLUE);

            if (IsKeyDown(KEY_SPACE))
                player.jump();

            if (IsKeyDown(KEY_D))
                player.right();
            if (IsKeyDown(KEY_A))
                player.left();
            if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
                player.slowX();
            BeginMode3D(camera);
                for (auto &obj : objects) {
                    obj.render(camera);
                }
                for (auto &s : scenes) {
                    s.render(camera);
                }
            player.render(camera);
            EndMode3D();
            EndTextureMode();

        }
        BeginDrawing();
            //DrawTextureRec(target.texture, (Rectangle){0, 0, (float)WIDTH, (float)-HEIGHT}, Vector2{0, 0}, WHITE);
            DrawTexturePro(target.texture, (Rectangle){0, 0, (float)WIDTH, (float)-HEIGHT},{0,0,(float)screenWidth, (float)screenHeight} ,Vector2{0, 0}, 0, WHITE);
        EndDrawing();
    }


    // end stuff
    for (auto const& t : textures) {
        UnloadTexture(t.second);
    }
    UnloadModel(cube);
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}

