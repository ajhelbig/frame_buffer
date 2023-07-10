#include "frame_buffer.h"

//primatives
void Frame_Buffer_Init(Frame_Buffer *fb, int width, int height, int pixel_size, Color color){

	fb->width = width;
	fb->height = height;
	fb->pixel_size = pixel_size;
	fb->background_color = color;

	//allocating all the pixels
	fb->pixels = (Pixel **)malloc((height / pixel_size) * sizeof(Pixel *));

	for(int i = 0; i < (height / pixel_size); ++i){

		fb->pixels[i] = (Pixel *)malloc((width / pixel_size) * sizeof(Pixel));

	}

	//initializing each pixel
	for(int i = 0; i < (height / pixel_size); ++i){

		for(int j = 0; j < (width / pixel_size); ++j){
			fb->pixels[i][j].draw_pos.x = j * pixel_size;
			fb->pixels[i][j].draw_pos.y = i * pixel_size;
			fb->pixels[i][j].pos.x = j * pixel_size + (pixel_size / 2);
			fb->pixels[i][j].pos.y = i * pixel_size + (pixel_size / 2);
			fb->pixels[i][j].color = color;
		}

	}

}

void Frame_Buffer_Destroy(Frame_Buffer *fb){

	for (int i = 0; i < (fb->height / fb->pixel_size); ++i)
	{

		free(fb->pixels[i]);

	}

	free(fb->pixels);

}

void Frame_Buffer_Draw(Frame_Buffer *fb){//drawing each pixel

	for (int i = 0; i < (fb->width / fb->pixel_size); ++i)
	{

		for (int j = 0; j < (fb->height / fb->pixel_size); ++j)
		{
			
			DrawRectangleV(fb->pixels[i][j].draw_pos,
				(Vector2){fb->pixel_size, fb->pixel_size},
				fb->pixels[i][j].color);

		}

	}

	DrawFPS(0,0);

}

void Frame_Buffer_Draw_Background(Frame_Buffer *fb){

	for(int i = 0; i < fb->width / fb->pixel_size; ++i){

		for(int j = 0; j < fb->height / fb->pixel_size; ++j){

			fb->pixels[i][j].color = fb->background_color;

		}

	}

}

//shapes
int max(int a, int b){

	if(a < b)
		return b;

	return a;

}

int min(int a, int b){

	if(a < b)
		return a;

	return b;

}

void Draw_Line(Frame_Buffer *fb, int x1, int y1, int x2, int y2, Color color){

	//Goal to use |Ax0 + By0 + C| / sqrt(A^2 + B^2)
	//Find if neighboring pixels are within a threshold distance to the line
	//to be drawn.

	//calculate y = mx + b then convert to Ax + By + C = 0

	double m = (fb->pixels[y1][x1].pos.y - fb->pixels[y2][x2].pos.y) / 
	(fb->pixels[y1][x1].pos.x - fb->pixels[y2][x2].pos.x);

	double b = fb->pixels[y1][x1].pos.y - (m * fb->pixels[y1][x1].pos.x);

	double A = 1;
	double B = -(1 / m);
	double C = b / m;

	double denominator = sqrt(A * A + B * B);

	//max distance from line is half the lenght of a pixels side length
	double max_distance = (fb->pixel_size / 2);

	for(int i = min(x1, x2); i <= max(x1, x2); ++i){

		for(int j = min(y1, y2); j <= max(y1, y2); ++j){

			//probably more cache efficient to access in [i][j] not sure though

			double Ax = A * fb->pixels[j][i].pos.x;//probably be cache inefficient
			double By = B * fb->pixels[j][i].pos.y;//probably cache inefficient

			double numerator = (abs(Ax + By + C ));

			double dist = numerator / denominator;

			if(dist <= max_distance){
				fb->pixels[j][i].color = color;//probably cache inefficient
			}

		}

	}

}

