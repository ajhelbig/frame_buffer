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

	//need to do this using relative coordinates in case coordinates are off the screen
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

bool inShape(int numPts, Vector2 pts[], Vector2 pt){

	//implement point in polygon algorithm

	//find equation of the line from pt horizontally to the right edge of the screen

	//find equation of the lines forming the shape

	//determine if pt line intersects and even or odd number of shape lines

	//if even pt is outside the shape if odd the pt is inside the shape

	return false;

} 

void Draw_Poly(Frame_Buffer *fb, int numPts, Vector2 pts[], Color color, bool fill){

	//the order of the points matters lines drawn from p0 -> p1 ... pn -> p0
	for(int i = 0; i < numPts - 1; ++i){
		Draw_Line(fb, pts[i].x, pts[i].y, pts[i + 1].x, pts[i + 1].y, color);
	}

	Draw_Line(fb, pts[numPts - 1].x, pts[numPts - 1].y, pts[0].x, pts[0].y, color);

	if(fill){

		for (int i = 0; i < fb->virtual_width; ++i)
		{
			
			for (int j = 0; j < fb->virtual_height; ++j)
			{
				
				if(inShape(numPts, pts, fb->pixels[i][j].pos)){

					Draw_Pixel(fb, fb->pixels[i][j].pos.y, fb->pixels[i][j].pos.y, color);

				}

			}

		}

	}

}

//math

void Rotate(Vector2 *pt, float deg){

	float x = pt->x;
	float y = pt->y;

	pt->x = (x * cos(DEG2RAD * deg)) - (y * sin(DEG2RAD * deg));
	pt->y = (x * sin(DEG2RAD * deg)) + (y * cos(DEG2RAD * deg));

}

void Translate(Vector2 *pt, int x, int y){

	pt->x = pt->x + x;
	pt->y = pt->y + y;

}

void Rotate_2D(Vector2 origin, int numPts, Vector2 pts[], float deg){

	//translate to origin
	for(int i = 0; i < numPts; ++i){

		Translate(&pts[i], -origin.x, -origin.y);

	}

	//rotate about origin
	for(int i = 0; i < numPts; ++i){

		Rotate(&pts[i], deg);

	}

	//translate back to original position
	for(int i = 0; i < numPts; ++i){

		Translate(&pts[i], origin.x, origin.y);

	}

}

Vector2* Round(int numPts, Vector2 pts[]){

	Vector2 *roundedPts = (Vector2*)malloc(numPts * sizeof(Vector2));

	for (int i = 0; i < numPts; ++i)
	{

		roundedPts[i].x = round(pts[i].x);
		roundedPts[i].y = round(pts[i].y);

	}

	return roundedPts;

}

//animations

void Rotating_Line(Frame_Buffer *fb, int len, int points, int point, Color color){

	point %= points;
	double points_size = 360.0 / points;//make better names for theses vars
	double degree = point * points_size;

	double centerx = (fb->virtual_width) / 2.0;
	double centery = (fb->virtual_height) / 2.0;

	Vector2 origin;
	origin.x = (fb-> virtual_width) / 2.0;
	origin.y = (fb->virtual_height) / 2.0;

	int endx = ((double)len * cos(DEG2RAD * degree)) + centerx;
	int endy = -((double)len * sin(DEG2RAD * degree)) + centery;

	Draw_Line(fb, centerx, centery, endx, endy, color);

}

void Rotating_Poly(Frame_Buffer *fb, int numPts, Vector2 pts[], int numPos, int currPos, Color color){

	currPos %= numPts;
	double arc_angle = 360.0 / numPos;//make better names for theses vars
	double degree = currPos * arc_angle;

	Vector2 origin;
	origin.x = (fb->virtual_width) / 2.0;
	origin.y = (fb->virtual_height) / 2.0;

	Rotate_2D(origin, numPts, pts, degree);

	Vector2 *roundedPts = Round(numPts, pts);

	Draw_Poly(fb, numPts, pts, color, true);

	free(roundedPts);

}
