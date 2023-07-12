#include "frame_buffer.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 510;
    const int screenHeight = 510;
    int pixelSize = 10;
    int virtualSW = (screenWidth / pixelSize);
    int virtualSH = (screenHeight / pixelSize);

    Frame_Buffer fb;
    Frame_Buffer_Init(&fb, screenWidth, screenHeight, pixelSize, (Color){0,0,0,255});

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    int current_point_on_circle = 0;

    //SetTargetFPS(10);               // Set our game to run at 60 frames-per-second
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

            //frame buffer emulator

            Frame_Buffer_Draw_Background(&fb);

            //Draw_Line(&fb, -1,-1, virtualSW - 1, virtualSH - 1, WHITE);      

            Rotating_Line(&fb, 20, 32, current_point_on_circle, (Color){255,255,255,255});

            current_point_on_circle += 1;

            Frame_Buffer_Draw(&fb);
            
            //frame buffer emulator

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();              // Close window and OpenGL context
    Frame_Buffer_Destroy(&fb);  // Deallocate frame buffer struct
    //--------------------------------------------------------------------------------------
    return 0;
}
