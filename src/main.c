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

    int current_point = 0;

    Vector2 pts[] = {(Vector2){10, 10}, (Vector2){virtualSW - 11, 10}, (Vector2){virtualSW / 2, virtualSH / 2}, (Vector2){virtualSW - 11, virtualSH - 11}, (Vector2){10, virtualSH - 11}};

    // Vector2 pts[] = {(Vector2){10, virtualSW / 2}, (Vector2){10, virtualSH - 10}, (Vector2){virtualSW - 10, virtualSH - 10}};

    //SetTargetFPS(5);               // Set our game to run at 60 frames-per-second
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

            current_point += 1;

            Rotating_Poly(&fb, 5, pts, 360, current_point, (Color){255,255,255,255});

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
