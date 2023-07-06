#include "frame_buffer.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 500;
    const int screenHeight = 500;

    Frame_Buffer fb;
    Frame_Buffer_Init(&fb, 500.0, 500.0, 50.0, (Color){0,0,0,255});

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    //SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground((Color){255,255,255,255});

            Frame_Buffer_Draw(&fb);

            DrawFPS(0,0);
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    Frame_Buffer_Destroy(&fb);
    //--------------------------------------------------------------------------------------
    return 0;
}
