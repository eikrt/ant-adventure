#include <raylib.h>
#include <iostream>
#include "player.h"

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
    Texture2D ant_texture = LoadTexture("res/ant_worker_side_1.png");
    Entity player({0.0f,3.0f,0.3f},{0.4f,0.25f,0.1f}, ant_texture);
    Object ground({-10.0f,-0.1f,0.0f},{100.0f,0.1f,1.0f}, ant_texture);
    Object cube({1.0f,0.0f,0.0f},{1.0f,1.0f,1.0f}, ant_texture);
    
    float gravity = 0.01f;

    while (!WindowShouldClose())
    {
        player.tick(gravity);
        player.collision_object(ground);
        player.collision_object(cube);
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
                DrawCube((Vector3) {0.0f, -0.2f, 0.0f}, 200.0f,0.1f,200.0f,BLUE);
            cube.render(camera);
            ground.render(camera);
            player.render(camera);
            EndMode3D();
            EndTextureMode();


        }
        EndDrawing();
    }


    // end stuff
    CloseWindow();

    return 0;
}

