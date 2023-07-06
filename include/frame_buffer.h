#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct Pixel{

	Color color;
	Vector2 pos;

} Pixel;

typedef struct Frame_Buffer{

	int width;
	int height;
	int pixel_size;
	Pixel **fb;

} Frame_Buffer;

void Frame_Buffer_Init(Frame_Buffer *fb, int width, int height, int pixel_size, Color color);
void Frame_Buffer_Destroy(Frame_Buffer *fb);
void Frame_Buffer_Draw(Frame_Buffer *fb);

#endif