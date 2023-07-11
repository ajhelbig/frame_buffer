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

	double A = (fb->pixels[x1][y1].pos.y - fb->pixels[x2][y2].pos.y);

	//negative because the y axis is flipped
	double B = -(fb->pixels[x1][y1].pos.x - fb->pixels[x2][y2].pos.x);

	double C = (fb->pixels[x1][y1].pos.x * fb->pixels[x2][y2].pos.y - 
				fb->pixels[x2][y2].pos.x * fb->pixels[x1][y1].pos.y);

	double denominator = sqrt(A * A + B * B);

	//max distance from line is half the lenght of a pixels side length
	double max_distance = (fb->pixel_size / 2);

	for(int i = min(x1, x2); i <= max(x1, x2); ++i){

		for(int j = min(y1, y2); j <= max(y1, y2); ++j){

			double Ax = A * fb->pixels[i][j].pos.x;
			double By = B * fb->pixels[i][j].pos.y;

			double numerator = (fabs(Ax + By + C ));

			double dist = numerator / denominator;

			if(dist <= max_distance){
				fb->pixels[i][j].color = color;
			}

		}

	}

}

//animations

void Rotating_Line(Frame_Buffer *fb, int len, int points, int point, Color color){

	point %= points;
	double points_size = 360.0 / points;//make better names for theses vars
	double degree = point * points_size;

	double centerx = (fb->width / fb->pixel_size) / 2.0;
	double centery = (fb->height / fb->pixel_size) / 2.0;

	int endx = ((double)len * sin(DEG2RAD * degree)) + centerx;
	int endy = ((double)len * cos(DEG2RAD * degree)) + centery;

	Draw_Line(fb, centerx, centery, endx, endy, color);

}

