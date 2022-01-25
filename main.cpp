#include <raylib.h>
#include <iostream>
using namespace std;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    InitWindow(screenWidth, screenHeight, "Ant Adventure");

    SetTargetFPS(60);

    SetExitKey(KEY_DELETE);

    Camera camera = {
            .position = {0.0f, 3.0f, 5.0f},
            .target   = {0.0f, 1.0f, 0.0f},
            .up       = {0.0f, 1.0f, 0.0f},
            .fovy     = 70.0f,
    };

    Texture2D ant = LoadTexture("res/ant_worker_side_1.png");
    Vector3 antPosition = {0.0f,1.0f,0.0f};


    while (!WindowShouldClose())
    {

        BeginDrawing();
        {

            ClearBackground(SKYBLUE);

            if (IsKeyDown(KEY_SPACE))
                cout << "Jump!";
            BeginMode3D(camera);
            {
                DrawCube((Vector3) {0.0f, -0.2f, 00.0f}, 200.0f,0.1f,200.0f,BLUE),
                
                DrawCube((Vector3) {0.0f, -10.0f, 0.0f},
                         100.0f, 20.0f, 1.0f, BROWN);


            }
            DrawBillboard(camera,ant,antPosition, 0.5f, WHITE);
            EndMode3D();

            EndTextureMode();


        }
        EndDrawing();
    }


    // end stuff
    CloseWindow();

    return 0;
}

