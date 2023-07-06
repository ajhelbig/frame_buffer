#include "frame_buffer.h"

void Frame_Buffer_Init(Frame_Buffer *frame_buff, int width, int height, int pixel_size, Color color){

	frame_buff->width = width;
	frame_buff->height = height;
	frame_buff->pixel_size = pixel_size;

	//allocating all the pixels
	frame_buff->fb = (Pixel **)malloc((height / pixel_size) * sizeof(Pixel *));

	for(int i = 0; i < (height / pixel_size); ++i){

		frame_buff->fb[i] = (Pixel *)malloc((width / pixel_size) * sizeof(Pixel));

	}

	//initializing each pixel
	for(int i = 0; i < (height / pixel_size); ++i){

		for(int j = 0; j < (width / pixel_size); ++j){
			frame_buff->fb[i][j].pos.x = j * pixel_size;
			frame_buff->fb[i][j].pos.y = i * pixel_size;
			frame_buff->fb[i][j].color = color;
		}

	}

}

void Frame_Buffer_Destroy(Frame_Buffer *frame_buff){

	for (int i = 0; i < (frame_buff->width / frame_buff->pixel_size); ++i)
	{

		free(frame_buff->fb[i]);

	}

	free(frame_buff->fb);

}

void Frame_Buffer_Draw(Frame_Buffer *frame_buff){//drawing each pixel

	for (int i = 0; i < (frame_buff->width / frame_buff->pixel_size); ++i)
	{

		for (int j = 0; j < (frame_buff->height / frame_buff->pixel_size); ++j)
		{
			
			DrawRectangleV(frame_buff->fb[i][j].pos,
				(Vector2){frame_buff->pixel_size - 1, frame_buff->pixel_size - 1},
				frame_buff->fb[i][j].color);

		}

	}

	DrawLine(0, 0, frame_buff->width, 0, (Color){255,255,255,255});
	DrawLine(1, 0, 1, frame_buff->height, (Color){255,255,255,255});

}
