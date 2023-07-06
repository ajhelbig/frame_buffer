
add_executable(${PROJECT_NAME} 
	main.c
	frame_buffer.c
)

target_link_libraries(${PROJECT_NAME} 
	raylib 
)
