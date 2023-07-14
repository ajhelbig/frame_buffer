#include "frame_buffer.h"

//primatives

void Frame_Buffer_Init(Frame_Buffer *fb, int width, int height, int pixel_size, Color color){

	fb->width = width;
	fb->height = height;
	fb->virtual_width = width / pixel_size;
	fb->virtual_height = height / pixel_size;
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

	for (int i = 0; i < fb->virtual_height; ++i)
	{

		free(fb->pixels[i]);

	}

	free(fb->pixels);

}

void Frame_Buffer_Draw(Frame_Buffer *fb){//drawing each pixel

	for (int i = 0; i < fb->virtual_width; ++i)
	{

		for (int j = 0; j < fb->virtual_height; ++j)
		{
			
			DrawRectangleV(fb->pixels[i][j].draw_pos,
				(Vector2){fb->pixel_size, fb->pixel_size},
				fb->pixels[i][j].color);

		}

	}

	DrawFPS(0,0);

}

void Frame_Buffer_Draw_Background(Frame_Buffer *fb){

	for(int i = 0; i < fb->virtual_width; ++i){

		for(int j = 0; j < fb->virtual_height; ++j){

			Draw_Pixel(fb, i, j, fb->background_color);

		}

	}

}

void Draw_Pixel(Frame_Buffer *fb, int x, int y, Color color){

	if(y >= 0 && y < fb->virtual_height && x >= 0 && x < fb->virtual_width )
		fb->pixels[y][x].color = color;

}

void Background_Color(Frame_Buffer *fb, Color color){

	fb->background_color = color;

}

//shapes

int max(int a, int b){

	if(a < b)
		return b;

	return a;

}

int min(int a, int b){

	if(a > b)
		return b;

	return a;

}

void Draw_Line(Frame_Buffer *fb, int x1, int y1, int x2, int y2, Color color){

	// Goal to use |Ax0 + By0 + C| / sqrt(A^2 + B^2) to
	// find if neighboring pixels are within a threshold 
	// distance to the line to be drawn.

	double A = ( ((double)(y1 * fb->pixel_size) + fb->pixel_size / 2.0) - ((double)(y2 * fb->pixel_size) + fb->pixel_size / 2.0) );

	double B = -( ((double)(x1 * fb->pixel_size) + fb->pixel_size / 2.0) - ((double)(x2 * fb->pixel_size) + fb->pixel_size / 2.0) );

	double C = ( ((double)(x1 * fb->pixel_size) + fb->pixel_size / 2.0) * ((double)(y2 * fb->pixel_size) + fb->pixel_size / 2.0) - 
				((double)(x2 * fb->pixel_size) + fb->pixel_size / 2.0) * ((double)(y1 * fb->pixel_size) + fb->pixel_size / 2.0) );

	double denominator = sqrt(A * A + B * B);

	//max distance from line is half the lenght of a pixels side length
	double max_distance = (fb->pixel_size / 2.0);

	for(int y = min(y1, y2); y <= max(y1, y2); ++y){

		if(y < 0 || y >= fb->virtual_height)
			continue; //may be able to optimize this

		for(int x = min(x1, x2); x <= max(x1, x2); ++x){

			if(x < 0 || x >= fb->virtual_width)
				continue; //may be able to optimize this

			double Ax = A * ((double)(x * fb->pixel_size) + fb->pixel_size / 2.0);
			double By = B * ((double)(y * fb->pixel_size) + fb->pixel_size / 2.0);

			double numerator = (fabs(Ax + By + C));

			double dist = numerator / denominator;

			if(dist <= max_distance){

				Draw_Pixel(fb, x, y, color);

			}

		}

	}

}

void Draw_Poly(Frame_Buffer *fb, int numPts, Vector2 pts[], Color color){

	for(int i = 0; i < numPts - 1; ++i){
		Draw_Line(fb, pts[i].x, pts[i].y, pts[i + 1].x, pts[i + 1].y, color);
	}

	Draw_Line(fb, pts[numPts - 1].x, pts[numPts - 1].y, pts[0].x, pts[0].y, color);

}

//animations

void Rotating_Line(Frame_Buffer *fb, int len, int points, int point, Color color){

	point %= points;
	double points_size = 360.0 / points;//make better names for theses vars
	double degree = point * points_size;

	double centerx = (fb->virtual_width) / 2.0;
	double centery = (fb->virtual_height) / 2.0;

	int endx = ((double)len * cos(DEG2RAD * degree)) + centerx;
	int endy = -((double)len * sin(DEG2RAD * degree)) + centery;

	Draw_Line(fb, centerx, centery, endx, endy, color);

}
