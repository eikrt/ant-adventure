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
    Entity player({0.0f,1.0f,1.0f},{0.1f,0.3f,0.1f}, ant_texture);
    Object ground({0.0f,1.0f,0.0f},{100.0f,20.0f,1.0f}, ant_texture);
    float gravity = 0.01f;

    while (!WindowShouldClose())
    {
        player.tick(gravity);
        player.collision_object(ground);
        BeginDrawing();
        {

            ClearBackground(SKYBLUE);

            if (IsKeyDown(KEY_SPACE))
                player.jump();
            BeginMode3D(camera);
            {
                DrawCube((Vector3) {0.0f, -0.2f, 00.0f}, 200.0f,0.1f,200.0f,BLUE),
                
                DrawCube((Vector3) {0.0f, -10.0f, 0.0f},
                         100.0f, 20.0f, 1.0f, BROWN);


            }
            player.render(camera);
           // DrawBillboard(camera,ant,antPosition, 0.5f, WHITE);
            EndMode3D();

            EndTextureMode();


        }
        EndDrawing();
    }


    // end stuff
    CloseWindow();

    return 0;
}

