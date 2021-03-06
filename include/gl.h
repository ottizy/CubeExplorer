#pragma once
#include <iostream>


#ifndef _WIN32
#include <GL/gl.h>
#define GLX_GLXEXT_PROTOTYPES
#include <GL/glext.h>
#include <GL/glx.h>
#include "../Windows/glfw/include/glfw3.h"
#endif

#ifdef _WIN32
#include <glad/include/glad.h>
#include <gl/gl.h>
#include <glfw/include/glfw3.h>

#endif

constexpr float PI = 3.14159265359f;

void clear_OpenGL_errors();
bool check_OpenGL_errors(const char* function, const char* file, int line);
size_t get_draw_calls();

void increment_draw_calls();
void check_framebuffer_status();

#define NOP ((void)0)

#ifdef _WIN32
#define TRAP				__debugbreak()
#else
#define TRAP				__asm__("int3"); __asm__("int3"); __asm__("int3");
#endif

#define GL_ASSERT(stmt)	if (!(stmt)) TRAP;

#ifdef _DEBUG

#define GLC(stmt)			clear_OpenGL_errors(); \
							stmt; \
							GL_ASSERT(check_OpenGL_errors(#stmt, __FILE__, __LINE__));

#define CHECK_FRAME_BUFFER() check_framebuffer_status()

#define LOG(msg) std::cout << msg << std::endl;

#else

#define GLC(stmt) stmt;
#define CHECK_FRAME_BUFFER() NOP;
#define LOG(msg) NOP;

#endif

#define DRAW_CALL(stmt) increment_draw_calls(); \
						stmt;


#define UNUSED(x) (void)x;
#define MAYBE_UNUSED(x) (void)x;
