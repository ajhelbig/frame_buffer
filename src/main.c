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
    int pixelSize = 10;
    int virtualSW = (screenWidth / pixelSize) - 1;
    int virtualSH = (screenHeight / pixelSize) - 1;

    Frame_Buffer fb;
    Frame_Buffer_Init(&fb, screenWidth, screenHeight, pixelSize, (Color){0,0,0,255});

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    //SetTargetFPS(4);               // Set our game to run at 60 frames-per-second
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

            Draw_Line(&fb, virtualSW / 2, virtualSH / 2, virtualSW / 4, virtualSH / 4, (Color){255,255,255,255});

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
