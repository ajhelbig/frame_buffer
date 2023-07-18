#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "stdbool.h"

typedef struct Pixel{

	Color color;
	Vector2 draw_pos; //position of the upper left corner of each pixel to draw
	Vector2 pos;      //position of the center of the pixel

} Pixel;

typedef struct Frame_Buffer{

	int width;        	//width of the drawing window
	int height;       	//height of the drawing window
	int virtual_width;	//width of the pixel window
	int virtual_height;	//height of the pixel window
	int pixel_size;
	Color background_color;
	Pixel **pixels;

} Frame_Buffer;

//primatives
void Frame_Buffer_Init(Frame_Buffer *fb, int width, int height, int pixel_size, Color color);
void Frame_Buffer_Destroy(Frame_Buffer *fb);
void Frame_Buffer_Draw(Frame_Buffer *fb);
void Frame_Buffer_Draw_Background(Frame_Buffer *fb);
void Draw_Pixel(Frame_Buffer *fb, int x, int y, Color color);
void Background_Color(Frame_Buffer *fb, Color color);

//shapes
void Draw_Line(Frame_Buffer *fb, int x1, int y1, int x2, int y2, Color color);
void Draw_Poly(Frame_Buffer *fb, int numPts, Vector2 pts[], Color color, bool fill);

//math
void Rotate_2D(Vector2 origin, int numPts, Vector2 pts[], float deg);

//animations
void Rotating_Line(Frame_Buffer *fb, int len, int points, int point, Color color);
void Rotating_Poly(Frame_Buffer *fb, int numPts, Vector2 pts[], int numPos, int currPos, Color color);


#endif