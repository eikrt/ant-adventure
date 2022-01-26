#include <raylib.h>
#include <iostream>
#include "player.h"
#include <vector>
using namespace std;
int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    InitWindow(screenWidth, screenHeight, "Ant Adventure");

    SetTargetFPS(60);

    SetExitKey(KEY_DELETE);
    

    // physics
    Camera camera = {
            .position = {0.0f, 1.0f, 5.0f},
            .target   = {0.0f, 1.0f, 0.0f},
            .up       = {0.0f, 1.0f, 0.0f},
            .fovy     = 70.0f,
    };
    //Image cube_img = LoadImage("res/stone_brick.png"); 
    //Mesh mesh = GenMeshCubicmap(cube_img, (Vector3){ 1.0f, 1.0f, 1.0f });
   // Model cube = LoadModelFromMesh(mesh);
    Model cube = LoadModel("models/cube.obj");
    Texture2D ant_texture = LoadTexture("res/ant_worker_side_1.png");
    Texture2D spruce_texture = LoadTexture("res/spruce.png");
    Texture2D cube_texture = LoadTexture("res/stone_brick.png");
    cube.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = cube_texture;
    Entity player({0.1f,1.0f,0.3f},{0.4f,0.25f,0.1f}, ant_texture);
    vector<Object> objects;
    objects.push_back(Object({0.0f,-1.0f,0.0f},{1.0f,1.0f,1.0f}, cube));
    objects.push_back(Object({-2.0f,-1.0f,0.0f},{1.0f,1.0f,1.0f}, cube));
    objects.push_back(Object({-1.0f,-1.0f,0.0f},{1.0f,1.0f,1.0f}, cube));
    objects.push_back(Object({1.0f,-1.0f,0.0f},{1.0f,1.0f,1.0f}, cube));
    objects.push_back(Object({1.0f,0.0f,0.0f},{1.0f,1.0f,1.0f}, cube));
    objects.push_back(Object({2.0f,1.0f,0.0f},{1.0f,1.0f,1.0f}, cube));
    vector<Entity> scenery;
    scenery.push_back(Entity({0.0f,0.0f,-5.3f},{0.4f,0.25f,0.1f}, spruce_texture));
    float gravity = 0.01f;

    while (!WindowShouldClose())
    {
        player.tick(gravity);
        for (auto &obj : objects) {
            player.collision_object(obj);
        }
       // player.collision_object(ground);
        //player.collision_object(cube);

        BeginDrawing();
        {
            ClearBackground(SKYBLUE);

            if (IsKeyDown(KEY_SPACE))
                player.jump();

            if (IsKeyDown(KEY_D))
                player.right();
            if (IsKeyDown(KEY_A))
                player.left();
            if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
                player.stopX();
            BeginMode3D(camera);
                DrawCube((Vector3) {0.0f, -1.0f, 0.0f}, 200.0f,0.1f,200.0f,(Color){51,153,51, 255});
                for (auto &obj : objects) {
                    obj.render(camera);
                }
                for (auto &s : scenery) {
                    s.render(camera);
                }
            player.render(camera);
            EndMode3D();
            EndTextureMode();


        }
        EndDrawing();
    }


    // end stuff
    UnloadTexture(ant_texture);
    UnloadModel(cube);
    CloseWindow();

    return 0;
}

