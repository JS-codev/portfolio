cmake_minimum_required(VERSION 3.10)

project(OPENGL!!!!)
set(CMAKE_CXX_STANDARD 17)

# Provide all the source files
add_executable(run 
    src/main.cpp
    src/glad.c
    src/Camera.cpp
    src/Mesh.cpp
    src/Shader.cpp
    src/Window.cpp
)

set(CMAKE_BUILD_TYPE Debug)

# Add compiler flags (-g -std=c++17)
target_compile_options(run PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-g -std=c++17>)

# Add include directories for GLFW, GLAD, etc.
target_include_directories(run PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add library directories (assuming your lib folder contains glfw3.dll, etc.)
target_link_directories(run PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Link libraries (glfw3dll and opengl32)
target_link_libraries(run PRIVATE glfw3dll opengl32)

# Automatically run the executable after it's built
add_custom_command(TARGET run POST_BUILD
    COMMAND $<TARGET_FILE:run>  # Run the executable after building
    COMMENT "Running Executable..."
)
# The glfw3.dll must be at the same path as Makefile (build folder)

# To run: cd build > cmake .. -G "MinGW Makefiles" 
# Then make (it will update any saved changes made)