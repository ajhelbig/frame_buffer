
add_executable(${PROJECT_NAME} 
	main.cpp
	frame_buffer.cpp
)

target_link_libraries(${PROJECT_NAME} 
	raylib 
)
