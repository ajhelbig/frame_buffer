#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

typedef struct Pixel{

	Color color;
	Vector2 draw_pos; //position of the upper left corner of each pixel to draw
	Vector2 pos;      //position of the center of the pixel

} Pixel;

typedef struct Frame_Buffer{

	int width;        //width of the drawing window
	int height;       //height of the drawing window
	int pixel_size;
	Color background_color;
	Pixel **pixels;

} Frame_Buffer;

//primatives
void Frame_Buffer_Init(Frame_Buffer *fb, int width, int height, int pixel_size, Color color);
void Frame_Buffer_Destroy(Frame_Buffer *fb);
void Frame_Buffer_Draw(Frame_Buffer *fb);
void Frame_Buffer_Draw_Background(Frame_Buffer *fb);

//shapes
void Draw_Line(Frame_Buffer *fb, int x1, int y1, int x2, int y2, Color color);

#endif