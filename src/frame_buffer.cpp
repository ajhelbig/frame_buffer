#include "frame_buffer.hpp"

void Frame_Buffer_Init(Frame_Buffer *frame_buff, float width, float height, float pixel_size, Color color){

	frame_buff->width = width;
	frame_buff->height = height;
	frame_buff->pixel_size = pixel_size;

	//allocating all the pixels
	frame_buff->fb = (Pixel **)malloc((height / pixel_size) * sizeof(Pixel *));

	for(int i = 0; i < height / pixel_size; ++i){

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

void Frame_Buffer_Draw(Frame_Buffer *frame_buff){ //seg faulting here

	for (int i = 0; i < frame_buff->width; ++i)
	{
		printf("fuck\n");
		for (int j = 0; j < frame_buff->height; ++j)
		{
			printf("shit\n");
			// Vector2 size = {frame_buff->pixel_size, frame_buff->pixel_size};

			// DrawRectangleV(frame_buff->fb[i][j].pos,
			// 				size,
			// 				frame_buff->fb[i][j].color);

		}

	}

}
